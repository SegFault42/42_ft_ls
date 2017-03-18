#include "../include/ft_ls.h"

#define REG 0
#define DIRE 1

extern t_argp	g_argp[];

void	sort_lst(t_ctrl *ctrl, struct dirent *content_dir)
{
	t_file	*tmp;
	int		node;
	int		i;

	tmp = ctrl->first;
	node = 1;
	i = 0;
	if (tmp == NULL)
	{
		add_head(ctrl, content_dir->d_name);
		return ;
	}
	while (tmp)
	{
		while (content_dir->d_name[i] && content_dir->d_name[i] == tmp->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->name[i])
		{
			add_before(ctrl, node, content_dir->d_name);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, content_dir->d_name);
			return ;
		}
		i = 0;
		while (content_dir->d_name[i] && content_dir->d_name[i] == tmp->next->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, content_dir->d_name);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

uint8_t	check_file_type(char *argument)
{
	uint8_t	ret;

	if ((ret = is_reg_or_dir(argument)) == REG)
		return (REG);
	return (DIRE);
}

/*char	*get_path(char *cur_dir)*/
/*{*/
	/*char	*path;*/
	/*int		i;*/

	/*i = ft_strlen(cur_dir) -1 ;*/
	/*path = NULL;*/
	/*while (cur_dir[i] != '/' && i > 0)*/
	/*{*/
		/*--i;*/
	/*}*/
	/*if (i == 0)*/
		/*path = ft_strdup(".");*/
	/*else*/
		/*path = ft_strndup(cur_dir, i);*/
	/*return (path);*/
/*}*/

static int8_t	open_directory(DIR **dir, char *directory)
{
	if ((*dir = opendir(directory)) == NULL)
	{
		ft_dprintf(2, "ls: %s: %s\n", directory, strerror(errno));
		return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

static void	close_directory(DIR **dir)
{
	if (closedir(*dir) == -1)
	{
		ft_dprintf(STDERR_FILENO, RED"%s\n"END, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void	print_lst(t_ctrl *ctrl)
{
	if (ctrl->first != NULL)
	{
		if (g_argp[MINUS_R].active == 0)
			print_list(ctrl);
		else
			print_list_reverse(ctrl);
	}
}

static bool	check_minus_a(struct dirent *content_dir)
{
	if (g_argp[MINUS_A].active == 0)
	{
		if (content_dir->d_name[0] == HIDE_FILE)
			return (true);
	}
	return (false);
}

static void	recursive(char *dir_name)
{
	struct dirent	*entry;
	char			*d_name;
	DIR				*d;
	int				path_length;
	char			path[PATH_MAX];

	open_directory(&d, dir_name);
	while (1)
	{
		entry = readdir(d);
		if (entry == NULL) // si il n'y a plus de dossier a ouvrir
			break;
		d_name = entry->d_name;
		printf("%s/%s\n", dir_name, d_name);
		if (entry->d_type & DT_DIR)
		{
			if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0)
			{
				path_length = snprintf (path, PATH_MAX, "%s/%s", dir_name, d_name);
				printf ("%s\n", path);
				if (path_length >= PATH_MAX)
				{
					fprintf (stderr, "Path length has got too long.\n");
					exit (EXIT_FAILURE);
				}
				recursive(path);
			}
		}
	}
	close_directory(&d);
}
void	upper_r(char *directory)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			lst_r_upper;
	t_file			*tmp;
	char			*path = NULL;

	path = strdup(directory);
	ft_memset(&lst_r_upper, 0, sizeof(t_ctrl));
	if (open_directory(&dir, directory) == EXIT_ERROR)
		return ;
	while ((content_dir = readdir(dir)) != NULL)
	{
		if (check_minus_a(content_dir) == true)
			continue ;
		sort_lst(&lst_r_upper, content_dir);
	}
	print_lst(&lst_r_upper);
	close_directory(&dir);
	tmp = lst_r_upper.first;
	while (tmp->next)
	{
		if (check_file_type(tmp->name) == DIRE)
		{
			path = ft_strjoin(path, "/");
			path = ft_strjoin(path, tmp->name);
			ft_dprintf(1, RED"%s\n"END, path);
			upper_r(path);
		}
		tmp = tmp->next;
	}
}

void	print_directory(char *directory)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			ctrl;
	/*t_file			*tmp;*/
	/*char			*path;*/

	content_dir = NULL;
	dir = NULL;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	if (open_directory(&dir, directory) == EXIT_ERROR)
		return ;
	if (g_argp[UPPER_R].active == 1)
		recursive(directory);
	else
		while ((content_dir = readdir(dir)) != NULL)
		{
			if (check_minus_a(content_dir) == true)
				continue ;
			sort_lst(&ctrl, content_dir);
		}
	print_lst(&ctrl);
	free_list(&ctrl);
	close_directory(&dir);
}

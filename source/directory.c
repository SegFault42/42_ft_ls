#include "../include/ft_ls.h"

#define REG 0
#define DIRE 1

extern t_argp	g_argp[];

void	sort_lst_dir(t_ctrl *ctrl, char *path)
{
	t_file	*tmp;
	int	i;
	int	node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
	{
		add_head(ctrl, path);
		return ;
	}
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] < tmp->name[i])
		{
			add_before(ctrl, node, path);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, path);
			return ;
		}
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, path);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

void	sort_lst_dir_rev(t_ctrl *ctrl, char *path)
{
	t_file	*tmp;
	int	i;
	int	node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
	{
		add_head(ctrl, path);
		return ;
	}
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] > tmp->name[i])
		{
			add_before(ctrl, node, path);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, path);
			return ;
		}
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] > tmp->next->name[i])
		{
			add_after(ctrl, node, path);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

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

void		print_all_directory(char *path)
{
	struct dirent	*entry;
	DIR				*dir;
	t_ctrl			lst;

	ft_memset(&lst, 0, sizeof(t_ctrl));
	if (open_directory(&dir, path) == EXIT_ERROR)
		return ;
	while ((entry = readdir(dir)) != NULL)
	{
		if (check_minus_a(entry) == true)
			continue ;
		sort_lst(&lst, entry);
	}
	close_directory(&dir);
	print_lst(&lst);
	/*free_list(&lst);*/
}

static void	recursive(char *directory)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*d_name;
	int				 path_length;
	char			 path[PATH_MAX];
	t_ctrl			lst;
	t_file			*tmp;

	ft_memset(&lst, 0, sizeof(t_ctrl));
	if (open_directory(&dir, directory) == EXIT_ERROR)
		return ;
	print_all_directory(directory);
	while ((entry = readdir(dir)))
	{
		d_name = entry->d_name;
		if (check_minus_a(entry) == true)
			continue ;
		if (entry->d_type & DT_DIR)
		{
			if (ft_strcmp(d_name, "..") != 0 && ft_strcmp(d_name, ".") != 0)
			{
				path_length = snprintf(path, PATH_MAX, "%s/%s", directory, d_name);
				if (g_argp[MINUS_R].active == 1)
					sort_lst_dir_rev(&lst, path);
				else
					sort_lst_dir(&lst, path);
				if (path_length >= PATH_MAX)
					exit (EXIT_FAILURE);
			}
		}
	}
	tmp = lst.first;
	while (tmp)
	{
		RC;
		ft_dprintf(1, "%s:\n", tmp->name);
		recursive(tmp->name);
		tmp= tmp->next;
	}
	closedir(dir);
	free_list(&lst);
}

void	print_directory(char *directory)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			ctrl;

	content_dir = NULL;
	dir = NULL;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	if (open_directory(&dir, directory) == EXIT_ERROR)
		return ;
	if (g_argp[UPPER_R].active == 1)
		recursive(directory);
	else
	{
		while ((content_dir = readdir(dir)) != NULL)
		{
			if (check_minus_a(content_dir) == true)
				continue ;
			sort_lst(&ctrl, content_dir);
		}
	}
	print_lst(&ctrl);
	/*free_list(&ctrl);*/
	close_directory(&dir);
}

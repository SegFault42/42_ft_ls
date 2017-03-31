#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern char		g_info[255];

int8_t	open_directory(DIR **dir, char *directory)
{
	if ((*dir = opendir(directory)) == NULL)
	{
		ft_dprintf(2, "ls: %s: %s\n", directory, strerror(errno));
		return (EXIT_ERROR);
	}
	return (EXIT_SUCCESS);
}

void	close_directory(DIR **dir)
{
	if (closedir(*dir) == -1)
	{
		ft_dprintf(STDERR_FILENO, RED"%s\n"END, strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	particular_minus_t(t_ctrl *ctrl)
{
	int		i;
	char	**tab;
	t_file	*tmp;
	t_ctrl	ctr;
	struct stat		file_stat;

	ft_memset(&ctr, 0, sizeof(t_ctrl));
	i = count_nb_node(ctrl);
	tab = (char **)ft_memalloc(sizeof(char *) * i + 1);
	tmp = ctrl->first;
	ft_set_2d_tab(tab, i + 1);
	i = 0;
	if (tmp != NULL)
	{
		while (tmp)
		{
			tab[i] = tmp->name;
			tmp = tmp->next;
			++i;
		}
		sort_param(tab);
	}
	i = 0;
	while (tab[i])
	{
		if (file_stat.st_mode & S_IFLNK)
			lstat(tab[i], &file_stat);
		else
			stat(tab[i], &file_stat);
		sort_by_time(&ctr, file_stat.st_atimespec.tv_sec, tab[i]);
		++i;
	}
	print_lst(&ctr);
	/*ft_2d_tab_free(tab);*/
	/*free_list(&ctr);*/
}

void	rewrite_info_padded(t_ctrl *ctrl, size_t *padding)
{
	t_file		*tmp;
	char		**split;
	int			i;

	tmp = ctrl->first;
	while (tmp)
	{
		i = 0;
		split = ft_strsplit(tmp->info, ' ');
		ft_memset(tmp->info, 0, sizeof(tmp->info));
		while (split[i])
		{
			if (i == 2 || i == 3)
			{
				ft_strcat(tmp->info, split[i]);
				ft_strxcat(tmp->info, " ", (padding[i] - ft_strlen(split[i])));
				if (i == 2 || i == 3)
					ft_strcat(tmp->info, " "); // double espace apres string
			}
			else
			{
				ft_strxcat(tmp->info, " ", (padding[i] - ft_strlen(split[i])));
				ft_strcat(tmp->info, split[i]);
			}
			ft_strcat(tmp->info, " "); // espace entre chaque tab
			++i;
		}
		if (tmp->info[10] == '|')
			tmp->info[10] = ' ';
		tmp = tmp->next;
		ft_2d_tab_free(split);
	}
}

void	padding_l(t_ctrl *ctrl)
{
	t_file		*tmp;
	char		**split;
	size_t			padding[8];
	int				i;

	i = -1;
	ft_memset(&padding, 0, sizeof(padding));
	while (++i < 8)
	{
		tmp = ctrl->first;
		while (tmp)
		{
			split = ft_strsplit(tmp->info, ' ');
			if (ft_strlen(split[i]) > padding[i])
			padding[i] = ft_strlen(split[i]);
			ft_2d_tab_free(split);
			tmp = tmp->next;
		}
	}
	rewrite_info_padded(ctrl, padding);
	(void)ctrl;
}

void	print_directory(char *directory, t_env *env)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			ctrl;
	struct stat		file_stat;
	char			*file = NULL;

	char	buf[PATH_MAX];
	int		size_buf;

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
			file = ft_strjoin(directory, "/");
			file = ft_strjoin(file, content_dir->d_name);
			lstat(file, &file_stat);
			if (g_argp[MINUS_L].active == 1)
				minus_l(file, env);
			if (file_stat.st_mode & S_IFLNK)
			{
				if ((size_buf = readlink(file, buf, sizeof(buf) - 1)) != -1)
				{
					buf[size_buf] = '\0';
					ft_dprintf(1, "%s\n", buf);
				}
			}
			sort_lst(&ctrl, content_dir);
			if (file)
				ft_strdel(&file);
			/*ft_strdel(&env->file.info);*/
		}
		if (g_argp[MINUS_L].active == 1)
			padding_l(&ctrl);
		if (g_argp[MINUS_T].active == 1)
			particular_minus_t(&ctrl);
		else
			print_lst(&ctrl);
		/*free_list(&ctrl);*/
	}
	close_directory(&dir);
}

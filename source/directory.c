#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern char g_info[255];

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

void	rewrite_info_padded(t_ctrl *ctrl, int pad)
{
	t_file		*tmp;
	/*char		*tmp_str;*/
	char		**tab;
	int			i;
	int			nb_space;

	i = 0;
	tmp = ctrl->first;
	while (tmp->next)
	{
		/*tmp_str = ft_strdup(tmp->info);*/
		tab = ft_strsplit(tmp->info, ' ');
		ft_memset(tmp->info, 0, 256);
		while (tab[i])
		{
			if (i == 1)
			{
				nb_space = pad - ft_strlen(tab[i]);
				while (nb_space > 0)
				{
					ft_strcat(tmp->info, " ");
					--nb_space;
				}
			}
			ft_strcat(tmp->info, tab[i]);
			ft_strcat(tmp->info, " ");
			++i;
		}
		ft_dprintf(1, RED"%s\n"END, tmp->info);
		break ;
	}
	(void)pad;
	(void)nb_space;
}

void	padding_l(t_ctrl *ctrl)
{
	t_file		*tmp;
	int			i;
	int			tmp_c;
	static int	nb_char = 0;

	i = 12;
	tmp = ctrl->first;
	tmp_c = 0;
	while (tmp->next)
	{
		ft_dprintf(1, YELLOW"%s\n"END, &tmp->info[i]);
		while (tmp->info[i] != ' ')
		{
			++i;
			++tmp_c;
		}
		if (tmp_c > nb_char)
			nb_char = tmp_c;
		tmp = tmp->next;
		i = 12;
		tmp_c = 0;
	}
	ft_dprintf(1, ORANGE"%d\n"END, nb_char);
	rewrite_info_padded(ctrl, nb_char);
}

void	print_directory(char *directory, t_env *env)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			ctrl;
	struct stat		file_stat;
	char			*file;

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
			if (g_argp[MINUS_L].active == 1)
			{
				file = ft_strjoin(directory, "/");
				file = ft_strjoin(file, content_dir->d_name);
				/*ft_dprintf(1, GREEN"dir = %s"END, file);*/
				minus_l(file, env);
			}
			/*RC;*/
			if (file_stat.st_mode & S_IFLNK)
				lstat(content_dir->d_name, &file_stat);
			else
				stat(content_dir->d_name, &file_stat);
			sort_lst(&ctrl, content_dir);
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

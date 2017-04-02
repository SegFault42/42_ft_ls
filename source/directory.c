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
	if (g_argp[MINUS_L].active == 1)
		padding_l(&ctr);
	print_lst(&ctr);
	/*ft_2d_tab_free(tab);*/
	/*free_list(&ctr);*/
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
		recursive(directory, env);
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
			if (content_dir->d_type == DT_LNK)
			{
				if ((size_buf = readlink(file, buf, sizeof(buf) - 1)) != -1)
					buf[size_buf] = '\0';
				sort_lst(&ctrl, content_dir, buf);
			}
			else
				sort_lst(&ctrl, content_dir, NULL);
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

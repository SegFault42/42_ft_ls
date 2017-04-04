#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern char		g_info[255];
extern int		g_total;

int8_t	open_directory(DIR **dir, char *directory)
{
	char	*name;

	name = ft_strrchr(directory, '/');
	if ((*dir = opendir(directory)) == NULL)
	{
		if (name != NULL)
			ft_dprintf(2, "ls: %s: %s\n", &ft_strrchr(directory, '/')[1], strerror(errno));
		else
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

void	particular_minus_t(t_ctrl *ctrl, char *directory, t_env *env)
{
	int		i;
	char	**tab;
	t_file	*tmp;
	t_ctrl	ctr;
	struct stat		file_stat;
	char			*file = NULL;

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
		file = ft_strjoin(directory, "/");
		file = ft_strjoin(file, tab[i]);
		if (lstat(file, &file_stat) < 0)
		{
			ft_dprintf(1, "ls: %s: %s\n", &ft_strrchr(file, '/')[1], strerror(errno));
			continue ;
		}
		if (g_argp[MINUS_L].active == 1)
			minus_l(file, env);
		sort_by_time(&ctr, file_stat.st_mtimespec.tv_sec, file);
		if (file)
			ft_strdel(&file);
		++i;
	}
	if (g_argp[MINUS_L].active == 1)
		padding_l(&ctr);
	print_lst(&ctr);
	/*ft_2d_tab_free(tab);*/
	/*free_list(&ctr);*/
}

void	insert_string(t_ctrl *ctrl, char *directory)
{
	/*char	tmp[256];*/
	int		i;
	int		len_directory;
	int		j;

	j = 0;
	i = ft_strlen(ctrl->first->info);
	len_directory = ft_strlen(directory);
	g_total = 0;
	while (ctrl->first->info[i] != ' ')
		--i;
	ctrl->first->info[i++] = ' ';
	while (len_directory > 0)
	{
		ctrl->first->info[i] = directory[j];
		++i;
		++j;
		--len_directory;
	}
	ctrl->first->info[i++] = ' ';
	ctrl->first->info[i++] = '-';
	ctrl->first->info[i++] = '>';
	ctrl->first->info[i++] = ' ';
	/*ft_memset(tmp, 0, 256);*/
	/*ft_memmove(tmp, ctrl->first->info, 256);*/
	/*ft_dprintf(1, "%d\n", i);*/
}

void	print_directory(char *directory, t_env *env)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			ctrl;
	struct stat		file_stat;
	char			*file = NULL;
	char			buf[PATH_MAX];
	int				size_buf;

	content_dir = NULL;
	dir = NULL;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	lstat(directory, &file_stat);
	if (g_argp[MINUS_L].active == 1 && S_ISLNK(file_stat.st_mode) == 1)
	{
		if ((size_buf = readlink(directory, buf, sizeof(buf) - 1)) != -1)
			buf[size_buf] = '\0';
		sort_lst_file(&ctrl, buf);
		minus_l(directory, env);
		ctrl.first->info = g_info;
		padding_l(&ctrl);
		insert_string(&ctrl, directory);
		print_list(&ctrl);
		return ;
	}
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
			/*if (ft_strcmp(directory, "/") != 0)*/
			file = ft_strjoin(directory, "/");
			file = ft_strjoin(file, content_dir->d_name);
			if (lstat(file, &file_stat) < 0)
			{
				ft_dprintf(1, "ls: %s: %s\n", &ft_strrchr(file, '/')[1], strerror(errno));
				ft_strdel(&file);
				continue ;
			}
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
			particular_minus_t(&ctrl, directory, env);
		else
			print_lst(&ctrl);
		/*free_list(&ctrl);*/
	}
	close_directory(&dir);
}

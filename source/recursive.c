#include "../include/ft_ls.h"

extern t_argp	g_argp[];

static void		print_all_directory(char *path, t_env *env)
{
	struct dirent	*entry;
	struct stat		file_stat;
	DIR				*dir;
	t_ctrl			lst;
	char			buf[PATH_MAX];
	int				size_buf;
	char			*file = NULL;

	ft_memset(&lst, 0, sizeof(t_ctrl));
	if (open_directory(&dir, path) == EXIT_ERROR)
		return ;
	while ((entry = readdir(dir)) != NULL)
	{
		if (check_minus_a(entry) == true)
			continue ;
		file = ft_strjoin(path, "/");
		file = ft_strjoin(file, entry->d_name);
		if (lstat(file, &file_stat) < 0)
		{
			ft_dprintf(2, "ls: %s: %s\n", &ft_strrchr(file, '/')[1], strerror(errno));
			continue ;
		}
		if (g_argp[MINUS_L].active == 1)
			minus_l(file, env);
		if (entry->d_type == DT_LNK)
		{
			if ((size_buf = readlink(file, buf, sizeof(buf) - 1)) != -1)
				buf[size_buf] = '\0';
			sort_lst(&lst, entry, buf);
		}
		else
			sort_lst(&lst, entry, NULL);
	}
	if (g_argp[MINUS_L].active == 1)
		padding_l(&lst);
	if (g_argp[MINUS_T].active == 1)
		particular_minus_t(&lst, path, env);
	else
		print_lst(&lst);
	close_directory(&dir);
	free_list(&lst);
}

void	recursive(char *directory, t_env *env)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*d_name;
	int				 path_length;
	char			 *path;
	t_ctrl			lst;
	t_file			*tmp;

	ft_memset(&lst, 0, sizeof(t_ctrl));
	if (open_directory(&dir, directory) == EXIT_ERROR)
		return ;
	print_all_directory(directory, env);
	while ((entry = readdir(dir)))
	{
		d_name = entry->d_name;
		if (check_minus_a(entry) == true)
			continue ;
		if (entry->d_type & DT_DIR)
		{
			if (ft_strcmp(d_name, "..") != 0 && ft_strcmp(d_name, ".") != 0)
			{
				if (ft_strcmp(directory, "/") == 0)
					path = ft_strjoin("/", entry->d_name);
				else
				{
					path = ft_strjoin(directory, "/");
					path = ft_strjoin(path, entry->d_name);
				}
				path_length = ft_strlen(path);
				if (g_argp[MINUS_R].active == 1)
					sort_lst_dir_rev(&lst, path);
				else
					sort_lst_dir(&lst, path);
				ft_strdel(&path);
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
		recursive(tmp->name, env);
		tmp= tmp->next;
	}
	closedir(dir);
	free_list(&lst);
}

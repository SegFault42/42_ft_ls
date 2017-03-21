#include "../include/ft_ls.h"

extern t_argp	g_argp[];

static void		print_all_directory(char *path)
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

void	recursive(char *directory)
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

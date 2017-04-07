/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 06:39:15 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 06:41:17 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];

bool	print_all_directory_2(struct dirent *e, char *f, t_ctrl *lst, t_env *en)
{
	char			buf[PATH_MAX];
	int				size_buf;
	struct stat		file_stat;

	if (lstat(f, &file_stat) < 0 && print_error(f) == true)
		return (true);
	if (g_argp[MINUS_L].active == 1)
		minus_l(f, en);
	if (e->d_type == DT_LNK)
	{
		if ((size_buf = readlink(f, buf, sizeof(buf) - 1)) != -1)
			buf[size_buf] = '\0';
		sort_lst(lst, e, buf);
	}
	else
		sort_lst(lst, e, NULL);
	return (false);
}

static void		print_all_directory(char *path, t_env *env)
{
	struct dirent	*entry;
	DIR				*dir;
	t_ctrl			lst;
	char			*file;

	ft_memset(&lst, 0, sizeof(t_ctrl));
	if (open_directory(&dir, path) == EXIT_ERROR)
		return ;
	while ((entry = readdir(dir)) != NULL)
	{
		if (check_minus_a(entry) == true)
			continue ;
		file = join(path, entry->d_name);
		if (print_all_directory_2(entry, file, &lst, env) == true)
			continue ;
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
	int				path_length;
	char			*path;
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
					path = join(directory, entry->d_name);
				path_length = ft_strlen(path);
				if (g_argp[MINUS_R].active == 1)
					sort_lst_dir_rev(&lst, path);
				else
					sort_lst_dir(&lst, path);
				ft_strdel(&path);
				if (path_length >= PATH_MAX)
					exit(EXIT_FAILURE);
			}
		}
	}
	tmp = lst.first;
	while (tmp)
	{
		RC;
		ft_dprintf(1, "%s:\n", tmp->name);
		recursive(tmp->name, env);
		tmp = tmp->next;
	}
	closedir(dir);
	free_list(&lst);
}

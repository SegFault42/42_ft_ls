/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 02:07:30 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 03:59:46 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern char		g_info[255];
DIR				*g_dir;

void	print_directory_2(char *directory, t_ctrl *ctrl, t_env *env)
{
	char	buf[PATH_MAX];
	int		size_buf;

	if ((size_buf = readlink(directory, buf, sizeof(buf) - 1)) != -1)
		buf[size_buf] = '\0';
	sort_lst_file(ctrl, buf);
	minus_l(directory, env);
	ctrl->first->info = g_info;
	padding_l(ctrl);
	insert_string(ctrl, directory);
	print_list(ctrl);
}

void	padding_min_t_or_print(t_ctrl *ctrl, char *directory, t_env *env)
{
	if (g_argp[MINUS_L].active == 1)
		padding_l(ctrl);
	if (g_argp[MINUS_T].active == 1)
		particular_minus_t(ctrl, directory, env);
	else
		print_lst(ctrl);
}

bool	split_norme_2(char *file, struct stat file_stat, t_env *env)
{
	if (lstat(file, &file_stat) < 0)
	{
		ft_dprintf(2,
				"ls: %s: %s\n", &ft_strrchr(file, '/')[1], strerror(errno));
		ft_strdel(&file);
		return (true);
	}
	if (g_argp[MINUS_L].active == 1)
		minus_l(file, env);
	return (false);
}

#define NORME ft_strcmp

void	split_norme(char *dire, struct stat file_stat, t_ctrl *ctrl, t_env *env)
{
	char			*file;
	char			buf[PATH_MAX];
	int				size_buf;
	struct dirent	*cd;

	while ((cd = readdir(g_dir)) != NULL)
	{
		if (g_argp[UPPER_A].active == 1 && g_argp[MINUS_A].active == 0 &&
			(NORME(cd->d_name, ".") == 0 || ft_strcmp(cd->d_name, "..") == 0))
			continue ;
		if ((check_minus_a(cd) == true) && (g_argp[UPPER_A].active == 0))
			continue ;
		file = join(dire, cd->d_name);
		if (split_norme_2(file, file_stat, env) == true)
			continue ;
		if (cd->d_type == DT_LNK)
		{
			if ((size_buf = readlink(file, buf, sizeof(buf) - 1)) != -1)
				buf[size_buf] = '\0';
			sort_lst(ctrl, cd, buf);
		}
		else
			sort_lst(ctrl, cd, NULL);
		ft_strdel(&file);
	}
}

void	print_directory(char *directory, t_env *env)
{
	t_ctrl			ctrl;
	struct stat		file_stat;

	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	lstat(directory, &file_stat);
	if (g_argp[MINUS_L].active == 1 && S_ISLNK(file_stat.st_mode) == 1)
		return (print_directory_2(directory, &ctrl, env));
	if (open_directory(&g_dir, directory) == EXIT_ERROR)
		return ;
	if (g_argp[UPPER_R].active == 1)
		recursive(directory, env);
	else
	{
		split_norme(directory, file_stat, &ctrl, env);
		padding_min_t_or_print(&ctrl, directory, env);
	}
	close_directory(&g_dir);
}

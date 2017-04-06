/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 23:46:28 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 23:55:57 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern bool		g_total;

static void	print_regular_files_2(t_env *env, struct stat *f_stat, t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (env->files[i])
	{
		if (lstat(env->files[i], f_stat) < 0)
			continue ;
		if (g_argp[MINUS_L].active == 1)
			minus_l(env->files[i], env);
		if (g_argp[MINUS_T].active == 1)
			sort_by_time(ctrl, f_stat->st_mtimespec.tv_sec, env->files[i]);
		else
			sort_lst_file(ctrl, env->files[i]);
		++i;
	}
}

static void	print_regular_files(t_env *env)
{
	int				i;
	t_ctrl			ctrl;
	struct stat		file_stat;

	g_total = 0;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	if (g_argp[MINUS_R].active == 1)
	{
		i = ft_count_2d_tab(env->files);
		while (--i >= 0)
			ft_dprintf(1, "%s\n", env->files[i]);
	}
	else
	{
		print_regular_files_2(env, &file_stat, &ctrl);
		if (g_argp[MINUS_L].active == 1)
			padding_l(&ctrl);
		print_lst(&ctrl);
		free_list(&ctrl);
	}
	if (env->directory[0] != NULL)
		RC;
}

static void	browse_directory_2(t_env *env, int i)
{
	if (env->nb_args == 1)
	{
		ft_dprintf(1, "%s:\n", env->directory[i]);
		print_directory(env->directory[i], env);
	}
	else
		print_directory(env->directory[i], env);
}

void		browse_directory(t_env *env)
{
	int	i;

	i = 0;
	g_total = 1;
	if (g_argp[MINUS_R].active == 1)
	{
		i = ft_count_2d_tab(env->directory);
		while (--i >= 0)
			browse_directory_2(env, i);
	}
	else
		while (env->directory[i])
		{
			if (env->nb_args == 1)
			{
				ft_dprintf(1, "%s:\n", env->directory[i]);
				print_directory(env->directory[i], env);
			}
			else
				print_directory(env->directory[i], env);
			++i;
			if (env->directory[i] != NULL)
				RC;
		}
}

void		print(t_env *env)
{
	if (env->files[0] != NULL)
		print_regular_files(env);
	if (env->directory[0] != NULL)
		browse_directory(env);
}

#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern bool		g_total;

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
		i = 0;
		while (env->files[i])
		{
			if (lstat(env->files[i], &file_stat) < 0)
				continue ;
			if (g_argp[MINUS_L].active == 1)
				minus_l(env->files[i], env);
			if (g_argp[MINUS_T].active == 1)
				sort_by_time(&ctrl, file_stat.st_mtimespec.tv_sec, env->files[i]);
			else
				sort_lst_file(&ctrl, env->files[i]);
			++i;
		}
		if (g_argp[MINUS_L].active == 1)
			padding_l(&ctrl);
		print_lst(&ctrl);
		free_list(&ctrl);
	}
	if (env->directory[0] != NULL)
		RC ;
}

void	browse_directory(t_env *env)
{
	int	i;
	int	len_tab;

	i = 0;
	g_total = 1;
	len_tab = ft_count_2d_tab(env->directory);
	if (g_argp[MINUS_R].active == 1)
	{
		i = ft_count_2d_tab(env->directory);
		while (--i >= 0)
		{
			if (len_tab > 1)
			{
				ft_dprintf(1, "%s:\n", env->directory[i]);
				print_directory(env->directory[i], env);
			}
			else
				print_directory(env->directory[i], env);
		}
	}
	else
		while (env->directory[i])
		{
			if (env->nb_args == 1)
			/*if (len_tab > 1)*/
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

void	print(t_env *env)
{
	if (env->files[0] != NULL)
		print_regular_files(env);
	if (env->directory[0] != NULL)
		browse_directory(env);
}

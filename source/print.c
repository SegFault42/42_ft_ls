#include "../include/ft_ls.h"

extern t_argp	g_argp[];

static void	print_regular_files(t_env *env)
{
	int				i;
	t_ctrl			ctrl;
	struct stat		file_stat;
	/*char			*file;*/

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
			/*if (g_argp[MINUS_L].active == 1)*/
			/*{*/
				/*file = ft_strjoin("./", env->files[i]);*/
				/*ft_dprintf(1, "%s\n", file);*/
				/*minus_l(file, env);*/
			/*}*/
			/*ft_dprintf(1, "%s = %d\n", env->files[i], file_stat.st_mtimespec.tv_sec);*/
			if (file_stat.st_mode & S_IFLNK)
				lstat(env->files[i], &file_stat);
			else
				stat(env->files[i], &file_stat);
			if (g_argp[MINUS_T].active == 1)
				sort_by_time(&ctrl, file_stat.st_mtimespec.tv_sec, env->files[i]);
			else
			{
				/*sort_lst_dir(&ctrl, env->files[i]);*/
				ft_dprintf(1, "%s\n", env->files[i]);
			}
			++i;
		}
		/*if (g_argp[MINUS_L].active == 1)*/
			/*padding_l(&ctrl);*/
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
			/*if (env->directory[i] != NULL)*/
				/*RC;*/
		}
	}
	else
		while (env->directory[i])
		{
			if (len_tab > 1)
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

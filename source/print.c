#include "../include/ft_ls.h"

extern t_argp	g_argp[];

static void	print_regular_files(t_env *env)
{
	int	i;

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
			ft_dprintf(1, "%s\n", env->files[i]);
			++i;
		}
	}
	if (env->directory[0] != NULL)
		RC ;
}

void	browse_directory(char **dir)
{
	int	i;
	int	len_tab;

	i = 0;
	len_tab = ft_count_2d_tab(dir);
	while (dir[i])
	{
		if (len_tab > 1)
		{
			ft_dprintf(1, "%s:\n", dir[i]);
			print_directory(dir[i]);
		}
		else
			print_directory(dir[i]);
		++i;
		if (dir[i] != NULL)
			RC;
	}
}

void	print(t_env *env)
{
	if (env->files[0] != NULL)
		print_regular_files(env);
	if (env->directory[0] != NULL)
		browse_directory(env->directory);
}

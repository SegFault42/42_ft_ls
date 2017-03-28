#include "../include/ft_ls.h"

void	quit(t_env *env, int argc)
{
	free(env->files);
	if (argc < 2)
		ft_2d_tab_free(env->directory);
	else
		free(env->directory);
	/*if (env->directory[0] != NULL)*/
		/*ft_strdel(&env->directory[0]);*/
	/*if (g_argp[MINUS_L].active = 1)*/
	/*if (env->file.info != NULL)*/
		/*free(env->file.info);*/
}

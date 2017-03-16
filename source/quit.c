#include "../include/ft_ls.h"

void	quit(t_env *env, int argc)
{
	free(env->files);
	if (argc < 2)
		ft_2d_tab_free(env->directory);
	else
		free(env->directory);
}

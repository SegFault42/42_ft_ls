#include "../include/ft_ls.h"

void	quit(t_env *env)
{
	free(env->files);
	free(env->directory);
}

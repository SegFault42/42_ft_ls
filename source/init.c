#include "../include/ft_ls.h"

void		init(t_ctrl *ctrl, t_env *env)
{
	ft_memset(ctrl, 0, sizeof(t_ctrl));
	ft_memset(env, 0, sizeof(t_env));
}

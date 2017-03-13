#include "../include/ft_ls.h"

void	free_argp()
{
	int	i;

	i = 0;
	while (g_argp[i].sign)
	{
		ft_strdel(&g_argp[i].sign);
		ft_strdel(&g_argp[i].description);
		++i;
	}
}

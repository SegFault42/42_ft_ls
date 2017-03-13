#include "../include/ft_ls.h"
/*
** get_option() recupere toute les option dans argv et les stock dans g_argp
*/
void	get_option(char **argv, int argc)
{
	int		arg;
	uint8_t	i;

	arg = 1;
	while (argv[arg])
	{
		i = 0;
		if (argv[arg][0] == '-' && g_argp[END_OPTION].active == 0)
		{
			while (g_argp[i].sign)
			{
				if (ft_strstr(argv[arg], g_argp[i].sign) != NULL)
					g_argp[i].active = 1;
				++i;
			}
		}
		++arg;
	}
	(void)argc;
}

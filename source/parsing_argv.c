#include "../include/ft_ls.h"

extern t_argp g_argp[];

static void	usage(char option)
{
	ft_dprintf(2, "ls: illegal option -- %c\nusage: ls [-Ralrt1] [file ...]\n",
	option);
	exit(EXIT_FAILURE);
}

static void	check_if_option_exist(char *argument)
{
	int	i;
	int	j;

	i = 1;
	while (argument[i])
	{
		j = 0;
		while (g_argp[j].sign)
		{
			/*ft_dprintf(1, "sign = %c, argument[j] = %c\n", g_argp[j].sign[0], argument[i]);*/
			if (g_argp[j].sign[0] == argument[i])
			{
				++i;
				continue ;
			}
			++j;
			if (j >= SIZE_ARGP)
				usage(argument[i]);
		}
		++i;
	}
}

/*
** get_option() recupere toute les option dans argv et les stock dans g_argp
*/
void	get_option(char **argv)
{
	int		arg;
	uint8_t	i;

	arg = 1;
	while (argv[arg])
	{
		check_if_option_exist(argv[arg]);
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
}

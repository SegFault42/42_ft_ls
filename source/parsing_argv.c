#include "../include/ft_ls.h"

extern t_argp g_argp[];

static void	usage(char option)
{
	ft_dprintf(2,
	"ft_ls: illegal option -- %c\nusage: ./ft_ls [-Ralrt1] [file ...]\n",
	option);
	exit(EXIT_FAILURE);
}

static void	check_if_option_exist(char *argument)
{
	int	i;
	int	j;
	int	ok;

	i = 1;
	ok = 0;
	while (argument[i])
	{
		j = 0;
		while (g_argp[j].sign)
		{
			if (g_argp[j].sign[0] == argument[i])
				ok = 1;
			++j;
		}
		if (ok == 0)
			usage(argument[i]);
		++i;
		ok = 0;
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
		i = 0;
		if (argv[arg][0] == '-' && g_argp[END_OPTION].active == 0)
		{
			check_if_option_exist(argv[arg]);
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

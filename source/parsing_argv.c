#include "../include/ft_ls.h"

extern t_argp g_argp[];

static void	usage(char option)
{
	ft_dprintf(STDERR_FILENO,
	/*"ls: illegal option -- %c\nusage: ./ft_ls [-Ralrt1] [file ...]\n",*/
	"ls: illegal option -- %c\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n",
	option);
	exit(EXIT_FAILURE);
}

/*
** verifie que l'option dans argument existe dans le tableau de structure g_argp
*/

static void	check_if_option_exist(char *argument)
{
	int	i;
	int	j;
	int	ok;

	i = 1;
	while (argument[i])
	{
		ok = 0;
		j = 0;
		while (g_argp[j].sign)
		{
			if (g_argp[j].sign[0] == argument[i])
			{
				if (ft_strstr(argument, "--") != 0 && ft_strlen(argument) > 2)
					usage(argument[i]);
				ok = 1;
				break ;
			}
			++j;
		}
		if (ok == 0)
			usage(argument[i]);
		++i;
	}
}

#define OPTION_ONE	0
#define OPTION_L	1

void	shutdown_option(char **argv)
{
	/*int	option[2];*/
	int	i;

	i = 0;
	if (g_argp[MINUS_L].active == 1 && g_argp[ONE].active == 1)
	{
		while (argv[i + 1] || argv[i + 1][0] == '-')
		{
			if (argv[i] != NULL && ft_strcmp(argv[i], "--") == 0)
				break ;
			++i;
		}
	}
	ft_dprintf(1, "%d\n", i);
}

/*
** get_option()
** recupere toute les option dans argv et active un booleen dans g_argp
*/

void		get_option(char **argv)
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
	/*shutdown_option(argv);*/
}

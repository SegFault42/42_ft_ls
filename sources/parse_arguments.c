/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:26:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/04 21:14:10 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char **parse_arg(char **argv, int argc)
{
	uint8_t	i;
	int		arg;
	char	**arguments;

	i = 0;
	arg = 0;
	arguments = (char **)malloc(sizeof(char *) * argc + 1);
	++argv;
	while (argv[arg])
	{
		if (argv[arg][0] == '-') // Si un - est au debut du premier argument
		{
			while (g_argp[i].sign)
			{
				if (ft_strstr(argv[arg], g_argp[i].sign) != NULL)
					g_argp[i].active = 1;
				++i;
			}
			i = 0;
		}
		arguments[arg] = ft_strdup(argv[arg]);
		++arg;
	}
	arguments[arg] = NULL;
	return (arguments);
}
void	fill_argp(char *param, char *description, int index)
{
	g_argp[index].description = ft_strdup(description);
	g_argp[index].sign = ft_strdup(param);
	g_argp[index].active = 0;
	if (g_argp[index].sign == NULL || g_argp[index].description == NULL)
		ft_error(MALLOC_ERROR);
}

void	init_argp()
{
	ft_memset(g_argp, 0, sizeof(g_argp));
	fill_argp("a", "Print hide file", 0);
	fill_argp("1", "One file per line", 1);
	fill_argp("R", "List subdirectory recursively", 2);
	fill_argp("r", "reverse sort", 3);
	fill_argp("t", "sort by time (new first)", 4);
	fill_argp("l", "print full info", 5);
}

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

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

uint8_t	parse_arg(char **argv)
{
	uint8_t	i;
	uint8_t	arg_value;

	i = 0;
	arg_value = 0;
	if (ft_strcmp(argv[1], "--") == 0)
		return (arg_value);
	if (argv[1][0] == '-') // Si un - est au debut du premier argument
	{
		while (g_argp[i].sign)
		{
			if (ft_strstr(argv[1], g_argp[i].sign) != NULL)
				g_argp[i].active = 1;
			++i;
		}
	}
	/*for (int i = 0; i < SIZE_ARGP; ++i)*/
		/*ft_dprintf(1, GREEN"sign = %s, active = %d, desc = %s\n"END,*/
		/*g_argp[i].sign, g_argp[i].active, g_argp[i].description);*/
	return (arg_value);
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

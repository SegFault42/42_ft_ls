/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:48:29 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/04 21:14:17 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

t_argp	g_argp[] =
{
	{"a", 0, "print hide file"},
	{"1", 0, "One file per line"},
	{"R", 0, "list subdirectory recursively"},
	{"r", 0, "reverse sort"},
	{"t", 0, "sort by time (new first)"},
	{"l", 0, "print full info"},
	{"--", 0, "end getting option"},
	{0, 0, 0}
};

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;
	t_env	env;
	int		i;

	i = 0;
	init(&ctrl, &env);
	get_option(argv);
	sort_argv(&env, argv, argc);
	print(&env);
	/*quit(&env, argc);*/
	return (EXIT_SUCCESS);
	(void)argc;
}

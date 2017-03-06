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

static uint8_t	parse_arg(char **argv)
{
	uint8_t	i;
	uint8_t	arg_value;

	i = 0;
	arg_value = 0;
	if (ft_strcmp(argv[1], "--") == 0 )
		return (arg_value);
	if (argv[1][0] == '-') // Si un - est au debut du premier argument
	{
		while (g_argp[i].sign)
		{
			if (ft_strstr(argv[1], g_argp[i].sign) != NULL)
				g_argp[i].active = 1;
	ft_dprintf(1, "sign = %s active = %d\n", g_argp[i].sign,  g_argp[i].active);
			++i;
		}
	}
	return (arg_value);
}

void			print_list(t_ctrl *ctrl)
{
	t_file	*tmp;

	tmp = ctrl->first;
	while (tmp)
	{
		ft_dprintf(1, "%s\n", tmp->name);
		tmp = tmp->next;
	}
}

void	init_argp()
{
	g_argp[0].sign = ft_strdup("a");
	g_argp[0].active = 0;
	g_argp[0].descritpion = ft_strdup("print hide file");
	g_argp[1].sign = ft_strdup("l");
	g_argp[1].active = 0;
	g_argp[1].descritpion = ft_strdup("One file per line");
	g_argp[2].sign = 0;
	g_argp[2].active = 0;
	g_argp[2].descritpion = 0;
}

int				main(int argc, char **argv)
{
	t_env	env;
	t_ctrl	ctrl;

	ft_memset(&ctrl, 0, sizeof(ctrl));
	ft_memset(&env, 0, sizeof(env));
	init_argp();
	if (argc > 1)
		parse_arg(argv);
	if (no_param(&ctrl, &env) == EXIT_ERROR)
		return (EXIT_FAILURE);
	print_list(&ctrl);
	(void)argc;
	return (EXIT_SUCCESS);
}

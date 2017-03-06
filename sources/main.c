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
	free_argp();
	return (EXIT_SUCCESS);
}

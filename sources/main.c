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


void	quit(char **arguments, t_ctrl *ctrl)
{
	free_argp();
	if (arguments != NULL)
		ft_2d_tab_free(arguments);
	/*free(ctrl.first->name);*/
	/*free(ctrl.first);*/
	exit(EXIT_SUCCESS);
	(void)ctrl;
}

int				main(int argc, char **argv)
{
	t_env	env;
	t_ctrl	ctrl;
	char	**arguments;

	arguments = NULL;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	ft_memset(&env, 0, sizeof(t_env));
	init_argp();
	/*if (argc > 1)*/
		arguments = parse_arg(argv, argc -1);
	if (only_option(arguments, &ctrl, &env) == EXIT_SUCCESS)
		quit(arguments, &ctrl);
	return (EXIT_SUCCESS);
}

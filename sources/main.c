/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:48:29 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/01 22:54:53 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static uint8_t	parse_arg(char **argv)
{
	uint8_t	i;
	uint8_t	arg_value;

	i = 0;
	while (argv[++i])
	{
		if (ft_strcmp(argv[i], "-l") == 0)
			arg_value = L_MIN;
		else if (ft_strcmp(argv[i], "-la") == 0)
			arg_value = L_MIN | A_MIN;
		ft_dprintf(1, "%s\n", argv[i]);
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

int				main(int argc, char **argv)
{
	t_env	env;
	t_ctrl	ctrl;

	ft_memset(&ctrl, 0, sizeof(ctrl));
	ft_memset(&env, 0, sizeof(env));
	env.arg_value = parse_arg(argv);
	if (no_param(&ctrl) == EXIT_ERROR)
		return (EXIT_ERROR);
	print_list(&ctrl);
	RC;
	move_maillon(&ctrl, 1, 5);
	RC;
	print_list(&ctrl);
	(void)argc;
	(void)argv;
	/*while (3){}*/
	return (EXIT_SUCCESS);
}

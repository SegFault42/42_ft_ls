/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:48:29 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/28 23:31:52 by rabougue         ###   ########.fr       */
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

void	print_list(t_ctrl *ctrl)
{
	t_file	*tmp;

	tmp = ctrl->first;
	while (tmp->next)
	{
		ft_dprintf(1, "%s\n", tmp->name);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	t_env	env;
	t_file	*file;
	t_ctrl	ctrl_file;

	file = create_first_maillon(&ctrl_file);
	ft_memset(&file, 0, sizeof(file));
	ft_memset(&env, 0, sizeof(env));
	env.arg_value = parse_arg(argv);
	if (no_param(&ctrl_file) == EXIT_ERROR)
		return (EXIT_ERROR);
	ft_dprintf(1, RED"Print list = \n"END);
	print_list(&ctrl_file);
	while (ctrl_file.first->next)
	{
		free_maillon(&ctrl_file);
	}
	free(file);
	RC;
	ft_dprintf(1, RED"Print list = \n"END);
	print_list(&ctrl_file);
	(void)argc;
	(void)argv;
	while (42){}
	return (EXIT_SUCCESS);
}

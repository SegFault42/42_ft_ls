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

bool			check_if_arg_only_option(char **arguments, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (arguments[i][0] != '-')
			return (false);
		++i;
	}
	return (true);
}

int				main(int argc, char **argv)
{
	t_env	env;
	t_ctrl	ctrl;
	char	**arguments;
	int		i;

	i = 0;
	arguments = NULL;
	ft_memset(&ctrl, 0, sizeof(ctrl));
	ft_memset(&env, 0, sizeof(env));
	init_argp();
	if (argc > 1 && ft_strcmp(argv[1], "--") != 0)
		arguments = parse_arg(argv, argc - 1);
	if (check_if_arg_only_option(arguments, argc) == true)
		if (get_files(&ctrl, &env, ".") == EXIT_ERROR)
			return (EXIT_FAILURE);
	while (i < argc - 1)
	{
		if (arguments[i][0] != '-')
			if (get_files(&ctrl, &env, arguments[i]) == EXIT_ERROR)
				return (EXIT_FAILURE);
		++i;
	}
	free_argp();
	if (arguments != NULL)
		ft_2d_tab_free(arguments, argc -1);
	/*free(ctrl.first->name);*/
	/*free(ctrl.first);*/
	return (EXIT_SUCCESS);
}

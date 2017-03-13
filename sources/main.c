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

void			print_list_reverse(t_ctrl *ctrl)
{
	int		i;
	int		j;
	t_file	*tmp;

	i = 0;
	j = 0;
	tmp = ctrl->first;
	while (tmp)
	{
		tmp = tmp->next;
		++i;
	}
	--i;
	while (i >= 0)
	{
		tmp = ctrl->first;
		while (j < i)
		{
			tmp = tmp->next;
			++j;
		}
		ft_dprintf(1, "%s\n", tmp->name);
		--i;
		j = 0;
	}
}

void	quit(char **arguments, t_ctrl *ctrl, t_env *env)
{
	free_argp();
	if (arguments != NULL)
		ft_2d_tab_free(arguments);
	/*ft_2d_tab_free(env->arguments);*/
	/*free(ctrl.first->name);*/
	/*free(ctrl.first);*/
	exit(EXIT_SUCCESS);
	(void)ctrl;
	(void)env;
}

void	save_arguments(t_env *env, char **argv, int argc)
{
	int	i;

	i = 0;
	if ((env->arguments = (char **)ft_memalloc(sizeof(char *) * argc + 1)) == NULL)
		ft_error(MALLOC_ERROR);
	while (argv[i])
	{
		env->arguments[i] = argv[i];
		++i;
	}
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
	save_arguments(&env, argv, argc);
	arguments = parse_arg(argv, argc -1);
	if (only_option(arguments, &ctrl, &env) == EXIT_SUCCESS)
		quit(arguments, &ctrl, &env);
	return (EXIT_SUCCESS);
}

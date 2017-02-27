/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:48:29 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/27 17:23:51 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void		check_if_two_same_param()
{}

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

int main(int argc, char **argv)
{
	t_env	env;

	ft_memset(&env, 0, sizeof(env));
	env.arg_value = parse_arg(argv);
	if (no_param() == EXIT_ERROR)
		return (EXIT_ERROR);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}

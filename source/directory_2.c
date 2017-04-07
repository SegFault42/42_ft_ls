/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 06:03:17 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 06:06:41 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];

bool	print_error(char *file)
{
	ft_dprintf(2, "ls: %s: %s\n", &ft_strrchr(file, '/')[1], strerror(errno));
	return (true);
}

bool	minus_t_2(char *file, t_env *env)
{
	if (g_argp[MINUS_L].active == 1)
		minus_l(file, env);
	return (false);
}

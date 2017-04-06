/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 22:03:14 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 22:03:44 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];

void	print_lst(t_ctrl *ctrl)
{
	if (ctrl->first != NULL)
	{
		if (g_argp[MINUS_R].active == 1)
			print_list_reverse(ctrl);
		else
			print_list(ctrl);
	}
}

void	print_list_no_such(t_ctrl *ctrl)
{
	t_file	*tmp;

	tmp = ctrl->first;
	while (tmp)
	{
		ft_dprintf(2, "ls: %s: No such file or directory\n", tmp->name);
		tmp = tmp->next;
	}
}

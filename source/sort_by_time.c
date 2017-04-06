/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_by_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 00:03:36 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 01:14:49 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	sort_by_time(t_ctrl *ctrl, size_t value, char *name)
{
	t_file	*tmp;
	int		node;
	char	*name_tmp;

	node = 1;
	tmp = ctrl->first;
	name_tmp = ft_strrchr(name, '/');
	if (name_tmp != NULL)
		name = &name_tmp[1];
	if (tmp == NULL)
		return (add_head(ctrl, name, value));
	while (tmp)
	{
		if (value > tmp->timestamp)
			return (add_before(ctrl, node, name, value));
		else if (tmp->next == NULL)
			return (add_tail(ctrl, name, value));
		else if (value > tmp->next->timestamp)
		{
			add_after(ctrl, node, name, value);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

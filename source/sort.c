/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 00:03:15 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 19:59:17 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	sort_lst_file(t_ctrl *ctrl, char *name)
{
	t_file	*tmp;
	int		node;
	int		i;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
		return (add_head(ctrl, name, 0));
	while (tmp)
	{
		while (name[i] && name[i] == tmp->name[i])
			++i;
		if (name[i] < tmp->name[i])
			return (add_before(ctrl, node, name, 0));
		else if (tmp->next == NULL)
			return (add_tail(ctrl, name, 0));
		i = 0;
		while (name[i] && name[i] == tmp->next->name[i])
			++i;
		if (name[i] < tmp->next->name[i])
			return (add_after(ctrl, node, name, 0));
		tmp = tmp->next;
		++node;
	}
}

void	sort_lst_dir(t_ctrl *ctrl, char *path)
{
	t_file	*tmp;
	int		i;
	int		node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
		return (add_head(ctrl, path, 0));
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] < tmp->name[i])
			return (add_before(ctrl, node, path, 0));
		else if (tmp->next == NULL)
			return (add_tail(ctrl, path, 0));
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] < tmp->next->name[i])
			return (add_after(ctrl, node, path, 0));
		tmp = tmp->next;
		++node;
	}
}

void	sort_lst_dir_rev(t_ctrl *ctrl, char *path)
{
	t_file	*tmp;
	int		i;
	int		node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
		return (add_head(ctrl, path, 0));
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] > tmp->name[i])
			return (add_before(ctrl, node, path, 0));
		else if (tmp->next == NULL)
			return (add_tail(ctrl, path, 0));
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] > tmp->next->name[i])
			return (add_after(ctrl, node, path, 0));
		tmp = tmp->next;
		++node;
	}
}

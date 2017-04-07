/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:57:32 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 19:59:15 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	before(t_ctrl *ctrl, int node, struct dirent *content_dir, char *link)
{
	add_before(ctrl, node, content_dir->d_name, 0);
	if (link != NULL)
		fill_node(ctrl, node, link);
}

void	tail(t_ctrl *ctrl, struct dirent *content_dir, char *link)
{
	add_tail(ctrl, content_dir->d_name, 0);
	if (link != NULL)
		fill_node(ctrl, -1, link);
}

void	after(t_ctrl *ctrl, int node, struct dirent *content_dir, char *link)
{
	add_after(ctrl, node, content_dir->d_name, 0);
	if (link != NULL)
		fill_node(ctrl, node, link);
}

void	head(t_ctrl *ctrl, int node, struct dirent *content_dir, char *link)
{
	add_head(ctrl, content_dir->d_name, 0);
	if (link != NULL)
		fill_node(ctrl, node, link);
}

#define CT_DIR content_dir

void	sort_lst(t_ctrl *ctrl, struct dirent *content_dir, char *link)
{
	t_file	*tmp;
	int		node;
	int		i;

	tmp = ctrl->first;
	node = 1;
	i = 0;
	if (tmp == NULL)
		return (head(ctrl, node, content_dir, link));
	while (tmp)
	{
		while (content_dir->d_name[i] && content_dir->d_name[i] == tmp->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->name[i])
			return (before(ctrl, node, content_dir, link));
		else if (tmp->next == NULL)
			return (tail(ctrl, content_dir, link));
		i = 0;
		while (CT_DIR->d_name[i] && CT_DIR->d_name[i] == tmp->next->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->next->name[i])
			return (after(ctrl, node, content_dir, link));
		tmp = tmp->next;
		++node;
	}
}

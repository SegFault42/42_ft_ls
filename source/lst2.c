/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 21:44:44 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 22:02:14 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern char		g_info[255];
extern size_t	g_nb_blocks;

size_t	count_nb_node(t_ctrl *ctrl)
{
	size_t	i;
	t_file	*tmp;

	i = 0;
	tmp = ctrl->first;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

void	free_list(t_ctrl *ctrl)
{
	t_file	*tmp;

	if (ctrl->first != NULL)
	{
		tmp = ctrl->first;
		while (tmp->next)
			free_maillon(ctrl);
		ft_strdel(&ctrl->first->name);
		free(ctrl->first);
		ctrl->first = NULL;
	}
}

void	free_maillon(t_ctrl *ctrl)
{
	t_file	*tmp;

	tmp = ctrl->first;
	while (tmp->next->next)
		tmp = tmp->next;
	ft_strdel(&tmp->next->name);
	ft_strdel(&tmp->next->info);
	ft_strdel(&tmp->next->link);
	free(tmp->next);
	tmp->next = NULL;
}

void	add_tail(t_ctrl *ctrl, char *str, int value)
{
	t_file	*new;
	t_file	*tmp;

	new = create_maillon();
	if (ctrl->first == NULL)
		ctrl->first = new;
	else
	{
		tmp = ctrl->first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = NULL;
	if (str != NULL)
		if ((new->name = ft_strdup(str)) == NULL)
			error(MALLOC_ERROR);
	if (value != 0)
		new->timestamp = value;
	if (g_info[0] != '\0' && g_argp[MINUS_L].active == 1)
	{
		new->info = (char *)ft_memalloc(sizeof(char) * 255);
		ft_memcpy(new->info, g_info, 255);
	}
}

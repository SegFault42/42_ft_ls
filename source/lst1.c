/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 21:42:50 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 22:15:49 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];
bool			g_total = 0;
extern size_t	g_nb_blocks;

void	print_list_reverse(t_ctrl *ctrl)
{
	int		i;
	int		j;
	t_file	*tmp;

	i = 0;
	j = 0;
	tmp = ctrl->first;
	if (g_argp[MINUS_L].active == 1 && g_total == 1)
		ft_dprintf(1, "total %d\n", g_nb_blocks);
	while (tmp && ++i)
		tmp = tmp->next;
	while (--i >= 0)
	{
		tmp = ctrl->first;
		while (j < i)
		{
			tmp = tmp->next;
			++j;
		}
		if (g_argp[MINUS_L].active == 1)
			ft_dprintf(1, "%s ", tmp->info);
		ft_dprintf(1, "%s\n", tmp->name);
		j = 0;
	}
}

void	fill_node(t_ctrl *ctrl, int node, char *link)
{
	t_file	*tmp;
	int		i;

	i = 0;
	tmp = ctrl->first;
	if (node == -1)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	else if (node > 1)
		while (i < node)
		{
			if (tmp->next == NULL)
			{
				ft_dprintf(2, RED"Error fill_node\n"END);
				exit(EXIT_FAILURE);
			}
			tmp = tmp->next;
			++i;
		}
	tmp->link = ft_strdup(link);
}

void	print_list(t_ctrl *ctrl)
{
	t_file	*tmp;

	tmp = ctrl->first;
	if (g_argp[MINUS_L].active == 1 && g_total == 1)
		ft_dprintf(1, "total %d\n", g_nb_blocks);
	while (tmp)
	{
		if (g_argp[MINUS_L].active == 1)
			ft_dprintf(1, "%s", tmp->info);
		ft_dprintf(1, "%s", tmp->name);
		if (tmp->link != NULL && g_argp[MINUS_L].active == 1)
			ft_dprintf(1, " -> %s\n", tmp->link);
		else
			ft_dprintf(1, "\n");
		tmp = tmp->next;
	}
	g_nb_blocks = 0;
}

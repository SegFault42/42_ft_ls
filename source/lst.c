/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:52:21 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 23:35:56 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];
extern char		g_info[255];
extern size_t	g_nb_blocks;

t_file			*create_maillon(void)
{
	t_file	*new;

	if ((new = (t_file *)malloc(sizeof(t_file))) == NULL)
		error(MALLOC_ERROR);
	ft_memset(new, 0, sizeof(t_file));
	return (new);
}

void			add_head(t_ctrl *ctrl, char *str, int value)
{
	t_file	*new;

	new = create_maillon();
	if (ctrl->first == NULL)
	{
		ctrl->first = new;
		new->next = NULL;
	}
	else
	{
		new->next = ctrl->first;
		ctrl->first = new;
	}
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

static t_file	*add_after_2(int node, t_ctrl *ctrl)
{
	int		i;
	t_file	*tmp;

	i = 0;
	tmp = ctrl->first;
	while (i < node - 1 || node <= 0)
	{
		if (tmp->next == NULL || node <= 0)
		{
			ft_dprintf(STDIN_FILENO, "node index to big or to small");
			return (NULL);
		}
		tmp = tmp->next;
		++i;
	}
	return (tmp);
}

bool			add_after(t_ctrl *ctrl, int node, char *name, int value)
{
	t_file	*tmp;
	t_file	*new;

	tmp = add_after_2(node, ctrl);
	if (tmp == NULL)
		return (FALSE);
	new = create_maillon();
	if (tmp->next == NULL)
		new->next = NULL;
	else
		new->next = tmp->next;
	tmp->next = new;
	if (name != NULL)
		if ((new->name = ft_strdup(name)) == NULL)
			error(MALLOC_ERROR);
	if (value != 0)
		new->timestamp = value;
	if (g_info[0] != '\0' && g_argp[MINUS_L].active == 1)
	{
		new->info = (char *)ft_memalloc(sizeof(char) * 255);
		ft_memcpy(new->info, g_info, 255);
	}
	return (TRUE);
}

void			add_before(t_ctrl *ctrl, int node, char *name, int value)
{
	t_file	*new;

	if (node == 1)
	{
		new = create_maillon();
		if (name != NULL)
			if ((new->name = ft_strdup(name)) == NULL)
				error(MALLOC_ERROR);
		if (value != 0)
			new->timestamp = value;
		if (g_info[0] != '\0' && g_argp[MINUS_L].active == 1)
		{
			new->info = (char *)ft_memalloc(sizeof(char) * 255);
			ft_memcpy(new->info, g_info, 255);
		}
		new->next = ctrl->first;
		ctrl->first = new;
	}
}

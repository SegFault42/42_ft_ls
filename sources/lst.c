/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:52:21 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/02 00:34:26 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	free_maillon(t_ctrl *ctrl)
{
	t_file	*tmp;

	tmp = ctrl->first;
	while (tmp->next->next)
	{
		tmp = tmp->next;
		ft_dprintf(1, GREEN"%s\n"END, tmp->name);
	}
	ft_strdel(&tmp->name);
	free(tmp->next->next);
	tmp->next = NULL;
}

t_file	*create_maillon()
{
	t_file	*new;

	if ((new = (t_file *)malloc(sizeof(new))) == NULL)
	{
		ft_dprintf(STDERR_FILENO,
			"Memory allocation failure ! (create_maillon)\n");
		exit(EXIT_FAILURE);
	}
	return (new);
}

void	add_tail(t_ctrl *ctrl, char *str)
{
	t_file	*new;
	t_file	*tmp;

	new = create_maillon();
	if (ctrl->first == NULL) // dans le cas ou aucun maillon est existe
		ctrl->first = new;
	else // si au moin un maillon existe
	{
		tmp = ctrl->first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = NULL;
	if ((new->name = ft_strdup(str)) == NULL)
	{
		ft_dprintf(STDERR_FILENO,
		"Memory allocation failure ! (ft_strdup)\n");
		exit(EXIT_FAILURE);
	}
}

void	add_head(t_ctrl *ctrl, char *str)
{
	t_file	*new;

	new = create_maillon();
	if (ctrl->first == NULL) // dans le cas ou aucun maillon est existe
	{
		ctrl->first = new;
		new->next = NULL;
	}
	else // si au moin un maillon existe
	{
		new->next = ctrl->first;
		ctrl->first = new;
	}
	if ((new->name = ft_strdup(str)) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Memory allocation failure ! (ft_strdup)\n");
		exit(EXIT_FAILURE);
	}
}

void	move_maillon(t_ctrl *ctrl, int old_place, int new_place)
{
	t_file	*tmp_first;
	t_file	*tmp_next;
	int		i;

	i = 1;
	tmp_first = ctrl->first;
	while (i < old_place - 1)
	{
		ft_debug();
		tmp_first = tmp_first->next;
		++i;
	}
	tmp_next = tmp_first->next;
	ft_dprintf(STDOUT_FILENO, PURPLE"-%s-\n"END, tmp_next->name);
	tmp_first->next = tmp_next->next;
	ft_dprintf(STDOUT_FILENO, CYAN"-%s-\n"END, tmp_first->name);
	while (i < new_place - 1)
	{
		tmp_first = tmp_first->next;
		++i;
	}
	ft_dprintf(STDOUT_FILENO, CYAN"-%s-\n"END, tmp_first->name);
	tmp_next->next = tmp_first->next;
	tmp_first->next = tmp_next;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:52:21 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/04 13:54:45 by rabougue         ###   ########.fr       */
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
		error(MALLOC_ERROR);
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
		error(MALLOC_ERROR);
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
		error(MALLOC_ERROR);
}

bool	add_after(t_ctrl *ctrl, int node, char *name)
{
	t_file	*tmp;
	t_file	*new;
	int		i;

	i = 0;
	tmp = ctrl->first;
	while (i < node - 1 || node <= 0)
	{
		if (tmp->next == NULL || node <= 0)
		{
			ft_dprintf(STDIN_FILENO, "node index to big or to small");
			return (FALSE);
		}
		tmp = tmp->next;
		++i;
	}
	new = create_maillon();
	if (tmp->next == NULL)
		new->next = NULL;
	else
		new->next = tmp->next;
	tmp->next = new;
	if ((new->name = ft_strdup(name)) == NULL)
		error(MALLOC_ERROR);
	return (TRUE);
}

void	add_before(t_ctrl *ctrl, int node, char *name)
{
	t_file	*tmp;
	t_file	*new;

	tmp = ctrl->first;
	if (node == 1)
	{
		new = create_maillon();
		if ((new->name = ft_strdup(name)) == NULL)
			error(MALLOC_ERROR);
		new->next = ctrl->first;
		ctrl->first = new;
	}
	/*while (i < node - 1 || node <= 0)*/
	/*{*/
		/*if (tmp->next == NULL || node <= 0)*/
		/*{*/
			/*ft_dprintf(STDIN_FILENO, "node index to big or to small");*/
			/*return (FALSE);*/
		/*}*/
		/*tmp = tmp->next;*/
		/*++i;*/
	/*}*/

}

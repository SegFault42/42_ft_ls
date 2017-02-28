/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:52:21 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/28 23:27:25 by rabougue         ###   ########.fr       */
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

t_file	*create_first_maillon(t_ctrl *ctrl)
{
	t_file *new;

	if ((new = (t_file *)malloc(sizeof(new))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Memory allocation failure ! (create_maillon)\n");
		exit(EXIT_FAILURE);
	}
	ctrl->first = new;
	new->next = NULL;
	return (new);
}

t_file	*create_maillon()
{
	t_file *new;

	if ((new = (t_file *)malloc(sizeof(new))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Memory allocation failure ! (create_maillon)\n");
		exit(EXIT_FAILURE);
	}
	new->next = NULL;
	return (new);
}

void	add_tail(t_ctrl *ctrl, char *str)
{
	t_file *new = (t_file *)malloc(sizeof(new));
	t_file *tmp = NULL;

	if (new == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Memory allocation failure ! (add_tail)\n");
		exit(EXIT_FAILURE);
	}
	new->next = NULL;
	new->name = str;
	tmp = ctrl->first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_head(t_ctrl *ctrl, char *str)
{
	t_file *new;

	new = create_maillon();

	if (new == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Memory allocation failure ! (add_head)\n");
		exit(EXIT_FAILURE);
	}
	new->next = ctrl->first;
	ctrl->first = new;
	new->name = strdup(str);
}

/*void	move_maillon(t_ctrl *ctrl, int old_place, int new_place)*/
/*{*/
	/*t_file	*tmp;*/
	/*t_file	*tmp_old;*/
	/*int		i;*/

	/*tmp = ctrl->first;*/
	/*i = 1;*/
	/*while (i < old_place && tmp->next)*/
	/*{*/
		/*tmp = tmp->next;*/
		/*++i;*/
		/*printf("i = %d\n", i);*/
		/*printf("name = %s\n", tmp->name);*/
	/*}*/
/*}*/

/*int	main()*/
/*{*/
	/*t_file	*list = NULL;*/
	/*t_ctrl	*ctrl = NULL;*/
	/*t_file *tmp = NULL;*/

	/*ctrl = (t_ctrl *)malloc(sizeof(ctrl));*/
	/*list = create_maillon();*/
	/*if (list == NULL || ctrl == NULL)*/
	/*{*/
		/*printf("Memory allocation failure ! (main)\n");*/
		/*exit(EXIT_FAILURE);*/
	/*}*/
	/*list->next = NULL;*/
	/*ctrl->first = list;*/
	/*list->name = strdup("un");*/
	/*add_tail(ctrl, "deux");*/
	/*add_tail(ctrl, "trois");*/
	/*add_tail(ctrl, "quatre");*/
	/*add_tail(ctrl, "cinq");*/
	/*tmp = ctrl->first;*/
	/*[>move_maillon(ctrl, 2, 3);<]*/
	/*[>while (tmp)<]*/
	/*[>{<]*/
		/*[>printf("lol = %s->\n", tmp->name);<]*/
		/*[>tmp = tmp->next;<]*/
	/*[>}<]*/
/*}*/

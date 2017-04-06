/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:16:26 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 23:18:44 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	padding_l(t_ctrl *ctrl)
{
	t_file		*tmp;
	char		**split;
	size_t		padding[8];
	int			i;

	i = -1;
	ft_memset(&padding, 0, sizeof(padding));
	while (++i < 8)
	{
		tmp = ctrl->first;
		while (tmp)
		{
			split = ft_strsplit(tmp->info, ' ');
			if (ft_strlen(split[i]) > padding[i])
				padding[i] = ft_strlen(split[i]);
			ft_2d_tab_free(split);
			tmp = tmp->next;
		}
	}
	rewrite_info_padded(ctrl, padding);
}

void	rewrite_info_padded_2(t_file *tmp, char **split, size_t *padding, int i)
{
	if (i == 0)
		padding_permissions(tmp, split[i]);
	else if (i == 1)
		padding_nb_links(tmp, split[i], padding[i]);
	else if (i == 2)
		padding_user(tmp, split[i], padding[i]);
	else if (i == 3)
		padding_group(tmp, split[i], padding[i]);
	else if (i == 4)
	{
		if (ft_strchr(split[i], '|') != NULL)
			padding_minus_major(tmp, split[i]);
		else
			padding_size(tmp, split[i], padding[i]);
	}
	else if (i == 5)
		padding_month(tmp, split[i], padding[i]);
	else if (i == 6)
		padding_day(tmp, split[i], padding[i]);
	else if (i == 7)
		padding_hour(tmp, split[i], padding[i]);
}

void	rewrite_info_padded(t_ctrl *ctrl, size_t *padding)
{
	t_file		*tmp;
	char		**split;
	int			i;

	tmp = ctrl->first;
	while (tmp)
	{
		i = 0;
		split = ft_strsplit(tmp->info, ' ');
		ft_memset(tmp->info, 0, sizeof(tmp->info));
		while (split[i])
		{
			rewrite_info_padded_2(tmp, split, padding, i);
			++i;
		}
		if (tmp->info[10] == '|')
			tmp->info[10] = ' ';
		tmp = tmp->next;
		ft_2d_tab_free(split);
	}
}

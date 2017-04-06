/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:16:26 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 21:36:32 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

static void	padding_permissions(t_file *tmp, char *split)
{
	ft_strcat(tmp->info, split);
	if (ft_strlen(split) == 10)
		ft_strcat(tmp->info, " ");
	ft_strcat(tmp->info, " ");
}

static void	padding_nb_links(t_file *tmp, char *split, size_t padding)
{
	ft_strxcat(tmp->info, " ", padding - ft_strlen(split));
	ft_strcat(tmp->info, split);
	ft_strcat(tmp->info, " ");
}

void	padding_user(t_file *tmp, char *split, size_t padding)
{
	ft_strcat(tmp->info, split);
	ft_strxcat(tmp->info, " ", padding - ft_strlen(split));
	ft_strcat(tmp->info, " ");
	ft_strcat(tmp->info, " ");
}

void	padding_group(t_file *tmp, char *split, size_t padding)
{
	ft_strcat(tmp->info, split);
	ft_strxcat(tmp->info, " ", padding - ft_strlen(split));
	ft_strcat(tmp->info, " ");
	ft_strcat(tmp->info, " ");
}

void	padding_size(t_file *tmp, char *split, size_t padding)
{
	ft_strxcat(tmp->info, " ", padding - ft_strlen(split));
	ft_strcat(tmp->info, split);
	ft_strcat(tmp->info, " ");
}

void	padding_month(t_file *tmp, char *split, size_t padding)
{
	ft_strxcat(tmp->info, " ", padding - ft_strlen(split));
	ft_strcat(tmp->info, split);
	ft_strcat(tmp->info, " ");
}

void	padding_day(t_file *tmp, char *split, size_t padding)
{
	padding = 2;

	ft_strxcat(tmp->info, " ", padding - ft_strlen(split));
	ft_strcat(tmp->info, split);
	ft_strcat(tmp->info, " ");
}

void	padding_hour(t_file *tmp, char *split, size_t padding)
{
	if (ft_strcmp(split, "10000") == 0)
		ft_strcat(tmp->info, " ");
	if (ft_strlen(split) == 4)
		ft_strcat(tmp->info, " ");
	else
		ft_strxcat(tmp->info, " ", padding - ft_strlen(split));
	ft_strcat(tmp->info, split);
	ft_strcat(tmp->info, " ");
}

void	padding_minus_major(t_file *tmp, char *split, size_t padding)
{
	int		i;
	char	**split_minor;

	i = 0;
	ft_strcat(tmp->info, " ");
	split_minor = ft_strsplit(split, ',');
	if (ft_strlen(split_minor[0]) == 1)
		ft_strcat(tmp->info, " ");
	ft_strcat(tmp->info, split_minor[0]);
	ft_strcat(tmp->info, ",");
	if (ft_strlen(split_minor[1]) == 1)
		ft_strxcat(tmp->info, " ", 3);
	else if (ft_strlen(split_minor[1]) == 2)
		ft_strxcat(tmp->info, " ", 2);
	else if (ft_strlen(split_minor[1]) == 3)
		ft_strxcat(tmp->info, " ", 1);
	while (split_minor[i])
	{
		if (split_minor[1][i] == '|')
			split_minor[1][i] = ' ';
		++i;
	}
	ft_strcat(tmp->info, split_minor[1]);
	ft_strcat(tmp->info, " ");
	ft_2d_tab_free(split_minor);
	(void)padding;
}

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
					padding_minus_major(tmp, split[i], padding[i]);
				else
					padding_size(tmp, split[i], padding[i]);
			}
			else if (i == 5)
				padding_month(tmp, split[i], padding[i]);
			else if (i == 6)
				padding_day(tmp, split[i], padding[i]);
			else if (i == 7)
				padding_hour(tmp, split[i], padding[i]);
			++i;
		}
		if (tmp->info[10] == '|')
			tmp->info[10] = ' ';
		tmp = tmp->next;
		ft_2d_tab_free(split);
	}
}

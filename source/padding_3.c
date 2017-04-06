/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 23:16:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 23:19:52 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	padding_permissions(t_file *tmp, char *split)
{
	ft_strcat(tmp->info, split);
	if (ft_strlen(split) == 10)
		ft_strcat(tmp->info, " ");
	ft_strcat(tmp->info, " ");
}

void	padding_nb_links(t_file *tmp, char *split, size_t padding)
{
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

void	padding_minus_major(t_file *tmp, char *split)
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
}

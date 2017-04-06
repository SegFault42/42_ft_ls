/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_@.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 23:14:13 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 23:16:00 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

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

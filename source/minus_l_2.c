/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus_l_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 22:17:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 22:20:24 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	get_size(char **info, struct stat *file_stat)
{
	int		six_month;
	char	*itoa;

	six_month = 15778476;
	itoa = ft_itoa(file_stat->st_size);
	ft_strcat(*info, itoa);
	ft_strdel(&itoa);
	ft_strcat(*info, " ");
}

void	get_time(char **info, struct stat *file_stat)
{
	char	**split;
	int		six_month;

	six_month = 15778476;
	split = ft_strsplit(ctime(&file_stat->st_mtime), ' ');
	ft_strcat(*info, split[1]);
	ft_strcat(*info, " ");
	ft_strcat(*info, split[2]);
	ft_strcat(*info, " ");
	if (file_stat->st_mtime > time(0))
		ft_strccat(*info, split[4], '\n');
	else if (file_stat->st_mtime < (time(0) - six_month))
		ft_strccat(*info, split[4], '\n');
	else
		ft_strncat(*info, split[3], 5);
	ft_strcat(*info, " ");
	ft_2d_tab_free(split);
}

void	get_major_minor(char **info, struct stat *file_stat)
{
	char	*itoa;

	if (S_ISLNK(file_stat->st_mode) != 1)
	{
		itoa = ft_itoa(major(file_stat->st_rdev));
		ft_strcat(*info, itoa);
		ft_strdel(&itoa);
		ft_strcat(*info, ",|");
	}
	else
		ft_strxcat(*info, " ", 7);
	itoa = ft_itoa(minor(file_stat->st_rdev));
	ft_strcat(*info, itoa);
	ft_strdel(&itoa);
	ft_strcat(*info, " ");
}

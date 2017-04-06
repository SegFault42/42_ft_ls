/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 21:30:34 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 21:30:49 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

extern t_argp	g_argp[];

uint8_t	is_reg_or_dir(char *argument)
{
	struct stat	file_stat;

	if (lstat(argument, &file_stat) < 0 || stat(argument, &file_stat) < 0)
		return (-1);
	if (S_ISDIR(file_stat.st_mode))
		return (DIRE);
	return (REG);
}

bool	check_minus_a(struct dirent *content_dir)
{
	if (g_argp[MINUS_A].active == 0)
	{
		if (content_dir->d_name[0] == HIDE_FILE)
			return (true);
	}
	return (false);
}

uint8_t	check_file_type(char *argument)
{
	if (is_reg_or_dir(argument) == REG)
		return (REG);
	return (DIRE);
}

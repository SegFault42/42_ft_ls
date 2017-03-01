/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:26:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/01 16:21:59 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int8_t	no_param(t_ctrl *ctrl)
{
	DIR				*directory;
	struct dirent	*content_dir;

	directory = NULL;
	content_dir = NULL;
	if ((directory = opendir(".")) == NULL)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (EXIT_ERROR);
	}
	while ((content_dir = readdir(directory)) != NULL)
	{
		if (content_dir->d_name[0] == '.')
			continue ;
		/*ft_dprintf(1, "d_ino = %d\n", content_dir->d_ino);*/
		/*ft_dprintf(1, "d_off = %d\n", content_dir->d_off);*/
		/*ft_dprintf(1, "reclen = %d\n", content_dir->d_reclen);*/
		add_tail(ctrl, content_dir->d_name);
		/*ft_dprintf(1, "type = %d\n", content_dir->d_type);*/
	}
	return (EXIT_SUCCESS);
}

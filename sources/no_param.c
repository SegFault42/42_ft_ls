/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:26:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/28 22:32:03 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int8_t	no_param(t_ctrl *ctrl)
{
	DIR				*directory;
	struct dirent	*content_dir;
	t_file			*tmp;

	directory = NULL;
	content_dir = NULL;
	tmp = ctrl->first;
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
		tmp->name = ft_strdup(content_dir->d_name);
		add_tail(ctrl, NULL);
		tmp = tmp->next;
		/*ft_dprintf(1, "type = %d\n", content_dir->d_type);*/
	}
	return (EXIT_SUCCESS);
}

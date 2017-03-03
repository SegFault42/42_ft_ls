/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:26:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/03 19:24:49 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

bool	who_is_first(char *new_node, char *str)
{
	int	i;

	i = 0;
	while (new_node[i] || str[i])
	{
		if (new_node[i] != str[i])
		{
			if (new_node[i] < str[i])
				return (true); // renvoie true si new_node est plus petit
			else
				return (false);// renvoie false si new_node est plus grand
		}
		++i;
	}
	return (true);
}

void	sort_lst(t_ctrl *ctrl, char *str)
{
	t_file	*tmp;
	int		node;
	bool	lol;

	node = 1;
	tmp = ctrl->first;
	while (tmp)
	{
		if ((lol = who_is_first(str, tmp->name)) == true)
		{
			add_after(ctrl, node, str);
			break ;
		}
		++node;
		tmp = tmp->next;
	}
}

int8_t	no_param(t_ctrl *ctrl)
{
	DIR				*directory;
	struct dirent	*content_dir;
	int				i;

	i = 0;
	directory = NULL;
	content_dir = NULL;
	if ((directory = opendir(".")) == NULL)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (EXIT_ERROR);
	}
	while ((content_dir = readdir(directory)) != NULL)
	{
		printf(CYAN"%s\n"END, content_dir->d_name);
		if (content_dir->d_name[0] == '.')
			continue ;
		/*ft_dprintf(1, "d_ino = %d\n", content_dir->d_ino);*/
		/*ft_dprintf(1, "d_off = %d\n", content_dir->d_off);*/
		/*ft_dprintf(1, "reclen = %d\n", content_dir->d_reclen);*/
		/*ft_dprintf(1, "type = %d\n", content_dir->d_type);*/
		if (i == 0)
		{
			add_tail(ctrl, content_dir->d_name);
			++i;
			continue ;
		}
		sort_lst(ctrl, content_dir->d_name);
		++i;
	}
	return (EXIT_SUCCESS);
}

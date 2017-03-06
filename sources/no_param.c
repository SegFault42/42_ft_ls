/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_param.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 15:26:57 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/04 21:14:10 by rabougue         ###   ########.fr       */
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
			if (new_node[i] > str[i])
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
	int		i;

	tmp = ctrl->first;
	node = 1;
	i = 0;
	if (tmp == NULL)
	{
		add_head(ctrl, str);
		return ;
	}
	while (tmp)
	{
		while (str[i] && str[i] == tmp->name[i])
			++i;
		if (str[i] < tmp->name[i])
		{
			add_before(ctrl, node, str);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, str);
			return ;
		}
		i = 0;
		while (str[i] && str[i] == tmp->next->name[i])
			++i;
		if (str[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, str);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

int8_t	no_param(t_ctrl *ctrl, t_env *env)
{
	DIR				*directory;
	struct dirent	*content_dir;
	int				i;

	i = 0;
	directory = NULL;
	content_dir = NULL;
	ft_dprintf(1, "sign = %s active = %d\n", g_argp[0].sign,  g_argp[0].active);
	if ((directory = opendir(".")) == NULL)
	{
		ft_dprintf(2, "%s\n", strerror(errno));
		return (EXIT_ERROR);
	}
	while ((content_dir = readdir(directory)) != NULL)
	{
		if (g_argp[0].active == 0)
		{
			if (content_dir->d_name[0] == '.')
				continue ;
		}
		sort_lst(ctrl, content_dir->d_name);
		++i;
	}
	return (EXIT_SUCCESS);
	(void)env;
}

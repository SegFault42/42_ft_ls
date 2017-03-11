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

void	sort_lst(t_ctrl *ctrl, struct dirent *content_dir)
{
	t_file	*tmp;
	int		node;
	int		i;

	tmp = ctrl->first;
	node = 1;
	i = 0;
	if (tmp == NULL)
	{
		add_head(ctrl, content_dir->d_name);
		return ;
	}
	while (tmp)
	{
		while (content_dir->d_name[i] && content_dir->d_name[i] == tmp->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->name[i])
		{
			add_before(ctrl, node, content_dir->d_name);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, content_dir->d_name);
			return ;
		}
		i = 0;
		while (content_dir->d_name[i] && content_dir->d_name[i] == tmp->next->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, content_dir->d_name);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

int8_t	get_files(t_ctrl *ctrl, t_env *env, char *cur_dir)
{
	struct dirent	*content_dir;
	DIR				*directory;

	directory = NULL;
	content_dir = NULL;
	if ((directory = opendir(cur_dir)) == NULL)
	{
		/*ft_dprintf(2, "%s\n", strerror(errno));*/
		/*return (EXIT_ERROR);*/
		ft_dprintf(2, "ls: %s: %s\n", cur_dir, strerror(errno));
		return (EXIT_FAILURE);
	}
	while ((content_dir = readdir(directory)) != NULL)
	{
		if (g_argp[MINUS_A].active == 0)
		{
			if (content_dir->d_name[0] == HIDE_FILE)
				continue ;
		}
		/*if (g_argp[UPPER_R].active == 1 && content_dir->d_type == DT_DIR)*/
			/*get_files(ctrl, env, content_dir->d_name);*/
		sort_lst(ctrl, content_dir);
	}
	if (closedir(directory) == -1)
	{
		ft_dprintf(STDERR_FILENO, RED"%s\n"END, strerror(errno));
		exit(EXIT_FAILURE);
	}
	print_list(ctrl);
	free_list(ctrl);
	return (EXIT_SUCCESS);
	(void)env;
}

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

char	*get_path(char *cur_dir)
{
	char	*path;
	int		i;

	i = ft_strlen(cur_dir) -1 ;
	path = NULL;
	while (cur_dir[i] != '/' && i > 0)
	{
		--i;
	}
	if (i == 0)
		path = ft_strdup(".");
	else
		path = ft_strndup(cur_dir, i);
	return (path);
}

char	*get_files_name(char *cur_dir)
{
	char	*file;
	int		i;

	i = ft_strlen(cur_dir) -1 ;
	file = NULL;
	while (cur_dir[i] != '/' && i > 0)
	{
		--i;
	}
	if (i == 0)
		file = ft_strdup(cur_dir);
	else
		file = ft_strdup(&cur_dir[i] + 1);
	return (file);
}

bool	is_regular_file(char *cur_dir)
{
	struct stat		file_stat;
	struct dirent	*content_dir;
	DIR				*directory;
	char			*path;
	char			*file;

	directory = NULL;
	content_dir = NULL;
	path = NULL;
	if (stat(cur_dir, &file_stat) < 0)
	{
		ft_error(-1);
		exit(EXIT_FAILURE);
	}
	if (S_ISREG(file_stat.st_mode))
		path = get_path(cur_dir);
	else
		return (EXIT_FAILURE);
	if ((directory = opendir(path)) == NULL)
	{
		ft_dprintf(2, "ls: %s: %s\n", cur_dir, strerror(errno));
		return (EXIT_FAILURE);
	}
	file = get_files_name(cur_dir);
	while ((content_dir = readdir(directory)))
	{
		if (ft_strcmp(content_dir->d_name, file) == 0)
		{
			ft_dprintf(1, "%s\n", content_dir->d_name);
			break ;
		}
	}
	ft_strdel(&path);
	ft_strdel(&file);
	return (EXIT_SUCCESS);
}

bool	is_directory(t_ctrl *ctrl, char *cur_dir)
{
	struct dirent	*content_dir;
	DIR				*directory;

	directory = NULL;
	content_dir = NULL;
	if ((directory = opendir(cur_dir)) == NULL)
	{
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
	if (g_argp[MINUS_R].active == 0)
		print_list(ctrl);
	else
		print_list_reverse(ctrl);
	free_list(ctrl);
	return (EXIT_SUCCESS);
}

int8_t	get_files(t_ctrl *ctrl, t_env *env, char *cur_dir)
{
	/*if (is_regular_file(cur_dir) == EXIT_SUCCESS)*/
		/*return (EXIT_SUCCESS);*/
	/*else*/
		is_directory(ctrl, cur_dir);
	return (EXIT_SUCCESS);
	(void)env;
}

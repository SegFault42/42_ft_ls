#include "../include/ft_ls.h"

void	sort_lst_dir(t_ctrl *ctrl, char *path)
{
	t_file	*tmp;
	int	i;
	int	node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
	{
		add_head(ctrl, path);
		return ;
	}
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] < tmp->name[i])
		{
			add_before(ctrl, node, path);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, path);
			return ;
		}
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, path);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

void	sort_lst_dir_rev(t_ctrl *ctrl, char *path)
{
	t_file	*tmp;
	int	i;
	int	node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
	{
		add_head(ctrl, path);
		return ;
	}
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] > tmp->name[i])
		{
			add_before(ctrl, node, path);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, path);
			return ;
		}
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] > tmp->next->name[i])
		{
			add_after(ctrl, node, path);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
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

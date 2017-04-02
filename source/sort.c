#include "../include/ft_ls.h"

void	sort_by_time(t_ctrl *ctrl, size_t value, char *name)
{
	t_file	*tmp;
	int	i;
	int	node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
	{
		add_head(ctrl, name, value);
		return ;
	}
	while (tmp)
	{
		if (value > tmp->timestamp)
		{
			add_before(ctrl, node, name, value);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, name, value);
			return ;
		}
		if (value > tmp->next->timestamp)
		{
			add_after(ctrl, node, name, value);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
	
}

void	sort_lst_file(t_ctrl *ctrl, char *name)
{
	t_file	*tmp;
	int	i;
	int	node;

	node = 1;
	i = 0;
	tmp = ctrl->first;
	if (tmp == NULL)
	{
		add_head(ctrl, name, 0);
		return ;
	}
	while (tmp)
	{
		while (name[i] && name[i] == tmp->name[i])
			++i;
		if (name[i] < tmp->name[i])
		{
			add_before(ctrl, node, name, 0);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, name, 0);
			return ;
		}
		i = 0;
		while (name[i] && name[i] == tmp->next->name[i])
			++i;
		if (name[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, name, 0);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

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
		add_head(ctrl, path, 0);
		return ;
	}
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] < tmp->name[i])
		{
			add_before(ctrl, node, path, 0);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, path, 0);
			return ;
		}
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, path, 0);
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
		add_head(ctrl, path, 0);
		return ;
	}
	while (tmp)
	{
		while (path[i] && path[i] == tmp->name[i])
			++i;
		if (path[i] > tmp->name[i])
		{
			add_before(ctrl, node, path, 0);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, path, 0);
			return ;
		}
		i = 0;
		while (path[i] && path[i] == tmp->next->name[i])
			++i;
		if (path[i] > tmp->next->name[i])
		{
			add_after(ctrl, node, path, 0);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

void	sort_lst(t_ctrl *ctrl, struct dirent *content_dir, char *link)
{
	t_file	*tmp;
	int		node;
	int		i;

	tmp = ctrl->first;
	node = 1;
	i = 0;
	if (tmp == NULL)
	{
		add_head(ctrl, content_dir->d_name, 0);
		if (link != NULL)
			fill_node(ctrl, node, link);
		return ;
	}
	while (tmp)
	{
		while (content_dir->d_name[i] && content_dir->d_name[i] == tmp->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->name[i])
		{
			add_before(ctrl, node, content_dir->d_name, 0);
			if (link != NULL)
				fill_node(ctrl, node, link);
			return ;
		}
		else if (tmp->next == NULL)
		{
			add_tail(ctrl, content_dir->d_name, 0);
			if (link != NULL)
				fill_node(ctrl, -1, link);
			return ;
		}
		i = 0;
		while (content_dir->d_name[i] && content_dir->d_name[i] == tmp->next->name[i])
			++i;
		if (content_dir->d_name[i] < tmp->next->name[i])
		{
			add_after(ctrl, node, content_dir->d_name, 0);
			if (link != NULL)
				fill_node(ctrl, node, link);
			return ;
		}
		tmp = tmp->next;
		++node;
	}
}

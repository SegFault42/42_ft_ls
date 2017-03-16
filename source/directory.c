#include "../include/ft_ls.h"

#define REG 0
#define DIRE 1

extern t_argp	g_argp[];

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

uint8_t	check_file_type(char *argument)
{
	uint8_t	ret;

	if ((ret = is_reg_or_dir(argument)) == REG)
		return (REG);
	return (DIRE);
}

/*char	*get_path(char *cur_dir)*/
/*{*/
	/*char	*path;*/
	/*int		i;*/

	/*i = ft_strlen(cur_dir) -1 ;*/
	/*path = NULL;*/
	/*while (cur_dir[i] != '/' && i > 0)*/
	/*{*/
		/*--i;*/
	/*}*/
	/*if (i == 0)*/
		/*path = ft_strdup(".");*/
	/*else*/
		/*path = ft_strndup(cur_dir, i);*/
	/*return (path);*/
/*}*/

void	print_directory(char *directory)
{
	struct dirent	*content_dir;
	DIR				*dir;
	t_ctrl			ctrl;

	content_dir = NULL;
	dir = NULL;
	ft_memset(&ctrl, 0, sizeof(t_ctrl));
	if ((dir = opendir(directory)) == NULL)
	{
		ft_dprintf(2, "ls: %s: %s\n", directory, strerror(errno));
		return ;
	}
	while ((content_dir = readdir(dir)) != NULL)
	{
		if (g_argp[MINUS_A].active == 0)
		{
			if (content_dir->d_name[0] == HIDE_FILE)
				continue ;
		}
		/*if (content_dir->d_type == DT_DIR && g_argp[UPPER_R].active == 1)*/
		/*{*/
			/*ft_dprintf(1, "name = %s, type = %d\n", content_dir->d_name, content_dir->d_type);*/
			/*sleep(1);*/
			/*print_directory(content_dir->d_name);*/
		/*}*/
		sort_lst(&ctrl, content_dir);
	}
	if (closedir(dir) == -1)
	{
		ft_dprintf(STDERR_FILENO, RED"%s\n"END, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (ctrl.first != NULL)
	{
		if (g_argp[MINUS_R].active == 0)
			print_list(&ctrl);
		else
			print_list_reverse(&ctrl);
	}
}


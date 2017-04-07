/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_argv_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 04:50:37 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 04:53:17 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	sort_param(char **arguments)
{
	char	*tmp;
	int		find;
	int		i;

	find = 1;
	while (find)
	{
		find = 0;
		i = 0;
		while (arguments[i + 1])
		{
			if (ft_strcmp(arguments[i], arguments[i + 1]) > 0)
			{
				tmp = arguments[i];
				arguments[i] = arguments[i + 1];
				arguments[i + 1] = tmp;
				find = 1;
			}
			++i;
		}
	}
}

void	directory_2(char **argv, t_ctrl *ctrl, int j)
{
	int			ret;
	int			i;
	struct stat	file_stat;

	i = j;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 2 && ft_strcmp(argv[i], "--") == 0)
		{
			++i;
			continue ;
		}
		if ((ret = lstat(argv[i], &file_stat)) < 0)
			sort_lst_file(ctrl, argv[i]);
		++i;
	}
}

void	print_no_such_file_or_directory(char **argv)
{
	t_ctrl		*ctrl;
	int			i;

	i = 1;
	if ((ctrl = (t_ctrl *)malloc(sizeof(t_ctrl))) == NULL)
		ft_critical_error(MALLOC_ERROR);
	ft_memset(ctrl, 0, sizeof(t_ctrl));
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 2 && ft_strcmp(argv[i], "--") == 0)
		{
			++i;
			break ;
		}
		else if (argv[i][0] == '-')
			++i;
		else
			break ;
	}
	directory_2(argv, ctrl, i);
	print_list_no_such(ctrl);
	free_list(ctrl);
}

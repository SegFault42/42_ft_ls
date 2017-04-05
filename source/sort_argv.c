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

static int		count_where_is_first_file_2(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '-')
			break ;
		if (ft_strcmp(argv[i], "--") == 0)
		{
			++i;
			break ;
		}
		++i;
	}
	return (i);
}

static int		count_where_is_first_file(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && ft_strcmp(argv[i], "--") != 0)
	{
		if (argv[i][0] != '-')
			break ;
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '-')
			break ;
		++i;
	}
	if (argv[i] != NULL && ft_strcmp(argv[i], "--") == 0)
		++i;
	return (i);
}

/*
** stock tout les fichier regulier dans env->files et tout les dossiers dans
** env->directory
*/

static void	stock_reg_and_dir(t_env *env, char **argv, int argc)
{
	int		first_file;
	int		cp_first_file;
	int		i;
	int		j;
	int		nb_file;
	uint8_t	ret;

	i = -1;
	j = -1;
	first_file = count_where_is_first_file(argv);
	cp_first_file = first_file;
	nb_file = argc - first_file;
	env->files = (char **)malloc(sizeof(char *) * nb_file + 1);
	env->directory = (char **)malloc(sizeof(char *) * nb_file + 1);
	if (env->files == NULL || env->directory == NULL)
		ft_critical_error(MALLOC_ERROR);
	ft_set_2d_tab(env->files, nb_file + 1);
	ft_set_2d_tab(env->directory, nb_file + 1);
	while (argv[cp_first_file])
	{
		if ((ret = is_reg_or_dir(argv[cp_first_file])) == REG)
		{
			env->files[++i] = argv[cp_first_file];
		}
		else if (ret == DIRE)
			env->directory[++j] = argv[cp_first_file];
		++cp_first_file;
	}
}

void	print_no_such_file_or_directory(char **argv)
{
	struct stat	file_stat;
	t_ctrl		*ctrl;
	int			i;
	int			ret;

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
	print_list_no_such(ctrl);
	free_list(ctrl);
}

void		sort_argv(t_env *env, char **argv, int argc)
{
	int	first_file;

	first_file = count_where_is_first_file_2(argv);
	if (argc - first_file > 1)
		env->nb_args = 1;
	/*ft_dprintf(1, "%d\n", argc - first_file);*/
	if ((count_where_is_first_file(argv) - argc) == 0)
	{
		stock_reg_and_dir(env, argv, argc + 1);
		env->directory[0] = ft_strdup(".");
	}
	else
		stock_reg_and_dir(env, argv, argc);
	if (env->files[0] != NULL)
		sort_param(env->files);
	if (env->directory[0] != NULL)
		sort_param(env->directory);
}

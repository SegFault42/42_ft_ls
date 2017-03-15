#include "../include/ft_ls.h"

#define DIR 1
#define REG 0

char	**sort_param(char **arguments, int argc)
{
	char	*tmp;
	int		find;
	int		i;

	find = 1;
	while (find)
	{
		find = 0;
		i = -1;
		while (++i < argc - 1)
		{
			if (ft_strcmp(arguments[i], arguments[i + 1]) > 0)
			{
				tmp = arguments[i];
				arguments[i] = arguments[i + 1];
				arguments[i + 1] = tmp;
				find = 1;
			}
		}
	}
	return (arguments);
}

static int		count_where_is_first_file(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && ft_strcmp(argv[i], "--") != 0)
	{
		if (argv[i][0] != '-')
			break ;
		++i;
	}
	if (argv[i] != NULL && ft_strcmp(argv[i], "--") == 0)
		++i;
	return (i);
}

uint8_t	is_reg_or_dir(char *argument)
{
	struct stat	file_stat;

	if (stat(argument, &file_stat) < 0)
	{
		ft_dprintf(1, "ft_ls: %s: %s\n", argument, strerror(errno));
		return (-1);
	}
	if (S_ISDIR(file_stat.st_mode))
		return (DIR);
	return (REG);
}

void	stock_reg_and_dir(t_env *env, char **argv, int argc)
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
	ft_set_2d_tab(env->files, nb_file + 1);
	ft_set_2d_tab(env->directory, nb_file + 1);
	while (argv[cp_first_file])
	{
		if ((ret = is_reg_or_dir(argv[cp_first_file])) == REG)
			env->files[++i] = argv[cp_first_file];
		else if (ret == DIR)
			env->directory[++j] = argv[cp_first_file];
		++cp_first_file;
	}
}

void	sort_argv(t_env *env, char **argv, int argc)
{
	stock_reg_and_dir(env, argv, argc);
	ft_dprintf(1, "files :\n");
	int	k = 0;
	while (env->files[k])
	{
		ft_dprintf(1, "%s\n", env->files[k]);
		++k;
	}
	RC;
	ft_dprintf(1, "directory :\n");
	k = 0;
	while (env->directory[k])
	{
		ft_dprintf(1, "%s\n", env->directory[k]);
		++k;
	}
}

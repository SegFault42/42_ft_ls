#include "../include/ft_ls.h"

char			*check_if_arg_only_option(char **arguments)
{
	int	i;
	int	other;
	char	*dir;

	i = 0;
	other = 0;
	dir = NULL;
	while (arguments[i])
	{
		if (arguments[i][0] != OPTION_VALUE)
		{
			++other;
			if (other > 1)
			{
				ft_strdel(&dir);
				return (NULL);
			}
			if ((dir = ft_strdup(arguments[i])) == NULL)
				ft_error(MALLOC_ERROR);
		}
		++i;
	}
	if (dir == NULL)
		if ((dir = ft_strdup(".")) == NULL)
			ft_error(MALLOC_ERROR);
	return (dir);
}

int	count_nb_file(char **arguments)
{
	int	i;
	int	nb_file;

	i = 0;
	nb_file = 0;
	if (arguments == NULL)
		return (0);
	while (arguments[i])
	{
		if (arguments[i][0] != OPTION_VALUE)
			++nb_file;
		++i;
	}
	return (nb_file);
}

void	one_or_no_file(t_ctrl *ctrl, t_env *env, char **arguments, int nb_file)
{
	int i;

	i = 0;
	if (nb_file == 0)
	{
		if (get_files(ctrl, env, ".") == EXIT_ERROR)
			exit (EXIT_FAILURE);
	}
	else
	{
		while (arguments[i])
		{
			if (arguments[i][0] != OPTION_VALUE)
				if (get_files(ctrl, env, arguments[i]) == EXIT_ERROR)
					exit (EXIT_FAILURE);
			++i;
		}
	}
}

bool	only_option(char **arguments, t_ctrl *ctrl, t_env *env)
{
	char	*dir;
	int		nb_file;
	int		i;

	dir = NULL;
	i = 0;
	nb_file = count_nb_file(arguments);
	if (nb_file < 2)
		one_or_no_file(ctrl, env, arguments, nb_file);
	else
	{
		while (arguments[i])
		{
			if (arguments[i][0] != OPTION_VALUE)
			{
				ft_dprintf(1, "%s:\n", arguments[i]);
				if (get_files(ctrl, env, arguments[i]) == EXIT_ERROR)
					exit (EXIT_FAILURE);
				--nb_file;
				if (nb_file > 0)
					ft_dprintf(1, "\n");
			}
			++i;
		}
	}
		return (EXIT_SUCCESS);
	/*}*/
}

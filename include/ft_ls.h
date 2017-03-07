/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:46:45 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/04 15:52:48 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include "../libft/includes/libft.h"

# define	MINUS_ONE	1
# define	MINUS_A		2

# define	SIZE_ARGP	(6)
# define	HIDE_FILE	'.'

typedef struct	s_file
{
	char		*name;
	uint8_t		type;
	struct s_file	*next;
}				t_file;

typedef struct	s_ctrl
{
	t_file		*first;
}				t_ctrl;

typedef struct	s_env
{
	uint8_t		arg_value;
}				t_env;

typedef struct	s_argp
{
	char		*sign;
	bool		active;
	char		*description;
}				t_argp;

t_argp	g_argp[SIZE_ARGP];
//{
	//{"a", 0, "print hide file"},
	//{"1", 0, "One file per line"},
	//{"R", 0, "list subdirectory recursively"},
	//{"r", 0, "reverse sort"},
	//{"t", 0, "sort by time (new first)"},
	//{"l", 0, "print full info"},
	//{0, 0, 0}
//};

/*
** no_param.c
*/
bool			who_is_first(char *new_node, char *str);
int8_t			no_param(t_ctrl *ctrl, t_env *env);
void			sort_lst(t_ctrl *ctrl, char *str);
/*
** lst.c
*/
void			add_before(t_ctrl *ctrl, int node, char *name);
bool			add_after(t_ctrl *ctrl, int node, char *str);
void			add_head(t_ctrl *ctrl, char *str);
void			add_tail(t_ctrl *ctrl, char *str);
void			free_maillon(t_ctrl *ctrl);
t_file			*create_maillon();
/*
** parse_arguments.c
*/
void			fill_argp(char *param, char *description, int index);
uint8_t			parse_arg(char **argv);
void			init_argp();
void			free_argp();



void			print_list(t_ctrl *ctrl);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:46:45 by rabougue          #+#    #+#             */
/*   Updated: 2017/03/02 15:52:37 by rabougue         ###   ########.fr       */
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

# define	L_MIN	1
# define	R_UP	2
# define	A_MIN	4
# define	R_MIN	8
# define	T_MIN	16

typedef struct	s_file
{
	char		*name;
	struct s_file		*next;
}				t_file;

typedef struct	s_ctrl
{
	t_file		*first;
}				t_ctrl;

typedef struct	s_env
{
	uint8_t		arg_value;
}				t_env;

int8_t	no_param();

/*
** lst.c
*/
void			add_head(t_ctrl *ctrl, char *str);
void			add_tail(t_ctrl *ctrl, char *str);
t_file			*create_maillon();
t_file			*create_first_maillon(t_ctrl *ctrl);
void			free_maillon(t_ctrl *ctrl);
bool			add_after(t_ctrl *ctrl, int node, char *str);

int8_t			no_param(t_ctrl *ctrl);

#endif

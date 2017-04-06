/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:46:45 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 19:20:02 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <errno.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "../libft/includes/libft.h"

# define MINUS_A		(0)
# define ONE			(1)
# define UPPER_R		(2)
# define MINUS_R		(3)
# define MINUS_T		(4)
# define MINUS_L		(5)
# define END_OPTION		(6)
# define UPPER_A		(7)
# define MINUS_P		(8)

# define SIZE_ARGP		(7)

# define HIDE_FILE		'.'
# define OPTION_VALUE	'-'

# define REG			(0)
# define DIRE			(1)

# define TIMESTAMP		(0)

typedef struct		s_file
{
	char			*name;
	size_t			timestamp;
	char			*info;
	char			*link;
	struct s_file	*next;
}					t_file;

typedef struct		s_ctrl
{
	t_file			*first;
}					t_ctrl;

typedef struct		s_env
{
	char			**files;
	char			**directory;
	t_file			file;
	size_t			nb_blocks;
	bool			nb_args;
}					t_env;

typedef struct		s_argp
{
	char			*sign;
	bool			active;
	char			*description;
}					t_argp;

/*
** **********************************init.c************************************
*/
void				init(t_ctrl *ctrl, t_env *env);
/*
** ******************************parsing_argv.c********************************
*/
void				get_option(char **argv);
/*
** ********************************sort_argv.c*********************************
*/
void				sort_argv(t_env *env, char **argv, int argc);
void				sort_param(char **arguments);
/*
** ********************************sort_argv.c*********************************
*/
void				quit(t_env *env, int argc);
/*
** ************************************print.c*********************************
*/
void				print(t_env *env);
/*
** **************************************lst.c*********************************
*/
void				print_lst(t_ctrl *ctrl);
void				print_list(t_ctrl *ctrl);
void				print_list_reverse(t_ctrl *ctrl);
void				free_list(t_ctrl *ctrl);
void				free_maillon(t_ctrl *ctrl);
t_file				*create_maillon();
void				add_tail(t_ctrl *ctrl, char *str, int value);
void				add_head(t_ctrl *ctrl, char *str, int value);
bool				add_after(t_ctrl *ctrl, int node, char *name, int value);
void				add_before(t_ctrl *ctrl, int node, char *name, int value);
void				sort_lst_dir(t_ctrl *ctrl, char *path);
size_t				count_nb_node(t_ctrl *ctrl);
/*
** **********************************directory.c*******************************
*/
void				close_directory(DIR **dir);
int8_t				open_directory(DIR **dir, char *directory);
void				print_directory(char *directory, t_env *env);
void				particular_minus_t(t_ctrl *ctrl, char *directo, t_env *env);
/*
** ************************************check.c*********************************
*/
bool				check_minus_a(struct dirent *content_dir);
uint8_t				check_file_type(char *argument);
uint8_t				is_reg_or_dir(char *argument);
/*
** ************************************recursive.c*****************************
*/
void				recursive(char *directory, t_env *env);
/*
** ************************************sort.c**********************************
*/
void				sort_lst_dir(t_ctrl *ctrl, char *path);
void				sort_by_time(t_ctrl *ctrl, size_t value, char *name);
void				sort_lst_dir_rev(t_ctrl *ctrl, char *path);
void				sort_lst(t_ctrl *ctrl, struct dirent *content, char *link);
/*
** **********************************minus_l.c*********************************
*/
void				minus_l(char *file, t_env *env);
void				padding_l(t_ctrl *ctrl);
void				fill_node(t_ctrl *ctrl, int node, char *link);
/*
** **********************************minus_l.c*********************************
*/
void				padding_l(t_ctrl *ctrl);
void				rewrite_info_padded(t_ctrl *ctrl, size_t *padding);

void				sort_lst_file(t_ctrl *ctrl, char *name);
void				print_no_such_file_or_directory(char **argv);
void				print_list_no_such(t_ctrl *ctrl);
bool				check_minus_f(struct dirent *content_dir);

#endif

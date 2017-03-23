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
# include <time.h>
# include "../libft/includes/libft.h"

# define MINUS_A		(0)
# define ONE			(1)
# define UPPER_R		(2)
# define MINUS_R		(3)
# define MINUS_T		(4)
# define MINUS_L		(5)
# define END_OPTION		(6)

# define SIZE_ARGP		(7)

# define HIDE_FILE		'.'
# define OPTION_VALUE	'-'

# define REG			(0)
# define DIRE			(1)

typedef struct		s_file
{
	char			*name; // stock le nom du fichier
	size_t			timestamp;
	struct s_file	*next;
}					t_file;

typedef struct		s_ctrl
{
	t_file			*first;
}					t_ctrl;

typedef struct		s_env
{
	//char			**arguments;
	char			**files;
	char			**directory;
}					t_env;

typedef struct		s_argp
{
	char			*sign; // option
	bool			active; // present ou non
	char			*description; // description de l'option
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
void				print_directory(char *directory);
/*
** ************************************check.c*********************************
*/
bool				check_minus_a(struct dirent *content_dir);
uint8_t				check_file_type(char *argument);
uint8_t				is_reg_or_dir(char *argument);
/*
** ************************************recursive.c*****************************
*/
void				recursive(char *directory);
/*
** ************************************sort.c*********************************
*/
void				sort_lst_dir(t_ctrl *ctrl, char *path);
void				sort_by_time(t_ctrl *ctrl, size_t value, char *name);
void				sort_lst_dir_rev(t_ctrl *ctrl, char *path);
void				sort_lst(t_ctrl *ctrl, struct dirent *content_dir);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:46:45 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/12 05:51:15 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"

# define	L_MIN	1
# define	R_UP	2
# define	A_MIN	4
# define	R_MIN	8
# define	T_MIN	16

typedef struct	s_env
{
	uint8_t		arg_value;
}				t_env;

#endif

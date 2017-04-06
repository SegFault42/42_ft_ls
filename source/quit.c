/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 23:46:10 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 23:46:11 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

void	quit(t_env *env, int argc)
{
	free(env->files);
	if (argc < 2)
		ft_2d_tab_free(env->directory);
	else
		free(env->directory);
}

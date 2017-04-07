/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_directory_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 03:58:36 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/07 03:59:17 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

char	*join(char *directory, char *d_name)
{
	char	*file;
	char	*tmp;

	file = ft_strjoin(directory, "/");
	tmp = ft_strdup(file);
	ft_strdel(&file);
	file = ft_strjoin(tmp, d_name);
	ft_strdel(&tmp);
	return (file);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 05:48:29 by rabougue          #+#    #+#             */
/*   Updated: 2017/02/12 06:29:26 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_ls.h"

int main(int argc, char *argv[])
{
	DIR				*directory = NULL;
	struct dirent	*content_dir = NULL;

	if (argc < 2)
		return EXIT_ERROR;
	if ((directory = opendir(argv[1])) == NULL)
	{
		ft_fprintf(2, "%s\n", strerror(errno));
		return EXIT_ERROR;
	}
	while ((content_dir = readdir(directory)) != NULL)
	{
		ft_fprintf(1, "d_ino = %d\n", content_dir->d_ino);
		ft_fprintf(1, "d_off = %d\n", content_dir->d_off);
		ft_fprintf(1, "reclen = %d\n", content_dir->d_reclen);
		ft_fprintf(1, "name = %s\n", content_dir->d_name);
		ft_fprintf(1, "type = %d\n", content_dir->d_type);
		RC;
	}
	return EXIT_SUCCESS;
}

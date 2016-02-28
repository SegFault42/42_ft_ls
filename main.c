/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/28 11:34:55 by rabougue          #+#    #+#             */
/*   Updated: 2016/02/28 12:23:44 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_ls.h"

int main(int argc, const char *argv[])
{
	DIR				*rep = NULL;
	struct dirent	*fichierlu = NULL;
	struct stat		info;
	char			file[5];
	int i = 0;

	if (argc == 1 && (rep = opendir("./")) != NULL)
	{
		while((fichierlu = readdir(rep)) != NULL)
		{
			file[i] = fichierlu->d_name;
			i++;
		}
	}
	stat(argv[1], &info);
	ft_putnbr(info.st_blocks);
	/*if (argc == 2 && (rep = opendir(argv[1])) == NULL)*/
	/*{*/
		/*perror("Error ");*/
		/*return(EXIT_FAILURE);*/
	/*}*/
	/*else if (argc == 2 && (rep = opendir(argv[1])) == NULL)*/
	/*{*/
		/*perror("Error ");*/
		/*return(EXIT_FAILURE);*/
	/*}*/
	/*while((fichierlu = readdir(rep)) != NULL)*/
		/*ft_putendl(fichierlu->d_name);*/
	if (closedir(rep) == -1)
	{
		perror("Error ");
		return(EXIT_FAILURE);
	}
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charactere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 02:51:02 by rabougue          #+#    #+#             */
/*   Updated: 2017/04/06 03:59:51 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_replace_charactere(char **str, char old_c, char new_c)
{
	int	i;

	i = -1;
	while (str[i])
	{
		ft_dprintf(1, "%c\n", *str[i]);
		if (*str[i] == old_c)
			*str[i] = new_c;
		++i;
	}
}

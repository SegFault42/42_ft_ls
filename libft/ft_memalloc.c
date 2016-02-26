/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 15:34:57 by rabougue          #+#    #+#             */
/*   Updated: 2015/12/02 16:07:38 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}

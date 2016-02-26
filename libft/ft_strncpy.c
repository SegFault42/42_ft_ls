/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 21:40:19 by rabougue          #+#    #+#             */
/*   Updated: 2015/12/15 23:30:14 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		if (src[i] == '\0')
			dst[i] = '\0';
		dst[i] = src[i];
		i++;
	}
	if (i < n)
		ft_bzero(dst + i, n - i);
	return (dst);
}

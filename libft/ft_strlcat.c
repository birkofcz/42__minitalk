/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:44:15 by sbenes            #+#    #+#             */
/*   Updated: 2023/02/02 17:22:54 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	x;

	if (!dest && size == 0)
		return (ft_strlen(src));
	i = ft_strlen(dest);
	x = 0;
	if (i >= size)
		return (ft_strlen(src) + size);
	while (i + x < size -1 && src[x] != '\0')
	{
		dest[i + x] = src[x];
		x++;
	}
	dest[i + x] = '\0';
	return (i + ft_strlen(src));
}

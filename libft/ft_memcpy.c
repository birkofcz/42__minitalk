/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 10:23:47 by sbenes            #+#    #+#             */
/*   Updated: 2023/02/01 10:30:59 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pd;
	unsigned char	*ps;
	int				i;

	i = 0;
	pd = (unsigned char *)dest;
	ps = (unsigned char *)src;
	if (!dest && !src)
		return (0);
	while (n != 0)
	{
		pd[i] = ps[i];
		i++;
		n--;
	}
	return (pd);
}

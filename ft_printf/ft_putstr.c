/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:20:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/07 14:09:18 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
ft_strlen - libft version to measure the size of string.
*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
ft_putstr - using putchar to write string on stdout. 
if no string, needs to write "(null)".
Returns the number of characters written through the ft_strlen
*/

/*
int	ft_putstr(const char *s)
{
	size_t	i;

	if (!s)
		s = "(null)";
	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (ft_strlen(s));
} 
*/

int	ft_putstr(const char *s)
{
	if (!s)
		s = "(null)";
	return (write(1, s, ft_strlen(s)));
}

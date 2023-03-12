/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:29:34 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/05 17:30:07 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
ft_putnbr_unsigned - edited putnbr function from Piscine. 
Using recursivity to parse and write numbers 
with "write" function. Negative numbers are taken 
care of simply by usig datatype unsigned int.
Number of character written mesured by incrementing 
int len and returning it.
*/

int	ft_putnbr_unsigned(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb >= 10)
	{
		len += ft_putnbr_unsigned(nb / 10);
		len += ft_putnbr_unsigned(nb % 10);
	}
	else
		len += ft_putchar(nb + 48);
	return (len);
}

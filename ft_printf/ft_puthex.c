/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:41:35 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/06 13:40:03 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
ft_putnbr_hex - converts the input to its hexadecimal value, 
checking for case indicator (%x or %X).

START
|
Setting the hex string to choose the character from,
in two variants depending on the case we want.
|
|
When bigger than 15, recursive call with a nb / 16. 
Increment len to update the characters writen.
|
write to stdout the value modulo 16 = result representing 
the index on hex string. Increment len.
|
Returns len to measure characters written.
|
END
*/

int	ft_putnbr_hex(unsigned int nb, char x)
{
	char			*hex;
	int				len;

	len = 0;
	hex = "0123456789abcdef";
	if (x == 'X')
		hex = "0123456789ABCDEF";
	if (nb >= 16)
		len += ft_putnbr_hex(nb / 16, x);
	write(1, &hex[nb % 16], 1);
	len++;
	return (len);
}

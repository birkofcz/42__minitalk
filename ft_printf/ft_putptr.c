/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:30:30 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/05 15:26:59 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
ft_putnbr_phex - putnbr variation working with base 16. 
Writes the number using string and indexes.
Incrementing int len to measure number of characters written.
*/

int	ft_putnbr_phex(unsigned long long nb)
{
	char	*hex;
	int		len;

	len = 0;
	hex = "0123456789abcdef";
	if (nb >= 16)
		len += ft_putnbr_phex(nb / 16);
	write(1, &hex[nb % 16], 1);
	len++;
	return (len);
}

/*
-- ft_putptr --

To print the memory address of a value.
Memory adress is constructed as "0x" + hexadecimal number 
representing the pointer value. 

START
|
Make sure there is ptr. If ptr = NULL, function needs 
to print "(nil)". 
Returns the n of bytes written from write.
|
Cannot get the pointer value directly, we need to cast 
(unsigned long long) to ptr and store it as unsigned 
long long ptr_value. 
Unsigned long long is int datatype ensuring that 
it will take whatever size of pointer value, which is 
system dependent. 
|
Write "0x" to the stdout. It always starts with 0x 
followed by hexadecimal number.
|
Send pointer value (ptr_value) to the function which 
will convert it to hexadecimal (base 16) and write to stdout.
|
Return number of characters printed (len - measured 
in ft_putnbr_phex) + 2 for 0x.
|
END
*/

int	ft_putptr(void *ptr)
{
	unsigned long long	ptr_value;
	int					len;

	len = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	ptr_value = (unsigned long long)ptr;
	write(1, "0x", 2);
	len = ft_putnbr_phex(ptr_value);
	return (len + 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:18:37 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/06 13:26:27 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Handle all the following conversions:
. %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.
*/

#include "ft_printf.h"

/*
ft_crossroad - crossroad to functions dependent on identifier after %.
Writes the output and returns nc_printed.
*/

int	ft_crossroad(va_list args, char identifier)
{
	int	nc_printed;

	nc_printed = 0;
	if (identifier == 'c')
		nc_printed = ft_putchar_ftp(va_arg(args, int));
	else if (identifier == 's')
		nc_printed = ft_putstr_ftp(va_arg(args, char *));
	else if (identifier == 'p')
		nc_printed = ft_putptr(va_arg(args, void *));
	else if (identifier == 'd' || identifier == 'i')
		nc_printed = ft_putnbr(va_arg(args, int));
	else if (identifier == 'u')
		nc_printed = ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (identifier == 'x' || identifier == 'X')
		nc_printed = ft_putnbr_hex(va_arg(args, unsigned int), identifier);
	else if (identifier == '%')
		nc_printed = ft_putchar_ftp('%');
	return (nc_printed);
}
/*
-- ft_printf --
Int type function, returns the number of characters 
printed to stdout (nc_printed). 
Size will differ by what is being printed after 
the % placeholder (string, char, number etc..).
Every function taking care of it writes the
actual output to stdout and return the size all 
the way up to the ft_printf.
If no % - prints the string only with putchar.
*/

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		nc_printed;
	int		i;

	i = 0;
	nc_printed = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			nc_printed = nc_printed + ft_crossroad(args, str[i + 1]);
			i++;
		}
		else
			nc_printed = nc_printed + ft_putchar_ftp(str[i]);
		i++;
	}
	va_end(args);
	return (nc_printed);
}

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
CHAR
*/

int	ft_putchar_ftp(char c)
{
	return (write(1, &c, 1));
}

/*
STRING
*/

int	ft_putstr_ftp(const char *s)
{
	if (!s)
		s = "(null)";
	return (write(1, s, ft_strlen(s)));
}
/*
NUMBER
*/

int	ft_putnbr(int nb)
{
	int		len;

	len = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (nb < 0)
	{
		ft_putchar_ftp('-');
		len++;
		nb = -nb;
		len += ft_putnbr(nb);
	}
	else if (nb >= 10)
	{
		len += ft_putnbr(nb / 10);
		len += ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar_ftp(nb + 48);
		len++;
	}
	return (len);
}

/* 
POINTER
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

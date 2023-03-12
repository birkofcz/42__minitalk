/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:39:00 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/05 15:25:36 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
ft_putnbr - my putnbr function from Piscine. 
Using recursivity to parse and write numbers with "write" function. 
Incrementing int len for every number written to get the size.
*/

int	ft_putnbr(int nb)
{
	int		len;

	len = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (nb < 0)
	{
		ft_putchar('-');
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
		ft_putchar(nb + 48);
		len++;
	}
	return (len);
}

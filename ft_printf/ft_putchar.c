/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:17:54 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/05 15:24:38 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
ft_putchar - wrute function iself returns n of bytes (chars written).
*/

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

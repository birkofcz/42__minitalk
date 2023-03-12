/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:34:31 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/12 15:38:02 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <string.h>
#include <stdio.h>
/*
CLIENT SIDE - takes arguments and sends string
*/

/*
Encoding table - converting chars to binary to use it with signals.
*/

char *ft_ctobin(int c)
{
	char	*binary;
	int i;

	binary = (char *)malloc(9 * sizeof(char));
	if (!binary)
		return (NULL);
	binary[8] = '\0';
	i = 0;
	while (i < 8)
    {
        binary[7 - i] = (c % 2) + '0';
        c = c / 2;
        i++;
    }
    return (binary);
}

char	ft_bintoc(char *binary) {
    
	int decimal = 0;
	int i = 0;
    
	while (i < 8)
	{
        decimal = decimal * 2 + (binary[i] - '0');
		i++;
    }
    return ((char)decimal);
}


int	main(int argv, char *argc[])
{
	(void)argv;
	(void)argc;

	char *binary;
	char *binary2;
	char c = 'a';
	char *test = "Hello, world!";
	int i = 0;

	while (test[i] != '\0')
	{
		binary = ft_ctobin(test[i]);
		printf("For %c: %s\n", test[i], binary);
		i++;
	}
	binary2 = ft_ctobin(c);
	printf("Binary for char c is: %s. Converted back to char: %c\n", binary, ft_bintoc(binary2));
	return (0);
}
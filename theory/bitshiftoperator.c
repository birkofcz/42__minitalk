/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitshiftoperator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:21:31 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/11 16:56:45 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	unsigned int a = 1; //unsigned int is 32 bit integer.

	printf("Left shifted by 1: %d\n", a << 1);
	printf("Left shifted by 2: %d\n", a << 2);
	printf("Left shifted by 3: %d\n\n\n", a << 3);

	int i;
	for (i = 0; i < 32; i++)
	{
		printf("Left shifted by %02d: %08x | %u\n", i, a << i, a << i); //shifting one bit left gives us number multiplied by 2., shifting 2 bits left = multiplied by 4 and so on.
	}
	printf("\n\n");
	int j;
	for (j = 0; j < 32; j++)
	{
		a = 1;
		a <<= j;
		char binary[33]; // create a new binary string for the shifted value of a
		for (int b = 31; b >= 0; b--) 
		{
        	binary[b] = (a & 1) + '0';
        	a >>= 1;
    	}
    	binary[32] = '\0';
		printf("Left shifted by %02d: %s\n", j, binary);
	}
	return (0);
}
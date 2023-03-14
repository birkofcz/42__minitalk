/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/13 17:04:21 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SERVER PART - generating PID (Process ID), printing it and signal handling
*/

#include "../include/minitalk.h"
#include <stdio.h>

void	ft_write_byte(char *buffer);

char	ft_bintoc(char *binary) {
    
	int decimal = 0;
	int i = 0;
    
	while (i < 8)
	{
        decimal = decimal * 2 + (binary[i] - '0');
		i++;
    }
	printf("Binary: %s, Decimal: %d\n", binary, decimal);  // Add this line for debugging
    return ((char)decimal);
}

/* void	ft_bit_decoder(int signal)
{
	int bit_counter;
	char *buffer;
	int	transmit_complete;

	transmit_complete = 0;
	buffer = malloc(10000 * sizeof(char));
	if (!buffer)
		return;
	bit_counter = 0;
	while (transmit_complete == 0)
	{
		if (signal == SIGUSR1)
			buffer[bit_counter] = '0';
		else if (signal == SIGUSR2)
			buffer[bit_counter] = '1';
		else 
		{
			transmit_complete = 1;
			buffer[bit_counter++] = '\0';
		}
		bit_counter++;
		if (bit_counter % 8 == 0)
			ft_write_byte(buffer);
	}
} */

void ft_bit_decoder(int signal) {
  static char buffer[9]; // static array with a fixed size of 9 bytes
  int bit_counter = 0;
  int transmit_complete = 0;

  while (transmit_complete == 0) {
    if (signal == SIGUSR1) {
      buffer[bit_counter] = '0';
    } else if (signal == SIGUSR2) {
      buffer[bit_counter] = '1';
    } else {
      transmit_complete = 1;
      buffer[bit_counter] = '\0';
    }
    bit_counter++;

    // If the buffer is full, write it to the output function
    if (bit_counter == 8) {
      ft_write_byte(buffer);
      bit_counter = 0;
    }
  }
}


void	ft_write_byte(char *buffer)
{
	// static int bit_counter = 0;
	// char *binary;
	char c;
	// int	i;

	// i = 0;
	// binary = malloc(9 * sizeof(char));
	// if (!binary)
	// 	return ;
	// while (i < 9)
	// {
	// 	binary[bit_counter] = buffer[bit_counter];
	// 	bit_counter++;
	// }
	// binary[8] = '\0';
	c = ft_bintoc(buffer);
	write(1, &c, 1);
	fflush(stdout);
	//free(buffer);
}



int	main(int argc, char *argv[])
{
	int	pid;

	(void)argv;
	pid = getpid();
	printf("Server started.\nProcess ID: \033[31m%d\033[0m\nWaiting for signal...\n", pid);
	while (argc == 1)
	{
		signal(SIGUSR1, ft_bit_decoder);
		signal(SIGUSR2, ft_bit_decoder);
		//pause ();
	}
	return (0);
}


/* char	ft_decode_byte(int sig)
{
	char *binary;
	int i;

	binary = (char *)malloc(9 * sizeof(char));
	if (!binary)
		return ;
	binary[8] = '\0';
	i = 0;
	while (i < 9)
	{
		if (sig == SIGUSR1)
			binary[i] = '0';
		else if (sig == SIGUSR2)
			binary[i] = '1';
		i++;
	}
	return (ft_bintoc(binary));
} */

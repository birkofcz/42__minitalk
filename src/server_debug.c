/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/13 16:54:05 by sbenes           ###   ########.fr       */
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
    return ((char)decimal);
}

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
	char c;
	
	c = ft_bintoc(buffer);
	write(1, &c, 1);
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

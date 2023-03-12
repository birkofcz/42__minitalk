/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/12 16:36:27 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SERVER PART - generating PID (Process ID), printing it and signal handling
*/

#include "../include/minitalk.h"
#include <stdio.h>

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

char	ft_decode_byte(int sig)
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
}

void	ft_write_byte(int signal)
{
	int bit_counter;

	bit_counter = 0;
	if (signal == SIGUSR1 || signal == SIGUSR2)
		bite_counter++;
	if (bite_counter % 8 = 0)
	{
		write(1, &ft_decode_char(signal), 1);
	}
}


int	main(void)
{
	int	pid;

	pid = getpid();
	printf("Server started.\nProcess ID: \033[31m%d\033[0m\nWaiting for signal...\n", pid);
	
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:34:31 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/19 15:06:10 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/*
CLIENT SIDE - takes arguments and sends string
*/

/* 
ft_ctobin - encoding the character into binary, written in string.
 */

char	*ft_ctobin(int c)
{
	char	*binary;
	int		i;

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

/* 
ft_sbyte - SEND BYTE - taking the binary of the char, signalling 
to server - iterate through the binary string, SIGUSR1 for 0, 
SIGUSR2 for 1.
 */

int	handshake = 0;

void	ft_handshake(int sig)
{
	(void)sig;
	handshake = 1;
}

void	ft_sbyte(char c, int pid)
{
	char *binary;
	int i;

	signal(SIGUSR1, ft_handshake); 
	binary = ft_ctobin(c);
	i = 0;
	while (binary[i] != '\0')
	{
		if (binary[i] == '0')
			kill(pid, SIGUSR1);
		else if (binary[i] == '1')
			kill(pid, SIGUSR2);
		while (!handshake)
			usleep(200);
		handshake = 0;
		i++;
	}
	free(binary);
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
			ft_sbyte(argv[2][i++], pid);
		ft_sbyte('\0', pid);
	}
	else
	{
		ft_printf("\n\033[31mError: wrong format!\033[0m\n");
		ft_printf("\033[32mEnter: ./client <PID> <MESSAGE>\033[0m\n\n");
		return (1);
	}
	return (0);
}

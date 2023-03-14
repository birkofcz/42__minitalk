/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/14 16:19:11 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SERVER PART - generating PID (Process ID), printing it and signal handling
*/

#include "../include/minitalk.h"
#include <stdio.h>

char	ft_bintoc(char *binary)
{
	int	decimal;
	int	i;

	decimal = 0;
	i = 0;
	while (binary[i] != '\0')
	{
		decimal = decimal * 2 + (binary[i] - '0');
		i++;
	}
	printf("%d", decimal);
	return ((char)decimal);
}

void	ft_gotbyte(int signal)
{
	char	*binary;
	int		i;
	char	c;

	printf("Received signal: %d", signal);
	binary = (char *)malloc(9 * sizeof(char));
	if (!binary)
		return ;
	binary[8] = '\0';
	i = 0;
	while (binary[i] != '\0')
	{
		if (signal == SIGUSR1)
			binary[i] = '0';
		else if (signal == SIGUSR2)
			binary[i] = '1';
		i++;
	}
	c = ft_bintoc(binary);
	write(1, &c, 1);
	free(binary);
}

int	main(int argc, char *argv[])
{
	int	pid;

	(void)argv;
	pid = getpid();
	printf("Server started.\nProcess ID: \033[31m%d\033[0m\nWaiting for signal...\n", pid);
	while (argc == 1)
	{
		signal(SIGUSR1, ft_gotbyte);
		signal(SIGUSR2, ft_gotbyte);
		pause ();
	}
	return (0);
}



/* void ft_receivebyte(int signal)
{
    static char binary[9];
    static int i = 0;

    if (signal == SIGUSR1)
        binary[i] = '0';
    else if (signal == SIGUSR2)
        binary[i] = '1';
	i++;

    if (i == 8)
    {
        binary[i] = '\0';
        char c = ft_bintoc(binary);
        printf("%c", c);
        i = 0;
    }
} */

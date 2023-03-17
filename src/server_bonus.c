/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:01:00 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/17 16:15:28 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
SERVER PART - generating PID (Process ID), printing it and signal handling
*/

#include "../include/minitalk.h"
#include <stdio.h> // printf - replace with ft_printf
#include <stdlib.h>
#include <string.h> // memset - call it from libft
#include <time.h>

// ft_atoi - include from libft!
int	ft_atoi(const char *str)
{
	int	sign;
	int	output;

	sign = 1;
	output = 0;
	while (*str == '\f' || *str == '\n' || *str == '\r' || *str == '\t'
		|| *str == '\v' || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	return (output * sign);
}
char	ft_bintoc(const char *binary)
{
	int	decimal;
	int	i;

	decimal = 0;
	i = 0;
	while (binary[i] != '\0')
		decimal = decimal * 2 + (binary[i++] - '0');
	return ((char)decimal);
}

/* void	ft_rbyte(int sig)
{
	static char	binary[9];
	static int	i = 0;
	char		c;

	if (sig == SIGUSR1)
		binary[i++] = '0';
	else if (sig == SIGUSR2)
		binary[i++] = '1';
	if (i == 8)
	{
		binary[i] = '\0';
		c = ft_bintoc(binary);
		write(1, &c, 1);
		i = 0;
	}
} */

void handle_client_pid(const char *client_pid_str)
{
	int i;

	i = 0;
    int client_pid = ft_atoi(client_pid_str);
	while (i != 2)
	{
    	kill(client_pid, SIGUSR1);
		usleep(200);
		i++;
	}
	kill(client_pid, SIGUSR2);
    printf("Client PID received: %d\n", client_pid);
}

void ft_rbyte(int sig)
{
    static char binary[9];
    static int i = 0;
    static int listening_for_pid = 0;
    static char client_pid_str[12]; // Assuming maximum PID length is 11 digits
    static int client_pid_idx = 0;
    char c;

    if (sig == SIGUSR1)
        binary[i++] = '0';
    else if (sig == SIGUSR2)
        binary[i++] = '1';

    if (i == 8)
    {
        binary[i] = '\0';
        c = ft_bintoc(binary);

        if (listening_for_pid)
        {
            if (c == '\0')
            {
                client_pid_str[client_pid_idx] = '\0'; //// Properly terminate the client_pid_str
				usleep(500); 
                handle_client_pid(client_pid_str);
                client_pid_idx = 0;
                listening_for_pid = 0;
            }
            else
            {
                client_pid_str[client_pid_idx++] = c;
            }
        }
        else
        {
            if (c == '\0')
            {
                listening_for_pid = 1;
            }
            else
            {
                write(1, &c, 1);
            }
        }

        i = 0;
    }
}



int	main(int argc, char *argv[])
{
	int	pid_server;

	(void)argv;
	(void)argc;
	pid_server = getpid();
	printf("Server started.\nProcess ID: \033[31m%d\033[0m\n", pid_server);
	printf("Waiting for signal...\n");
	while (argc == 1)
	{
		signal(SIGUSR1, ft_rbyte);
		signal(SIGUSR2, ft_rbyte);
		pause();
	}
	return (0);
}

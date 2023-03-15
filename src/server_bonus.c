/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:01:00 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/15 14:26:06 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minitalk.h"
#include <stdio.h> // printf - replace with ft_printf
#include <stdlib.h>
#include <string.h> // memset - call it from libft

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

void ft_rbyte(int sig)
{
    static char binary[9];
    static int i = 0;
    static int state = 0; // 0 for receiving client PID, 1 for receiving message
    static int client_pid = 0;
    char c;

    if (sig == SIGUSR1)
        binary[i++] = '0';
    else if (sig == SIGUSR2)
        binary[i++] = '1';

    if (i == 8)
    {
        binary[i] = '\0';
        c = ft_bintoc(binary);

        if (state == 0)
        {
            client_pid = (int)c;
            state = 1; // Switch state to receiving message
        }
        else
        {
            write(1, &c, 1);

            // Check if the message is considered complete (ends with newline)
            if (c == '\n')
            {
                kill(client_pid, SIGUSR1); // Send acknowledgment signal back to the client
                state = 0; // Switch state back to receiving client PID for the next message
            }
        }

        i = 0;
    }
}

int main(int argc, char *argv[])
{
    int pid_server;

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

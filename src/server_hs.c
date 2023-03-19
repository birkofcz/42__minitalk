/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_hs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/19 11:05:22 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SERVER PART - generating PID (Process ID), printing it and signal handling
*/

#include "../include/minitalk.h"

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

void	ft_rbyte(int sig, siginfo_t *info, void *ucontext) 
{
	(void)ucontext;
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
	kill(info->si_pid, SIGUSR1);
}

int	main(int argc, char *argv[])
{
	int	pid_server;
	struct sigaction	sa;

	(void)argv;
	(void)argc;
	pid_server = getpid();
	printf("Server started.\nProcess ID: \033[31m%d\033[0m\n", pid_server);
	printf("Waiting for signal...\n");

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = ft_rbyte;
	sa.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (argc == 1)
	{
//		signal(SIGUSR1, ft_rbyte);
//		signal(SIGUSR2, ft_rbyte);
		pause();
	}
	return (0);
}

/*FT_RBYTE with timing functionality*/
/* 
void ft_rbyte(int sig)
{
    static char binary[9];
    static int i = 0;
    static struct timespec start, end;
    static int first_char_received = 0;
    char c;

    if (!first_char_received)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        first_char_received = 1;
    }

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

        if (c == '\0')
        {
            clock_gettime(CLOCK_MONOTONIC, &end);
            double elapsed_time = (end.tv_sec - start.tv_sec) * 1e3 + (end.tv_nsec - start.tv_nsec) / 1e6;
            printf("\nElapsed time: %f ms\n", elapsed_time);
            first_char_received = 0;
        }
    }
} */

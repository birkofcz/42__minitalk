/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/19 15:25:11 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SERVER PART - generating PID (Process ID), printing it and waiting 
for signal.
Handling the signals. 
Handshake functionality - it will signal back to the client 
after every byte recieved.
Client waits for the handshake and only then sends another 
byte. This speeds up the processand eliminating mistakes that arises 
from the signal timing problem;.
*/

#include "../include/minitalk.h"

/* 
ft_bintoc - decoder, converts binary into the character.
 */
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

/*
ft_rbyte - function to handle signal recieving, writing bit after 
bit into the binary.
Full binary represents one byte - decoded into char with bintoc.
Writes the char on screen.
Signalling back the handshake for client to continue with sending.
Repeat.
Using struct sigaction - with information about the client PID.
*/

void	ft_rbyte(int sig, siginfo_t *info, void *ucontext)
{
	static char	binary[9];
	static int	i = 0;
	char		c;

	(void)ucontext;
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
			write(1, "\n", 1);
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(int argc, char *argv[])
{
	int					pid_server;
	struct sigaction	sa;

	(void)argv;
	if (argc == 1)
	{
		pid_server = getpid();
		ft_printf("\n\033[32mServer started.\033[0m\n");
		ft_printf("Process ID: \033[31m%d\033[0m\n", pid_server);
		ft_printf("Receiving...\n");
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_sigaction = ft_rbyte;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		while (1)
			pause();
	}
	else
	{
		ft_printf("\n\033[31mError!\033[0m\n");
		ft_printf("\033[32mEnter: ./server\033[0m\n\n");
	}
	return (0);
}

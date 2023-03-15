/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/14 19:27:17 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SERVER PART - generating PID (Process ID), printing it and signal handling
*/

/* #include "../include/minitalk.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>

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

void	ft_gotbyte(int sig)
{
	char	*binary;
	int		i;
	char	c;

	printf("Received signal: %d", sig);
	binary = (char *)malloc(9 * sizeof(char));
	if (!binary)
		return ;
	memset(binary, '\0', 9);
	//binary[8] = '\0';
	i = 0;
	//while (binary[i] != '\0')
	while (i < 8)
	{
		if (sig == SIGUSR1)
		{
			binary[i] = '0';
			i++;
		}
		else if (sig == SIGUSR2)
		{
			binary[i] = '1';
			i++;
		}
	}
	c = ft_bintoc(binary);
	write(1, &c, 1);
	free(binary);
}

int	main(int argc, char *argv[])
{
    int	pid;

    (void)argv;
	(void)argc;
    pid = getpid();
    printf("Server started.\nProcess ID: \033[31m%d\033[0m\nWaiting for signal...\n", pid);
	while (argc == 1)
	{
		signal(SIGUSR1, ft_gotbyte);
   		signal(SIGUSR2, ft_gotbyte);
		pause();
	}
    return (0);
} */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char ft_bintoc(char *binary) {
  int decimal;
  int i;

  decimal = 0;
  i = 0;
  while (binary[i] != '\0') {
    decimal = decimal * 2 + (binary[i] - '0');
    i++;
  }
  return ((char)decimal);
}

/* char *binary;
int i;

void ft_gotbyte(int sig) {
  //printf("Received signal: %d\n", sig);
  if (sig == SIGUSR1) {
    binary[i] = '0';
    i++;
  } else if (sig == SIGUSR2) {
    binary[i] = '1';
    i++;
  }

  if (i == 8) {
    binary[i] = '\0';
    char c = ft_bintoc(binary);
    write(1, &c, 1);
    i = 0;
  }
} */

char *binary;
int i;

void ft_gotbyte(int sig) {

  if (sig == SIGUSR1) {
    binary[i] = '0';
    i++;
  } else if (sig == SIGUSR2) {
    binary[i] = '1';
    i++;
  }

  if (i == 8) {
    binary[i] = '\0';
    char c = ft_bintoc(binary);
    write(1, &c, 1);
    i = 0;
  }
}

int main(int argc, char *argv[]) {
  int pid;

  (void)argv;
  (void)argc;
  pid = getpid();
  printf("Server started.\nProcess ID: \033[31m%d\033[0m\nWaiting for signal...\n", pid);

  binary = (char *)malloc(9 * sizeof(char));
  if (!binary)
    return 1;
  memset(binary, '\0', 9);
  i = 0;

  while (argc == 1) {
    signal(SIGUSR1, ft_gotbyte);
    signal(SIGUSR2, ft_gotbyte);
    pause();
  }

  free(binary);
  return (0);
}



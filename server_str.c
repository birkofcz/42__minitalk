/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:23:43 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/17 11:38:31 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
SERVER PART - generating PID (Process ID), printing it and signal handling
*/

#include "include/minitalk.h"
#include <stdio.h> // printf - replace with ft_printf
#include <stdlib.h>
#include <string.h> // memset - call it from libft
#include <time.h>

char	*ft_strjoin(char *message, char *c_string);

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
} 

char	*ft_write_message(char *message, char c)
{
	char	*new_message;
	char	*c_string;

	c_string = (char *)malloc(2 * sizeof(char));
	if (!c_string)
		return (NULL);
	c_string[0] = c;
	c_string[1] = '\0';
	new_message = ft_strjoin(message, c_string);
	free(message);
	free(c_string);
	return (new_message);
}

/*
ft_strjoin - my libft version. Used for writing buffer into the pool.
*/

char	*ft_strjoin(char *message, char *c_string)
{
	char	*joined_str;
	size_t	size;
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (!message || !c_string)
		return (NULL);
	size = ft_strlen(message) + ft_strlen(c_string) + 1;
	joined_str = (char *)malloc(size * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (message[i] != '\0')
	{
		joined_str[i] = message[i];
		i++;
	}
	while (c_string[y] != '\0')
	{
		joined_str[i++] = c_string[y++];
	}
	joined_str[i] = '\0';
	return (joined_str);
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
	static char	*binary;
	static int	i = 0;
	char		c;
	static char *message = NULL;

	if (!message) // Check if the message is NULL and initialize it to an empty string	
	{
		message = (char *)malloc(1 * sizeof(char));
		message[0] = '\0';
	}
	if (!binary)
		binary = (char *)malloc(9 * sizeof(char));
	if (sig == SIGUSR1)
		binary[i++] = '0';
	else if (sig == SIGUSR2)
		binary[i++] = '1';
	if (i == 8)
	{
		binary[i] = '\0';
		c = ft_bintoc(binary);
		if (c == '\0')
		{
			printf("%s\n", message);
			free(message);
			free(binary);
			message = NULL; // Set the message variable to NULL after freeing
			binary = NULL;
		}
		message = ft_write_message(message, c);
		i = 0;
	}
} */

#include <time.h> // Include the time.h library

void	ft_rbyte(int sig)
{
	static char	*binary;
	static int	i = 0;
	char		c;
	static char *message = NULL;
	static struct timespec start_time; // Declare a timespec variable to store the start time
	static int first_signal_received = 0; // Flag to check if it's the first signal received

	if (!first_signal_received)
	{
		clock_gettime(CLOCK_MONOTONIC, &start_time); // Store the start time
		first_signal_received = 1;
	}

	if (!message) // Check if the message is NULL and initialize it to an empty string
	{
		message = (char *)malloc(1 * sizeof(char));
		message[0] = '\0';
	}
	if (!binary)
		binary = (char *)malloc(9 * sizeof(char));
	if (sig == SIGUSR1)
		binary[i++] = '0';
	else if (sig == SIGUSR2)
		binary[i++] = '1';
	if (i == 8)
	{
		binary[i] = '\0';
		c = ft_bintoc(binary);
		if (c == '\0')
		{
			struct timespec end_time;
			long elapsed_time;

			clock_gettime(CLOCK_MONOTONIC, &end_time);
			elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000; // Calculate elapsed time in milliseconds
			elapsed_time += (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

			printf("%s\n", message);
			printf("Elapsed time: %ld ms\n", elapsed_time); // Print the elapsed time

			free(message);
			free(binary);
			message = NULL; // Set the message variable to NULL after freeing
			binary = NULL;
			first_signal_received = 0; // Reset the first_signal_received flag
		}
		else
		{
			message = ft_write_message(message, c);
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
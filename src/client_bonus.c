/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:02:02 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/17 16:50:55 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minitalk.h"
#include <stdio.h>
/*
CLIENT SIDE BONUS - waiting to recieve the acknowledgement message.

ft_atoi, itoa and support functions - include from libft!
*/
static int	ft_str_len(long n)
{
	int		i;

	i = 1;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_put_nbr(long n, char *result, int *i)
{
	if (n > 9)
	{
		ft_put_nbr(n / 10, result, i);
		ft_put_nbr(n % 10, result, i);
	}
	else
		result[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	long	nbr;

	nbr = n;
	result = (char *)malloc((ft_str_len(nbr) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		result[i] = '-';
		nbr *= -1;
		i++;
	}
	ft_put_nbr(nbr, result, &i);
	result[i] = '\0';
	return (result);
}
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

// ACTUAL SHIT //////////////////////////////////////////////////////
/* 
ft_ctobin - encoding the character into binary, written in string.
 */

int signal_received = 0;

void ft_ackmessage(int sig)
{
    if (sig == SIGUSR1)
    {
        signal_received++;
    }
	if (sig == SIGUSR2)
		signal_received++;
}

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

void	ft_sbyte(char c, int pid)
{
	char	*binary;
	int		i;

	binary = ft_ctobin(c);
	i = 0;
	while (binary[i] != '\0')
	{
		if (binary[i] == '0')
			kill(pid, SIGUSR1);
		else if (binary[i] == '1')
			kill(pid, SIGUSR2);
		i++;
		usleep(400);
	}
	free(binary);
}

/* int	main(int argc, char *argv[])
{
	int	pid_server;
	char	*pids_char;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid_server = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			ft_sbyte(argv[2][i], pid_server);
			i++;
		}
		i = 0;
		ft_sbyte('\0', pid_server);
		pids_char = ft_itoa(pid_server);
		while (pids_char[i] != '\0')
			ft_sbyte(pids_char[i++], pid_server);
		while (1)
		{
			signal(SIGUSR1, ft_ackmessage);
			return (0);
		}
	}
	else
	{
		printf("\033[91mError: wrong format.\033[0m\n");
		printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	return (0);
} */

// ... (Other functions and includes remain the same)


int main(int argc, char *argv[])
{
    int pid_server;
    char *pids_char;
    int i;

    i = 0;
    if (argc == 3)
    {
        pid_server = ft_atoi(argv[1]);
        while (argv[2][i] != '\0')
        {
            ft_sbyte(argv[2][i], pid_server);
            i++;
        }
        i = 0;
        ft_sbyte('\0', pid_server);
        pids_char = ft_itoa(getpid());
        while (pids_char[i] != '\0')
            ft_sbyte(pids_char[i++], pid_server);
        ft_sbyte('\0', pid_server);
        free(pids_char);
        while (signal_received != 3 )
        {
        	signal(SIGUSR1, ft_ackmessage);
			signal(SIGUSR2, ft_ackmessage);
        	pause();
        }
        printf("Message successfully received by server!\n");
    }
    else
    {
        printf("\033[91mError: wrong format.\033[0m\n");
        printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
        return (1);
    }
    return (0);
}



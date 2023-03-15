/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:02:02 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/15 14:56:03 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minitalk.h"
#include <stdio.h>
/*
CLIENT SIDE - takes arguments and sends string
*/

/*ft_itoa*/
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



/*
ft_atoi - from libft to convert PID number from command line argument. 
*/

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
void	ft_spid(int pid_client, int pid_server)
{
	char *pid_client_str;
	int	i;

	i = 0;
	pid_client_str = ft_itoa(pid_client);
	while (pid_client != '\0')
	{
		ft_sbyte(pid_client_str[i++], pid_server);

	}
	if (pid_client_str == '\0')
		ft_sbyte('\n', pid_server);

}


void	ft_sbyte(char c, int pid_server)
{
	char	*binary;
	int		i;
	int		state;

	binary = ft_ctobin(c);
	i = 0;
	while (binary[i] != '\0')
	{
		if (binary[i] == '0')
			kill(pid_server, SIGUSR1);
		else if (binary[i] == '1')
			kill(pid_server, SIGUSR2);
		i++;
		usleep(350);
	}
	free(binary);
}

int	main(int argc, char *argv[])
{
	int	pid_client;
	int	pid_server;
	int	i;

	pid_client = getpid();
	i = 0;
	if (argc == 3)
	{
		pid_server = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			ft_sbyte(argv[2][i], pid_server);
			i++;
		}
	}
	else
	{
		printf("\033[91mError: wrong format.\033[0m\n");
		printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	return (0);
}


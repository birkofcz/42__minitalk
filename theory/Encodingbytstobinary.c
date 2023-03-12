/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Encodingbytstobinary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 15:39:22 by sbenes            #+#    #+#             */
/*   Updated: 2023/03/12 15:43:51 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This is a encoding and deconding proces for characters.
Character is 1 byte = 8 bits long.
Encoding character into the binary can be used to send it using UNIX signals. Signals
can't transfer any data, but can work as a flag.
For user defined usage, there are only two signals - SIGUSR1 and SIGUSR2.
Therefor, we can use SIGUSR1 to be a signal for reciever for "0" and SIGUSR2 for "1". 
We therefor can use it to transfer information - must be interpreted at reciever.
*/

char *ft_ctobin(int c)
{
	char	*binary;
	int i;

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

char	ft_bintoc(char *binary) {
    
	int decimal = 0;
	int i = 0;
    
	while (i < 8)
	{
        decimal = decimal * 2 + (binary[i] - '0');
		i++;
    }
    return ((char)decimal);
}


int	main(int argv, char *argc[])
{
	(void)argv;
	(void)argc;

	char *binary;
	char *binary2;
	char c = 'a';
	char *test = "Hello, world!";
	int i = 0;

	while (test[i] != '\0')
	{
		binary = ft_ctobin(test[i]);
		printf("For %c: %s\n", test[i], binary);
		i++;
	}
	binary2 = ft_ctobin(c);
	printf("Binary for char c is: %s. Converted back to char: %c\n", binary, ft_bintoc(binary2));
	return (0);
}
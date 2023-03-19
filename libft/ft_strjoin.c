/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:43:54 by sbenes            #+#    #+#             */
/*   Updated: 2023/02/03 15:37:23 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	size_t	size;
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_str = (char *)malloc(size * sizeof(char));
	if (!joined_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		joined_str[i] = s1[i];
		i++;
	}
	while (s2[y] != '\0')
	{
		joined_str[i++] = s2[y++];
	}
	joined_str[i] = '\0';
	return (joined_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:03:43 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 06:09:47 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*shaystack;
	char		*sneedle;
	size_t		i;
	size_t		j;

	shaystack = (char *)haystack;
	sneedle = (char *)needle;
	i = 0;
	if (*sneedle == '\0')
		return (shaystack);
	while (shaystack[i] != '\0' && i < len)
	{
		j = 0;
		while (sneedle[j] != '\0' && i + j < len)
		{
			if (sneedle[j] != haystack[i + j])
				break ;
			j++;
		}
		if (sneedle[j] == '\0')
			return ((shaystack + i));
		i++;
	}
	return (NULL);
}

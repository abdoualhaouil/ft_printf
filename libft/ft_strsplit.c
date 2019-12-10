/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:31:33 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 06:42:06 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_nbrword(const char *s, char w)
{
	size_t i;
	size_t c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] != w)
			if (s[i + 1] == w || s[i + 1] == '\0')
				c++;
		i++;
	}
	return (c);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**p;
	size_t	i;
	size_t	j;
	size_t	start;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	if (!(p = (char **)malloc((ft_nbrword(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		start = i;
		while (s[i] != c && s[i])
			i++;
		p[j++] = ft_strsub(s, start, i - start);
		while (s[i] == c && s[i])
			i++;
	}
	p[j] = NULL;
	return (p);
}

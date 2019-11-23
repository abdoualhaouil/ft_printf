/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 15:14:26 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 06:25:33 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	i;
	size_t	c;
	size_t	d;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	c = ft_strlen(s1);
	d = ft_strlen(s2);
	p = (char *)malloc((c + d + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (i < d + c)
	{
		if (i < c)
			p[i] = (char)s1[i];
		if (i >= c)
			p[i] = (char)s2[j++];
		i++;
	}
	p[i] = '\0';
	return (p);
}

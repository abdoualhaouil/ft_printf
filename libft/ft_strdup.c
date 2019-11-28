/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 06:37:53 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/24 10:17:36 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	unsigned char	*msrc;
	char			*p;
	long int				i;

	if (src)
	{
		msrc = (unsigned char *)src;
		i = 0;
		while (msrc[i])
			i++;
		p = (char *)malloc((i + 1) * sizeof(unsigned char));
		if (p == NULL)
			return (0);
		i = 0;
		while (msrc[i])
		{
			p[i] = msrc[i];
			i++;
		}
		p[i] = '\0';
	}
	else
		return (NULL);
	return (p);
}

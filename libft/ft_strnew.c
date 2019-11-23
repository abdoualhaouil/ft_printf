/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 09:27:41 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 06:18:11 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char		*p;
	size_t		i;

	i = 0;
	p = (char *)malloc((size + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < size)
	{
		p[i] = '\0';
		i++;
	}
	p[i] = '\0';
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 05:11:46 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 06:36:24 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*mstr;
	size_t			i;

	mstr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (mstr[i] == (unsigned char)c)
			return (mstr + i);
		i++;
	}
	return (NULL);
}

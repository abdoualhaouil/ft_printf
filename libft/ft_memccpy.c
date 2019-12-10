/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 05:42:50 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/18 00:22:57 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *des, const void *src, int c, size_t n)
{
	unsigned char	*msrc;
	unsigned char	*mdes;
	size_t			i;

	i = 0;
	mdes = (unsigned char *)des;
	msrc = (unsigned char *)src;
	while (i < n && (msrc[i] != (unsigned char)c))
	{
		mdes[i] = msrc[i];
		i++;
	}
	if (i != n)
		mdes[i] = msrc[i];
	if (i == n)
		return (NULL);
	return (mdes + i + 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 01:27:27 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 05:27:51 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *des, const void *src, size_t n)
{
	char	*msrc;
	char	*mdes;
	size_t	i;

	msrc = (char *)src;
	mdes = (char *)des;
	i = 0;
	while (i < n)
	{
		mdes[i] = msrc[i];
		i++;
	}
	return (mdes);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 06:59:22 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 05:33:49 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*sdst;
	char	*ssrc;
	int		i;

	sdst = (char *)dst;
	ssrc = (char *)src;
	i = 0;
	while (ssrc[i])
	{
		sdst[i] = ssrc[i];
		i++;
	}
	sdst[i] = '\0';
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 04:13:30 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 20:08:07 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *des, const void *src, size_t len)
{
	char	*p;
	char	*mdes;
	char	*msrc;

	mdes = (char *)des;
	msrc = (char *)src;
	if (mdes < msrc || msrc + len < mdes)
		ft_memcpy(mdes, msrc, len);
	else
	{
		p = (char *)malloc((len + 1) * sizeof(char));
		if (!p)
			return (NULL);
		ft_memcpy(p, msrc, len);
		ft_memcpy(mdes, p, len);
		free(p);
	}
	return (mdes);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 02:50:03 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 05:45:48 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (str[i])
		i++;
	while (i > 0 && str[i] != (char)c)
		i--;
	if (i != 0)
		return ((char *)(str + i));
	if (str[0] == ((char)c))
		return ((char *)str);
	return (NULL);
}

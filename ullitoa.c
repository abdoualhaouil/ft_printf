/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ullitoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:21:07 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 00:05:50 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static	int		ft_nbr(unsigned long long int n)
{
	int i;
	int c;

	c = 0;
	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char			*ft_itoallu(unsigned long long int n)
{
	char							*p;
	int								i;
	unsigned long long int			d;
	int								c;

	d = 1;
	i = 0;
	c = ft_nbr(n);
	if ((p = (char *)malloc((c + 1) * sizeof(char))) == NULL)
		return (NULL);
	while (c-- > 1)
		d *= 10;
	while (d != 0)
	{
		p[i++] = (n / d) + '0';
		n %= d;
		d /= 10;
	}
	p[i] = '\0';
	return (p);
}

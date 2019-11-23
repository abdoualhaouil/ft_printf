/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:21:07 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/04/21 06:26:48 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_nbr(unsigned int n)
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

static	void	f(int *c, int *d)
{
	while ((*c)-- > 1)
		*d *= 10;
}

char			*ft_itoa(int n)
{
	unsigned int	nb;
	char			*p;
	int				i;
	int				d;
	int				c;

	(n < 0) ? (nb = -n) :\
					(nb = n);
	d = 1;
	i = 0;
	c = ft_nbr(nb);
	(n < 0) ? (p = (char *)malloc((c + 2) * sizeof(char))) :\
					(p = (char *)malloc((c + 1) * sizeof(char)));
	if (p == NULL)
		return (NULL);
	(n < 0) ? (p[i++] = '-') : n;
	f(&c, &d);
	while (d != 0)
	{
		p[i++] = (nb / d) + '0';
		nb %= d;
		d /= 10;
	}
	p[i] = '\0';
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llitoa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:21:07 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 00:05:34 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		ft_nbr(size_t n)
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

static	void	f(long long int *c, long long int *d)
{
	while ((*c)-- > 1)
		*d *= 10;
}

char			*ft_itoall(long long int n)
{
	size_t			nb;
	char			*p;
	int				i;
	long long int	d;
	long long int	c;

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

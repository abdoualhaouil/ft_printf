/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:50:51 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/02 00:48:37 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zero(size_t n)
{
	char		*res;
	size_t		i;

	if (!(res = ft_strnew(n)))
		return (NULL);
	i = -1;
	while (++i < n)
		res[i] = '0';
	return (res);
}

char	*delete_zero(char *res)
{
	char	*tmp;
	int		i;
	int		len_res;

	i = 0;
	tmp = res;
	len_res = ft_strlen(res);
	while (res[i] == '0' && (i != len_res - 1))
		i++;
	if (!(res = ft_strsub(res, i, len_res - i)))
		return (NULL);
	free(tmp);
	return (res);
}

char	*multiplication(char *mantissa, char *exponent)
{
	char	*res;
	int		j;
	int		k;
	int		totaldidgit;
	int		remainder;
	int		i;

	k = ft_strlen(mantissa) + ft_strlen(exponent);
	if (!(res = zero(k + 1)))
		return (NULL);
	j = ft_strlen(mantissa);
	while (--j >= 0)
	{
		i = ft_strlen(exponent);
		remainder = 0;
		while (--i >= 0)
		{
			totaldidgit = ((mantissa[j] - '0') * (exponent[i] - '0'))
				+ remainder;
			remainder = ((res[k] - '0') + totaldidgit) / 10;
			res[k] = ((res[k] - '0') + totaldidgit) % 10 + '0';
			if (i == 0 && remainder > 0)
				res[k - 1] = ((res[k - 1] - '0') + remainder) + '0';
			k--;
		}
		k = j + ft_strlen(exponent);
	}
	res = delete_zero(res);
	return (res);
}

char	*ft_power(int base, int exp)
{
	char	*basec;
	char	*base1;
	char	*tmp;

	basec = ft_itoa(base);
	if (!(base1 = ft_strdup("1")))
		return (NULL);
	while (exp > 1)
	{
		if (exp % 2 == 1)
		{
			tmp = base1;
			if (!(base1 = multiplication(base1, basec)))
				return (NULL);
			free(tmp);
			exp--;
		}
		exp /= 2;
		tmp = basec;
		if (!(basec = multiplication(basec, basec)))
			return (NULL);
		free(tmp);
	}
	tmp = basec;
	(exp != 0) && (basec = multiplication(base1, basec));
	(exp == 0) && (basec = ft_strdup(base1));
	if (!basec)
		return (NULL);
	free(tmp);
	free(base1);
	return (basec);
}

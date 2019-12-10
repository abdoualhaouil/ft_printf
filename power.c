/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 19:50:51 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/07 23:27:46 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*delete_zero(char *res)
{
	char	*tmp;
	int		i;
	int		len_res;

	i = 0;
	len_res = ft_strlen(res);
	while (res[i] == '0' && (i != len_res - 1))
		i++;
	tmp = res;
	if (!(res = ft_strsub(res, i, len_res - i)))
		return (ft_free(res));
	free(tmp);
	return (res);
}

static	char	*tmp_multiplication(char *mantissa, char *exponent,
	int k, char *res)
{
	int		j;
	int		totaldidgit;
	int		remainder;
	int		i;

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
		k = j + ft_strlen(exponent) - 1;
	}
	return (res);
}

char			*multiplication(char *mantissa, char *exponent, int op)
{
	char	*res;
	int		k;

	k = (ft_strequ(mantissa, "1")) ? ft_strlen(mantissa) +
		ft_strlen(exponent) - 1 : ft_strlen(mantissa) + ft_strlen(exponent);
	if (!(res = zero(k)))
		return (ft_free(res));
	k--;
	res = tmp_multiplication(mantissa, exponent, k, res);
	(op == 0) && (res = delete_zero(res));
	return (res);
}

static	char	*tmp_power(int exp, char *basec, char *base1)
{
	char	*tmp;

	if (exp % 2 == 1)
	{
		tmp = base1;
		if (!(base1 = multiplication(base1, basec, 0)))
			return (ft_free(base1));
		free(tmp);
		exp--;
	}
	return (base1);
}

char			*ft_power(int base, int exp)
{
	char	*basec;
	char	*base1;
	char	*tmp;

	basec = ft_itoa(base);
	if (!(base1 = ft_strdup("1")))
		return (ft_free(base1));
	while (exp > 1)
	{
		base1 = tmp_power(exp, basec, base1);
		exp /= 2;
		tmp = basec;
		if (!(basec = multiplication(basec, basec, 0)))
			return (ft_free(basec));
		free(tmp);
	}
	tmp = basec;
	(exp != 0) && (basec = multiplication(base1, basec, 0));
	(exp == 0) && (basec = ft_strdup(base1));
	if (!basec)
		return (ft_free(basec));
	free(tmp);
	free(base1);
	return (basec);
}

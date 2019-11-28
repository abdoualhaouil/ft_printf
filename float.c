/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 10:36:08 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/28 11:02:45 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*char	*nan_and_infinity(unsigned long int mantissa,
							unsigned long int exponent)
{
	char *buffer;

	if (exponent == 32767)
	{
		(~(mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) &&
			~(mantissa >> 61 & 1)) && (buffer = ft_strdup("inf"));
		((mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) && ~(mantissa >> 61 & 1))
			&& (buffer = ft_strdup("inf"));
		(~(mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) && (mantissa >> 61 & 1))
			&& (buffer = ft_strdup("nan"));
		(~(mantissa >> 63 & 1) && (mantissa >> 62 & 1))\
			&& (buffer = ft_strdup("nan"));
		((mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) && (mantissa >> 61 & 1))
			&& (buffer = ft_strdup("nan"));
		((mantissa >> 63 & 1) && (mantissa >> 62 & 1))\
			&& (buffer = ft_strdup("nan"));
	}
	return (buffer);
}*/

char	*ft_float_int(t_double *d, int exp)
{
	t_float	*f;

	if (exp < 0)
		return (ft_strdup("0"));
	f = (t_float *)malloc(sizeof(t_float));
	(f->res) = zero(1);
	f->i = (exp >= 0 && exp < 64) ? 62 - exp : -1;
	f->j = 0;
	while (++(f->i) < 64)
	{
		if ((d->float_rep.mantissa >> f->i) & 1)
		{
			f->buffer = ft_power(2, f->j);
			f->tmp = (f->res);
			(f->res) = addition(f->buffer, (f->res));
			free(f->buffer);
			free(f->tmp);
		}
		f->j++;
	}
	(exp > 63) && (f->buffer = ft_power(2, exp - 63));
	(exp <= 63) && (f->buffer = ft_strdup("1"));
	f->tmp = (f->res);
	(f->res) = multiplication(f->buffer, (f->res));
	free(f->buffer);
	free(f->tmp);
	return (f->res);
}

char	*ft_float_dec(t_double *d, int exp)
{
	char		*res;
	t_float		*f;

	if (exp > 63)
		return (ft_strdup("0"));
	f = (t_float *)malloc(sizeof(t_float));
	f->i = (exp > 0 && exp < 63) ? 63 - exp : 64;
	f->j = (exp < 0) ? 0 : 1;
	f->res = ft_strnew(0);
	while (--(f->i) >= 0)
	{
		f->tmp = f->res;
		f->res = ft_strjoin(f->res, "0");
		free(f->tmp);
		if ((d->float_rep.mantissa >> f->i) & 1)
		{
			f->buffer = ft_power(5, f->j);
			f->tmp = f->res;
			f->res = addition(f->buffer, f->res);
			free(f->buffer);
			free(f->tmp);
		}
		f->j++;
	}
	(exp < 0) && (f->buffer = ft_power(5, -exp));
	(exp > 0 && exp < 63) && (f->buffer = ft_strdup("1"));
	res = multiplication(f->buffer, f->res);
	free(f->buffer);
	free(f->res);
	free(f);
	return (res);
}

char	*ft_float_main(t_double *d)
{
	char	*buff_int;
	char	*buff_dec;
	int		exp;

	exp = EXP;
	buff_dec = NULL;
	buff_int = NULL;
	buff_dec = ft_float_dec(d, exp);
	buff_int = ft_float_int(d, exp);
	printf("%s.%s\n", buff_int, buff_dec);
	return (NULL);
}

void	*ft_free(t_double *ptr)
{
	free(ptr);
	return (NULL);
}

char	*ft_float(long double number)
{
	char		*mantissa;
	//char		*tmp;
	t_double	*d;

	d = (t_double *)malloc(sizeof(t_double));
	d->number = number;
	/*if (d->float_rep.mantissa == 0)
		if (d->float_rep.sign == 1)
			return ((d->float_rep.sign == 1) ? "-0.0" : "0.0");
	if (!(mantissa = nan_and_infinity(d->float_rep.mantissa,
				d->float_rep.exponent)))
		return (ft_free(d));
	if (ft_strequ(mantissa, "inf"))
	{
		tmp = mantissa;
		if (d->float_rep.sign == 1)
			if (!(mantissa = ft_strjoin("-", mantissa)))
				return (ft_free(d));
		free(tmp);
		return (mantissa);
	}
	if (ft_strequ(mantissa, "nan"))
		return (mantissa);*/
	if (!(mantissa = ft_float_main(d)))
		return (ft_free(d));
	return (mantissa);
}

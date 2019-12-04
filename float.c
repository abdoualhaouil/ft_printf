/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 10:36:08 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/04 16:59:44 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	*nan_and_infinity(unsigned long int mantissa, unsigned long int sign)
{
	char	*buffer;
	char	*tmp;

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
	if (ft_strequ(buffer, "inf"))
	{
		tmp = buffer;
		if (sign)
			if (!(buffer = ft_strjoin("-", buffer)))
				return (NULL);
		free(tmp);
	}
	return (buffer);
}

char	*tmp_whole(t_double *d, t_float *f)
{
	if (++f->j > -1 && ((d->float_rep.mantissa >> f->i) & 1))
	{
		if (!(f->buffer = ft_power(2, f->j)))
			return (NULL);
		f->tmp = (f->res);
		if (!(f->res = addition(f->buffer, f->res, 0)))
			return (NULL);
		free(f->buffer);
		free(f->tmp);
	}
	return (f->res);
}

char	*ft_float_whole(t_double *d, int exp, t_float *f)
{
	if (exp < 0)
		return (ft_strdup("0"));
	if (!(f->res = zero(1)))
		return (NULL);
	f->i = (exp >= 0 && exp < 64) ? 62 - exp : -1;
	f->j = -1;
	while (++(f->i) < 64)
		if (!(f->res = tmp_whole(d, f)))
			return (NULL);
	(exp > 63) && (f->buffer = ft_power(2, exp - 63));
	(exp <= 63) && (f->buffer = ft_strdup("1"));
	if (!(f->buffer))
		return (NULL);
	f->tmp = (f->res);
	if (!(f->res = multiplication(f->buffer, (f->res))))
		return (NULL);
	free(f->buffer);
	free(f->tmp);
	return (f->res);
}

char	*tmp_frac(t_float *f, t_double *d)
{
	f->tmp = f->res;
	if (!(f->res = ft_strjoin(f->res, "0")))
		return (NULL);
	free(f->tmp);
	if ((d->float_rep.mantissa >> f->i) & 1)
	{
		if (!(f->buffer = ft_power(5, f->j)))
			return (NULL);
		f->tmp = f->res;
		if (!(f->res = addition(f->buffer, f->res, 0)))
			return (NULL);
		free(f->buffer);
		free(f->tmp);
	}
	f->j++;
	return (f->res);
}

char	*find_nbr_zero(t_float *f, t_double *d, int exp)
{
	f->j = 1;
	f->i = 63 - exp;
	while (((d->float_rep.mantissa >> --f->i) & 1) == 0)
		f->j++;
	if (exp >= 0 && exp < 64)
	{
		if (!(f->buffer = ft_power(5, f->j)))
			return (NULL);
		if (!(f->tmp = zero(f->j - ft_strlen(f->buffer))))
			return (NULL);
		free(f->buffer);
		if (!(f->buffer = ft_strdup("1")))
			return (NULL);
	}
	else
	{
		if (!(f->buffer = ft_power(5, -exp)))
			return (NULL);
		f->nbr_zero = -exp - ft_strlen(f->buffer);
		if (!(f->tmp = zero(f->nbr_zero)))
			return (NULL);
	}
	return (f->res);
}

char	*ft_float_frac(t_double *d, int exp, t_float *f)
{
	char		*res;

	if (exp > 63)
		return (ft_strdup("0"));
	f->i = (exp >= 0 && exp < 63) ? 63 - exp : 64;
	f->j = (exp < 0) ? 0 : 1;
	if (!(f->res = ft_strnew(0)))
		return (NULL);
	while (--(f->i) >= 0)
		if (!(tmp_frac(f, d)))
			return (NULL);
	if (!(find_nbr_zero(f, d, exp)))
		return (NULL);
	if (!(res = multiplication(f->buffer, f->res)))
		return (NULL);
	free(f->res);
	free(f->buffer);
	if (!(f->res = ft_strjoin(f->tmp, res)))
		return (NULL);
	f->i = ft_strlen(f->res) - 1;
	while (f->res[f->i] == '0' && f->i > 0)
		f->res[f->i--] = '\0';
	free(f->tmp);
	free(res);
	return (f->res);
}

char	*ft_float_main(t_double *d, t_flags *active)
{
	char	*buff_whole;
	char	*buff_frac;
	char	*res;
	int		exp;
	t_float *f;

	exp = EXP;
	if (!(f = (t_float *)malloc(sizeof(t_float))))
		return (NULL);
	if (!(buff_frac = ft_float_frac(d, exp, f)))
		return (NULL);
	free(f);
	if (!(f = (t_float *)malloc(sizeof(t_float))))
		return (NULL);
	if (!(buff_whole = ft_float_whole(d, exp, f)))
		return (NULL);
	res = ft_roundup(buff_frac, buff_whole, active);
	return (res);
}

char	*ft_float(long double number, t_flags *active)
{
	char		*mantissa;
	char		*tmp;
	t_double	*d;

	mantissa = NULL;
	d = (t_double *)malloc(sizeof(t_double));
	d->number = number;
	if (d->float_rep.mantissa == 0 && !((d->float_rep.mantissa >> 63) & 1))
		return ((d->float_rep.sign == 1) ? "-0." : "0.");
	else if (d->float_rep.exponent == 32767)
	{
		if (!(mantissa = nan_and_infinity(d->float_rep.mantissa,
				d->float_rep.sign)))
			return (ft_free(d));
		return (mantissa);
	}
	else if (!(mantissa = ft_float_main(d, active)))
		return (ft_free(d));
	if (d->float_rep.sign == 1)
	{
		tmp = mantissa;
		if (!(mantissa = ft_strjoin("-", mantissa)))
			return (ft_free(mantissa));
		free(tmp);
	}
	free(d);
	return (mantissa);
}

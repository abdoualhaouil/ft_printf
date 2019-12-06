/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 10:36:08 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 01:26:26 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

static	char	*nan_and_infinity(unsigned long int mantissa,
	unsigned long int sign)
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

int				find_nbr_zero(t_float *f, t_double *d, int exp)
{
	char	*buff;
	char	*zero_buff;

	f->j = 1;
	f->i = 63 - exp;
	while (((d->float_rep.mantissa >> --f->i) & 1) == 0)
		f->j++;
	if (exp >= 0 && exp < 64)
	{
		if (!(f->buffer2 = ft_strdup("1")))
			return (-1);
	}
	else
	{
		if (!(f->buffer2 = ft_power(5, -exp - 1)))
			return (-1);
		buff = f->buffer2;
		zero_buff = zero(-exp - 1);
		f->buffer2 = addition(zero_buff, f->buffer2, 1);
		free(buff);
		free(zero_buff);
	}
	return (0);
}

static	char	*ft_float_main(t_double *d, t_flags *active)
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
	free(f);
	res = ft_roundup(buff_frac, buff_whole, active);
	return (res);
}

char			*ft_float(long double number, t_flags *active)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 10:36:08 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/08 22:21:09 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*nan_and_infinity(unsigned long int mantissa,
	unsigned long int sign)
{
	char	*buffer;
	char	*tmp;

	if ((mantissa >> 63 & 1) && ((mantissa << 1) == 0))
		buffer = ft_strdup("inf");
	if ((mantissa >> 63 & 1) && (mantissa << 1))
		buffer = ft_strdup("nan");
	if (ft_strequ(buffer, "inf") && sign)
	{
		tmp = buffer;
		if (!(buffer = ft_strjoin("-", buffer)))
			return (ft_free(buffer));
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
		if (!(f->buffer2 = ft_strdup("1")))
			return (-1);
	if (!(exp >= 0 && exp < 64))
	{
		if (!(f->buffer2 = ft_power(5, -exp - 1)))
			return (-1);
		buff = f->buffer2;
		if (!(zero_buff = zero(-exp - 1)))
			return (-1);
		if (!(f->buffer2 = addition(zero_buff, f->buffer2, 1)))
			return (ft_free3(zero_buff, f->buffer2, -1));
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
		return (ft_free(f));
	if (!(buff_frac = ft_float_frac(d, exp, f)))
		return (ft_free(f));
	free(f);
	if (!(f = (t_float *)malloc(sizeof(t_float))))
		return (ft_free(f));
	if (!(buff_whole = ft_float_whole(d, exp, f)))
		return (ft_free(f));
	free(f);
	if (!(res = ft_roundup(buff_frac, buff_whole, active)))
		return (ft_free2(buff_frac, buff_whole));
	free(d);
	return (res);
}

static	char	*tmp_ft_float(t_double *d, char *mantissa)
{
	char	*tmp;

	if (d->float_rep.sign == 1)
	{
		tmp = mantissa;
		if (!(mantissa = ft_strjoin("-", mantissa)))
			return (ft_free(mantissa));
		free(tmp);
	}
	return (mantissa);
}

char			*ft_float(long double number, t_flags *active)
{
	char		*mantissa;
	t_double	*d;

	mantissa = NULL;
	d = (t_double *)malloc(sizeof(t_double));
	d->number = number;
	if (d->float_rep.mantissa == 0 && !((d->float_rep.mantissa >> 63) & 1))
	{
		free(d);
		return ((d->float_rep.sign == 1) ? "-0." : "0.");
	}
	else if (d->float_rep.exponent == 32767)
	{
		if (!(mantissa = nan_and_infinity(d->float_rep.mantissa,
				d->float_rep.sign)))
			return (ft_free(d));
		free(d);
		return (mantissa);
	}
	else if (!(mantissa = ft_float_main(d, active)))
		return (ft_free(d));
	if (!(mantissa = tmp_ft_float(d, mantissa)))
		return (ft_free(mantissa));
	return (mantissa);
}

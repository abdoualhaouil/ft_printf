/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:29:49 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/08 00:27:33 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char		*tmp_whole(t_double *d, t_float *f)
{
	if (++f->j > -1 && ((d->float_rep.mantissa >> f->i) & 1))
	{
		if (!(f->buffer = ft_power(2, f->j)))
			return (NULL);
		f->tmp = (f->res);
		if (!(f->res = addition(f->buffer, f->res, 0)))
			return (ft_free2(f->res, f->buffer));
		free(f->buffer);
		free(f->tmp);
	}
	return (f->res);
}

char				*ft_float_whole(t_double *d, int exp, t_float *f)
{
	if (exp < 0)
		return (ft_strdup("0"));
	if (!(f->res = zero(1)))
		return (NULL);
	f->i = (exp >= 0 && exp < 64) ? 62 - exp : -1;
	f->j = -1;
	while (++(f->i) < 64)
		if (!(f->res = tmp_whole(d, f)))
			return (ft_free2(d, f));
	(exp > 63) && (f->buffer = ft_power(2, exp - 63));
	(exp <= 63) && (f->buffer = ft_strdup("1"));
	if (!(f->buffer))
		return (NULL);
	f->tmp = (f->res);
	if (!(f->res = multiplication(f->buffer, (f->res), 0)))
		return (ft_free2(f->res, f->buffer));
	free(f->buffer);
	free(f->tmp);
	return (f->res);
}

char				*tmp_f(t_float *f)
{
	char	*tmp;

	if (f->j != (int)ft_strlen(f->buffer))
	{
		tmp = zero(f->j);
		f->tmp = f->buffer;
		if (!(f->buffer = addition(f->buffer, tmp, 1)))
			return (ft_free2(tmp, f->buffer));
		free(tmp);
		free(f->tmp);
	}
	return (f->buffer);
}

static	char		*tmp_frac(t_float *f, t_double *d, int exp)
{
	f->i = (exp >= 0 && exp < 63) ? 63 - exp : 64;
	f->j = 1;
	while (--(f->i) >= 0)
	{
		f->tmp = f->res;
		if (!(f->res = ft_strjoin(f->res, "0")))
			return (ft_free(f->res));
		free(f->tmp);
		if ((d->float_rep.mantissa >> f->i) & 1)
		{
			if (!(f->buffer = ft_power(5, f->j)))
				return (NULL);
			if (!(f->buffer = tmp_f(f)))
				return (NULL);
			f->tmp = f->res;
			if (!(f->res = addition(f->buffer, f->res, 1)))
				return (ft_free2(f->res, f->buffer));
			free(f->buffer);
			free(f->tmp);
		}
		f->j++;
	}
	return (f->res);
}

char				*ft_float_frac(t_double *d, int exp, t_float *f)
{
	char		*res;

	if (exp > 63)
		return (ft_strdup("0"));
	if (!(f->res = ft_strnew(0)))
		return (NULL);
	if (find_nbr_zero(f, d, exp) == -1)
		return (NULL);
	if (!(tmp_frac(f, d, exp)))
		return (NULL);
	if (!(res = multiplication(f->buffer2, f->res, 1)))
		return (ft_free2(f->buffer2, f->res));
	free(f->buffer2);
	free(f->res);
	f->i = ft_strlen(f->res) - 1;
	while (f->res[f->i] == '0' && f->i > 0)
		f->res[f->i--] = '\0';
	return (res);
}

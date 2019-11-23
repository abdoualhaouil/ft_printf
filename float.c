/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:18:33 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 22:16:40 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*final_float(char *mantissa, unsigned long int exponent, t_double *d)
{
	char	*two_power_exponent;
	char	*tmp_char;
	int		tmp;
	int		len_exp;
	int		len_man;

	tmp = exponent - 16383;
	if (tmp < 0)
		two_power_exponent = power_mantissa(5, -1 * tmp);
	else		
		two_power_exponent = power(2, tmp);
	if (d->float_rep.bit_cash == 1)
		mantissa[0] = '1';
	len_man = ft_strlen(mantissa);
    len_exp = ft_strlen(two_power_exponent);
	tmp_char = multiplication(mantissa, two_power_exponent, len_exp, len_man);
	if (d->float_rep.sign == 1)
		tmp_char = ft_strjoin("-", tmp_char);
	free (two_power_exponent);
	return (tmp_char);
}

char	*nan_and_Infinity(unsigned long int mantissa, unsigned long int exponent)
{
	char *buffer;

	buffer = ft_strnew(0);
	if (exponent == 32767)
	{
		(~(mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) &&  ~(mantissa >> 61 & 1))\
			&& (buffer = ft_strdup("inf"));
		((mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) &&  ~(mantissa >> 61 & 1))\
			&& (buffer = ft_strdup("inf"));
		(~(mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) && (mantissa >> 61 & 1))\
			&& (buffer = ft_strdup("nan"));
		(~(mantissa >> 63 & 1) && (mantissa >> 62 & 1))\
			&& (buffer = ft_strdup("nan"));
		((mantissa >> 63 & 1) && ~(mantissa >> 62 & 1) && (mantissa >> 61 & 1))\
			&& (buffer = ft_strdup("nan"));
		((mantissa >> 63 & 1) && (mantissa >> 62 & 1))\
			&& (buffer = ft_strdup("nan"));
		
	}

	return(buffer);
}

char	*ft_float(long double number)
{
	char		*mantissa;
	char		*final_mantissa;
	char		*tmp;
	int 		i;
	int			j;
	t_double	*d;

	final_mantissa = zero(1);
	d = (t_double *)malloc(sizeof(t_double));
	d->number = number;
	i = 63;
	j = 1;
	if (d->float_rep.mantissa == 0 && d->float_rep.bit_cash == 0)
	{
		if (d->float_rep.sign == 1)
			return ("-0.0");
		else
			return ("0.0");
	}
	mantissa = (nan_and_Infinity(d->float_rep.mantissa, d->float_rep.exponent));
	if (ft_strequ(mantissa, "inf"))
	{
		tmp = mantissa;
		if (d->float_rep.sign == 1)
			mantissa = ft_strjoin("-", mantissa);
		//free(tmp);
		return (mantissa);
	}
	if (ft_strequ(mantissa, "nan"))
		return (mantissa);
	while (--i >= 0)
	{
		if (d->float_rep.mantissa >> i & 1)
		{
			mantissa = power_mantissa(5, j);
			final_mantissa = addition(mantissa, final_mantissa);
			free(mantissa);
		}
		j++;
	}
	mantissa = final_float(final_mantissa, d->float_rep.exponent, d);
	free(final_mantissa);
	free(d);
	return (mantissa);
}
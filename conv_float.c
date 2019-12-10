/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 00:54:28 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/07 23:50:26 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char		*find_type_float(va_list ap, t_flags *active)
{
	char	*buffer;

	if (active->conversion >> 4 & 1)
		buffer = ft_float(va_arg(ap, long double), active);
	else if (active->conversion >> 1 & 1 || sizeof(va_arg(ap, double)) == 8)
		buffer = ft_float(va_arg(ap, double), active);
	else
		buffer = ft_float((float)va_arg(ap, double), active);
	return (buffer);
}

static	char		*conv_float_find_type(va_list ap, t_flags *active)
{
	char	*buffer;
	char	*tmp;
	int		i;
	int		precision;

	i = 0;
	(PRECISION == -1) && (precision = 6);
	(PRECISION != -1) && (precision = PRECISION);
	if (!(buffer = find_type_float(ap, active)))
		return (NULL);
	if (ft_strequ(buffer, "0.") || ft_strequ(buffer, "-0."))
	{
		if (!(tmp = zero(precision)))
			return (NULL);
		(precision != 0 || HASH) && (buffer = ft_strjoin(buffer, tmp));
		(precision == 0 && !HASH) && (buffer = (buffer[0] == '-') ?
			ft_strjoin("-0", tmp) : ft_strjoin("0", tmp));
		if (!buffer)
			return (ft_free(buffer));
		free(tmp);
	}
	if (ft_strequ(buffer, "inf") || ft_strequ(buffer, "nan") ||
		ft_strequ(buffer, "-inf"))
		return (buffer);
	return (buffer);
}

static	t_flags		*tmp_conv_float(char *buffer, t_flags *active, int count,
	int len_buffer)
{
	if (ft_strequ(buffer, "-inf"))
	{
		(PRECISION == 0) && ((PRECISION = 4));
		(ZERO) && (active->flags -= 8);
		if ((conv_string(buffer, active, count)) == -1)
			return (NULL);
	}
	else
	{
		(ft_strequ(buffer, "nan")) && (!(MINUS)) && (active->flags = 0);
		(ft_strequ(buffer, "nan")) && ((MINUS)) && (active->flags = 4);
		(ft_strequ(buffer, "inf")) && ((ZERO)) && (active->flags -= 8);
		if (WIDTH > len_buffer)
			(active->width -= len_buffer);
		else
			(active->width = 0);
	}
	return (active);
}

int					conv_float(va_list ap, t_flags *active, int count)
{
	char		*buffer;
	long int	len_buffer;
	int			minus;

	if (!(buffer = conv_float_find_type(ap, active)))
		return (-1);
	(buffer[0] == '-') && (minus = 1);
	(buffer[0] != '-') && (minus = 0);
	(buffer[0] == '-') && (buffer = buffer + 1);
	len_buffer = ft_strlen(buffer);
	active = tmp_conv_float(buffer, active, count, len_buffer);
	((PLUS || SPACE || minus) && (WIDTH > 0)) && (WIDTH--);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (count += ft_write(' ', WIDTH));
	(minus) && (count += ft_write('-', 1));
	(PLUS && !minus) && (count += ft_write('+', 1));
	(SPACE && !(PLUS) && !(minus)) && (count += ft_write(' ', 1));
	(!ft_strequ(buffer, "inf")) && (WIDTH > 0 && ZERO) &&
		(count += ft_write('0', WIDTH));
	(ft_strequ(buffer, "inf")) && (WIDTH > 0 && ZERO) &&
		(count += ft_write(' ', WIDTH));
	count += write(1, buffer, ft_strlen(buffer));
	(minus == 0) ? free(buffer) : free(buffer - 1);
	(MINUS) && (count += ft_write(' ', WIDTH));
	return (count);
}

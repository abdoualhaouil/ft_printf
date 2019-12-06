/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_dec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 05:24:55 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 00:03:12 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*find_type_dec(va_list ap, t_flags *active)
{
	char	*buffer;

	if (active->conversion >> 2 & 1)
		buffer = ft_itoall((char)va_arg(ap, int));
	else if (active->conversion & 1)
		buffer = ft_itoall((short int)va_arg(ap, int));
	else if (active->conversion >> 1 & 1)
		buffer = ft_itoall(va_arg(ap, long int));
	else if (active->conversion >> 3 & 1)
		buffer = ft_itoall(va_arg(ap, long long int));
	else
		buffer = ft_itoall(va_arg(ap, int));
	return (buffer);
}

static	char	*find_type_unsigned_dec(va_list ap, t_flags *active)
{
	char	*buffer;

	if (active->conversion >> 2 & 1)
		buffer = ft_itoallu((unsigned char)va_arg(ap, int));
	else if (active->conversion & 1)
		buffer = ft_itoallu((unsigned short int)va_arg(ap, int));
	else if (active->conversion >> 1 & 1)
		buffer = ft_itoallu(va_arg(ap, unsigned long int));
	else if (active->conversion >> 3 & 1)
		buffer = ft_itoallu(va_arg(ap, unsigned long long int));
	else
		buffer = ft_itoallu(va_arg(ap, unsigned int));
	return (buffer);
}

static	int		tmp_dec(t_flags *active, int len_buffer, int minus)
{
	int		precision;

	(ZERO && (PRECISION >= 0 || MINUS)) && (active->flags -= 8);
	(PLUS || SPACE || minus) && (WIDTH--);
	(active->precision < 0) && (precision = 0);
	(active->precision >= 0) && (precision = active->precision);
	(WIDTH > PRECISION && precision <= 0) && (active->width -= len_buffer);
	(precision >= WIDTH) && (active->width = 0);
	(WIDTH > PRECISION && active->precision > 0) && ((precision > len_buffer) ?\
		(active->width -= precision) : (active->width -= len_buffer));
	return (precision);
}

int				conv_dec(va_list ap, t_flags *active, int count)
{
	char	*buffer;
	char	*tmp;
	int		len;
	int		precision;
	int		minus;

	minus = 0;
	if (!(buffer = find_type_dec(ap, active)))
		return (-1);
	(buffer[0] == '-') && (minus = 1);
	tmp = buffer;
	(buffer[0] == '-') && (buffer = buffer + 1);
	(buffer[0] == '0' && active->precision >= 0) ? (buffer[0] = '\0') : 1;
	len = ft_strlen(buffer);
	precision = tmp_dec(active, len, minus);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (count += ft_write(' ', WIDTH));
	(minus) && (count += ft_write('-', 1));
	(PLUS && !minus) && (count += ft_write('+', 1));
	(SPACE && !(PLUS) && !minus) && (count += ft_write(' ', 1));
	(WIDTH > 0 && ZERO) && (count += ft_write('0', WIDTH));
	(PRECISION > len) && (count += ft_write('0', PRECISION - len));
	count += write(1, buffer, len);
	(WIDTH > 0 && !(ZERO) && MINUS) && (count += ft_write(' ', WIDTH));
	free(tmp);
	return (count);
}

int				conv_unsigned_dec(va_list ap, t_flags *active, int count)
{
	char	*buffer;
	int		len_buffer;
	int		precision;

	if (!(buffer = find_type_unsigned_dec(ap, active)))
		return (-1);
	(buffer[0] == '0' && active->precision >= 0) ? (buffer[0] = '\0') : 1;
	len_buffer = ft_strlen(buffer);
	(ZERO && (PRECISION >= 0 || MINUS)) && (active->flags -= 8);
	(active->precision < 0) && (precision = 0);
	(active->precision >= 0) && (precision = active->precision);
	(precision >= WIDTH) && (active->width = 0);
	(WIDTH > PRECISION && active->precision > 0) && ((precision > len_buffer) ?\
		(active->width -= precision) : (active->width -= len_buffer));
	(WIDTH > PRECISION && precision <= 0) && (active->width -= len_buffer);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (count += ft_write(' ', WIDTH));
	(WIDTH > 0 && ZERO) && (count += ft_write('0', WIDTH));
	(PRECISION > len_buffer) && (count += ft_write('0',
		PRECISION - len_buffer));
	count += write(1, buffer, len_buffer);
	(WIDTH > 0 && !(ZERO) && MINUS) && (count += ft_write(' ', WIDTH));
	free(buffer);
	return (count);
}

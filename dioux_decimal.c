/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 04:09:50 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/23 05:12:39 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char 	*find_type_dec(va_list ap, t_flags *active)
{
	char *buffer;

	if (active->conversion >> 2 & 1)
		buffer = ft_itoall((char )va_arg(ap, int));
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


char 	*find_type_unsigned_dec(va_list ap, t_flags *active)
{
	char *buffer;

	if (active->conversion >> 2 & 1)
			buffer = ft_itoallu((unsigned char)va_arg(ap, int));
	else if (active->conversion & 1)
		buffer = ft_itoallu((unsigned short int)va_arg(ap, int));
	else if (active->conversion >> 1 & 1)
		buffer = ft_itoallu(va_arg(ap, unsigned long int));
	else if (active->conversion >> 3 & 1)
		buffer = ft_itoallu(va_arg(ap, size_t));
	else
		buffer = ft_itoallu(va_arg(ap, unsigned int));
	return (buffer);
}

int	tmp_dec(t_flags *active, int len_buffer, int minus)
{
	int precision;

	(ZERO && (PRECISION >=0 || MINUS)) && (active->flags -= 8);
	(PLUS || SPACE || minus) && (WIDTH--);
	(active->precision < 0) && (precision = 0);
	(active->precision >= 0) && (precision = active->precision);
	(precision >= WIDTH) && (active->width = 0);
	(WIDTH > PRECISION && active->precision > 0) && ((precision > len_buffer) ?\
		(active->width -= precision) : (active->width -= len_buffer));
	return (precision);
}

char	*conversion_dec(va_list ap, t_flags *active)
{
	char	*buffer;
	char	*buffer1;
	int		len_buffer;
	int 	precision;
	int		minus;

	buffer1 = new_strnew(&list, 0);
	buffer = find_type_dec(ap, active);
	(buffer[0] == '-') ?  (minus = 1) : (minus = 0);
	(buffer[0] == '-') && (buffer = buffer + 1);
	(buffer[0] == '0' && active->precision >= 0) ? (buffer[0] = '\0') : 1;
	len_buffer = ft_strlen(buffer);
	precision = tmp_dec(active, len_buffer, minus);
	(WIDTH > PRECISION && precision <= 0) && (active->width -= len_buffer);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (buffer1 = width(WIDTH, ' '));
	(minus) && (buffer1 = ft_strjoin(buffer1, "-"));
	(PLUS && !minus) && (buffer1 = ft_strjoin(buffer1, "+"));
	(SPACE && !(PLUS) && !minus) && (buffer1 = ft_strjoin(buffer1, " "));
	(WIDTH > 0 && ZERO) && (buffer1 = ft_strjoin(buffer1, width(WIDTH, '0')));
	(PRECISION > len_buffer) && (buffer = ft_strjoin(width(PRECISION - \
		len_buffer, '0'), buffer)) \
	&& (buffer1 = ft_strjoin(buffer1, buffer));
	(PRECISION <= len_buffer) && (buffer1 = ft_strjoin(buffer1, buffer));
	(WIDTH > 0 && !(ZERO) && MINUS) && (buffer1 = \
		ft_strjoin(buffer1, width(WIDTH, ' ')));
	return (buffer1);
}


char	*conversion_unsigned_dec(va_list ap, t_flags *active)
{
	char	*buffer;
	char	*buffer1;
	int		len_buffer;
	int 	precision;

	buffer1 = ft_strnew(0);
	buffer = find_type_unsigned_dec(ap, active);
	(buffer[0] == '0' && active->precision >= 0) ? (buffer[0] = '\0') : 1;
	len_buffer = ft_strlen(buffer);
	(ZERO && (PRECISION >=0 || MINUS)) && (active->flags -= 8);
	(active->precision < 0) && (precision = 0);
	(active->precision >= 0) && (precision = active->precision);
	(precision >= WIDTH) && (active->width = 0);
	(WIDTH > PRECISION && active->precision > 0) && ((precision > len_buffer) ?\
		(active->width -= precision) : (active->width -= len_buffer));
	(WIDTH > PRECISION && precision <= 0) && (active->width -= len_buffer);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (buffer1 = width(WIDTH, ' '));
	(WIDTH > 0 && ZERO) && (buffer1 = ft_strjoin(buffer1, width(WIDTH, '0')));
	(PRECISION > len_buffer) && (buffer = ft_strjoin(width(PRECISION - \
		len_buffer, '0'), buffer)) \
	&& (buffer1 = ft_strjoin(buffer1, buffer));
	(PRECISION <= len_buffer) && (buffer1 = ft_strjoin(buffer1, buffer));
	(WIDTH > 0 && !(ZERO) && MINUS) && (buffer1 = \
		ft_strjoin(buffer1, width(WIDTH, ' ')));
	return (buffer1);
}
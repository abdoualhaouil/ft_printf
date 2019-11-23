/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux_octal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 10:17:11 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/23 05:14:42 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char 	*find_type_octal(va_list ap, t_flags *active)
{
	char *buffer;

	if (active->conversion >> 2 & 1)
		buffer = dec_to_octal((unsigned char)va_arg(ap, unsigned int));
	else if (active->conversion & 1)
		buffer = dec_to_octal((unsigned short int)va_arg(ap, unsigned int));
	else if (active->conversion >> 1 & 1)
		buffer = dec_to_octal(va_arg(ap, unsigned long int));
	else if (active->conversion >> 3 & 1)
		buffer = dec_to_octal(va_arg(ap, size_t));
	else
		buffer = dec_to_octal(va_arg(ap, unsigned int));
	return (buffer);
}


char	*dec_to_octal(size_t n)
{
	int i;
	char	*str;
	size_t nb;
	int r;

	nb = n;
	i = 0;
	while ((n /= 8) > 0)
		i++;
	str = ft_strnew(i + 2);
	str[i + 1] = '\0';
	while (nb > 0)
	{
		r = nb - (nb / 8) * 8;
		nb /= 8;
		str[i] = r + '0';
		i--;
	}
	return(str);
}

char	*conversion_octal(va_list ap, t_flags *active)
{
	char	*buffer;
	char	*buffer1;
	int		len_buffer;
	int 	precision;

	buffer1 = ft_strnew(0);
	buffer = find_type_octal(ap, active);
	(ft_strequ(buffer, "")) && (buffer = ft_strdup("0"));
	(buffer[0] == '0' && active->precision == 0) ? (buffer[0] = '\0') : 1;
	(ft_strequ(buffer, "0")) && (HASH) && (active->flags -= 2);
	len_buffer = ft_strlen(buffer);
	(HASH && active->precision <= len_buffer) && (WIDTH--);
	(ZERO && (PRECISION >=0 || MINUS)) && (active->flags -= 8);
	(active->precision < 0) && (precision = 0);
	(active->precision >= 0) && (precision = active->precision);
	(precision >= WIDTH) && (active->width = 0);
	(WIDTH > PRECISION && active->precision > 0) && ((precision > len_buffer) ?\
		(active->width -= precision) : (active->width -= len_buffer));
	(WIDTH > PRECISION && precision <= 0) && (active->width -= len_buffer);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (buffer1 = width(WIDTH, ' '));
	(HASH && !(active->precision > len_buffer)) && (buffer1 = ft_strjoin(buffer1, "0"));
	(WIDTH > 0 && ZERO) && (buffer1 = ft_strjoin(buffer1, width(WIDTH, '0')));
	(PRECISION > len_buffer) && (buffer = ft_strjoin(width(PRECISION - \
		len_buffer, '0'), buffer)) \
	&& (buffer1 = ft_strjoin(buffer1, buffer));
	(PRECISION <= len_buffer) && (buffer1 = ft_strjoin(buffer1, buffer));
	(WIDTH > 0 && !(ZERO) && MINUS) && (buffer1 = \
		ft_strjoin(buffer1, width(WIDTH, ' ')));
	return (buffer1);
}

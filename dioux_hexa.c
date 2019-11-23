/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:39:21 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/23 05:13:52 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char 	*find_type_hexa(va_list ap, t_flags *active, char c)
{
	char *buffer;

	if (active->conversion >> 2 & 1)
		buffer = dec_to_hex((unsigned char)va_arg(ap, unsigned int), c);
	else if (active->conversion & 1)
		buffer = dec_to_hex((unsigned short int)va_arg(ap, unsigned int), c);
	else if (active->conversion >> 1 & 1)
		buffer = dec_to_hex(va_arg(ap, unsigned long int), c);
	else if (active->conversion >> 3 & 1)
		buffer = dec_to_hex(va_arg(ap, size_t), c);
	else
		buffer = dec_to_hex(va_arg(ap, unsigned int), c);
	return (buffer);
}

char    *dec_to_hex(size_t n, char c)
{
	char 	*res;
	size_t	 r;
	size_t	nb;
	int i;

	i = 0;
	nb = n;
	while ((n /= 16) > 0)
		i++;
	res = ft_strnew(i + 2);
	res[i + 1] = '\0';
	while (nb > 0)
	{
		r = nb - (nb / 16) * 16;
		nb /= 16;
		if (r < 10)
			res[i] = r + '0';
		else if (c == 'x')
			res[i] = 'a' + r - 10;
		else if (c == 'X')
			res[i] = 'A' + r - 10;
		i--;
	}
	return(res);
}

char	*conversion_hexa(va_list ap, t_flags *active, char c)
{
	char	*buffer;
	char	*buffer1;
	int		len_buffer;
	int 	precision;

	(c == '0') && (active->flags |= 2U);
	buffer1 = ft_strnew(0);
	(c != '0') && (buffer = find_type_hexa(ap, active, c));
	(c == '0') && (buffer = dec_to_hex(va_arg(ap, size_t), 'x'));
 	(ft_strequ(buffer, "")) && (buffer = ft_strdup("0")) && (c != '0') && (HASH) && (active->flags -= 2);
	(HASH) && ((WIDTH) -= 2);
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
	(HASH && c == '0') && (buffer1 = ft_strjoin(buffer1, "0x"));
	(HASH && c == 'x') && (buffer1 = ft_strjoin(buffer1, "0x"));
	(HASH && c == 'X') && (buffer1 = ft_strjoin(buffer1, "0X"));
	(WIDTH > 0 && ZERO) && (buffer1 = ft_strjoin(buffer1, width(WIDTH, '0')));
	(PRECISION > len_buffer) && (buffer = ft_strjoin(width(PRECISION - \
		len_buffer, '0'), buffer)) \
	&& (buffer1 = ft_strjoin(buffer1, buffer));
	(PRECISION <= len_buffer) && (buffer1 = ft_strjoin(buffer1, buffer));
	(WIDTH > 0 && !(ZERO) && MINUS) && (buffer1 = \
		ft_strjoin(buffer1, width(WIDTH, ' ')));
	return (buffer1);
}
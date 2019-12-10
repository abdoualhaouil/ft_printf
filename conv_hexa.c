/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_hexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 06:29:09 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 23:16:49 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*dec_to_hex(size_t n, char c)
{
	char	*res;
	size_t	r;
	size_t	nb;
	int		i;

	i = 0;
	nb = n;
	while ((n /= 16) > 0)
		i++;
	if (!(res = ft_strnew(i + 2)))
		return (NULL);
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
	return (res);
}

static	char	*find_type_hexa(va_list ap, t_flags *active, char c)
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

static	void	tmp_hexa(t_flags *active, int len_buffer, int *precision)
{
	(HASH) && (WIDTH -= 2);
	(ZERO && (PRECISION >= 0 || MINUS)) && (active->flags -= 8);
	(active->precision < 0) && ((*precision) = 0);
	(active->precision >= 0) && ((*precision) = active->precision);
	((*precision) >= WIDTH) && (active->width = 0);
	(WIDTH > PRECISION && active->precision > 0) && (((*precision) > len_buffer)
		? (active->width -= (*precision)) : (active->width -= len_buffer));
	(WIDTH > PRECISION && (*precision) <= 0) && (active->width -= len_buffer);
}

int				conv_hexa(va_list ap, t_flags *active, char c, int count)
{
	char	*buffer;
	int		len_buff;
	int		precision;

	(c == '0') && (active->flags |= 2U);
	if ((c != '0') && !(buffer = find_type_hexa(ap, active, c)))
		return (-1);
	if ((c == '0') && !(buffer = dec_to_hex(va_arg(ap, size_t), 'x')))
		return (-1);
	(ft_strequ(buffer, "")) && (buffer = ft_strdup("0")) && (c != '0') &&
		(HASH) && (active->flags -= 2);
	if (!buffer)
		return (-1);
	(buffer[0] == '0' && active->precision >= 0) ? (buffer[0] = '\0') : 1;
	len_buff = ft_strlen(buffer);
	tmp_hexa(active, len_buff, &precision);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (count += ft_write(' ', WIDTH));
	((HASH && c == '0') || (HASH && c == 'x')) && (count += write(1, "0x", 2));
	(HASH && c == 'X') && (count += write(1, "0X", 2));
	(WIDTH > 0 && ZERO) && (count += ft_write('0', WIDTH));
	(PRECISION > len_buff) && (count += ft_write('0', PRECISION - len_buff));
	count += write(1, buffer, len_buff);
	(WIDTH > 0 && !(ZERO) && MINUS) && (count += ft_write(' ', WIDTH));
	free(buffer);
	return (count);
}

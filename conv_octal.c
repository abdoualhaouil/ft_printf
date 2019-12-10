/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_octal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 08:11:32 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 00:04:11 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*dec_to_octal(size_t n)
{
	char	*str;
	size_t	nb;
	int		r;
	int		i;

	nb = n;
	i = 0;
	while ((n /= 8) > 0)
		i++;
	if (!(str = ft_strnew(i + 2)))
		return (NULL);
	str[i + 1] = '\0';
	while (nb > 0)
	{
		r = nb - (nb / 8) * 8;
		nb /= 8;
		str[i] = r + '0';
		i--;
	}
	return (str);
}

static	char	*find_type_octal(va_list ap, t_flags *active)
{
	char *buffer;

	if (active->conversion >> 2 & 1)
		buffer = dec_to_octal((unsigned char)va_arg(ap, unsigned int));
	else if (active->conversion & 1)
		buffer = dec_to_octal((unsigned short int)va_arg(ap, unsigned int));
	else if (active->conversion >> 1 & 1)
		buffer = dec_to_octal(va_arg(ap, unsigned long int));
	else if (active->conversion >> 3 & 1)
		buffer = dec_to_octal(va_arg(ap, unsigned long long int));
	else
		buffer = dec_to_octal(va_arg(ap, unsigned int));
	return (buffer);
}

static	void	tmp_octal(t_flags *active, int len_buffer, int *precision)
{
	(HASH && active->precision <= len_buffer) && (WIDTH--);
	(ZERO && (PRECISION >= 0 || MINUS)) && (active->flags -= 8);
	(active->precision < 0) && ((*precision) = 0);
	(active->precision >= 0) && ((*precision) = active->precision);
	((*precision) >= WIDTH) && (active->width = 0);
	(WIDTH > PRECISION && active->precision > 0) && (((*precision) > len_buffer)
		? (active->width -= (*precision)) : (active->width -= len_buffer));
	(WIDTH > PRECISION && (*precision) <= 0) && (active->width -= len_buffer);
}

int				conv_octal(va_list ap, t_flags *active, int count)
{
	char	*buffer;
	int		len_buffer;
	int		precision;

	if (!(buffer = find_type_octal(ap, active)))
		return (-1);
	if (ft_strequ(buffer, ""))
	{
		free(buffer);
		if (!(buffer = ft_strdup("0")))
			return (-1);
	}
	(buffer[0] == '0' && active->precision == 0) ? (buffer[0] = '\0') : 1;
	(ft_strequ(buffer, "0")) && (HASH) && (active->flags -= 2);
	len_buffer = ft_strlen(buffer);
	tmp_octal(active, len_buffer, &precision);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (count += ft_write(' ', WIDTH));
	(HASH && !(active->precision > len_buffer)) && (count += ft_write('0', 1));
	(WIDTH > 0 && ZERO) && (count += ft_write('0', WIDTH));
	(PRECISION > len_buffer) && (count += ft_write('0',
		PRECISION - len_buffer));
	count += write(1, buffer, len_buffer);
	(WIDTH > 0 && !(ZERO) && MINUS) && (count += ft_write(' ', WIDTH));
	free(buffer);
	return (count);
}

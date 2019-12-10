/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 00:46:15 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/08 22:04:41 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		find_function(t_flags *active, va_list ap, char conversion)
{
	int		count;

	count = 0;
	(conversion == 'c') && (count = conv_char(va_arg(ap, int), active, count));
	(conversion == 's') && (count += conv_string(va_arg(ap, char *),
		active, count));
	(conversion == '%') && (count = conv_char('%', active, count));
	(conversion == 'u') && (count += conv_unsigned_dec(ap, active, count));
	(conversion == 'x') && (count += conv_hexa(ap, active, 'x', count));
	(conversion == 'X') && (count += conv_hexa(ap, active, 'X', count));
	(conversion == 'p') && (count += conv_hexa(ap, active, '0', count));
	(conversion == 'o') && (count += conv_octal(ap, active, count));
	(conversion == 'f') && (count += conv_float(ap, active, count));
	if (conversion == 'd' || conversion == 'i')
		count = conv_dec(ap, active, count);
	return (count);
}

int				ft_boolean(int i, const char *format)
{
	if (format[i] != 'c' && format[i] != 's' && format[i] != 'p'
		&& format[i] != 'd' && format[i] != 'X' && format[i] != 'i'
		&& format[i] != 'o' && format[i] != 'u' && format[i] != 'x'
		&& format[i] != 'f' && format[i] != '\0' && format[i] != '%')
		return (1);
	return (0);
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	t_flags		*active;
	int			counter;
	int			i;

	counter = 0;
	va_start(ap, format);
	i = -1;
	while (format[++i])
		if (format[i] == '%')
		{
			active = check_active_flags(format, i);
			while (ft_boolean(++i, format))
				;
			(format[i] == '\0') ? free(active) : 1;
			if (format[i] == '\0')
				break ;
			if ((counter += find_function(active, ap, format[i])) == -1)
				return (-1);
			free(active);
		}
		else
			(format[i]) && (counter += write(1, &format[i], 1));
	va_end(ap);
	return (counter);
}

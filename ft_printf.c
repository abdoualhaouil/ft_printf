/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:05:31 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 00:52:40 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*find_function(t_flags *active, va_list ap, char  conversion, int *count)
{
	char *res;

	res = ft_strnew(0);
	(conversion == 'c') && (res = conversion_char(va_arg(ap, int), active, count));
	(conversion == '%') && (res = conversion_per(active));
	if (conversion == 's')
	{
		if (!(res = va_arg(ap, char *)))
			res = ft_strdup("(null)");
		res = conversion_string(res, active);
	}
	(conversion == 'p') && (res = conversion_hexa(ap, active, '0'));
	if (conversion == 'd' || conversion == 'i')
		res = conversion_dec(ap, active);
	(conversion == 'u') && (res = conversion_unsigned_dec(ap, active));
	(conversion == 'o') && (res = conversion_octal(ap, active));
	(conversion == 'x') && (res = conversion_hexa(ap, active, 'x'));
	(conversion == 'X') && (res = conversion_hexa(ap, active, 'X'));
	(conversion == 'f') && (res = conversion_float(ap, active));
	return (res);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	char		*str;
	t_flags		*active;
	char		*res;
	int		*count;

	count = (int *)malloc(sizeof(int));
	(*count) = 0;
	res = ft_strnew(0);
	str	= (char *)format;
	i = -1;
	va_start(ap, format);
	while (str[++i])
	{
		if (str[i] == '%')
		{
			active = check_active_flags(str, i);
			while (str[++i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' && str[i] != 'X' \
				&& str[i] != 'i' && str[i] != 'o' && str[i] != 'u' && str[i] != 'x' && str[i] != 'f' && str[i] != '\0' && str[i] != '%');
			res = find_function(active, ap, str[i], count);
			(res) && ((*count) += write(1, res, ft_strlen(res)));
		}
		else
			(*count) += write(1, &str[i], 1);
		
	}
	return (*count);
}
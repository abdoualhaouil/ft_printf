/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:42:13 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 23:14:30 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*addition1(char *n1, char *n2)
{
	char	*res;
	int 	i;
	int 	j;
	int 	remainder;
	int 	colum;

	i = ft_strlen(n1);
	j = ft_strlen(n2);
	if (i != j)
	{
		(i > j) && (n2 = add_zero(n1, n2));
		(i < j) && (n1 = add_zero(n1, n2));
	}
	i = (i > j) ? i + 1: j + 1;
	res = ft_strnew(i + 1);
	remainder = 0;
	while (--i >= 1)
	{
		(n1[i - 1] == '.' && n2[i - 1] == '.') && (res[i] = '.') && (--i);
		colum = remainder;
		colum += (n1[i - 1] - '0') + (n2[i - 1] - '0');
		remainder = colum / 10;
		res[i] = colum % 10 + '0';
	}
	(remainder == 1) && (res[0] = 1 + '0');
	(remainder == 0) && (res = res + 1);
	return (res);
}

char	*find_type_float(va_list ap, t_flags *active)
{
	char	*buffer;

	if (active->conversion >> 4 & 1)
		buffer = ft_float(va_arg(ap, long double));
	else if (active->conversion >> 1 & 1 || sizeof(va_arg(ap, double)) == 8)
		buffer = ft_float(va_arg(ap, double));
	else
		buffer = ft_float((float)va_arg(ap, double));
	return (buffer);
}

int		five_round(char *buffer, int precision, int len_buffer, int i)
{
	int	j;

	if (buffer[i + precision + 1] == '5')
	{
		j = i + precision + 1;
		while (buffer[++j])
			if (buffer[j] != '0')
				break;
		if (j <= len_buffer - 1 || (((buffer[i + precision] - '0') % 2 != 0) \
			&& (buffer[i + precision] != '.')))
			return (1);
		if (((buffer[i + precision - 1] - '0') % 2 != 0) && \
			(buffer[i + precision] == '.'))
			return (1);
	}
	else 
		return (1);
	return (0);
}

char		*roundup_decpart(char *buffer, t_flags *active)
{
	char	*buffer1;
	long int 	precision;
	int 	i;
	int 	len_buffer;
	int 	ret;

	i = -1;
	len_buffer = ft_strlen(buffer);
	(PRECISION == -1) ? (precision = 6) : (precision = PRECISION);
	while (buffer[++i] != '.');
	(len_buffer < i + precision + 1) && (buffer = ft_strjoin(buffer, \
		width(i + precision - len_buffer + 1, '0')));
	if (buffer[i + precision + 1] >= '5')
	{
		if ((ret = five_round(buffer, precision, len_buffer, i) == 0))
			return (buffer);
		(buffer1 = width(i, '0')) && (buffer1 = ft_strjoin(buffer1, "."));
		(i + precision > len_buffer) && (i += precision + 1) && \
			(ft_strjoin(buffer, width(i - len_buffer, '0')));
		(i + precision <= len_buffer) && (i += precision + 1);
		(precision == 0) && (buffer1[i - 2] = '1') && (buffer1[i - 1] = '\0');
		(precision != 0) && (buffer1 = ft_strjoin(buffer1, \
			width(precision - 1, '0'))) && ((buffer1 = ft_strjoin(buffer1, "1")));
		buffer1 = addition1(buffer1, buffer);

	}
	else
		buffer1 = ft_strdup(buffer);
	return (buffer1);
}

char	*rowndup(va_list ap, t_flags *active)
{
	char	*buffer;
	int		i;
	int		len_buffer;
	int 	precision;

	i = 0;
	(PRECISION == -1) ? (precision = 6) : (precision = PRECISION);
	buffer = find_type_float(ap, active);
	if (ft_strequ(buffer, "inf") || ft_strequ(buffer, "nan") || ft_strequ(buffer, "-inf"))
		return (buffer);
	len_buffer = ft_strlen(buffer);
	buffer = roundup_decpart(buffer, active);
	while (buffer[++i] != '.');
	buffer[i + precision + 1] = '\0';
	(precision == 0 && !(HASH)) && (buffer[i + precision] = '\0');
	return(buffer);
}

char				*conversion_float(va_list ap, t_flags *active)
{
	char	*buffer;
	char	*buffer1;
	char	*tmp;
	long int		len_buffer;
	int 	minus;

	buffer1 = ft_strnew(0);
	buffer = rowndup(ap, active);
	tmp = buffer;
	if (ft_strequ(buffer, "-inf"))
	{
		(PRECISION == 0) && ((PRECISION = 4));
		(ZERO) && (active->flags -= 8);
		buffer1 = conversion_string(buffer, active);
		free (buffer);
		return (buffer1);
	}
	(ft_strequ(buffer, "nan")) && (!(MINUS)) && (active->flags = 0);
	(ft_strequ(buffer, "nan")) && ((MINUS)) && (active->flags = 4);
	(ft_strequ(buffer, "inf")) && ((ZERO)) && (active->flags -= 8);
	(buffer[0] == '-') ?  (minus = 1) : (minus = 0);
	
	(buffer[0] == '-') && (buffer = buffer + 1);
	len_buffer = ft_strlen(buffer);
	(PLUS || SPACE || minus) && (WIDTH--);
	if (WIDTH > len_buffer) 
		(active->width -= len_buffer);
	else
		(active->width = 0);
	(WIDTH > 0 && !(ZERO) && !(MINUS)) && (buffer1 = width(WIDTH, ' '));
	(minus) && (buffer1 = ft_strjoin(buffer1, "-"));
	(PLUS && !minus) && (buffer1 = ft_strjoin(buffer1, "+"));
	(SPACE && !(PLUS) && !(minus)) && (buffer1 = ft_strjoin(buffer1, " "));
	(!ft_strequ(buffer, "inf")) && (WIDTH > 0 && ZERO) && (buffer1 = ft_strjoin(buffer1, width(WIDTH, '0')));
	(ft_strequ(buffer, "inf")) && (WIDTH > 0 && ZERO) && (buffer1 = ft_strjoin(buffer1, width(WIDTH, ' ')));
	buffer1 = ft_strjoin(buffer1, buffer);
	(MINUS) && (buffer1 = ft_strjoin(buffer1, width(WIDTH, ' ')));

	return (buffer1);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 04:15:49 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/02 02:21:33 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_write(char c, int size)
{
	char	buff[size];
	int		i;

	i = -1;
	while (++i < size)
		buff[i] = c;
	write(1, buff, size);
	return (size);
}

int		conv_char(int c, t_flags *active, int count)
{
	(MINUS) && (ZERO) && (active->flags -= 8);
	!(MINUS) && (WIDTH > 1) && (!(ZERO)) && (count += ft_write(' ', WIDTH - 1));
	!(MINUS) && (WIDTH > 1) && (ZERO) && (count += ft_write('0', WIDTH - 1));
	(count += write(1, &c, 1));
	(MINUS) && (WIDTH > 1) && (count += ft_write(' ', WIDTH - 1));
	return (count);
}

int		tmp_string(t_flags *active, char *buffer, int count)
{
	int len_str;

	len_str = ft_strlen(buffer);
	if (active->width >= len_str)
	{
		if (MINUS)
		{
			count += write(1, buffer, len_str);
			count += ft_write(' ', WIDTH - len_str);
		}
		else
		{
			(!ZERO) && (count += ft_write(' ', WIDTH - len_str));
			(ZERO) && (count += ft_write('0', WIDTH - len_str));
			count += write(1, buffer, len_str);
		}
	}
	else
		count += write(1, buffer, len_str);
	return (count);
}

int		conv_string(char *buffer, t_flags *active, int count)
{
	char	*buffer1;
	char	*tmp;
	int		len_str;

	buffer1 = ft_strdup(buffer);
	if (!(buffer1))
		buffer1 = ft_strdup("(null)");
	len_str = ft_strlen(buffer1);
	if (active->precision > 0 && active->precision < len_str)
	{
		tmp = buffer1;
		if (!(buffer1 = ft_strsub(buffer1, 0, active->precision)))
			return (-1);
		free(tmp);
	}
	else if (PRECISION == 0)
		if (!(buffer1 = ft_strdup("")))
			return (-1);
	count += tmp_string(active, buffer1, count);
	free(buffer1);
	return (count);
}

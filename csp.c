/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:59:53 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 15:44:40 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*width(size_t n, int c) 
{
	char		*res;
	size_t		i;

	res = ft_strnew(n);
	i = -1;
	while (++i < n)
			res[i] = c;
	return (res);
}

char	*insert_string(char *str, char *buffer, int i, t_flags *active)
{
	int len;

	len = ft_strlen(str);
	if (active->flags >> 2 & 1)
		while (str[i])
		{
			buffer[i] = str[i];
			i++;
		}
	else
		while (len > 0)
		{
			buffer[i] = str[len - 1];
			len--;
			i--;
		}
	return(buffer);
}

char	*conversion_string(char *str, t_flags *active)
{
	char	*buffer;
	int 	len_str;

	len_str = ft_strlen(str);
	if (active->precision > 0 && active->precision < len_str)
		str = ft_strsub(str, 0, active->precision);	
	else if (PRECISION == 0)
		str = ft_strdup("");	
	len_str = ft_strlen(str);
	if (active->width >= len_str)
	{
		if (active->flags >> 2 & 1 || !(active->flags >> 3 & 1))
			buffer = width(active->width, ' ');
		else
			buffer = width(active->width, '0');
		if (active->flags >> 2 & 1)
			insert_string(str, buffer, 0, active);
		else
			insert_string(str, buffer, active->width - 1, active);
	}
	else if (active->precision == 0)
		buffer = ft_strdup("");
	else
		buffer = ft_strdup(str);
	return (buffer);
}

char	*conversion_char(int c, t_flags *active, int *count)
{
	char	*buffer1;

	(MINUS) && (ZERO) && (active->flags -= 8);
	!(MINUS) && (WIDTH > 1) && (!(ZERO)) && (buffer1 = width(WIDTH - 1, ' '))
		&& ((*count) += write(1, buffer1, WIDTH - 1));
	!(MINUS) && (WIDTH > 1) && (ZERO) && (buffer1 = width(WIDTH - 1, '0'))
		&& ((*count) += write(1, buffer1, WIDTH - 1));
	((*count) += write(1, &c, 1));
	(MINUS) && (WIDTH > 1) && (buffer1 = width(WIDTH - 1, ' ')) \
		&& ((*count) += write(1, buffer1, WIDTH - 1));
	return (NULL);
}

char				*conversion_per(t_flags *active)
{
	char	*buffer1;

	(MINUS) && (ZERO) && (active->flags -= 8);
	(MINUS) && (WIDTH > 1) && (buffer1 = width(WIDTH - 1, ' ')) \
		&& (buffer1 = ft_strjoin("%", buffer1));
	!(MINUS) && (WIDTH > 1) && (!(ZERO)) && (buffer1 = width(WIDTH - 1, ' '))
		&& (buffer1 = ft_strjoin(buffer1, "%"));
	!(MINUS) && (WIDTH > 1) && (ZERO) && (buffer1 = width(WIDTH - 1, '0'))
		&& (buffer1 = ft_strjoin(buffer1, "%"));
	(WIDTH <= 1) && (buffer1 = ft_strdup("%"));
	return (buffer1);	
}

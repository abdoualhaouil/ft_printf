/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 02:34:07 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/08 22:26:49 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*zero(size_t n)
{
	char		*res;
	size_t		i;

	if (!(res = ft_strnew(n)))
		return (NULL);
	i = -1;
	while (++i < n)
		res[i] = '0';
	return (res);
}

static	int		active_precision(const char *str, t_flags **active, int i)
{
	i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
	{
		(*active)->precision = 0;
		return (i - 1);
	}
	(*active)->precision = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	return (i);
}

int				active_width(const char *str, t_flags **active, int i)
{
	(*active)->width = ft_atoi(str + i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		i++;
	}
	return (i - 1);
}

static	t_flags	*flags(t_flags *active)
{
	active->flags = 0;
	active->conversion = 0;
	active->precision = -1;
	active->width = 0;
	return (active);
}

t_flags			*check_active_flags(const char *str, int i)
{
	t_flags		*active;

	if (!(active = (t_flags *)malloc(sizeof(t_flags))))
		return (NULL);
	active = flags(active);
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' && \
		str[i] != 'X' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u' && \
		str[i] != 'x' && str[i] != 'f' && str[i++] != '\0')
	{
		(str[i] == '+') && (active->flags |= 1U);
		(str[i] == '#') && (active->flags |= 2U);
		(str[i] == '-') && (active->flags |= 4U);
		(str[i] == '0') && (active->flags |= 8U);
		(str[i] == ' ') && (active->flags |= 16U);
		(str[i] == '.') && (i = active_precision(str, &active, i));
		(str[i] > '0' && str[i] <= '9') && (i = active_width(str, &active, i));
		(str[i] == 'h') && (active->conversion |= 1U);
		(str[i] == 'l') && (active->conversion |= 2U);
		(str[i] == 'h' && str[i + 1] == 'h') && (active->conversion |= 4U);
		(str[i] == 'l' && str[i + 1] == 'l') && (active->conversion |= 8U);
		(str[i] == 'L') && (active->conversion |= 16U);
	}
	(active->width < 0) && (active->width = 0);
	(active->precision < -1) && (active->precision = 6);
	return (active);
}

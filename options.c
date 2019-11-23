/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:14:41 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 00:23:49 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



int		active_precision(char *str, t_flags **active, int i)
{
	i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
	{
		(*active)->precision = 0;
		return (i - 1);
	}
	(*active)->precision = ft_atoi(str + i);
	while (str[i] >= '0' && str[i++] <= '9');
	return(i - 1);
}

int		active_width(char *str, t_flags **active, int i)
{
	(*active)->width = ft_atoi(str + i);
	while (str[i] >= '0' && str[i++] <= '9');
	return(i - 1);
}

t_flags		*check_active_flags(char *str, int i)
{
	t_flags 		*active;
	
	active = (t_flags *)malloc(sizeof(t_flags));
	active->flags = 0;
	active->conversion = 0;
	active->precision = -1;
	active->width = 0;
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd' && str[i] != 'X' \
				&& str[i] != 'i' && str[i] != 'o' && str[i] != 'u' && str[i] != 'x' && str[i] != 'f' && str[i++] != '\0')
	{
		active->flags = (str[i] == '+') ? 1U | active->flags : active->flags;
		active->flags = (str[i] == '#') ? 2U | active->flags : active->flags;
		active->flags = (str[i] == '-') ? 4U | active->flags : active->flags;
		active->flags = (str[i] == '0') ? 8U | active->flags : active->flags;
		active->flags = (str[i] == ' ') ? 16U | active->flags : active->flags;
		if (str[i] == '.')
			i = active_precision(str, &active, i);
		if (str[i] > '0' && str[i] <= '9')
			i = active_width(str, &active, i);
		active->conversion = (str[i] == 'h') ? 1U | active->conversion : active->conversion;
		active->conversion = (str[i] == 'l') ? 2U | active->conversion : active->conversion;
		active->conversion = (str[i] == 'h' && str[i + 1] == 'h') ? 4U | active->conversion : active->conversion;
		active->conversion = (str[i] == 'l' && str[i + 1] == 'l') ? 8U | active->conversion : active->conversion;
		active->conversion = (str[i] == 'L') ? 16U | active->conversion : active->conversion;
	}
	(active->width < 0) && (active->width = 0);
	(active->precision < -1) && (active->precision = 6);
	return (active);
}


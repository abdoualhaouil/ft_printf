/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_exponent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:29:00 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/02 00:00:19 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*delete_zero_exponent(char *str)
{
	int		i;

	i = -1;
	if (str[0] == '0')
	{
		while (str[++i])
			str[i] = str[i + 1];
		str[i - 1] = '\0';
	}
	return (str);
}

char	*add_zero_exponent(char *n1, char *n2)
{
	char	*str;
	int		i;
	int		j;
	int		r;

	i = ft_strlen(n1);
	j = ft_strlen(n2);
	r = (i > j) ? i - j : j - i;
	str = zero(r);
	if (i < j)
		if (!(str = ft_strjoin(str, n1)))
			return (NULL);
	if (i >= j)
		if (!(str = ft_strjoin(str, n2)))
			return (NULL);
	return (str);
}

char	*addition_exponent(char *n1, char *n2)
{
	char	*res;
	int		i;
	int		j;
	int		remainder;
	int		colum;

	i = ft_strlen(n1);
	j = ft_strlen(n2);
	if ((i > j) && !(n2 = add_zero_exponent(n1, n2)))
		return (NULL);
	if ((i < j) && !(n1 = add_zero_exponent(n1, n2)))
		return (NULL);
	i = (i > j) ? i + 1 : j + 1;
	if (!(res = ft_strnew(i)))
		return (NULL);
	remainder = 0;
	while (--i > 0)
	{
		colum = remainder;
		colum += (n1[i - 1] - '0') + (n2[i - 1] - '0');
		remainder = colum / 10;
		res[i] = colum % 10 + '0';
	}
	res[0] = ((remainder == 0) ? 0 : 1) + '0';
	delete_zero_exponent(res);
	return (res);
}
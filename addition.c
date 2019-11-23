/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:18:33 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 21:42:48 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*delete_zero(char *str)
{
	int		i;

	i = 1;
	while (str[++i])
		str[i] = str[i + 1];
	str[i - 1] = str[i];
	return (str);
}

char	*add_zero(char *n1, char *n2)
{
	char	*str;
	char	*tmp;
	int 	i;
	int		j;
	int 	r;

	i = ft_strlen(n1);
	j = ft_strlen(n2);
	r = (i > j) ? i - j : j - i;
	str = zero(r);
	tmp = str;
	(i < j)	&& (str = ft_strjoin(n1, str));
	(i >= j) && (str = ft_strjoin(n2, str));
	free(tmp);
	return (str);
}


char	*addition(char *n1, char *n2)
{
	char	*res;
	char	*tmp;
	int 	i;
	int 	j;
	int 	remainder;
	int 	colum;

	i = ft_strlen(n1);
	j = ft_strlen(n2);
	if (i != j)
	{
		(i > j) && (tmp = n2) && (n2 = add_zero(n1, n2));
		(i < j) && (tmp = n1) && (n1 = add_zero(n1, n2));
		free (tmp);
	}
	i = (i > j) ? i : j;
	res = ft_strnew(i);
	remainder = 0;
	while (--i > 1)
	{
		colum = remainder;
		colum += (n1[i] - '0') + (n2[i] - '0');
		remainder = colum / 10;
		res[i] = colum % 10 + '0';
	}
	res[1] = '.';
	res[0] = '0';
	return (res);
}

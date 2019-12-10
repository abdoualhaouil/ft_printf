/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:48:47 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/07 23:08:47 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*add_zero(char *n1, char *n2)
{
	char	*str;
	char	*tmp;
	int		i;
	int		j;
	int		r;

	i = ft_strlen(n1);
	j = ft_strlen(n2);
	r = (i > j) ? i - j : j - i;
	str = zero(r);
	tmp = str;
	if ((i < j) && !(str = ft_strjoin(str, n1)))
		return (NULL);
	if ((i >= j) && !(str = ft_strjoin(str, n2)))
		return (NULL);
	free(tmp);
	return (str);
}

char	*tmp_addition(int i, char *n1, char *n2)
{
	char	*res;
	char	*tmp1;
	int		remainder;
	int		colum;

	if (!(res = ft_strnew(i)))
		return (NULL);
	remainder = 0;
	while (--i >= 0)
	{
		colum = remainder;
		colum += (n1[i] - '0') + (n2[i] - '0');
		remainder = colum / 10;
		res[i] = colum % 10 + '0';
	}
	if (remainder == 1)
	{
		tmp1 = res;
		if (!(res = ft_strjoin("1", res)))
			return (ft_free(res));
		free(tmp1);
	}
	return (res);
}

char	*addition(char *n1, char *n2, int op)
{
	char	*res;
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	i = ft_strlen(n1);
	j = ft_strlen(n2);
	if ((i < j) && !(n1 = add_zero(n1, n2)))
		return (ft_free2(n1, n2));
	if ((i > j) && !(n2 = add_zero(n1, n2)))
		return (ft_free2(n1, n2));
	(i > j) ? tmp = n2 : 0;
	(i < j) ? tmp = n1 : 0;
	i = (i > j) ? i : j;
	if (!(res = tmp_addition(i, n1, n2)))
		return (NULL);
	(tmp) ? free(tmp) : 0;
	if (op == 0)
		if (!(res = delete_zero(res)))
			return (ft_free(res));
	return (res);
}

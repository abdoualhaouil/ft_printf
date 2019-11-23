/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:29:23 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 22:37:37 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char    *join_point(char *str, int len_mantissa, char *exponent, int len_exponent)
{
	char    *first;
	char	*tmp;
	char    *second;
	int     len;
	int     len_str;
	int     i;

	i = 0;    
	len_str = ft_strlen(str);
	len = (exponent[1] == '.') ? len_exponent + len_mantissa - 4 : len_mantissa - 2;
	len = (len == 0) ? 1 : len;
	second = ft_strsub(str, len_str - len, len);
	if (exponent[1] != '.')
	{
		while (str[i] == '0')
			i++;
	 	first = ft_strsub(str, i, len_str - len - i);
		(tmp = first) && (first = ft_strjoin(first, "."));
		free (tmp);
		(tmp = second) && (second = ft_strjoin(first, second));
		free (tmp);
	}
	else 
		second = ft_strjoin("0.", second);
	return (second); 
}

char    *ft_tmp_multiplication(char *mantissa, char *exponent, char *res, int *k)
{
	int     totaldidgit;   
	int     remainder;
	int     i;

	i = ft_strlen(exponent);
	remainder = 0;
	while (--i >= 0)
	{
		if (exponent[i] != '.')
		{
			totaldidgit = ((*mantissa - '0') * (exponent[i] - '0')) + remainder;
			remainder = ((res[*k] - '0') + totaldidgit) / 10;
			res[*k] =  ((res[*k] - '0') + totaldidgit) % 10 + '0';
			if (i == 0 && remainder > 0)
				res[*k - 1] =  ((res[*k - 1] - '0') + remainder) + '0';
			(*k)--;
		}
	}
	return (res);
}

char    *multiplication(char *mantissa, char *exponent, int len_exp, int len_man)
{
	char    *res;
	char	*tmp;
	int     j;
	int     k;

	k = len_man + len_exp;
	res = zero(k + 1);
	j = len_man;
	while (--j >= 0)
	{
		if (mantissa[j] != '.')
		{
			res = ft_tmp_multiplication(mantissa + j, exponent, res, &k);
			k = j + len_exp;
		}
	}
	tmp = res;
	if (ft_strlen(res) == 3)
	{
		res = res + 2;
		res = ft_strjoin(res, ".0");
		free(tmp);
	}
	else
	{
		(mantissa[1] != '.') && (len_man++);
		(tmp = res) && (res = join_point(res, len_man, exponent, len_exp));
		free(tmp);
	}
	return (res);
}

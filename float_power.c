/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_power.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 03:18:33 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 21:33:51 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*zero(size_t n)
{
	char		*res;
	size_t		i;

	res = ft_strnew(n);
	i = 0;
	while (i < n)
	{
		res[i] = '0';
		i++;
	}
	return (res);
}

char	*ft_reverse(char *str, int size)
{
	char	tmp_swp;
	int		i;
	int 	tmp_lenstr;

	i = size;
	while (str[--i] == '0')
		str[i] = '\0';
	size = i;
	tmp_lenstr = i + 1;
	i = 0;
	while (i < size)
	{
		tmp_swp = str[i];
		str[i] = str[size];
		str[size] = tmp_swp;
		i++;
		size--;
	}
	return (str);
}

char	*power(int base, int exp)
{
	char	*res;
	int		i;
	int		j;
	int		carry;
	int		tmp;

	i = -1;
	res = zero(SIZE);
	res[0] = '1';
	while (++i < exp)
	{
		carry = 0;
		j = -1;
		while (++j < SIZE)
		{
			tmp = base * (res[j] - '0') + carry;
			carry = 0;
			(tmp > 9) && (res[j] = tmp % 10 + '0');
			(tmp > 9) && (carry = tmp / 10);
			(tmp <= 9) && (res[j] = tmp + '0');
		}
	}
	res = ft_reverse(res, SIZE);
	return (res);
}

char    *power_mantissa(int base, int exp)
{
	char	*final_mantissa;
	char	*tmp_char;
	int		lenstr;
	int 	i;
	char	*tmp;

	i = SIZE;
	final_mantissa = power(base, exp);
	lenstr = exp - ft_strlen(final_mantissa);
	tmp_char = zero(lenstr + 2);
	tmp_char[1] = '.';
	tmp = final_mantissa;
	final_mantissa = ft_strjoin(tmp_char, final_mantissa);
	free(tmp_char);
	free(tmp);
	return (final_mantissa);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 11:49:46 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/08 00:31:01 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		five_round(char *buffer, int precision)
{
	int	j;
	int len;

	len = ft_strlen(buffer);
	if (buffer[precision - 1] == '5')
	{
		j = precision - 1;
		while (buffer[++j])
			if (buffer[j] != '0')
				break ;
		if (j <= len - 1 || (((buffer[precision - 2] - '0') % 2 != 0)))
			return (1);
	}
	else
		return (1);
	return (0);
}

static	int		ft_round_frac_tmp(char **buff_frac, long int precision, int len)
{
	char	*buff;
	char	*tmp;

	if (len < precision)
	{
		if (!(buff = zero(precision - len)))
			return (-1);
		tmp = (*buff_frac);
		if (!((*buff_frac) = ft_strjoin((*buff_frac), buff)))
			return (-1);
		free(tmp);
		free(buff);
	}
	return (0);
}

static	int		ft_round_frac(char **buff_frac, long int precision, int len)
{
	char	*tmp;
	char	*buff;

	if (ft_round_frac_tmp(buff_frac, precision, len) == -1)
		return (-1);
	if ((*buff_frac)[precision] >= '5')
	{
		if ((five_round((*buff_frac), precision) == 0))
			return (0);
		if (!(tmp = zero(len)))
			return (-1);
		tmp[precision - 1] = '1';
		buff = *buff_frac;
		if (!((*buff_frac) = addition((*buff_frac), tmp, 1)))
			return (-1);
		ft_free2(buff, tmp);
		if (ft_strlen(tmp) < ft_strlen(*buff_frac))
		{
			tmp = (*buff_frac);
			(*buff_frac) = ft_strdup((*buff_frac) + 1);
			free(tmp);
			return (1);
		}
	}
	return (0);
}

static	char	*ft_round_whole(char *buff_whole, long int precision, int ret,
					t_flags *active)
{
	char	*buff;
	char	*tmp;

	if (ret == 1)
	{
		if (!(buff = (precision == 0) ? zero(1) : zero(precision)))
			return (NULL);
		(precision != 0) && (buff[precision - 1] = '1');
		(precision == 0) && (buff[precision] = '1');
		tmp = buff_whole;
		if (!(buff_whole = addition(buff, buff_whole, 0)))
			return (ft_free2(buff_whole, buff));
		free(tmp);
		free(buff);
	}
	if (precision != 0 || (precision == 0 && HASH))
	{
		tmp = buff_whole;
		if (!(buff_whole = ft_strjoin(buff_whole, ".")))
			return (ft_free(buff_whole));
		free(tmp);
	}
	return (buff_whole);
}

char			*ft_roundup(char *buff_frac, char *buff_whole, t_flags *active)
{
	char		*buff;
	long int	precision;
	int			ret;
	int			len;

	ret = 0;
	len = ft_strlen((buff_frac));
	(PRECISION == -1) && (precision = 6);
	(PRECISION != -1) && (precision = PRECISION);
	if (precision - 1 >= 0)
		if ((ret = ft_round_frac(&buff_frac, precision, len)) == -1)
			return (NULL);
	len = ft_strlen(buff_whole);
	if (precision - 1 < 0 && buff_frac[0] >= '5' && (five_round(buff_frac,
		precision + 1) || (buff_whole[len - 1] - '0') % 2 != 0))
		ret = 1;
	if (!(buff_whole = ft_round_whole(buff_whole, precision, ret, active)))
		return (NULL);
	buff_frac[precision] = '\0';
	buff = ft_strjoin(buff_whole, buff_frac);
	free(buff_frac);
	free(buff_whole);
	return (buff);
}

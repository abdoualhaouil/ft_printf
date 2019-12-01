/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 03:07:03 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/02 00:48:28 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>
#include <math.h>

int		main(void)
{
	long double d = 1.2;

	printf("%s\n", ft_float(d));
	printf("%.63Lf\n", d);
	return (0);
}

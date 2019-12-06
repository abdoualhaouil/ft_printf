/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 03:07:03 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 01:10:36 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>
#include <math.h>

int		main(void)
{
	long double d = LDBL_MAX;

	ft_printf("%5f|%-5f|%+5f|% 5f|%#5f|%05f\n", INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY);
	printf("%5f|%-5f|%+5f|% 5f|%#5f|%05f", INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY);
	return (0);
}

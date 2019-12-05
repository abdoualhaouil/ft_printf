/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 03:07:03 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/05 23:02:36 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>
#include <math.h>

int		main(void)
{
	long double d = LDBL_MAX;

	ft_printf("%Lf\n", LDBL_MAX);
	return (0);
}

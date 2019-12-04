/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 03:07:03 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/04 16:54:19 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>
#include <math.h>

int		main(void)
{
	long double d = 1.595666;

	printf("%d\n", ft_printf("%f", 1.011));
	printf("%d\n", printf("%f", 1.1));
	return (0);
}

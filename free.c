/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 01:50:22 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/08 01:50:35 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			*ft_free2(void *str, void *str1)
{
	free(str);
	free(str1);
	return (NULL);
}

int				ft_free3(void *str, void *str1, int n)
{
	free(str);
	free(str1);
	return (n);
}

void			*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

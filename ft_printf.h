/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 00:44:39 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/12/06 22:14:41 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define EXP (d->float_rep.exponent - 16383)
# define PLUS (active->flags & 1)
# define HASH (active->flags >> 1 & 1)
# define MINUS (active->flags >> 2 & 1)
# define ZERO (active->flags >> 3 & 1)
# define SPACE (active->flags >> 4 & 1)
# define PRECISION (active->precision)
# define WIDTH (active->width)

typedef	struct		s_flags
{
	int				precision;
	int				width;
	unsigned int	flags;
	unsigned int	conversion;
}					t_flags;

typedef struct		s_bitfields
{
	unsigned long int mantissa : 64;
	unsigned long int exponent : 15;
	unsigned long int sign : 1;
}					t_bitfields;

typedef	union		u_double
{
	long double		number;
	t_bitfields		float_rep;
}					t_double;

typedef	struct		s_float
{
	char	*buffer;
	char	*buffer2;
	char	*res;
	char	*tmp;
	int		i;
	int		j;
}					t_float;

t_flags				*check_active_flags(const char *str, int i);
int					ft_printf(const char *format, ...);
int					conv_char(int c, t_flags *active, int count);
int					conv_dec(va_list ap, t_flags *active, int count);
int					conv_unsigned_dec(va_list ap, t_flags *active, int count);
int					ft_write(char c, int size);
char				*ft_itoall(long long int n);
char				*ft_itoallu(unsigned long long int n);
int					conv_hexa(va_list ap, t_flags *active, char c, int count);
int					conv_octal(va_list ap, t_flags *active, int count);
int					conv_string(char *buffer, t_flags *active, int count);
char				*ft_power(int base, int exp);
char				*ft_float(long double number, t_flags *active);
char				*addition(char *n1, char *n2, int op);
char				*zero(size_t n);
char				*ft_float_calcul(t_double *d, int exp, int base);
char				*multiplication(char *mantissa, char *exponent, int op);
char				*add_zero(char *n1, char *n2);
char				*delete_zero(char *res);
int					conv_float(va_list ap, t_flags *active, int count);
char				*zero(size_t n);
char				*ft_roundup(char *buff_frac, char *buff_whole,
						t_flags *active);
char				*ft_float_frac(t_double *d, int exp, t_float *f);
char				*ft_float_whole(t_double *d, int exp, t_float *f);
int					find_nbr_zero(t_float *f, t_double *d, int exp);
void				*ft_free(void *ptr);
void				*ft_free2(void	*str, void *str1);
#endif

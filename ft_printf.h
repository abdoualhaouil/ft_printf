/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:58:04 by aalhaoui          #+#    #+#             */
/*   Updated: 2019/11/22 21:34:55 by aalhaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
#include <limits.h>
#define SIZE 16384

#define PLUS active->flags & 1
#define HASH active->flags >> 1 & 1
#define MINUS active->flags >> 2 & 1
#define ZERO active->flags >> 3 & 1
#define SPACE active->flags >> 4 & 1
#define PRECISION active->precision
#define WIDTH active->width

typedef	struct		s_flags
{
	int				precision;
	int				width;
	unsigned int	flags;
	unsigned int	conversion;
}					t_flags;

typedef struct		s_bitfields
{
	unsigned long int mantissa : 63;
	unsigned long int bit_cash : 1;
	unsigned long int exponent : 15;
	unsigned long int sign : 1;
}					t_bitfields;

typedef union		s_double
{
	long double		number;
	t_bitfields		float_rep;
}					t_double;

typedef	struct		s_mantissa
{
	char			*power;
	char			*a;
}					t_char;

char				*conversion_per(t_flags *active);
char				*conversion_float(va_list ap, t_flags *active);
int					tmp_dec(t_flags *active, int len_buffer, int minus);
char				*ft_float(long double number);
char				*power_mantissa(int base, int exp);
char				*itoa(size_t n);
char				*power(int base, int exp);
char				*ft_reverse(char *str, int size);
char				*zero(size_t n);
char				*addition(char *n1, char *n2);
char				*add_zero(char *n1, char *n2);
char				*delete_zero(char *str);
char				*addition_exponent(char *n1, char *n2);
char				*final_float(char *mantissa, unsigned long int exponent, t_double *d);
char				*multiplication(char *mantissa, char *exponent, int len_man, int len_exp);
t_flags				*check_active_flags(char *str, int i);
char				*conversion_char(int c, t_flags *active, int *count);
char				*find_function(t_flags *active, va_list ap, \
	char  conversion, int *count);
int					ft_printf(const char *format, ...);
char				*conversion_string(char *str, t_flags *active);
char				*conversion_pointer(size_t p, t_flags *active);
char				*dec_to_hex(size_t n, char c);
char				*width(size_t n, int c);
char				*conversion_dec(va_list ap, t_flags *active);
char				*ft_itoall(long long int n);
char				*insert_string(char *str, char *buffer, int i, t_flags *active);
int					active_precision(char *str, t_flags **active, int i);
int					active_width(char *str, t_flags **active, int i);
char				*conversion_unsigned_dec(va_list ap, t_flags *active);
char				*ft_itoallu(unsigned long long int n);
char				*find_type_octal(va_list ap, t_flags *active);
char				*conversion_octal(va_list ap, t_flags *active);
char				*dec_to_octal(size_t n);
char				*conversion_hexa(va_list ap, t_flags *active, char c);
char				*find_type_hexa(va_list ap, t_flags *active, char c);



#endif

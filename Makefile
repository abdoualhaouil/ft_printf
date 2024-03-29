NAME= libftprintf.a

SRC= active_flags.c\
	 conv_cs.c\
	 conv_dec.c\
	 conv_hexa.c\
	 ft_printf.c\
	 llitoa.c\
	 ullitoa.c\
	 conv_octal.c\
	 float.c\
	 power.c\
	 addition.c\
	 conv_float.c\
	 round.c \
	 tmp_float.c \
	 free.c

OBJ= $(SRC:.c=.o)
LIBSRC= libft/ft_atoi.c  	libft/ft_bzero.c			libft/ft_isalnum.c	\
		  libft/ft_isalpha.c	libft/ft_isascii.c	libft/ft_isdigit.c	 	\
		  libft/ft_isprint.c 	libft/ft_itoa.c 	libft/ft_memalloc.c	libft/ft_memccpy.c	libft/ft_memchr.c 	\
		  libft/ft_memcmp.c	libft/ft_memcpy.c		libft/ft_memdel.c 	\
		  libft/ft_memmove.c	libft/ft_memset.c		libft/ft_putchar.c	libft/ft_putchar_fd.c \
		  libft/ft_putendl.c	libft/ft_putendl_fd.c	libft/ft_putnbr.c		libft/ft_putnbr_fd.c	\
		  libft/ft_putstr.c	libft/ft_putstr_fd.c		libft/ft_strcat.c		\
		  libft/ft_strchr.c	libft/ft_strclr.c		libft/ft_strcmp.c		libft/ft_strcpy.c		\
		  libft/ft_strdel.c	libft/ft_strdup.c		libft/ft_strequ.c		libft/ft_striter.c	\
		  libft/ft_striteri.c	libft/ft_strjoin.c	libft/ft_strlcat.c	libft/ft_strlen.c		\
		  libft/ft_strmap.c	libft/ft_strmapi.c	libft/ft_strncat.c	libft/ft_strncmp.c 	\
		  libft/ft_strncpy.c	libft/ft_strnequ.c	libft/ft_strnew.c		libft/ft_strnstr.c 	\
		  libft/ft_strrchr.c		libft/ft_strsplit.c	libft/ft_strstr.c 	\
		  libft/ft_strsub.c	libft/ft_strtrim.c	libft/ft_tolower.c	libft/ft_toupper.c libft/ft_max.c	\

LIBOBJ= $(LIBSRC:.c=.o)

cc= gcc
GCF= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a $(LIBOBJ) ft_printf.h
	ar rc $(NAME) $(OBJ) $(LIBOBJ)
	ranlib $(NAME)

libft/libft.a:
	make -C libft

%.o: %.c 
	$(CC) $(GCF) -c $< -o $@

clean:
	make clean -C libft 
	rm -fr $(OBJ)

fclean: clean 
	make fclean -C libft 
	rm -fr $(NAME)

re: fclean all
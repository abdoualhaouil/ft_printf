# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalhaoui <aalhaoui@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 01:18:26 by aalhaoui          #+#    #+#              #
#    Updated: 2019/12/06 23:38:55 by aalhaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INC = libft.h
SRC = *.c
OBJ = *.o

all : $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror $(SRC) -I $(INC)
	ar rc $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

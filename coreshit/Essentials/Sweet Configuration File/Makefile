# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-goug <ele-goug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/23 05:39:41 by ele-goug          #+#    #+#              #
#    Updated: 2014/11/02 21:43:29 by ele-goug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= g++
NAME	= scf.a

SRC	= scf.cpp

OBJ	= $(SRC:.cpp=.o)

CFLAGS	= -I ./.. -Ofast -fpermissive

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

%.o:		%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:		all clean re fclean

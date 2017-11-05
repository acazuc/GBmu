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

NAME	= essentials.a

RM	= rm -f

SRC	= Capsule/capsule.a \
	  Sweet\ Configuration\ File/scf.a

all:
	make -C Capsule
	make -C Sweet\ Configuration\ File
	ar rcT $(NAME) $(SRC)
	ranlib $(NAME)

clean:
	make -C Capsule clean
	make -C Sweet\ Configuration\ File clean

fclean:
	make -C Capsule fclean
	make -C Sweet\ Configuration\ File fclean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean re fclean

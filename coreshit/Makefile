
CC	= g++
NAME	= Coretest

SRC	= memboy.cpp \
	  try.cpp

OBJ	= $(SRC:.cpp=.o)

CFLAGS	= -I . -I Essentials -std=gnu++11

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
	make -C Essentials
	$(CC) $(CFLAGS) $(OBJ) Essentials/essentials.a -o $(NAME)

clean:
	make -C Essentials clean
	$(RM) $(OBJ)

fclean:		clean
	make -C Essentials fclean
	$(RM) $(NAME)

re:		fclean all

%.o:		%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:		all clean re fclean

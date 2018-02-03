#####################################
##                                 ##
##             Krystal             ##
##	( development build )      ##
##                                 ##
##       Sweet Mare Software       ##
##       15/01/18 - --/--/18       ##
##                                 ##
#####################################

CC	= g++
NAME	= krystal.a

SRC	= krystal.cpp

OBJ	= $(SRC:.cpp=.o)

CFLAGS	= -I ./.. -std=gnu++11 -O1 -fpermissive -lpthread

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

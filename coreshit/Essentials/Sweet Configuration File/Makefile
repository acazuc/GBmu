######################################
##                                  ##
##     Sweet Configuration File     ##
##	     ( 1st try )            ##
##                                  ##
##       Sweet Mare Software        ##
##       05/09/17 - --/--/17        ##
##                                  ##
######################################

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

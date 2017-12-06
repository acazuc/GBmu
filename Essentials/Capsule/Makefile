######################################
##                                  ##
##             Capsule              ##
##             ( beta )             ##
##                                  ##
##       Sweet Mare Software        ##
##                                  ##
######################################

CC	= g++
NAME	= capsule.a

SRC	= ring/gen.cpp \
	  ring/crush.cpp \
	  ring/add.cpp \
	  ring/per.cpp \
	  ring/get.cpp \
	  ring/put.cpp \
	  ring/lock.cpp \
	  ring/jump.cpp \
	  ring/rem.cpp \
	  ring/spin.cpp \
	  ring/clear.cpp \
          magictable/gen.cpp \
          magictable/add.cpp \
          magictable/get.cpp \
          magictable/put.cpp \
          magictable/allstar.cpp

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

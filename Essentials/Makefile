######################################
##                                  ##
##       The Essentials Sweet       ##
##             ( beta )             ##
##                                  ##
##       Sweet Mare Software        ##
##     last revision 21/11/17       ##
##                                  ##
######################################

NAME	= essentials.a

RM	= rm -f

SRC	= Capsule/capsule.a \
	  Sweet\ Configuration\ File/scf.a \
	  Krystal/krystal.a

all:
	make -C Capsule
	make -C Sweet\ Configuration\ File
	make -C Krystal
	ar rcT $(NAME) $(SRC)
	ranlib $(NAME)

clean:
	make -C Capsule clean
	make -C Sweet\ Configuration\ File clean
	make -C Krystal clean

fclean:
	make -C Capsule fclean
	make -C Sweet\ Configuration\ File fclean
	make -C Krystal fclean
	$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean re fclean

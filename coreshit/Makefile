
CC	= g++
NAME	= Coretest

SRC	= InstructionSet/_blank.cpp \
	  InstructionSet/instructionstable.cpp \
	  InstructionSet/ldrr.cpp \
	  InstructionSet/ldrn.cpp \
	  InstructionSet/ldrhl.cpp \
	  InstructionSet/ldhlr.cpp \
	  InstructionSet/ldhln.cpp \
	  InstructionSet/ldabc.cpp \
	  InstructionSet/ldade.cpp \
	  InstructionSet/ldarc.cpp \
	  InstructionSet/ldrca.cpp \
	  InstructionSet/ldarn.cpp \
	  InstructionSet/ldrna.cpp \
	  InstructionSet/ldann.cpp \
	  InstructionSet/ldnna.cpp \
	  InstructionSet/ldahli.cpp \
	  InstructionSet/ldahld.cpp \
	  InstructionSet/ldbca.cpp \
	  InstructionSet/lddea.cpp \
	  InstructionSet/ldhlia.cpp \
	  InstructionSet/ldhlda.cpp \
	  InstructionSet/ldddnn.cpp \
	  InstructionSet/ldsphl.cpp \
	  InstructionSet/push.cpp \
	  InstructionSet/pop.cpp \
	  InstructionSet/ldhlspe.cpp \
	  InstructionSet/ldnnsp.cpp \
	  InstructionSet/addar.cpp \
	  InstructionSet/addan.cpp \
	  InstructionSet/addahl.cpp \
	  InstructionSet/adcar.cpp \
	  InstructionSet/adcan.cpp \
	  InstructionSet/adcahl.cpp \
	  InstructionSet/subar.cpp \
	  InstructionSet/suban.cpp \
	  InstructionSet/subahl.cpp \
	  InstructionSet/sbcar.cpp \
	  InstructionSet/sbcan.cpp \
	  InstructionSet/sbcahl.cpp \
	  InstructionSet/andr.cpp \
	  InstructionSet/andn.cpp \
	  InstructionSet/andhl.cpp \
	  InstructionSet/orr.cpp \
	  InstructionSet/orn.cpp \
	  InstructionSet/orhl.cpp \
	  InstructionSet/xorr.cpp \
	  InstructionSet/xorn.cpp \
	  InstructionSet/xorhl.cpp \
	  InstructionSet/cpr.cpp \
	  InstructionSet/cpn.cpp \
	  InstructionSet/cphl.cpp \
	  \
	  InstructionSet/jp.cpp \
	  InstructionSet/jpcc.cpp \
	  InstructionSet/nop.cpp \
	  memboy.cpp \
	  core.cpp \
	  mastercore.cpp

OBJ	= $(SRC:.cpp=.o)

CFLAGS	= -I . -I InstructionSet -I Essentials -std=gnu++11

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


CC	= g++
NAME	= libcore.a

SRC	= InstructionSet/_blank.cpp \
	  InstructionSet/instructionstable.cpp \
	  InstructionSet/extendedtable.cpp \
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
	  InstructionSet/incr.cpp \
	  InstructionSet/incrhl.cpp \
	  InstructionSet/decr.cpp \
	  InstructionSet/decrhl.cpp \
	  InstructionSet/addhlss.cpp \
	  InstructionSet/addspe.cpp \
	  InstructionSet/incss.cpp \
	  InstructionSet/decss.cpp \
	  InstructionSet/rlca.cpp \
	  InstructionSet/rla.cpp \
	  InstructionSet/rrca.cpp \
	  InstructionSet/rra.cpp \
	  InstructionSet/rlcr.cpp \
	  InstructionSet/rlchl.cpp \
	  InstructionSet/rlr.cpp \
	  InstructionSet/rlhl.cpp \
	  InstructionSet/rrcr.cpp \
	  InstructionSet/rrchl.cpp \
	  InstructionSet/rrr.cpp \
	  InstructionSet/rrhl.cpp \
	  InstructionSet/slar.cpp \
	  InstructionSet/slahl.cpp \
	  InstructionSet/srar.cpp \
	  InstructionSet/srahl.cpp \
	  InstructionSet/srlr.cpp \
	  InstructionSet/srlhl.cpp \
	  InstructionSet/swapr.cpp \
	  InstructionSet/swaphl.cpp \
	  InstructionSet/bitbr.cpp \
	  InstructionSet/bitbhl.cpp \
	  InstructionSet/setbr.cpp \
	  InstructionSet/setbhl.cpp \
	  InstructionSet/resbr.cpp \
	  InstructionSet/resbhl.cpp \
	  InstructionSet/jp.cpp \
	  InstructionSet/jpcc.cpp \
	  InstructionSet/jr.cpp \
	  InstructionSet/jrcc.cpp \
	  InstructionSet/jphl.cpp \
	  InstructionSet/call.cpp \
	  InstructionSet/callcc.cpp \
	  InstructionSet/ret.cpp \
	  InstructionSet/reti.cpp \
	  InstructionSet/retcc.cpp \
	  InstructionSet/rstb.cpp \
	  InstructionSet/daa.cpp \
	  InstructionSet/cpla.cpp \
	  InstructionSet/nop.cpp \
	  InstructionSet/ccf.cpp \
	  InstructionSet/scf.cpp \
	  InstructionSet/di.cpp \
	  InstructionSet/ei.cpp \
	  InstructionSet/halt.cpp \
	  InstructionSet/stop.cpp \
	  memboy.cpp \
	  core.cpp \
	  mastercore.cpp

OBJ	= $(SRC:.cpp=.o)

CFLAGS	= -I . -I InstructionSet -I ../Essentials -std=gnu++11 -Ofast -flto

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
	gcc-ar rc $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

%.o:		%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:		all clean re fclean


all:	
	rgbasm -o tamere.o tamere.s
	rgblink -o yay.gb tamere.o
	./gbcs yay.gb
	rgbasm -o stupiddraw.o stupiddraw.s
	rgblink -o stupiddraw.gb stupiddraw.o
	./gbcs stupiddraw.gb
	rgbasm -o freetests.o freetests.s
	rgblink -o freetests.gb freetests.o
	./gbcs freetests.gb

.PHONY:	all

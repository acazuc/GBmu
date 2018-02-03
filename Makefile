# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acazuc <acazuc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 06:50:12 by acazuc            #+#    #+#              #
#    Updated: 2017/12/13 13:45:41 by acazuc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Build/gbmu

CC = g++

CFLAGS = -g -Ofast -std=c++11 -flto

INCLUDES_PATH = include/ -I coreshit -I Essentials

SRCS_PATH = src/

SRCS_NAME = Main.cpp \
	    LCD.cpp \
	    MainDisplay.cpp \
	    DebugDisplay.cpp \
	    Audio.cpp \
	    BindDisplay.cpp \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = obj/

OBJS_NAME = $(SRCS_NAME:.cpp=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

LIBRARY = `pkg-config --cflags --libs gtk+-3.0` -lGL -lepoxy -lportaudio -L coreshit -L Essentials -lcore -lessentials

all: odir $(NAME)

$(NAME): $(OBJS) coreshit/libcore.a
	@echo " - Making $(NAME)"
	@$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBRARY)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@echo " - Compiling $<"
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDES_PATH) $(LIBRARY)

coreshit/libcore.a:

odir:
	make -C coreshit
	@mkdir -p $(OBJS_PATH)

clean:
	make -C coreshit clean
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	make -C coreshit fclean
	@echo " - Cleaning executable"
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re odir

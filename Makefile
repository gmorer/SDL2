# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2019/03/05 18:26:42 by tet              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Inner

CC = gcc -g

CFLAGS = -Werror -Wall -Wextra

LDLIBS = $(shell sdl2-config --libs) -lSDL2 -lSDL2_ttf -lSDL2_image -lm

LDFLAGS = $(shell sdl2-config --cflags)

CPATH = src/

CFILES = \
	main.c \
	map_generator.c \
	loop.c \
	game.c \
	menu.c \
	menu_buttons.c \
	options.c \
	init_sdl.c \
	event.c \
	file_selector.c \
	sdl_lib.c \
	alert.c

OPATH = obj/

OFILES = $(CFILES:.c=.o)

OBJ = $(addprefix $(OPATH), $(OFILES))

HPATH = inc/

HFILES = \
	inc/inc.h \
	inc/menu.h \
	inc/file_selector.h

INC = $(addprefix -I , $(HPATH))

.PHONY: all install clean fclean re

all: $(NAME)

$(NAME): $(OPATH) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

$(OPATH):
	mkdir -p $(OPATH)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2016/11/22 11:58:26 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Minesweeper

CC = clang

CFLAGS = -Werror -Wall -Wextra -g

LDLIBS = $(shell sdl2-config --libs) -lSDL2 -lSDL2_ttf -lSDL2_image -lm

LDFLAGS = $(shell sdl2-config --cflags)

CPATH = src/

CFILES = \
	main.c \
	map_generator.c \
	loop.c \
	game.c \
	menu.c \
	options.c \
	init_sdl.c

OPATH = obj/

OFILES = $(CFILES:.c=.o)

OBJ = $(addprefix $(OPATH), $(OFILES))

HPATH = inc/

HFILES = \
	inc/inc.h

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

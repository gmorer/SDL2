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

NAME = line
CC = clang
SDL = SDL2-2.0.5
CFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_image
FLAGS = -Weverything -g
CPATH = src/
OPATH = obj/
HPATH = inc/
INC = $(addprefix -I , $(HPATH))
CFILES = main.c\
				 draw.c\
				 tab.c\
				 texture.c\
				 loop.c\
				 mouse.c\
				 init_res.c\
				 close.c
OFILES = $(CFILES:.c=.o)
HFILES = inc/inc.h\
				 inc/image.h\
				 inc/texture.h\
				 inc/event.h\
				 inc/res.h
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(FLAGS) $(CFLAGS) -o $(NAME)

install :
		./install_sdl.sh

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
		mkdir -p $(OPATH)
		$(CC) $(FLAGS) $(INC) $< -c -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

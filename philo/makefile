# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/11 11:17:11 by bsomers       #+#    #+#                  #
#    Updated: 2022/09/22 12:24:51 by bsomers       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = 	philo.c \
		parse.c \
		utils.c \
		actions.c \
		get_time.c \
		init.c \
		print.c

HEADER = philo.h

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		cc $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
		cc -c $(CFLAGS) -o $@ $<

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)
re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re

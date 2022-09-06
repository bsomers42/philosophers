# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/11 11:17:11 by bsomers       #+#    #+#                  #
#    Updated: 2022/09/06 17:55:43 by bsomers       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = 	philo.c \
		parse.c \
		parse_utils.c \
		actions.c \
		get_time.c \
		init.c \
		print.c

HEADER = philo.h

CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=address

OBJ = $(SRC:.c=.o)

ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address
else
	CFLAGS += -Ofast
endif

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

# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bsomers <bsomers@student.42.fr>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/11 11:17:11 by bsomers       #+#    #+#                  #
#    Updated: 2022/06/11 11:18:56 by bsomers       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c

HEADER = philo.h

CFLAGS = -Wall -Wextra -Werror -pthread

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
		$(CC) -c $(CFLAGS) -o $@ $<

clean:
		rm -f $(OBJ)
		@make clean -C $(LIBFT)

fclean: clean
		rm -f $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: all clean fclean re

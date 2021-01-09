# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kawish <kawish@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/09 09:52:36 by kawish        #+#    #+#                  #
#    Updated: 2021/01/09 14:24:56 by kawish        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf
OBJ_FILES = main.o ft_printf.o
HEADER_FILES = ft_printf.h
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
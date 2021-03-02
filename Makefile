# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kawish <kawish@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2021/01/09 09:52:36 by kawish        #+#    #+#                  #
#    Updated: 2021/03/02 13:12:06 by kgajadie      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
OBJ_FILES = ft_printf.o \
			set.o \
			format_s.o \
			format_c.o \
			format_d.o \
			format_u.o \
			format_x.o \
			format_p.o \
			utils.o \
			uitoa.o \
			uitoa_hex.o \
			precision_width_diuxp.o

HEADER_FILE = ft_printf.h
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	cp $< $@
	ar -crs $@ $(OBJ_FILES)

%.o: %.c $(HEADER_FILE)
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIBFT):
	make -C libft

clean:
	make fclean -C libft
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
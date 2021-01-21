/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/09 10:17:02 by kawish        #+#    #+#                 */
/*   Updated: 2021/01/19 17:47:49 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

struct fields {
	int is_minus;
	int is_zeroed;
	int width;
	int precision;
	char conv_char;
};

# include "../libft/libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>

void	strprintf(char *fmt, ...);
int		ft_is_nonzerodigit(int c);
int		ft_printf(const char *fmt, ...);
void	ft_putstr_fd(char *s, int fd);

# endif

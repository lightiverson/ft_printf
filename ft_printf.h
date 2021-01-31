/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/09 10:17:02 by kawish        #+#    #+#                 */
/*   Updated: 2021/01/26 16:09:04 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdbool.h>

/*
** struct
*/
struct		fields
{
	int		is_minus;
	int		is_zeroed;
	int		width;
	int		precision;
	char	conv_char;
};

/*
** ft_printf prototype
*/
int			ft_printf(const char *fmt, ...);


void		strprintf(char *fmt, ...);
int			ft_is_nonzerodigit(int c);
void		ft_putstr_fd(char *s, int fd);
void		print_fields(struct fields *f);

# endif

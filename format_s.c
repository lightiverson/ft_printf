/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_s.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 12:02:57 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/07 15:27:13 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		width_s(char *sval_dup, int sval_dup_len, struct fields *fp)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (fp->is_minus)
	{
		ft_putstr_fd(sval_dup, 1);
		while (j < (fp->width - sval_dup_len))
		{
			write(1, &fp->padding_char, 1);
			j++;
		}
	}
	else
	{
		while (i < (fp->width - sval_dup_len))
		{
			write(1, &fp->padding_char, 1);
			i++;
		}
		ft_putstr_fd(sval_dup, 1);
	}
	fp->count = fp->count + strlen(sval_dup) + (fp->width - sval_dup_len);
}

void		format_s(struct fields *fp, char *sval)
{
	char			sval_dup[strlen(sval) + 1];
	int				sval_dup_len;

	strlcpy(sval_dup, sval, sizeof(sval_dup));
	sval_dup_len = strlen(sval_dup);
	if (((fp->precision >= 0) && (fp->precision < sval_dup_len)))
	{
		sval_dup[fp->precision] = '\0';
		sval_dup_len = strlen(sval_dup);
	}
	if (sval_dup_len < fp->width)
		width_s(sval_dup, sval_dup_len, fp);
	else
	{
		ft_putstr_fd(sval_dup, 1);
		fp->count = fp->count + strlen(sval_dup);
	}
}

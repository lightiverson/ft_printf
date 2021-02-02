/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kawish <kawish@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/24 14:35:22 by kawish        #+#    #+#                 */
/*   Updated: 2021/02/02 17:22:59 by kawish        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Printf converts, formats, and prints its arguments on the standard out under the control of the format. [Description]
** It returns the number of characters printed. [Return value]
** The format string contains two types of objects:
** ordinary characters, which are copied to the output stream, [Dit is één functie.]
** and conversion specifications, each of which cause conversion and printing of the next succesive argument to printf. [Dit is één functie.]
** Each conversion specification begins with a % and ends with a conversion character. [Zo kan je filteren op een conversion specification.]
** Syntax
** The syntax for a format placeholder is
** %[parameter][flags][width][.precision][length]type
*/

/*
** init_fields: intializes struct fields
*/

void		init_fields(struct fields *fp)
{
	// fp->is_minus = 0;
	fp->is_minus = false;
	fp->is_zeroed = 0;
	fp->width = 0;
	fp->precision = -1;
	fp->conv_char = '\0';
}

/*
** set_fields: iterates through the format placeholder and edits the members of the fields struct accordingly.
** Takes as arguments pointer p to the position in the format placeholder string. The list of unnamed arguments ap. And pointer to the fields struct fp.
** Returns a pointer p to a position in string fmt at the format specifier .
** 
** int i: holds the precision value from the struct.
** first the code checks for - or 0.
** then the code checks for the width field.
** then the precision field.
** then the conversion character.
** then any incombatibilities between precies fields.
** 
** The Precision field usually specifies a maximum limit on the output, depending on the particular formatting type.
** For the string type, it limits the number of characters that should be output, after which the string is truncated.
** For floating point numeric types, it specifies the number of digits to the right of the decimal point that the output should be rounded.
*/

const char	*set_fields(const char *p, va_list ap, struct fields *fp)
{
	int	i;
	
	// printf("\nset_fields()\n");

	p++;

	while (*p == '-' || *p == '0')
	{
		if (*p == '-')
			fp->is_minus = true;
		if (*p == '0')
			fp->is_zeroed = 1;
		p++;
	}
	if (ft_is_nonzerodigit(*p))
	{
		if (*p == '-')
		{
			fp->is_minus = true;
			p++;
		}
		fp->width = atoi(p);
		while (isdigit(*p))
			p++;
	}
	if (*p == '.') 
	{
		p++;
		if (*p == '*')
		{
			i = va_arg(ap, int);
			if (i >= 0)
				fp->precision = i;
			p++;
		}
		else
		{
			if (*p == '-')
				p++;
			else
				fp->precision = atoi(p);
			while (isdigit(*p))
				p++;
		}
	}
	fp->conv_char = *p;
	if (fp->is_zeroed && fp->is_minus)
	{
		// printf("fp->is_zeroed AND fp->is_minus are TRUE\n");
		fp->is_zeroed = 0;
	}
	if ( fp->is_zeroed && ( (fp->precision > -1) && (fp->conv_char == 'd') ) )
	{
		fp->is_zeroed = 0;
	}
	
	/* if a precision is given with a numeric conversion, the 0 flag is ignored. */
	// print_fields(fp);
	return (p);
}

/*
** get_format_string: writes formatted version of current argument string ca to stdout.
** Takes as arguments pointer to the struct, and the the current argument string ca.
** Returns nothing as of now. Should return the number of characters written to stdout.
** 
** char ca_dup[strlen(ca) + 1]: is a duplicate of current argument. Created so that we can truncate the string by changing a character to '\0'.
** int ca_dup_len: is the length of the duplicate of current argument.
** int i, j: are counter variables.
** char c: the padding character.
*/

void		get_format_string(struct fields *fp, char *ca)
{
	char			ca_dup[strlen(ca) + 1];
	int				ca_dup_len;
	int				i;
	int				j;
	char			c;

	strlcpy(ca_dup, ca, sizeof(ca_dup));
	ca_dup_len = strlen(ca_dup);
	i = 0;
	j = 0;
	c = ' ';

	if (fp->is_zeroed)
		c = '0';
	if (((fp->precision >= 0) && (fp->precision < ca_dup_len)))
	{
		ca_dup[fp->precision] = '\0';
		ca_dup_len = strlen(ca_dup);
	}
	if (ca_dup_len < fp->width)
	{
		if (fp->is_minus)
		{
			ft_putstr_fd(ca_dup, 1);
			while (j < (fp->width - ca_dup_len))
			{
				write(1, &c, 1);
				j++;
			}
		}
		else
		{
			while (i < (fp->width - ca_dup_len))
			{
				write(1, &c, 1);
				i++;
			}
			ft_putstr_fd(ca_dup, 1);
		}
	}
	else
		ft_putstr_fd(ca_dup, 1);
}

int			count_chars(int n)
{
	int c;

	c = 0;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
	{
		n = n * -1;
		c++;
	}
	while (n > 9)
	{
		c++;
		n = n / 10;
	}
	c++;
	return (c);
}

int			count_digits(int n)
{
	int c;

	c = 0;
	if (n == -2147483648)
		return (10);
	else if (n < 0)
	{
		n = n * -1;
	}
	while (n > 9)
	{
		c++;
		n = n / 10;
	}
	c++;
	return (c);
}

char*		precision_d(struct fields *fp, char *a, int num_of_digits)
{
	char			*ret;
	char			*ret_dup;
	int				i;

	// printf("fp->precision + strlen(a) = %d\n", fp->precision + strlen(a));
	ret = malloc((fp->precision + strlen(a)) * sizeof(*ret));
	if (!ret)
		return NULL;

	i = 0;
	ret_dup = ret;

	strlcpy(ret_dup, a, fp->precision + strlen(a));
	// printf("ret = %s\n", ret);

	if (*a == '-')
		ret_dup++;

	memmove( ret_dup+(fp->precision - num_of_digits), ret_dup, fp->precision - num_of_digits );
	// printf("ret = %s\n", ret);

	while (i < fp->precision - num_of_digits)
	{
		*ret_dup = '0';
		ret_dup++;
		i++;
	}
	// printf("ret = %s\n", ret);

	free(a);
	return(ret);
}

char* width_d(int chars_a, struct fields *fp, int dval, int digits_a, char *a)
{
	char ret[fp->width + chars_a + 1]; // 5 + 3 + 1
	char *p_ret;
	int i;

	i = 0;
	p_ret = ret;

	strlcpy(ret, ft_itoa(dval), sizeof(ret));
	printf("\nret = %s\n", ret);

	if (*p_ret == '-')
	p_ret++;

	memmove(p_ret+(fp->width - chars_a), p_ret, digits_a);
	printf("\nret = %s\n", ret);

	while (i < fp->width - chars_a)
	{
		p_ret[i] = '0';
		i++;
	}

	return (ret);
}

void		format_d(struct fields *fp, int dval)
{
	// Eigenlijk heb je ze alle drie nodig:
	// het aantal digits
	// het aantal characters
	// de string of dval

	char			*a;
	int				digits_a;
	int				chars_a;

	a = ft_itoa(dval);
	if (!a)
		return;

	digits_a = count_digits(dval);
	// printf("digits_a = %d\n", digits_a);

	chars_a = count_chars(dval);
	// printf("chars_a = %d\n", chars_a);

	if (fp->precision >= 0 && digits_a < fp->precision)
		a = precision_d(fp, a, digits_a);

	// width
	if (chars_a < fp->width) // 3 < 5
	{
		a = width_d(chars_a, fp, dval, digits_a, a);
	}
	

	ft_putstr_fd(a, 1);
}

void		format(va_list ap, struct fields *fp)
{
	char			*ca;
	int				dval;

	if (fp->conv_char == 's')
	{
		ca = va_arg(ap, char*);
		if (ca == NULL)
			get_format_string(fp, "(null)");
		else
			get_format_string(fp, ca);
	}
	else if (fp->conv_char == 'd')
	{
		dval = va_arg(ap, int);
		format_d(fp, dval);
	}
}

/*
** iterate_fmt: loops over the string fmt per character. Any character that is not % gets written to terminal. If a character equals % set_fields() is called. And then get_format_string is called.
** Takes as arguments string fmt, list of unnamend arguments, and a pointer to the struct declared in ft_printf.
** Returns the number of characters written to terminal.
** 
** const char p: pointer to fmt as to not lose the original pointer to fmt.
** char *ca; ca stands for current argument. Pointer to the current argument in va_list ap.
** if (*p != '%'): handles ordinary characters. Else handles percentage and characters following until format specifier.
** in the else block, set_fields() is called and returns a pointer p to a position in string fmt at the format specifier.
** in the else block, get_format_string() is called and writes the formatted string to stdout.
*/

int			interate_fmt(const char *fmt, va_list ap, struct fields *fp)
{
	// printf("\niterate_fmt()\n");
	const char		*p;

	p = fmt;
	init_fields(fp);
	// print_fields(fp);

	while (*p)
	{
		if (*p != '%')
			write(1, p, 1);
		else
		{
			p = set_fields(p, ap, fp);
			format(ap, fp);
		}
		p++;
	}
	return (0);
}

/*
** ft_printf: my version of printf.
** Takes as arguments string fmt, and unnamed arguments.
** Returns the number of characters written to terminal.
** 
** va_list ap: ap stands for arguments pointer. Special type of variable that points to list of unnamed arguments.
** struct fields f: fields describes all the conversion fields variables. For example flags, width specifier.
** int ret: stands for return. Keeps track of the number of characters written, and returns this value as last step.
*/

int			ft_printf(const char *fmt, ...)
{
	// printf("\nft_// printf()\n");
	va_list			ap;
	struct fields	f;
	int				ret;

	va_start(ap, fmt);
	ret = interate_fmt(fmt, ap, &f);
	va_end(ap);
	return (ret);
}

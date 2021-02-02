#include "ft_printf.h"

// /* kijk of je overal ca_dup kan gebruiken ipv ca */
void		bu_get_format_string(struct fields *fp, char *ca)
{
	// printf("\nget_format_string()\n");

	char s[(fp->width + (strlen(ca) + 1))];
	char ca_dup[strlen(ca) + 1];
	int ca_dup_len;
	
	strlcpy(ca_dup, ca, sizeof(ca_dup));
	ca_dup_len = strlen(ca_dup);

	if (fp->is_zeroed)
		memset(s, '0', sizeof(s));
	else
		memset(s, ' ', sizeof(s));
	if (((fp->precision >= 0) && (fp->precision < ca_dup_len)))
	{
		// printf("fp->precision is 0 of groter EN kleiner dan ca_dup_len\n");

		ca_dup[fp->precision] = '\0';
		ca_dup_len = strlen(ca_dup);
	}
	if (fp->width > ca_dup_len)
	{ 
		// printf("fp->width is groter dan ca_dup_len\n");

		s[fp->width] = '\0'; /* dan moet s, fp->width + 1 lang zijn */
		if (fp->is_minus) 
			strncpy(s, ca_dup, ca_dup_len); /* moet abcdef aan het begin van s */
		else 
			strncpy(s+(fp->width - ca_dup_len), ca_dup, ca_dup_len); /* moet abcdef aan het eind van s */
	}
	else
		strlcpy(s, ca_dup, sizeof(s));
		ft_putstr_fd(s, 1);
}

int			int_len(int n)
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

void		back_up_format_d(struct fields *fp, int dval)
{
	// "xxxxx-0028" width = 10, precision = 4
	// dval = -28
	// precision = 4
	// width = 10;
	// dval_len = 3;
	char s[fp->width + int_len(dval)];
	char *p;
	int dval_len;
	char c;
	
	// memset(s, '\0', sizeof(s));
	p = s;
	dval_len = int_len(dval);
	c = ' ';

	if (fp->is_zeroed)
		c = '0';

	if (dval < 0)
	{
		*p++ = '-'; // s = "-"
		dval = dval * -1; // dval = 28
		dval_len = int_len(dval);
	}

	if (((fp->precision >= 0) && (fp->precision > dval_len)))
	{
		memset(p, '0', (fp->precision - dval_len)); // s = "-00"
		p = p + (fp->precision - dval_len);
	}

	// printf("dval = %d\n", dval);
	// printf("ft_itoa(dval) = %s\n", ft_itoa(dval));
	strlcpy(p, ft_itoa(dval), (strlen(ft_itoa(dval)) + 1));
	// printf("s = %s\n", s); // "-0028"

	if (fp->width > (int)strlen(s))
	{
		if (fp->is_minus)
		{
			ft_putstr_fd(s, 1);
			while (fp->width > (int)strlen(s))
			{
				write(1, &c, 1);
				fp->width--;
			}
		}
		else
		{
			while (fp->width > (int)strlen(s))
			{
				write(1, &c, 1);
				fp->width--;
			}
			ft_putstr_fd(s, 1);
		}
	}
	else
	{
		ft_putstr_fd(s, 1);
	}
}

void		back_up_precision_d(struct fields *fp, int dval)
{
	char *digits;
	char *answer;
	int digits_len;
	int is_nega;

	is_nega = false;
	if (dval < 0)
	{
		is_nega = true;
	}
	
	digits = ft_itoa(dval);
	printf("digits = %s\n", digits);
	digits_len = (int)strlen(digits);
	printf("digits_len = %d\n", digits_len);

	if (fp->precision >= 0 && fp->precision > digits_len)
	{
		answer = malloc((fp->precision + digits_len) * sizeof(*answer));
		// answer = calloc(1, (fp->precision + digits_len) * sizeof(*answer));
		// memset(answer, 'x', fp->precision + digits_len);
		// answer[fp->precision + digits_len] = '\0';
		// printf("strlen(answer) = %lu\n", strlen(answer));

		strlcpy(answer, digits, fp->precision + digits_len);

		// je moet answer na de min 2 plekken opschuiven
		// -__52
		// memmove(answer+3, answer+1, 2);

		// printf("x = %d\n", is_nega+(fp->precision-(digits_len-is_nega)));
		// printf("c = %d\n", is_nega);
		// printf("v = %d\n", fp->precision-(digits_len-is_nega));
		memmove( answer+(is_nega+(fp->precision-(digits_len-is_nega))), answer+(is_nega), fp->precision-(digits_len-is_nega) );

		answer[1] = '0';
		answer[2] = '0';
		printf("answer = %s\n", answer);

		// precision = 4
		// number of digits = 3
		// is_nega = 1
	}
	
}

void back_up_1_precision_d(struct fields *fp, int dval)
{
	char *digits;
	char *answer;
	char *answer_dup;
	int no_of_digits;
	int is_negative;
	int i;

	i = 0;
	is_negative = 0;
	digits = ft_itoa(dval);
	// printf("digits = %s\n", digits);

	if (*digits == '-')
	{
		is_negative = 1;
		digits++;
	}
	no_of_digits = (int)strlen(digits);
	// printf("no_of_digits = %d\n", no_of_digits);

	if (fp->precision >= 0 && no_of_digits < fp->precision)
	{
		answer = malloc((fp->precision + no_of_digits + is_negative) * sizeof(*answer));
		if (!answer)
		{
			// printf("malloc() failed!");
			return;
		}
		answer_dup = answer;
		
		// printf("fp->precision + no_of_digits + is_negative = %d\n", (fp->precision + no_of_digits + is_negative));

		if (is_negative)
		{
			*answer_dup = '-';
			// printf("answer = %s\n", answer);

			answer_dup++;
		}
		strlcpy(answer_dup, digits, fp->precision + no_of_digits + is_negative);
		// printf("answer = %s\n", answer);

		memmove( answer_dup+(fp->precision - no_of_digits), answer_dup, fp->precision - no_of_digits );
		// printf("answer = %s\n", answer);

		while (i < fp->precision - no_of_digits)
		{
			*answer_dup = '0';
			answer_dup++;
			i++;
		}
		ft_putstr_fd(answer, 1);
	}
}

void back_up_2_precision_d(struct fields *fp, int dval)
{
	char *digits;
	char *answer;
	char *answer_dup;
	int no_of_digits;
	int is_negative;
	int i;

	i = 0;
	is_negative = 0;
	digits = ft_itoa(dval);
	// printf("digits = %s\n", digits);

	if (*digits == '-')
	{
		is_negative = 1;
		digits++;
	}
	no_of_digits = (int)strlen(digits);
	// printf("no_of_digits = %d\n", no_of_digits);

	if (fp->precision >= 0 && no_of_digits < fp->precision)
	{
		answer = malloc((fp->precision + no_of_digits + is_negative) * sizeof(*answer));
		if (!answer)
		{
			// printf("malloc() failed!");
			return;
		}
		answer_dup = answer;
		
		// printf("fp->precision + no_of_digits + is_negative = %d\n", (fp->precision + no_of_digits + is_negative));

		if (is_negative)
		{
			*answer_dup = '-';
			// printf("answer = %s\n", answer);

			answer_dup++;
		}
		strlcpy(answer_dup, digits, fp->precision + no_of_digits + is_negative);
		// printf("answer = %s\n", answer);

		memmove( answer_dup+(fp->precision - no_of_digits), answer_dup, fp->precision - no_of_digits );
		// printf("answer = %s\n", answer);

		while (i < fp->precision - no_of_digits)
		{
			*answer_dup = '0';
			answer_dup++;
			i++;
		}
		ft_putstr_fd(answer, 1);
	}
}

/*
** ft_is_nonzerodigit: checkt of c een digit is, behalve 0, inclusief - teken
*/
int		ft_is_nonzerodigit(int c)
{
	if ( (c >= '1' && c <= '9') || (c == '-'))
		return (1);
	else
		return (0);
}

/*
** print_fields: print de staat van de struct fields voor debugging
*/
void print_fields(struct fields *f)
{
	printf("\nprint_fields()\n");
	printf("f.is_minus = %d\n", f->is_minus);
	printf("f.is_zeroed = %d\n", f->is_zeroed);
	printf("f.width = %d\n", f->width);
	printf("f.precision = %d\n", f->precision);
	printf("f.conv_char = %c\n", f->conv_char);
}
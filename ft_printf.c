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
** init_fields: initialiseerd de struct fields met begin waarden
*/
void init_fields(struct fields *fp)
{
	fp->is_minus = 0;
	fp->is_zeroed = 0;
	fp->width = 0;
	fp->precision = -1;
	fp->conv_char = '\0';
}

/*
** set_fields: itereert door format placeholder, geeft een waarde een elke corresponderende member van de fields struct
*/
const char * set_fields(const char *p, va_list ap, struct fields *fp)
{
	// printf("\nset_fields()\n");

	int i;

	p++; /* Zet p een character na % */

	while (*p == '-' || *p == '0')
	{
		if (*p == '-') /* Left-align the output of this placeholder. (The default is to right-align the output.) */
		{
			fp->is_minus = 1;
		}
		if (*p == '0') /* When the 'width' option is specified, prepends zeros for numeric types. (The default prepends spaces.) */
		{
			fp->is_zeroed = 1;
		}
		p++;
	}

	if (ft_is_nonzerodigit(*p)) /* The Width field specifies a minimum number of characters to output, */
	{
		if (*p == '-')
		{
			fp->is_minus = 1;
			p++;
		}
		i = atoi(p);
		fp->width = i;
		while (isdigit(*p))
			p++;
	}

	/* The Precision field usually specifies a maximum limit on the output, depending on the particular formatting type. */
	/* For the string type, it limits the number of characters that should be output, after which the string is truncated. */
	/* For floating point numeric types, it specifies the number of digits to the right of the decimal point that the output should be rounded. */
	if (*p == '.') 
	{
		p++;
		if (*p == '*') /* Precision is dynamic value passed as another argument. */
		{
			i = va_arg(ap, int);
			if (i >= 0) /* als de precision 0 of hoger is, set precision, anders blijf -1 */
				fp->precision = i;
			p++;
		}
		else
		{
			if (*p == '-')
				p++;
			else
			{
				i = atoi(p);
				fp->precision = i;
			}
			while (isdigit(*p))
				p++;
		}
	}
	/* Hier zijn alle conversion characters gecheckt en komt er een s (of d of i of x etc.). */
	/* signed decimal specifier character */
	fp->conv_char = *p;

	if (fp->is_zeroed && fp->is_minus) /* if the 0 and - flags both appear, the 0 flag is ignored. */
	{
		// printf("fp->is_zeroed AND fp->is_minus are TRUE\n");
		fp->is_zeroed = 0;
	}

	// if a precision is given with a numeric conversion, the 0 flag is ignored.
	
	// print_fields(fp);
	return (p);
}

// /* kijk of je overal ca_dup kan gebruiken ipv ca */
void get_format_string_back_up(struct fields *fp, char *ca)
{
	// printf("\nget_format_string()\n");

	char s[(fp->width + (strlen(ca) + 1))]; // 17
	char ca_dup[strlen(ca) + 1];
	int ca_dup_len;
	
	strlcpy(ca_dup, ca, sizeof(ca_dup));
	ca_dup_len = strlen(ca_dup);

	if (fp->is_zeroed) /* als fp->is_zeroed true is */
		memset(s, '0', sizeof(s));
	else
		memset(s, ' ', sizeof(s));

	/*
	** Als precision 0 of groter is EN kleiner dan ca_dup_len
	** dan moet er getruncate worden?
	*/	
	if (((fp->precision >= 0) && (fp->precision < ca_dup_len)))
	{
		// printf("fp->precision is 0 of groter EN kleiner dan ca_dup_len\n");

		ca_dup[fp->precision] = '\0'; /* truncate zn moer */
		ca_dup_len = strlen(ca_dup); /* zet ca_dup_len gelijk aan de nieuwe lengte van ca_dup vanwege truncation door kleine precision */
	}

	if (fp->width > ca_dup_len) /* als de width groter is dan de lengte van ca */
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

void get_format_string(struct fields *fp, char *ca)
{
	char ca_dup[strlen(ca) + 1];
	int ca_dup_len;
	int i;
	char c;

	strlcpy(ca_dup, ca, sizeof(ca_dup));
	ca_dup_len = strlen(ca_dup); // 6
	i = 0;
	c = ' ';

	if (fp->is_zeroed)
		c = '0';

	if (((fp->precision >= 0) && (fp->precision < ca_dup_len)))
	{
		ca_dup[fp->precision] = '\0'; /* truncate zn moer */
		ca_dup_len = strlen(ca_dup); /* zet ca_dup_len gelijk aan de nieuwe lengte van ca_dup vanwege truncation door kleine precision */
	}

	if (ca_dup_len < fp->width) // als len van je argument kleiner is dan width, word width padded
	{
		if (!fp->is_minus) // right aligned
		{
			while (i < (fp->width - ca_dup_len))
			{
				write(1, &c, 1);
				i++;
			}
			i = 0;
			ft_putstr_fd(ca_dup, 1);
		}
		else
		{
			ft_putstr_fd(ca_dup, 1);
			while (i < (fp->width - ca_dup_len))
			{
				write(1, &c, 1);
				i++;
			}
			i = 0;
		}
	}
	else
		ft_putstr_fd(ca_dup, 1);
}

/*
** iterate_fmt: loops over the string fmt per character. Any character that is not % gets written to terminal. If a character equals % set_fields() is called. And then get_format_string is called.
** Takes as arguments string fmt, list of unnamend arguments, and a pointer to the struct declared in ft_printf.
** Returns the number of characters written to terminal.
** p: pointer to fmt as to not lose the original pointer to fmt.
** ca: ca stands for current argument. Pointer to the current argument in va_list ap.
** if (*p != '%'): handles ordinary characters. Else handles percentage and characters following until format specifier.
*/
int	interate_fmt(const char *fmt, va_list ap, struct fields *fp)
{
	// printf("\niterate_fmt()\n");
	const char	*p;
	char		*ca;

	p = fmt;
	init_fields(fp);
	// print_fields(fp);

	while (*p)
	{
		if (*p != '%')
			write(1, p, 1);
		else
		{
			/* Zolang de eerstvolgende character geen conversion character is, handel elke flag? */
			p = set_fields(p, ap, fp);

			// va_copy(v, ap);
			ca = va_arg(ap, char*);
			if (ca == NULL)
				get_format_string(fp, "(null)"); /* zet hier de function call die de fields struct leest en var arg accordingely aanpast */
			else
				get_format_string(fp, ca); /* zet hier de function call die de fields struct leest en var arg accordingely aanpast */
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
int	ft_printf(const char *fmt, ...)
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

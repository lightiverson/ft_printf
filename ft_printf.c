#include "ft_printf.h"

/*
** Printf converts, formats, and prints its arguments on the standard out under the control of the format. [Description]
** It returns the number of characters printed. [Return value]
** The format string contains two types of objects:
** ordinary characters, which are copied to the output stream, [Dit is één functie.]
** and conversion specifications, each of which cause conversion and printing of the next succesive argument to printf. [Dit is één functie.]
** Each conversion specification begins with a % and ends with a conversion character. [Zo kan je filteren op een conversion specification.]
** if the 0 and - flags both appear, the 0 flag is ignored.

** Syntax
** The syntax for a format placeholder is
** %[parameter][flags][width][.precision][length]type
*/

/*
** print_fields: print de staat van de struct fields voor debugging
*/
void print_fields(struct fields *f)
{
	printf("f.is_minus = %d\n", f->is_minus);
	printf("f.is_zeroed = %d\n", f->is_zeroed);
	printf("f.width = %d\n", f->width);
	printf("f.precision = %d\n", f->precision);
}

/* 
** init_fields: initialiseerd de struct fields met begin waarden
*/
void init_fields(struct fields *fp)
{
	printf("init_fields()\n");
	fp->is_minus = -1;
	fp->is_zeroed = -1;
	fp->width = -1;
	fp->precision = -1;
}

/*
** set_fields: itereert door format placeholder, geeft een waarde een elke corresponderende member van de fields struct
*/
const char * set_fields(const char *p, va_list ap, struct fields *fp)
{
	int i;

	p++; /* Zet p een character na % */

	if (*p == '-') /* Left-align the output of this placeholder. (The default is to right-align the output.) */
	{
		printf("\nis_minus = TRUE\n");
		fp->is_minus = 1;
		print_fields(fp);
		p++;
	}

	if (*p == '0') /* When the 'width' option is specified, prepends zeros for numeric types. (The default prepends spaces.) */
	{
		printf("\nis_zeroed = TRUE\n");
		fp->is_zeroed = 1;
		print_fields(fp);
		p++;
	}

	if (ft_is_nonzerodigit(*p)) /* The Width field specifies a minimum number of characters to output, */
	{
		if (*p == '-')
		{
			printf("\nwidth is a negative number. So is_minus = TRUE\n");
			fp->is_minus = 1;
			print_fields(fp);
			p++;
		}
		
		i = atoi(p);
		printf("\nwidth = %d\n", i);
		fp->width = i;
		print_fields(fp);
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
			printf("\nprecision = %d\n", i);
			fp->precision = i;
			print_fields(fp);
			p++;
		}
		else
		{
			// printf("\nUse ft_itoa to handel precision number.\n");
			/* het is het character 1. */
			// hier moet ik aangeven wat de precision is om later weer te gebruiken.

			i = atoi(p);
			printf("\nprecision = %d\n", i);
			fp->precision = i;
			print_fields(fp);

			while (isdigit(*p))
				p++;
		}
	}
	
	/* Hier zijn alle conversion characters gecheckt en komt er een s (of d of i of x etc.). */
	/* signed decimal specifier character */
	if (*p == 's')
		printf("%s", va_arg(ap, char *));
	return (p);
}

int interate_fmt(const char *fmt, va_list ap, struct fields *fp)
{
	const char *p; /* Extra pointer om fmt vast te houden aan het begin van de string */

	p = fmt;
	init_fields(fp);
	print_fields(fp);

	while (*p)
	{
		if (*p != '%') /* Handeld ordinary characters. */
			printf("%c", *p);
		else /* huidige character is een percentage */
		{
			/* Zolang de eerstvolgende character geen conversion character is, handel elke flag? */
			p = set_fields(p, ap, fp);
		}
		p++;
	}
	return (0);
}

int ft_printf(const char *fmt, ...)
{
	va_list ap; /* arguments pointer */
	struct fields f;
	int ret;

	va_start(ap, fmt); /* Laat ap verwijzen naar de eerste unnamed argument */
	ret = interate_fmt(fmt, ap, &f);
	va_end(ap); /* clean up als ie klaar is */
	return (ret);
}

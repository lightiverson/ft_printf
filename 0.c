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

/* minprintf: minimale versie van printf met variable argument list */
void minprintf(char *fmt, ...)
{
	va_list ap; /* verwijst naar iedere unnamed arg na elke keer */
	char *p;
	char *sval;
	int ival;
	double dval;

	va_start(ap, fmt); /* laat ap verwijzen naar de eerste unnamed arg */

	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) { /* hij word eerst ge-increment, en daarna gedereferenced */
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			for (sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap); /* clean up als ie klaar is */
}

void mijnfunctie(char *fmt, ...)
{
	va_list ap;
	char *p;
	char *m_fmt;

	m_fmt = strdup(fmt); /* Malloced fmt, want fmt zelf is read-only. En kan dus niet gewijzigd worden. */
	if (!m_fmt)
		printf("Malloc failed.\n");

	va_start(ap, fmt);

	while (strchr(m_fmt, '%')) /* Looped over m_fmt totdat er geen % meer is. Want als er geen % is, mag de heel m_fmt geprint worden */
	{
		/* Handelt alles behalve het format gedeelte */
		p = strchr(m_fmt, '%'); /* p = %s._My_name_is_%s.% */
		*p = '\0'; /* Veranderd de % in een 0. Zodat de string nu tot % is.*/
		fputs(m_fmt, stdout);

		/* Handelt het format gedeelte */
		p++; /* Zet de pointer 1 plek verder dan de % om vervolgens te checken wat de format character is.*/
		if (*p == 's')
		{
			fputs(va_arg(ap, char *), stdout);
			p++;
		}

		memmove(m_fmt, p, strlen(p) + 1); /*Zet m_fmt gelijk aan f_mft na de format character.*/
	}
	fputs(m_fmt, stdout);

	free(m_fmt);
	va_end(ap); /* clean up als ie klaar is */
}

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
int set_fields(const char *fmt, va_list ap, struct fields *fp)
{
	const char *p; /* Extra pointer om fmt vast te houden aan het begin van de string */
	int i;

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
	ret = set_fields(fmt, ap, &f);
	va_end(ap); /* clean up als ie klaar is */
	return (ret);
}

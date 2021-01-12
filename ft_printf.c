#include "ft_printf.h"

/*
** Printf converts, formats, and prints its arguments on the standard out under the control of the format. [Description]
** It returns the number of characters printed. [Return value]
** The format string contains two types of objects:
** ordinary characters, which are copied to the output stream, [Dit is één functie.]
** and conversion specifications, each of which cause conversion and printing of the next succesive argument to printf. [Dit is één functie.]
** Each conversion specification begins with a % and ends with a conversion character. [Zo kan je filteren op een conversion specification.]
** if the 0 and - flags both appear, the 0 flag is ignored.
*/

void test_va(char *fmt, ...)
/* eigen printf functie die alleen werkt met strings */
/* char *fmt is het hele eerste argument */
{
	printf("fmt = %s\n", fmt);

	/* The type va_list is used to declare a variable that will refer to each argument in turn; in minprintf, this variable is called ap, for “argument pointer. */
	va_list ap; /* verwijst naar iedere unnamed arg na elke keer */
	char *p;
	char *sval;

	va_start(ap, fmt); /* laat ap verwijzen naar de eerste unnamed arg */
	sval = va_arg(ap, char *);
	printf("sval = :%s:\n", sval);

	va_end(ap); /* clean up als ie klaar is */
}

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

void strprintf_BU(char *fmt, ...)
// Hello,_%s
{
	va_list ap; /* Verwijst naar alle unnamed arguments. */
	char *p;
	char *sval;

	va_start(ap, fmt); /* Laat ap verwijzen naar de eerste unnamed argument. */

	p = fmt;
	while (*p)
	{
		if (*p != '%') { /* Handeld ordinary characters. */
			putchar(*p);
		}
		// else if (*++p == 's') /* Huidige character is een %, en de character daarnaast is een s. */
		// {
		// 	fputs(va_arg(ap, char *), stdout);
		// }
		else /* huidige character is een percentage */
		{
			putchar(*++p);
		}
		p++;
	}
	va_end(ap); /* clean up als ie klaar is */
}


/* 
** set_field: met deze functie kan je de waardes "setten" van een field in de struct fields. 
*/
void set_field(int *field, int x)
{
	*field = x;
}

/*
** print_fields: print de staat van de struct fields voor debugging
*/
void print_fields(struct fields *f)
{
	printf("\nf.is_minus = %d\n", f->is_minus);
	printf("f.is_zeroed = %d\n", f->is_zeroed);
}

/* 
** init_fields: initialiseerd de struct fields met begin waarden
*/
struct fields init_fields(void)
{
	struct fields temp;

	temp.is_minus = -1;
	temp.is_zeroed = -1;
	return (temp);
}

void strprintf(char *fmt, ...)
// Hello,_%s._My_name_is_%s.
{
	va_list ap; /* Verwijst naar alle unnamed arguments. */
	char *p;
	char *sval;
	struct fields f;
	int i;

	va_start(ap, fmt); /* Laat ap verwijzen naar de eerste unnamed argument. */

	p = fmt;

	f = init_fields();
	print_fields(&f);
	// set_field(&f.is_minus, 28);
	// print_fields(&f);

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
				f.is_minus = 1;
				print_fields(&f);
				p++;
			}

			if (*p == '0') /* When the 'width' option is specified, prepends zeros for numeric types. (The default prepends spaces.) */
			{
				printf("\nis_zeroed = TRUE\n");
				f.is_zeroed = 1;
				print_fields(&f);
				p++;
			}

			// je wilt eigenlijk atoi gebruiken om door te loopen
			if (ft_is_nonzerodigit(*p)) /* The Width field specifies a minimum number of characters to output, */
			{
				i = atoi(p);
				printf("\nwidth = %d\n", i);
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
					printf("\nprecision = %d\n", va_arg(ap, int));
					p++;
				}
				else
				{
					// printf("\nUse ft_itoa to handel precision number.\n");
					/* het is het character 1. */
					// hier moet ik aangeven wat de precision is om late rweer te gebruiken.

					printf("\nprecision = %d\n", atoi(p));

					while (isdigit(*p))
						p++;
				}
			}
			
			/* Hier zijn alle conversion characters gecheckt en komt er een s (of d of i of x etc.). */
			if (*p == 's')
				printf("%s", va_arg(ap, char *));
		}
		p++;
	}
	va_end(ap); /* clean up als ie klaar is */
}
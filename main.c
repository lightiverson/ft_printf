#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

/*
** Printf converts, formats, and prints its arguments on the standard out under the control of the format. [Description]
** It returns the number of characters printed. [Return value]
** The format string contains two types of objects:
** ordinary characters, which are copied to the output stream, [Dit is één functie.]
** and conversion specifications, each of which cause conversion and printing of the next succesive argument to printf. [Dit is één functie.]
** Each conversion specification begins with a % and ends with a conversion character. [Zo kan je filteren op een conversion specification.]
** 
*/

// int main (void)
// {
// 	struct point
// 	{
// 		int x;
// 		int y;
// 	};

// 	struct point maxpt = { 320, 200 };

// 	maxpt.x = 4;

// 	printf("%d, %d", maxpt.x, maxpt.y);
	
// 	return (0);
// }

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
		switch (*++p) {
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

void strprintf(char *fmt, ...)
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

void mijnfunctie(char *fmt, ...)
{
	printf("\n\nmijnfunctie() gecalled.\n");

	va_list ap;
	char *p;
	char *m_fmt;

	m_fmt = strdup(fmt);
	if (!m_fmt)
		printf("Malloc failed.\n");
	// printf("m_fmt = %s\n", m_fmt);

	va_start(ap, fmt);

	// while (*m_fmt != '\0')
	while (strchr(m_fmt, '%'))
	{
		// printf("while loop executed.\n");
		// printf("%c", *fmt); /* print elke character fan fmt */

		p = strchr(m_fmt, '%'); /* p = %s._My_name_is_%s.% */

		*p = '\0';
		// printf("m_fmt = %s\n", m_fmt);
		fputs(m_fmt, stdout);

		p++;
		// printf("p = %s\n", p);
		if (*p == 's')
		{
			fputs(va_arg(ap, char *), stdout);
			p++;
		}
		// printf("\nc = %c", *p);
		memmove(m_fmt, p, strlen(p) + 1);
		// printf("\nm_fmt = %s\n", m_fmt);
		// break;
		// m_fmt++;
	}
	fputs(m_fmt, stdout);
	// printf("\np = %s", p);
}

int main (void)
{
	char *s = "world";
	char *s1 = "world";
	char *s2 = "Kawish";
	// printf(":hello, %s:", s);
	// printf("\n");
	// strprintf(":hello, %s:", s);
	// printf(":Hello,_%s._My_name_is_%s.:", s1, s2);
	mijnfunctie("Hello,_%s._My_name_is_%s.", s1, s2);
	return (0);
}
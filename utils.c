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
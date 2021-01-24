#include "ft_printf.h"

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
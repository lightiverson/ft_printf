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

#include "ft_printf.h"

int main (void)
{
	// Check zero flag, and width of 4, with int.
	// printf("%04X",3);
	// ft_printf("%04X",3);

	// Check precision of 3.
	printf("%.3s", "abcdef");
	printf("\n");
	ft_printf("%.3s", "abcdef");
	return (0);
}
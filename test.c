#include "ft_printf.h"

int main (void)
{
	/* GOEIE */

	/* %s */
	// printf(":%s:\n", "abcdef");
	// ft_printf(":%s:\n", "abcdef");

	/* gelijke width */
	// printf(":%6s:\n", "abcdef");
	// ft_printf(":%6s:\n", "abcdef");

	/* grotere width */
	// printf(":%10s:\n", "abcdef");
	// ft_printf(":%10s:\n", "abcdef");

	/* kleinere width */
	// printf(":%3s:\n", "abcdef");
	// ft_printf(":%3s:\n", "abcdef");

	/* grotere width, is_minus */
	// printf(":%-10s:\n", "abcdef");
	// ft_printf(":%-10s:\n", "abcdef");	

	/* grotere precision */
	// printf(":%.10s:\n", "abcdef");
	// ft_printf(":%.10s:\n", "abcdef");

	/* kleinere precision */
	// printf(":%.3s:\n", "abcdef");
	// ft_printf(":%.3s:\n", "abcdef");

	/* gelijke precision */
	// printf(":%.6s:\n", "abcdef");
	// ft_printf(":%.6s:\n", "abcdef");

	/* precision zonder getal */
	// printf(":%.s:\n", "abcdef");
	// ft_printf(":%.s:\n", "abcdef");



	/* width = 10, string */
	// printf(":%10s:\n", "abcdef");
	// ft_printf(":%10s:\n", "abcdef");

	/* width = 10, precison = 3, string */
	// printf(":%10.3s:\n", "abcdef");
	// ft_printf(":%10.3s:\n", "abcdef");

	/* zeroed, width = 10, string */
	// printf(":%010s:\n", "abcdef");
	// ft_printf(":%010s:\n", "abcdef");

	/* minus, width = 10, string */
	// printf(":%-10s:\n", "abcdef");
	// ft_printf(":%-10s:\n", "abcdef");

	/* zeroed, minus, width = 10, string */
	// printf(":%-010s:\n", "abcdef");
	// ft_printf(":%-010s:\n", "abcdef");

	/* width = 3, precison = 10, string */
	// printf(":%3.10s:\n", "abcdef");
	// ft_printf(":%3.10s:\n", "abcdef");	

	printf("hello, %s.\n", NULL);
	ft_printf("hello, %s.\n", NULL);

	return (0);
}
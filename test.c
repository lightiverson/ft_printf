#include "ft_printf.h"

int main (void)
{
	/* %s */
	// char *naam = "Ajay";
	// printf(":Hallo, %s:\n", naam);
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

	/* NULL string */
	// printf("hello, %s.\n", NULL);
	// ft_printf("hello, %s.\n", NULL);	

	// ------------

	/* %d */
	// printf("Your age is :%d:\n", 28);
	// ft_printf("Your age is :%d:\n", 28);

	/* width = 4 */
	// printf("Your age is :%4d:\n", 28);
	// ft_printf("Your age is :%4d:\n", 28);

	/* width = 4, right aligned */
	// printf("Your age is :%-4d:\n", 28);
	// ft_printf("Your age is :%-4d:\n", 28);

	/* precision = * */
	// printf("Your age is :%.d:\n", 28);
	// ft_printf("Your age is :%.d:\n", 28);

	// printf("Your age is :%.0d:\n", 28);
	// ft_printf("Your age is :%.0d:\n", 28);

	// printf("Your age is :%.1d:\n", 28);
	// ft_printf("Your age is :%.1d:\n", 28);

	// printf("Your age is :%.2d:\n", 28);
	// ft_printf("Your age is :%.2d:\n", 28);

	// printf("Your age is :%.3d:\n", 28);
	// ft_printf("Your age is :%.3d:\n", 28);

	// printf("Your age is :%.4d:\n", 28);
	// ft_printf("Your age is :%.4d:\n", 28);

	// printf("Your age is :%.5d:\n", 28);
	// ft_printf("Your age is :%.5d:\n", 28);

	/* NEGATIVE NUMBERS */

	/* %d */
	// printf("Your age is :%d:\n", -28);
	// ft_printf("Your age is :%d:\n", -28);

	/* width = 4 */
	// printf("Your age is :%4d:\n", -28);
	// ft_printf("Your age is :%4d:\n", -28);

	/* width = 4, right aligned */
	// printf("Your age is :%-4d:\n", -28);
	// ft_printf("Your age is :%-4d:\n", -28);

	/* width = 4, zeroed */
	// printf(":%05d:\n", -28);
	// ft_printf(":%05d:\n", -28);

	// width = 7, is_zero, precision = 5, negative number
	// printf(":%7.4d:\n", -54);
	// ft_printf(":%7.4d:\n", -54);
	// printf(":%07.4d:\n", -54);
	// printf(":%07.4d:\n", -54);

	// ft_printf(":%07d:\n", 54);
	// ft_printf(":%07d:\n", 54);

	// printf(":%.d:\n", 54);
	// ft_printf(":%.d:\n", 54);

	// printf(":%.1d:\n", 54);
	// ft_printf(":%.1d:\n", 54);

	// printf(":%.4d:\n", 54);
	// ft_printf(":%.4d:\n", 54);

	// printf(":%.d:\n", -54);
	// ft_printf(":%.d:\n", -54);

	// printf(":%.1d:\n", -54);
	// ft_printf(":%.1d:\n", -54);

	// printf(":%7d:\n", 33);
	// ft_printf(":%7d:\n", 33);

	// printf(":%-7d:\n", 33);
	// ft_printf(":%-7d:\n", 33);

	// printf(":%07d:\n", -14);
	// ft_printf(":%07d:\n", -14);

	// printf(":%7d:\n", -14);
	// ft_printf(":%7d:\n", -14);

	// printf(":%8.5d:\n", 34);
	// ft_printf(":%8.5d:\n", 34);

	// printf(":%.0d:\n", 2);
	// ft_printf(":%.0d:\n", 2);

	// wat is het verschil tussen left aligned en right aligned met nullen negatief en width?
	// printf(":%-07d", -14);

	// printf("%d", printf(":%d:", 45));
	// printf("\n\n");
	// ft_printf("%d", ft_printf(":%d:", 45));

	// %c
	// printf(":%c:\n", 'a');
	// ft_printf(":%c:\n", 'a');

	// printf(":%2c:\n", 'a');
	// ft_printf(":%2c:\n", 'a');
	
	// printf(":%-2c:\n", 'a');
	// ft_printf(":%-2c:\n", 'a');

	/* DEZE GAAT NOG FOUT!! FIXEN!! */
	// printf(":%0*.*d:\n", 3, -2, 0);
	// ft_printf(":%0*.*d:\n", 3, -2, 0);
	// ft_printf(":%03.*d:\n", -2, 0);

	/* %u */
	// printf(":%u:\n", 7235);
	// ft_printf(":%u:\n", 7235);

	// printf(":%.6u:\n", 7235);
	// ft_printf(":%.6u:\n", 7235);

	// printf(":%6u:\n", 7235);
	// ft_printf(":%6u:\n", 7235);

	// printf(":%-6u:\n", 7235);
	// ft_printf(":%-6u:\n", 7235);

	// printf(":%06u:\n", 7235);
	// ft_printf(":%06u:\n", 7235);

	// printf("%u", 4294967294u);
	// ft_printf("%u", 4294967295u);
	// ft_printf("%u", 4294967294u);

	// printf(":%7u:\n", 33);
	// ft_printf(":%7u:\n", 33);

	// printf("return = %d\n", printf(":%.5u:\n", 2));
	// printf("return = %d\n", ft_printf(":%.5u:\n", 2));

	// printf(":%.6d:\n", -3);
	// ft_printf(":%.6d:\n", -3);

	// printf(":%.5d:\n", 2);
	// ft_printf(":%.5d:\n", 2);
	
	// printf(":%.4d:\n", 54);
	// ft_printf(":%.4d:\n", 54);

	// printf(":%.4d:\n", -54);
	// ft_printf(":%.4d:\n", -54);

	// printf(":%8.5d:\n", 34);
	ft_printf(":%8.5d:\n", 34);

	return (0);
}
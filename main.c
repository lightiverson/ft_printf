#include "ft_printf.h"

int main (void)
{
	char *s1 = "world";
	char *s2 = "Kawish";
	printf(":%.10s:", "hello, world");
	printf("\n");
	strprintf(":%.10s:", "hello, world");
	return (0);
}
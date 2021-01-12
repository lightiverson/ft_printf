#include "ft_printf.h"

int main (void)
{
	char *s1 = "world";
	char *s2 = "Kawish";
	// printf("%--4X",3);
	// printf("\n");
	// strprintf(":%-.10s:", "hello, world");
	strprintf("%04X",3);
	return (0);
}
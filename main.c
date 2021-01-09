#include "ft_printf.h"

int main (void)
{
	char *s = "world";
	char *s1 = "world";
	char *s2 = "Kawish";
	// printf(":hello, %s:", s);
	// printf("\n");
	// strprintf(":hello, %s:", s);
	printf("Hello,_%s._My_name_is %s.", s1, s2);
	printf("\n");
	strprintf("Hello,_%s._My_name_is %s.", s1, s2);
	return (0);
}
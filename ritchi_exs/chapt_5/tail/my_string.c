#include "my_string.h"

char *my_strcpy(char *dst, const char *src)
{
	char *saveptr = dst;
	while ((*dst++ = *src++))
		;
	return saveptr;
}

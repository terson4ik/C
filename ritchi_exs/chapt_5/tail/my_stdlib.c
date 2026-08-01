#include <stdio.h>
#include "my_stdlib.h"

#define ISNUM(X) (((X) >= '0' && (X) <= '9') ? 1 : 0)

int my_atoi(const char *s)
{
	int res, sign;
	
	sign = 1;
	if (!ISNUM(*s) && (*s == '-' || *s == '+'))
		sign = (*s++ == '-') ? -1 : 1;
		
	for (res = 0; ISNUM(*s); s++)
		res = res * 10 + *s - '0';
	return res * sign;
}

int get_line(char *s, int lim)
{
	int c;
	
	char *run = s;
	while (--lim > 0 && (c = getchar()) != EOF) {
		*run++ = c;
		if (c =='\n')
			break;
	}
	*run = '\0';
	return run - s;
}

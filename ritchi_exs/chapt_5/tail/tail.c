#include <stdio.h>
#include "alloc.h"
#include "my_stdlib.h"
#include "my_string.h"

void move_up(char **pparr, int max);
void write_n_elems(char **pparr, int max);
void erase_all(char **pparr, int max);

#define DEFAULT_N   10
int main(int argc, char **argv) 
{
    char **lines;
    char line[MAX_LINE];
    unsigned int n, runner, len;
    enum states { FULL, FILLING } state;
    if (*(argv + 1) && **(argv + 1) == '-')
        n = my_atoi(*(argv + 1) + 1);
    else
        n = DEFAULT_N;
    if (!n)
        return 0;
    lines = ptr_alloc(n);
    if (!lines) {
        fprintf(stderr, "Error: size %d is too big\n", n);
        return 1;
    }
    
    runner = 0;
    state = FILLING;
    while ((len = get_line(line, MAX_LINE)) > 0) {
		switch (state) {
			case FILLING:
				*(lines + runner) = chr_alloc(len);
				my_strcpy(*(lines + runner), line);
				runner++;
				if (runner > n) {
					runner = n-1;
					state = FULL;
				}
				break;
			case FULL:				
				move_up(lines, runner);
				if (len > chr_get_cur_size(*(lines + runner)))
					*(lines + runner) = chr_realloc(*(lines + runner), len);
				my_strcpy(*(lines + runner), line);
				break;
			default:
				fprintf(stderr, "INVALID STATE");
				return 2;
				break;
		}
	}
	write_n_elems(lines, (state == FULL) ? n-1 : runner-1);
	erase_all(lines, (state == FULL) ? n-1 : runner-1);
    return 0;
}
void erase_all(char **pparr, int max)
{ /* emulation if free from stdlib */
	int i;
	for (i = max; i >= 0; i--) {
		char **prev = (pparr + i - 1);
		chr_free(*pparr);
		ptr_free(pparr + i);
		pparr = prev;
	}
}
void move_up(char **pparr, int max)
{ /* Demonstration. i need struct circle and true malloc. */
	int left = 0;
	while (left <= max-1) {
		char *next = pparr[left];
		pparr[left] = pparr[left + 1];
		pparr[left + 1] = next;
		left++;
	}
}

void write_n_elems(char **pparr, int max)
{
	int i;
	for (i = 0; i <= max; i++)
		printf("%s", pparr[i]);
}
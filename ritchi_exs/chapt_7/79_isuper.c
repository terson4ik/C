#include <stdio.h>

int is_upper_time(char c);
int is_upper_memory(char c);

#define DEFAULT_ASCII_CHARS 128
static char table[DEFAULT_ASCII_CHARS] = { 0 }; /* alternative: calloc */
void init_table()
{
    int i;
    for (i = 'A'; i <= 'Z'; i++)
        table[i] = 1;
}

int main()
{
    int c;
    init_table();
    while ((c = getchar()) != EOF) {
        printf("time: %s - upper%c\n", is_upper_time(c) ? "YES" : "NO", c);
        printf("memory: %s - upper%c\n", is_upper_memory(c) ? "YES" : "NO", c);
    }
    return 0;
}

int is_upper_memory(char c)
{
    return c >= 'A' && c <= 'Z' ? 1 : 0;
}

int is_upper_time(char c)
{
    return table[(unsigned int)c];
}

#include <stdio.h>

/* the next three macro names is bad
#define MYMACRO(arg) f(arg); g(arg);
#define MYMACRO(arg) f(arg); g(arg)
#define MYMACRO(arg) { f(arg); g(arg); }
*/

#define SAFEMYMACRO(arg) do { f(arg); g(arg); } while(0)

void f(const char *s);
void g(const char *s);

int main(void)
{
    SAFEMYMACRO("ARGS");
    return 0;
}
void f(const char *s)
{
}
void g(const char *s)
{
}

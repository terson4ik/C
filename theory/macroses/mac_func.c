#include <stdio.h>

/* this is macros with parameters: */
#define MAX(A, B)   ((A) > (B) ? (A) : (B))
/* btw this is макроопределения */
#define MAKE_ARRAY_SUM_FUNCTION(FUNNAME, TYPE) \
    TYPE FUNNAME(const TYPE *a, int n) \
    { \
        TYPE s = 0; \
        while(n > 0) { \
            s += *a; \
            a++; \
            n--; \
        } \
        return s; \
    }

/* int ## _arr = int_arr */
#define MAKE_SIMLE_SUM_FUNC(TYPE) \
    TYPE TYPE ## _arr_sum(TYPE *a, int n) \
    { \
        TYPE s = 0; \
        while(n > 0) { \
            s += *a; \
            a++; \
            n--; \
        } \
        return s; \
    } \
MAKE_SIMLE_SUM_FUNC(float);

/* #x = "x" automatically */
#define VAR_PRINT(x) printf("%s = %d\n", #x, x)
#define COOL_VAR_PRINT(x) printf(#x " = %d\n", x)

int main(void)
{
    int a = 15, b = 10;
    printf("%d\n", MAX(a, b));
    VAR_PRINT(a);
    COOL_VAR_PRINT(b);
    
    return 0;
}

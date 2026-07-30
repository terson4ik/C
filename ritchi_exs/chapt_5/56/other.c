#include <stdio.h>
#define DEC_BASE 10
#define FLT_DEC_BASE 10.0
#define ERR_VAL -1
#define ISDIGIT(c) (((c) >= '0' && (c) <= '9') ? 1 : 0)


int atoi(const char *s)
{
    int res, sign = 1;

    while (*s == ' ' || *s == '\t' || *s == '\n')
        s++;
    if (!ISDIGIT(*s)) {
        if (*s == '-' || *s == '+') {
            sign = (*s == '-') ? -1 : 1;
            s++;
        } else
            return ERR_VAL;
    }
    for (res = 0; ISDIGIT(*s); s++) /* Danger use *s++,     */
        res = res * DEC_BASE + *s - '0'; /* because side effects */

    return res * sign;
}

double atof(const char *s)
{
    double val, pow, exp;
    int sign = 1, exp_sign = 1; /* by default + */

    while (*s == ' ' || *s == '\t' || *s == '\n')
        s++;
    if (!ISDIGIT(*s)) {
        if (*s == '-' || *s == '+') {
            sign = (*s == '-') ? -1 : 1;
            s++;
        } else if (*s != '.')
            return ERR_VAL;
    }
    for (val = 0.0; ISDIGIT(*s); s++)
        val = val * FLT_DEC_BASE + *s - '0';
    pow = 1.0;
    if (*s == '.') {
        for (++s/* pow was init */; ISDIGIT(*s); s++) {
            val = val * FLT_DEC_BASE + *s - '0';
            pow *= FLT_DEC_BASE;
        }
    }
    exp = 1.0;
    if (*s == 'E' || *s == 'e') {
        int exp_base;
        s++;
        if (!ISDIGIT(*s)) {
            if (*s == '-' || *s == '+') {
                exp_sign = (*s == '-') ? -1 : 1;
                s++;
            } else
                return (val * sign) / pow;
        }
        for (exp_base = 0; ISDIGIT(*s); s++)
            exp_base = exp_base * DEC_BASE + *s - '0';
        while (exp_base--)
            exp *= FLT_DEC_BASE;
    }
    return (exp_sign < 0) ? (val * sign) / (exp * pow):
                            (val * sign * exp) / pow;
}

void reverse(char *left)
{
    char *right = left;
    while (*right)
        right++;
    for (--right; right > left; left++, right--) {
        char tmp_left = *left;
        *left = *right;
        *right = tmp_left;
    }
}

char   *itoa(int num, char *dst)
{
    char *tmp_dst = dst;
    int sign = (num < 0) ? -1 : 1;

    do { /* 123 = 3->2->1 then need reverse */
        int val = num % DEC_BASE;
        *tmp_dst++ = ((val < 0) ? -val : val) + '0';
    } while (num /= DEC_BASE);
    if (sign < 0)
        *tmp_dst++ = '-';
    *tmp_dst = '\0';
    reverse(dst);
    return dst;
}

char   *itob(int num, char *dst)
{
    char *tmp_dst = dst;
    unsigned int cast_n = num;

    do {
        *tmp_dst++ = (cast_n & 01) + '0';
    } while (cast_n >>= 1);

    *tmp_dst = '\0';
    reverse(dst);
    return dst;
}

int strindex(const char *s1, const char *s2)
{
    const char *run1;
    const char *run2;
    
    for (run1 = s1; *run1; run1++) {
        const char *save_indx = run1;
        for (run2 = s2; *run2 && *run2 == *save_indx; run2++, save_indx++)
            ;
        if (*run2 == '\0') /* successfully running loop */
            return run1 - s1;
    }
    return ERR_VAL;
}

int get_line(char *s, int lim)
{
    char *save_p = s;
    int c;

    while (--lim > 0 && (c = getchar()) != EOF) {
        *s++ = c;
        if (c == '\n')
            break;
    }
    *s = '\0';
    return s - save_p;
}
static int engine_rec_atoi(const char *s, int akum)
{
    if (!*s || (!ISDIGIT(*s))) {
        return akum; 
    }
    akum = akum * DEC_BASE + *s - '0';
    return engine_rec_atoi(s + 1, akum);
}

int rec_atoi(const char *s)
{
    int sign = 1;
    while (*s == ' ' || *s == '\t' || *s == '\n')
        s++;
    if (*s == '-' || *s == '+') {
        sign = (*s == '-') ? -1 : 1;
        s++;
    }
    return engine_rec_atoi(s, 0) * sign;
}
static int engine_rec_itoa(char *s, int n)
{
    int bias = 0, tmp;
    if (n)
        bias = engine_rec_itoa(s, n / 10);
    else 
        return 0;

    tmp = n % DEC_BASE;
    *(s + bias) = ((tmp < 0) ? -tmp : tmp) + '0';
    return bias + 1;
}

void rec_itoa(int num, char *dst)
{
    if (num < 0)
        *dst++ = '-';

    if (!num) {
        *dst++ = '0';
        *dst = '\0';
    } else
        *(dst + engine_rec_itoa(dst, num)) = '\0';
}

static char *engine_rec_rev(char *right, char *left)
{
    char tmp;
    if (!*right)
        return left;

    left = engine_rec_rev(right + 1, left);
    if (left >= right)
        return left;

    tmp = *left;
    *left = *right;
    *right = tmp;

    return left + 1;
}
void rec_rev(char *s)
{
    engine_rec_rev(s, s);
}

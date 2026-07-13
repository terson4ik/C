#include <stdio.h>
#include <limits.h>
#include <float.h>

#ifndef DEBUG_PRINT
#define DEBUG_PRINT 0
#endif

#define STRIP puts("----------------------------------------")
#define FROM_HEAD "->limit from HEADER: "
#define FROM_MAN "->limit from manual: "

#define PRINT_H_LIMIT(type, val) printf(#type FROM_HEAD "%d\n", val)
#define PRINT_H_LIMIT_UNS(type, val) printf(#type FROM_HEAD "%u\n", val)
#define PRINT_M_LIMIT(type) printf(#type FROM_MAN "%d\n", type)
#define PRINT_M_LIMIT_UNSG(type) printf(#type FROM_MAN "%u\n", type)

#define L_PRINT_H_LIMIT(type, val) printf(#type FROM_HEAD "%ld\n", val)
#define L_PRINT_H_LIMIT_UNS(type, val) printf(#type FROM_HEAD "%lu\n", val)
#define L_PRINT_M_LIMIT(type) printf(#type FROM_MAN "%ld\n", type)
#define L_PRINT_M_LIMIT_UNSG(type) printf(#type FROM_MAN "%lu\n", type)

#define F_PRINT_H_LIMIT(type, val) printf(#type FROM_HEAD "%g\n", val)
#define F_PRINT_M_LIMIT(type) printf(#type FROM_MAN "%g\n", type)
#define L_F_PRINT_H_LIMIT(type, val) printf(#type FROM_HEAD "%Lg\n", val)
#define L_F_PRINT_M_LIMIT(type) printf(#type FROM_MAN "%Lg\n", type)

#if DEBUG_PRINT
#define DEBUG_PRINTING(flt_num) fprintf(stderr, "%g\n", flt_num)
#else
#define DEBUG_PRINTING(flt_num) do {} while(0)
#endif

#define GEN_FUNCTION_GET_MAX_FLOAT(type) \
type type## _get_max()                                  \
{                                                       \
    type res = 1.0, buf = 0.1, prev, mul;               \
    while(res != buf) { /* after infinity res = buf */  \
        prev = buf;                                     \
        buf = res;                                      \
        res *= 2.0; /* While not overflow to infinity */\
        DEBUG_PRINTING(res);                            \
    } /* After infinity get previous largest value */   \
    res = prev;                                         \
    mul = res / 2.0;                                    \
    while(mul > 0.0) { /* Filling the mantissa */       \
        prev = buf;                                     \
        buf = res;                                      \
        res += mul;                                     \
        DEBUG_PRINTING(res);                            \
        if(res == buf) { /* If infinity */              \
            buf = res = prev;                           \
            mul /= 2.0;    /* Then multiply number is too largest, cut it */ \
        }                                               \
    }                                                   \
    return res;                                         \
}

typedef long double lng_dbl;
GEN_FUNCTION_GET_MAX_FLOAT(float)
GEN_FUNCTION_GET_MAX_FLOAT(double)
GEN_FUNCTION_GET_MAX_FLOAT(lng_dbl)

#define GEN_FUNCTION_GET_MIN_FLOAT(type)    \
type type## _get_min()                      \
{                                           \
    type res = 1.0, buf;                    \
    do {                                    \
/* it's catch DE NORMALISATION NUMBER       \
 * because after s.expa.mantissa            \
 * if 0.00000.0000001 after /2.0 we have    \
 *    0.00000.0000000, and this number after *2 give 0 \
 * if after *2 = 0 then it's over, we catch this */    \
        buf = res;                          \
        res /= 2.0;                         \
        DEBUG_PRINTING(res);                \
    } while(res * 2.0 == buf && buf != 0.0);\
    return buf;                             \
}

GEN_FUNCTION_GET_MIN_FLOAT(float)
GEN_FUNCTION_GET_MIN_FLOAT(double)
GEN_FUNCTION_GET_MIN_FLOAT(lng_dbl)

#define GEN_FUNCTION_GET_TRUE_MIN_FLOAT(type) \
type type## _get_true_min()                 \
{                                           \
    type eps = 1.0, res;                    \
/* It's finding epsilon. Epsilon is length of mantissa, this mechanism find \
 * this size. for example, for float is 23          \
 * https://en.wikipedia.org/wiki/Single-precision_floating-point_format \
 * this work like this: if eps = 1E-24 then after After converting the  \
 * exponent to 24, it dropped that bit, which caused the inaccuracy */ \
    while(1 + (eps / 2.0) > 1)              \
        eps /= 2;                           \
    res = type## _get_min();                \
/* de normalize number divided by eps is it equal MINIMUM number NORMALIZED \
 * number because 0.00000.0000001 * size_of_,mantissa = 0.00001.0000000000  \
 * because eps have NEGATIVE number, we need "/" because -1 / -1 = -1 + 1;  \
*/ \
    return res / eps;                             \
}
#if 0
/* 1. Ищем Эпсилон (вес младшего бита мантиссы).        \
     * Делим 1.0 пополам, пока проц не перестанет видеть    \
     * разницу между 1.0 и (1.0 + eps) из-за нехватки бит.  \
     * Для float цикл остановится на значении 2^-23. */     \
    while(1.0 + (eps / 2.0) > 1.0)                          \
        eps /= 2.0;                                         \
                                                            \
    /* 2. Получаем самое дно - последний выживший бит       \
     * денормализованных чисел (для float это 2^-149). */   \
    res = type## _get_min();                                \
                                                            \
    /* 3. Сдвигаем бит на место нормализации.               \
     * Нам нужно перетащить этот 1 бит с правого края       \
     * мантиссы на 23 позиции влево (на место скрытой 1).   \
     * Математически: res / eps = (2^-149) / (2^-23).       \
     * При делении степени вычитаются: -149 - (-23) = -126. \
     * Мы получаем 2^-126, что и есть нормализованный MIN. */\
    return res / eps;                                       \
#endif

GEN_FUNCTION_GET_TRUE_MIN_FLOAT(float)
GEN_FUNCTION_GET_TRUE_MIN_FLOAT(double)
GEN_FUNCTION_GET_TRUE_MIN_FLOAT(lng_dbl)

int main(void)
{
    unsigned char c_u = 0;
    char c = 0;
    unsigned short s_u = 0;
    short s = 0;
    unsigned int i_u = 0;
    int i = 0;
    unsigned long l = 0;
    long l_u = 0;

    float f;
    double d;
    long double d_l;
    PRINT_H_LIMIT(c, CHAR_MAX);
    PRINT_H_LIMIT(c, CHAR_MIN);
    PRINT_H_LIMIT_UNS(c_u, UCHAR_MAX);
    PRINT_H_LIMIT_UNS(c_u, 0);

    c = (unsigned char)(~0) >> 1;
    PRINT_M_LIMIT(c);
    c = ((unsigned char)(~0) >> 1) + 1;
    PRINT_M_LIMIT(c);
    c_u = ~0;
    PRINT_M_LIMIT_UNSG(c_u);
    c_u = 0;
    PRINT_M_LIMIT_UNSG(c_u);
    STRIP;
    PRINT_H_LIMIT(s, SHRT_MAX);
    PRINT_H_LIMIT(s, SHRT_MIN);
    PRINT_H_LIMIT_UNS(s_u, USHRT_MAX);
    PRINT_H_LIMIT_UNS(s_u, 0);

    s = (unsigned short)~0 >> 1;
    PRINT_M_LIMIT(s);
    s = ((unsigned short)~0 >> 1) + 1;
    PRINT_M_LIMIT(s);
    s_u = ~0;
    PRINT_M_LIMIT_UNSG(s_u);
    s_u = 0;
    PRINT_M_LIMIT_UNSG(s_u);
    STRIP;
    PRINT_H_LIMIT(i, INT_MAX);
    PRINT_H_LIMIT(i, INT_MIN);
    PRINT_H_LIMIT_UNS(i_u, UINT_MAX);
    PRINT_H_LIMIT_UNS(i_u, 0);

    i = (unsigned int)~0 >> 1;
    PRINT_M_LIMIT(i);
    i = 1 + ((unsigned int)~0 >> 1);
    PRINT_M_LIMIT(i);
    i_u = ~0;
    PRINT_M_LIMIT_UNSG(i_u);
    i_u = 0;
    PRINT_M_LIMIT_UNSG(i_u);
    STRIP;
    L_PRINT_H_LIMIT(l, LONG_MAX);
    L_PRINT_H_LIMIT(l, LONG_MIN);
    L_PRINT_H_LIMIT_UNS(l_u, ULONG_MAX);
    L_PRINT_H_LIMIT_UNS(l_u, (unsigned long)0);

    l = (unsigned long)~0 >> 1;
    L_PRINT_M_LIMIT(l);
    l = 1 + ((unsigned long)~0 >> 1);
    L_PRINT_M_LIMIT(l);
    l_u = ~0;
    L_PRINT_M_LIMIT_UNSG(l_u);
    l_u = 0;
    L_PRINT_M_LIMIT_UNSG(l_u);
    STRIP;
    F_PRINT_H_LIMIT(f, FLT_MAX);
    F_PRINT_H_LIMIT(f, FLT_MIN);
    f = float_get_max();
    F_PRINT_M_LIMIT(f);
    f = float_get_min();
    F_PRINT_M_LIMIT(f);
    f = float_get_true_min();
    F_PRINT_M_LIMIT(f);
    STRIP;
    F_PRINT_H_LIMIT(d, DBL_MAX);
    F_PRINT_H_LIMIT(d, DBL_MIN);
    d = double_get_max();
    F_PRINT_M_LIMIT(d);
    d = double_get_min();
    F_PRINT_M_LIMIT(d);
    d = double_get_true_min();
    F_PRINT_M_LIMIT(d);
    STRIP;
    L_F_PRINT_H_LIMIT(d_l, LDBL_MAX);
    L_F_PRINT_H_LIMIT(d_l, LDBL_MIN);
    d_l = lng_dbl_get_max();
    L_F_PRINT_M_LIMIT(d_l);
    d_l = lng_dbl_get_min();
    L_F_PRINT_M_LIMIT(d_l);
    d_l = lng_dbl_get_true_min();
    L_F_PRINT_M_LIMIT(d_l);

    return 0;
}

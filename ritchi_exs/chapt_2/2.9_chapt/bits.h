#ifndef BITS_H
#  define BITS_H
typedef unsigned long long u_64;

void print_n_bits(u_64 x, u_64 p, u_64 n);
void print_bits(u_64 x);
u_64 getbits(u_64 x, u_64 p, u_64 n);
u_64 setbits(u_64 x, u_64 p, u_64 n, u_64 y);
u_64 invert(u_64 x, u_64 p, u_64 n);
u_64 rightrot(u_64 x, u_64 n);
#endif

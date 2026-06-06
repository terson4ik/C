#include <stdio.h>
#include <stdlib.h>

unsigned long long str_to_int(const char *str)
{
    long long res = 0;
    const char *tmp = str;
    for(; *tmp; tmp++) {
        if(*tmp < '0' || *tmp > '9') {
            fprintf(stderr, "%c is not a number. positive please", *tmp);
            exit(100);
        }
        res = (res * 10) + (*tmp - '0');
    }
    return res;
}

int digit_size(long long num)
{
    if(num == 0)
        return 1;

    int tmp, res;
    for(res = 0, tmp = num; tmp; ++res, tmp /= 10)
    {} 

    return res;
}

int main(int argc, char **argv)
{
    if(argc != 3)
        return(1);

    int max, min, cur;
    long long i;
    min = str_to_int(argv[1]);
    max = str_to_int(argv[2]);
    if(min > max)
        return(2);

    cur = 0;
    i   = 1;
    while(cur < max) {
        int tmp_len = digit_size(i * i);
        cur += tmp_len;
        
        if(cur >= min) {
            long long tmp_num = i * i;
            long long div;
            int trunc;
            
            trunc = (cur == min) ? 0 : cur - min + 1;
            if(trunc) {
            for(div = 1; trunc; --trunc, div *= 10)
            {}
            tmp_num %= div;
            }

            trunc = (cur <= max) ? 0 : cur - max;
            for(div = 1; trunc; --trunc, div *= 10)
            {}
            tmp_num /= div;

            printf("%0lld", tmp_num);
            min += digit_size(tmp_num);
        }
       ++i; 
    }
    printf("\n");
    
    return 0;
}

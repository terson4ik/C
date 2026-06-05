#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_LONG_LONG  19

long long str_to_num(const char *str)
{
    if(!*str)
        return 0;
    const char *tmp;
    char buff, minus;
    long long res = 0;
    if(*str == '-') {
        minus = 1;
        tmp = str + 1;
    } else {
        minus = 0;
        tmp = str;
    }
    for(; *tmp; ++tmp) {
        if(*tmp < '0' || *tmp > '9')
            return 0;
        buff = *tmp - '0';
        res = res * 10 + buff;
    }
    if(minus)
        return res * (-1);
    else
        return res;
}

/*
char rec_put_digits(char *str, int limit, long long num)
{
    char size = 0;
    if(!limit || !num){
        return 0;
    }
    size = 1 + rec_put_digits(str, limit - 1, num / 10);
    *(str + size - 1) = num % 10 + '0';
    return size;
}

char num_to_str(char *str, int limit, long long num)
{
    int res;
    if(num == 0)
        if(limit > 1){
            str[0] = '0';
            str[1] = 0;
            return 1;
        }
    if(num < 0){
        str[0] = '-';
        num *= -1;
        *(str + (res = 1 + rec_put_digits(str + 1, limit, num))) = 0;
    } else
        *(str + (res = rec_put_digits(str, limit, num))) = 0;
    return res;
}
*/

void copy_str(char *dest, const char *src, int size)
{
    if(size < 0) {
        fprintf(stderr, "INVALID SIZE: %d\n", size);
        exit(4);
    }
    char *tmp_dest = dest;
    const char *tmp_src = src;
    int i;
    for(i = size ; *tmp_src && i; ++tmp_dest, ++tmp_src, --i)
        *tmp_dest = *tmp_src;
    *tmp_dest = 0;
}
    
int str_len(const char *str)
{
    const char *tmp;
    for(tmp = str; *tmp; ++tmp)
    {}
    return tmp - str;
}

void reverse_char_arr(char *str)
{
    int i, j;
    char tmp;
    for(i = 0, j = str_len(str) - 1; i < j; ++i, --j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

char num_to_str(char *str, int limit, long long num)
{
    char minus;
    char *tmp_str;
    if(num == 0) {
        if(limit > 1) {
            *str = '0';
            *(str + 1) = 0;
            return 1;
        }
        *(str) = 0;
        return 0;
    }
    if(limit == 0) {
        *str = 0;
        return 0;
    }
    if(num < 0) {
        str[0] = '-';
        num *= (-1);
        tmp_str = str + 1;
        minus = 1;
    } else {
        tmp_str = str;
        minus = 0;
    }

    char size = 0;
    long long buff = num;
    while(limit && buff) {
        *tmp_str = (buff % 10) + '0';
        ++size;
        ++tmp_str;
        --limit;
        buff /= 10;
    }
    *tmp_str = 0;
    if(minus)
        reverse_char_arr(str + 1);
    else
        reverse_char_arr(str);
    return size;
}

int digit_size(long long digit)
{
    int res;
    long long buff;
    for(res = 0, buff = digit; buff; ++res, buff /= 10)
    {}
    return res;
}


int main (int argc, char **argv)
{ 
    if(argc != 3)
        return 1;
    int cur, i, max, min;
    long long tmp;
    cur = 0;
    min = str_to_num(argv[1]);
    max = str_to_num(argv[2]);
    char tmp_arr[MAX_SIZE_LONG_LONG * 2 + 1];
    i = 1;
    while(cur < max) {
        cur += digit_size(tmp = (long long)i * i);
        if(cur >= min) {
            int len, j;
            num_to_str(tmp_arr, MAX_SIZE_LONG_LONG + MAX_SIZE_LONG_LONG, tmp);
            len = str_len(tmp_arr);
            cur -= len;
            if(cur < min)
                j = min - cur - 1;
            else 
                j = 0;
            cur += j;
            while(cur < max && j < len) {
                putchar(tmp_arr[j]);
                ++j;
                ++cur;
            }
        }
        ++i;
    }
    putchar('\n');

    return 0;
}

/*
int main(int argc, char **argv)
{ 
    if(argc != 3)
        return 1;
    int diapason, cur_size, max_val, min_val, i, j;
    char is_over;
    max_val = str_to_num(argv[2]);
    min_val = str_to_num(argv[1]);
    diapason = max_val - min_val;
    if(diapason <= 0)
        return 2;
    long long buffer;
    char *buff_str = (char*)malloc(MAX_SIZE_LONG_LONG + 1);
    char *res_str = (char*)malloc(diapason + 2);
    cur_size = 0;
    i = 1;  /* iterator for i * i 
    j = 0;  /* offset relative to address 
    is_over = 0;
    while(cur_size <= max_val) {
        cur_size += digit_size(buffer = (long long)i * i);
        if(cur_size >= min_val) {
            if(cur_size == (min_val + j)) {
                num_to_str(buff_str, MAX_SIZE_LONG_LONG + 1, buffer);
                copy_str(res_str + j, buff_str, diapason - j + 1);
                j += digit_size(buffer);
            } else {
                int k;
                int len = str_len(res_str);
                num_to_str(buff_str, MAX_SIZE_LONG_LONG + 1, buffer);
                //cur_size -= str_len(buff_str);
                if(max_val < (min_val + j)) {
                    j = min_val - max_val;
                    is_over = 1;
                }
                k = 0;
                if(!len)
                    k = (min_val + j) - (cur_size - str_len(buff_str)) - 1;
                copy_str(res_str + len, buff_str + k, diapason - len + 1);
                j += str_len(res_str + len);
            }
        }
        if((min_val + str_len(res_str) - 1) >= max_val || is_over) {
            res_str[j] = 0;
            cur_size = max_val;
            break;
        }
        ++i;
    }
    printf("%s\n", res_str);

    free(buff_str);
    free(res_str);
    return 0;
}
*/

#include <stdio.h>

int str_end(const char *orig, const char *template);
const char *find_end(const char *str);
void print_true(int expr);

int main() /* int argc, char **argv */
{
    char word[] = "Valeria will be mine\n";
    char *fake = "Abobus";
    char *tru = "mine\n";
    print_true(str_end(word, fake));
    print_true(str_end(word, tru));

    return 0;
}
int str_end(const char *orig, const char *template)
{
    const char *end_orig = find_end(orig);
    const char *end_tmpl = find_end(template);
    int len_tmpl = end_tmpl - template;
    int len_orig = end_orig - orig;
    if (len_tmpl == 0)
        return (len_orig == 0) ? 1 : 0;
    else if (len_orig == 0)
        return 0; /* len_tmpl != 0 */
    else if (len_orig >= len_tmpl) {
        end_orig--, end_tmpl--;
        while (end_tmpl > template && *end_orig == *end_tmpl)
            end_orig--, end_tmpl--;
        /* after loop, end_template == template --> this is final step */
        if (*end_orig == *end_tmpl)
            return 1;
    }
    return 0;
}
void print_true(int expr)
{
    printf("%s, it's %s.\n", (expr) ? "Yes" : "No", (expr) ? "true" : "fake");
}


const char *find_end(const char *str)
{
    while(*str)
        str++;
    return str;
}

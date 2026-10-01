#include <stdio.h>
#include <stdlib.h>

#include "word_list.h"
#include "extraIO.h"

#define OUT_OF_MEMMORY_ERROR 5
static void exit_out_of_memory(void);

int main(void)
{
    word_que q; /* two pointers */
    word *w = word_init();

    if (!w)
        exit_out_of_memory();

    word_que_init(&q);
    while(!feof(stdin)) {
        int need_exec;
        fputs("> ", stdout);
        enum word_status w_stat;
        need_exec = 1;
        while ((w_stat = get_word(w)) != EOL) {
            if (!need_exec)
                continue;

            switch (w_stat) {
            case OK:        
                    if (!word_que_add(&q, word_get_buf(w)))
                        exit_out_of_memory();
                    break;
            case QUOT_FAIL:
                    fputs("Error: unmatched quotes\n", stderr);
                    need_exec = 0;
                    break;
            case FATAL_ERR: 
                    exit_out_of_memory();
              /* no break */
            case EOL: /* skip */
            }
            
        }
        if (need_exec)
            word_item_execute(q.f);
        word_item_dispose(&q.f);
    }

    word_dispose_struct(&w);
    fputs("^D\n", stdout);
    return 0;
}

static void exit_out_of_memory(void)
{
    fputs("Error: no left RAM\n", stderr);
    exit(OUT_OF_MEMMORY_ERROR);
}

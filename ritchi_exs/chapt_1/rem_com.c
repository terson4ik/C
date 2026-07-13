#include <stdio.h>
#include <stdlib.h>

/* example
 * if meet "" or '' we need to skip all chars which have != \' or \" 
 * if find "/*" and state don't detected READONLY \" \' then skip chars
 * while don't find second part "'/*'" , after this meet switch mode to 
 * putchars, while not found another portion of "/*"
 * until no time EOF 
 * it's over
 * okey, if meet the \"or\' then switch mode to READ ONLY, without hunt "/*"
 * after second \" or \' turn off this mode and "/*" legitimate.
 * off course, if "/* \" "  then, because we turn on mode erase comments, we
 * ignore this
 */
/* by default state = common, if meet "/" then state == START and if next step
 * meet '*' that state = IGNOTE, else put '/' and char.
 * in state = IGNORE, if meet '*' then state = END, and if meet in this state
 * '/' then state == COMMON */
void hand_comm(int c);

int main(void)
{
    int c;
    while((c = getchar()) != EOF)
        hand_comm(c);
    return 0;
}

void hand_comm(int c)
{
    enum states {
        START,
        END,
        COMMON,
        IGNORE,
        READONLY_ONE,
        READONLY_TWO,
        ONE_IGN,
        TWO_IGN,
        TWO_IGN_ONCE,
        TWO_SLESH,
    } static gstate = COMMON;
//its comment will be remove. in original C "//" does not exists.
    switch(gstate) {
        case COMMON:
            if(c == '/') {
                gstate = START;
                return;
            } else
                putchar(c);
            if(c == '\\')
                gstate = ONE_IGN;
            else if(c == '\"')
                gstate = READONLY_TWO;
            else if(c == '\'')
                gstate = READONLY_ONE;
            return;
        case START:
            if(c == '/') 
                gstate = TWO_SLESH;
            else if(c == '*')
                gstate = IGNORE;
            else {
                gstate = COMMON;
                printf("/%c", c);
            }
            return;
        case TWO_SLESH:
            if(c == '\n') {
                gstate = COMMON;
                putchar('\n');
            }
            return;
        case READONLY_TWO:
            if(c == '\\')
                gstate = TWO_IGN;
            else if(c == '\"')
                gstate = COMMON;
            putchar(c);
            return;
        case READONLY_ONE:
            if(c == '\\')
                gstate = TWO_IGN_ONCE;
            else if(c == '\'')
                gstate = COMMON;
            putchar(c);
            return;
        case ONE_IGN:
            putchar(c);
            gstate = COMMON;
            return;
        case TWO_IGN:
            putchar(c);
            gstate = READONLY_TWO;
            return;
        case TWO_IGN_ONCE:
            putchar(c);
            gstate = READONLY_ONE;
            return;
        case IGNORE:
            if(c == '*')
                gstate = END;
            return;
        case END:
            if(c == '/') {
                gstate = COMMON;
            } else
                gstate = IGNORE;
            return;
        default:
            fprintf(stderr, "undefined behaver");
            exit(1);
    }
}
/***/

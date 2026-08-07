#include "m_sort.h"
#include "mstring.h"

#define ERRVALL -1

int binsearch(char *word, struct key tab[], int lim)
{
    int mid, cond;
    int left = 0;
    int right = lim - 1;
    while (left <= right) {
        mid = (left + right) / 2;
        cond = mstrcmp(word, tab[mid].word);
        if (cond > 0)
            left = mid + 1;
        else if (cond < 0)
            right = mid - 1;
        else /* cond == 0 */
            return mid;
    }
    return ERRVALL;
}

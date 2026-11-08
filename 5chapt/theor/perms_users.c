#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int i;
    int n = getgroups(0, NULL);
    gid_t *arr = malloc(sizeof(gid_t) * n);
    getgroups(n, arr);
    /* effective and real group ID not guarantied */
    /* use combo getgroups() + getegid() */
    printf("all supplementary groups ID:\n");
    for (i = 0; i < n; i++)
        printf("%d: %d\n", i+1, arr[i]);

    printf("UID:%u\n", getuid());
    printf("EUID:%u\n", geteuid());
    printf("UID:%u\n", getgid());
    printf("EUID:%u\n", getegid());

    /* don't recommended */
  /*printf("SAVED_UID:%u\n", getresuid()); res -- real, effective, saved */
    /* use setegid and setgid is equal for a common user 
     * but for root they change all: real effective and saved IDs
     *
     * also we have setregid setresuid and etc */
    return 0;
}

#include <stdio.h>
#include <unistd.h>

#define print_id(fid) printf(#fid ": %d\n", fid)
int main()
{
    print_id(getuid());
    print_id(getgid());
    print_id(getegid());
    print_id(geteuid());

    print_id(getpid());
    print_id(getppid());
    print_id(getppid());
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 5; i++) {
        fork();
    }

    sleep(3);

    return (0);
}

/*
    Output for 3 times:
    ex2─┬─ex2─┬─ex2───ex2
        │     └─ex2
        ├─ex2───ex2
        └─ex2

    Output for 5 times:
    ex2─┬─ex2─┬─ex2─┬─ex2─┬─ex2───ex2
        │     │     │     └─ex2
        │     │     ├─ex2───ex2
        │     │     └─ex2
        │     ├─ex2─┬─ex2───ex2
        │     │     └─ex2
        │     ├─ex2───ex2
        │     └─ex2
        ├─ex2─┬─ex2─┬─ex2───ex2
        │     │     └─ex2
        │     ├─ex2───ex2
        │     └─ex2
        ├─ex2─┬─ex2───ex2
        │     └─ex2
        ├─ex2───ex2
        └─ex2

    Since each call of fork() (in case of success) creates 2 processes, each of them having fork() calls as well, in total there will be 2^n processes 
    (i.e. 8 processes in the first case and 32 in the second)
*/
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <string.h>
#include <sys/resource.h>

int main() {
	int n = 10;
    int mb = 1024;
    for (int i = 0; i < n; i++) {
        memset(malloc(mb * 1024 * 1024), 0, mb * 1024 * 1024);

        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        printf("mem usage - %d\n", usage.ru_maxrss);

        sleep(1);
    }

    return 0;
}
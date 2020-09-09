#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 1;

    int n;
    sscanf(argv[1], "%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n-i; j++)
            printf(" ");
        for (int j = 1; j <= 2*i-1; j++)
            printf("*");
        printf("\n");
    }

    return 0;
}

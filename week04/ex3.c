#include <stdlib.h>
#include <stdio.h>

int main() {
    char cmd[256];
    while (1) {
        fgets(cmd, 256, stdin);
        system(cmd);
    }

    return 0;
}
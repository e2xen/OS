#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 20

int main() {
    int random_file = open("/dev/random", O_RDONLY);
    int output_file = open("ex1.txt", O_CREAT | O_WRONLY, S_IRWXU);

    char buff[N];
    read(random_file, buff, N);
    write(output_file, buff, N);

    close(random_file);
    close(output_file);

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_NAME "ex1.txt"

int main() {
    char s[] = "This is a nice day";

    int file = open(FILE_NAME, O_RDWR);
    ftruncate(file, sizeof(char)*strlen(s));

    struct stat st;
    stat(FILE_NAME, &st);

    char *addr = mmap(0, st.st_size, PROT_WRITE, MAP_SHARED, file, 0);
    memcpy(addr, s, strlen(s));
    munmap(addr, st.st_size);

    close(file);

    return 0;
}
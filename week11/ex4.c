#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SOURCE_FILE_NAME "ex1.txt"
#define DEST_FILE_NAME "ex1.memcpy.txt"


int main() {
    
    int src_file = open(SOURCE_FILE_NAME, O_RDONLY);
    size_t size = lseek(src_file, 0, SEEK_END);
    char *src = mmap(0, size, PROT_READ, MAP_PRIVATE, src_file, 0);

    int dest_file = open(DEST_FILE_NAME, O_RDWR | O_CREAT, 0666);
    ftruncate(dest_file, size);
    char *dest = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, dest_file, 0);

    memcpy(dest, src, size);

    close(src_file);
    close(dest_file);

    return 0;
}
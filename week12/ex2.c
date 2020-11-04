#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv) {
    char c;

    if (argc < 2) {
        while (fread(&c, sizeof(char), 1, stdin))
            printf("%c", c);

        return 0;
    }

    int j = 1;
    char *mode = "w+";
    if (!strcmp(argv[1], "-a")) {
        j++;
        mode = "a+";
    }

    int n_outputs = argc-j+1;
    FILE** outputs = malloc(n_outputs*sizeof(FILE*));
    for (int i = 0; i < n_outputs-1; i++) 
        outputs[i] = fopen(argv[i+j], mode);
    outputs[n_outputs-1] = stdout;

    while (fread(&c, sizeof(char), 1, stdin))
        for (int i = 0; i < n_outputs; i++)
            fwrite(&c, sizeof(char), 1, outputs[i]);

    for (int i = 0; i < n_outputs-1; i++)
        fclose(outputs[i]);

    return 0;
}
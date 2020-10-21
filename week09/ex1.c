#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int n_frames = 10;

    printf("Ageing algorithm with %d frames\n", n_frames);

    int *pages = malloc(n_frames * sizeof(int));
    memset(pages, 0, n_frames);
    unsigned char *age = malloc(n_frames * sizeof(unsigned char));
    memset(age, 0, n_frames);

    FILE* file = fopen("Lab 09 input.txt", "r");

    int hit = 0;
    int miss = 0;
    int current;

    while(fscanf(file, "%d", &current) != EOF) {
        int p = -1;
        for (int i = 0; i < n_frames; i++)
            if (current == pages[i])
                p = i;

        if (p == -1) {
            int i_min = 0;
            for (int i = 0; i < n_frames; i++)
                if (age[i] < age[i_min])
                    i_min = i;

            pages[i_min] = current;
            age[i_min] = 1<<7;

            miss++;
        } else {
            age[p] >>= 1;
            age[p] |= 1<<7;

            hit++;
        }

    }

    printf("Hits: %d\nMisses: %d\n", hit, miss);
    printf("Hit/Miss ratio: %f\n", (double)hit/miss);

    return 0;
}


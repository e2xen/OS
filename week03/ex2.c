#include <stdio.h>

void swap(int *p1, int *p2) {
    int tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void bubble_sort(int array[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 1; j < size-i; j++)
            if (array[j-1] > array[j])
                swap(&array[j-1], &array[j]);
}

int main() {
    int size, array[100];
    printf("Enter the size of the array:");
    scanf("%d", &size);
    printf("Enter the array:");
    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);

    bubble_sort(array, size);

    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");

    return 0;
}

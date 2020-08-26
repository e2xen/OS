#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int a = INT_MAX;
    float b = FLT_MAX;
    double c = DBL_MAX;

    printf("int size = %lu, float size = %lu, double size = %lu\n", sizeof(a), sizeof(b), sizeof(c));
    printf("int max = %d, max float = %f, max double = %f\n", a, b, c);

    return 0;
}

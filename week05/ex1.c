#include <stdio.h>
#include <pthread.h>

void* callback (void *arg) {
    printf("Thread %d is created\n", *(int*)arg);
}

int main() {
    pthread_t thread;

    for (int i = 0; i < 5; i++) {
        printf("Creating new thread - %d\n", i);
        pthread_create(&thread, NULL, &callback, &i);
        pthread_join(thread, NULL);
    }

    return 0;
}
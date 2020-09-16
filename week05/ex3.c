#include <stdio.h>
#include <pthread.h>

#define N 10
int i = 0;

int buffer[N];
int counter = 0;

int consumerAsleep = 1;
int producerAsleep = 0;

void* producer(void *arg) {
    while (1) {
        if (producerAsleep)
            continue;
        
        buffer[counter++] = 1; //produce
        if (counter == N) {
            printf("Producer finished - %d\n", i++);
            counter--;
            producerAsleep = 1;
            consumerAsleep = 0;
        }
    }
}

void* consumer(void *arg) {
    while (1) {
        if (consumerAsleep)
            continue;
        
        buffer[counter--] = 0; //consume
        if (counter == 0) {
            counter++;
            producerAsleep = 0;
            consumerAsleep = 1;
        }
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, &producer, NULL);
    pthread_create(&consumer_thread, NULL, &consumer, NULL);

    for(;;) {}

    return 0;
}

// program freezed after 1915554 iterations of producer-consumer process
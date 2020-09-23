#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int starting_time;
    int exit_time;
    int waiting_time;
} process;

int compare(const void *a, const void *b) {
    process **m = (process**) a;
    process **n = (process**) b;
    if ((*m)->arrival_time == (*n)->arrival_time)
        return ((*m)->id < (*n)->id) ? -1 : 1;
    return ((*m)->arrival_time < (*n)->arrival_time) ? -1 : 1;
}

process* _delete_min(process** array, int size) {
    if (size <= 0)
        return 0;

    int min_i = 0;
    process* min_p = array[min_i];
    for (int i = 1; i < size; i++)
        if (array[i]->burst_time < min_p->burst_time) {
            min_i = i;
            min_p = array[i];
        }

    for (int i = min_i + 1; i < size; i++)
        array[i-1] = array[i];

    return min_p;
}



int main() {
    process **inp_proc, **proc;
    int n;

    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    proc = malloc(n*sizeof(process*));
    inp_proc = malloc(n*sizeof(process*));
    for (int i = 0; i < n; i++)
        inp_proc[i] = malloc(sizeof(process));

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &(inp_proc[i]->arrival_time), &(inp_proc[i]->burst_time));
        inp_proc[i]->id = i;
    }

    for (int i = 0; i < n; i++)
        proc[i] = inp_proc[i];


    qsort(proc, n, sizeof(process*), &compare);

    process **queue = malloc(n*sizeof(process*));
    int q_size = 0;

    int current_time = 0;
    int done = 0;
    process* current_p;
    while (done < n || q_size > 0) {
        while (done < n && proc[done]->arrival_time <= current_time)
            queue[q_size++] = proc[done++];
        if (q_size <= 0)
            current_time++;
        else {
            current_p = _delete_min(queue, q_size--);
            current_p->starting_time = current_time;
            current_p->exit_time = current_p->starting_time + current_p->burst_time;
            current_p->waiting_time = current_time - current_p->arrival_time;
            current_time += current_p->burst_time;
        }
    }



    printf("Scheduling graph:\n");
    for (int i = 0; i < n; i++) {
        printf("%d: ", i);
        for (int j = 0; j < inp_proc[i]->starting_time; j++)
            printf(" ");
        for (int j = inp_proc[i]->starting_time; j < inp_proc[i]->exit_time; j++)
            printf("#");
        printf("\n");
    }
    printf("\n");


    int av_turnaround = 0;
    int av_waiting = 0;
    for (int i = 0; i < n; i++) {
        av_turnaround += inp_proc[i]->exit_time - inp_proc[i]->starting_time;
        av_waiting += inp_proc[i]->waiting_time;
        printf("Process %d\n", i);
        printf("Completion time: %d\n", inp_proc[i]->exit_time);
        printf("Turnaround time: %d\n", inp_proc[i]->exit_time - proc[i]->starting_time);
        printf("Waiting time: %d\n\n", inp_proc[i]->waiting_time);
    }

    printf("Average turnaround time: %f\nAverage waiting time: %f\n", (double)av_turnaround/n, (double)av_waiting/n);

    return 0;
}


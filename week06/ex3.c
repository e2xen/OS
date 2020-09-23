#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int starting_time;
    int exit_time;
    int waiting_time;
    int remaining_time;
} process;

int compare(const void *a, const void *b) {
    process **m = (process**) a;
    process **n = (process**) b;
    if ((*m)->arrival_time == (*n)->arrival_time)
        return ((*m)->id < (*n)->id) ? -1 : 1;
    return ((*m)->arrival_time < (*n)->arrival_time) ? -1 : 1;
}

void _delete(process** array, int index, int size) {
    if (size <= 0)
        return;

    for (int i = index + 1; i < size; i++)
        array[i-1] = array[i];
}



int main() {
    process **inp_proc, **proc;
    int n, quantum;

    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    printf("Enter the quantum:\n");
    scanf("%d", &quantum);

    proc = malloc(n*sizeof(process*));
    inp_proc = malloc(n*sizeof(process*));
    for (int i = 0; i < n; i++)
        inp_proc[i] = malloc(sizeof(process));

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &(inp_proc[i]->arrival_time), &(inp_proc[i]->burst_time));
        inp_proc[i]->remaining_time = inp_proc[i]->burst_time;
        inp_proc[i]->id = i;
    }

    for (int i = 0; i < n; i++)
        proc[i] = inp_proc[i];


    qsort(proc, n, sizeof(process*), &compare);

    process **queue = malloc(n*sizeof(process*));
    int q_size = 0;

    int current_time = 0;
    int done = 0;

    while (done < n || q_size > 0) {
        while (done < n && proc[done]->arrival_time <= current_time)
            queue[q_size++] = proc[done++];
        if (q_size <= 0)
            current_time++;
        else {
            for (int i = 0; i < q_size; i++) {
                if (queue[i]->remaining_time == queue[i]->burst_time) {
                    queue[i]->starting_time = current_time;
                    queue[i]->waiting_time = current_time - queue[i]->arrival_time;
                }
                if (queue[i]->remaining_time <= quantum) {
                    current_time += queue[i]->remaining_time;
                    queue[i]->exit_time = current_time;
                    _delete(queue, i, q_size--);
                    i--;
                } else {
                    queue[i]->remaining_time -= quantum;
                    current_time += quantum;
                }
                while (done < n && proc[done]->arrival_time <= current_time)
                    queue[q_size++] = proc[done++];
            }
        }
    }



    printf("Scheduling graph (turnaround time shown):\n");
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
        int turnaround = inp_proc[i]->exit_time - inp_proc[i]->starting_time;
        inp_proc[i]->waiting_time += turnaround - inp_proc[i]->burst_time;
        av_turnaround += turnaround;
        av_waiting += inp_proc[i]->waiting_time;
        printf("Process %d\n", i);
        printf("Completion time: %d\n", inp_proc[i]->exit_time);
        printf("Turnaround time: %d\n", inp_proc[i]->exit_time - proc[i]->starting_time);
        printf("Waiting time: %d\n\n", inp_proc[i]->waiting_time);
    }

    printf("Average turnaround time: %f\nAverage waiting time: %f\n", (double)av_turnaround/n, (double)av_waiting/n);

    return 0;
}

/**
    Input: 10 processes and quantum 3
    their arrival time and burst time:
    0 1
    0 2
    0 4
    0 6
    0 8
    11 8
    11 6
    11 4
    11 2
    11 1

    Obtained results:
        for FCFS:
        Average turnaround time: 4.200000
        Average waiting time: 13.400000

        for SJF:
        Average turnaround time: 4.200000
        Average waiting time: 7.900000

        for Robin:
        Average turnaround time: 15.300000
        Average waiting time: 16.400000

    SJF performed better than others
**/

#include <stdio.h>
#include <stdlib.h>

// struct representing a process
typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int starting_time;
    int exit_time;
    int waiting_time;
} process;

// function for comparison of two processes by their arrival time
// uses id field to make qsort() stable
int compare(const void *a, const void *b) {
    process **m = (process**) a;
    process **n = (process**) b;
    if ((*m)->arrival_time == (*n)->arrival_time)
        return ((*m)->id < (*n)->id) ? -1 : 1;
    return ((*m)->arrival_time < (*n)->arrival_time) ? -1 : 1;
}

// function returning max of two values
int _max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    process **inp_proc; // inp_proc contains processes in the order of their entering
    process **proc; // proc will contain processes in sorted order (by arrival time)
    int n; // number of processes

    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    // inp_proc and proc initialization
    proc = malloc(n*sizeof(process*));
    inp_proc = malloc(n*sizeof(process*));
    for (int i = 0; i < n; i++)
        inp_proc[i] = malloc(sizeof(process));

    printf("Enter the arrival time and burst time of each process:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &(inp_proc[i]->arrival_time), &(inp_proc[i]->burst_time));
        inp_proc[i]->id = i;
    }

    // copying inp_proc to proc
    for (int i = 0; i < n; i++)
        proc[i] = inp_proc[i];

    qsort(proc, n, sizeof(process*), &compare); // sorting proc

    // assigning values for the first process
    proc[0]->starting_time = proc[0]->arrival_time;
    proc[0]->exit_time = proc[0]->arrival_time + proc[0]->burst_time;
    proc[0]->waiting_time = proc[0]->starting_time;
    // assigning values for other processes
    for (int i = 1; i < n; i++) {
        proc[i]->starting_time = _max(proc[i-1]->exit_time, proc[i]->arrival_time); // starting time is max of exit time of previous process and its arrival time
        proc[i]->exit_time = proc[i]->starting_time + proc[i]->burst_time; // exit time is sum of starting time and burst time
        proc[i]->waiting_time = proc[i]->starting_time - proc[i]->arrival_time; // waiting time id the difference between starting time and arrival time
    }


    // next just the output and average values calculation

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


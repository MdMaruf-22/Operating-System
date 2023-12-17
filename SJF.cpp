#include<stdio.h>
#include<stdlib.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    return p1->burst_time - p2->burst_time;
}

int main() {
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].pid = i + 1;
    }

    // Sort processes based on burst time
    qsort(processes, n, sizeof(struct Process), compare);

    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].burst_time;
    processes[0].waiting_time = 0;

    for (i = 1; i < n; i++) {
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);

        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %f\n", avg_waiting_time);
    printf("Average Turnaround Time: %f\n", avg_turnaround_time);

    return 0;
}

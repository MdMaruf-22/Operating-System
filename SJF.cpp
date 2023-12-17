#include <stdio.h>
#include <stdlib.h>

struct Process {
    int p;
    int at;
    int bt;
    int wt;
    int tt;
    int ct;
};

int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    return p1->bt - p2->bt;
}

int main() {
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process prs[n];

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time of process %d: ", i + 1);
        scanf("%d %d", &prs[i].at, &prs[i].bt);
        prs[i].p = i + 1;
    }
    qsort(prs, n, sizeof(struct Process), compare);

    prs[0].ct = prs[0].at + prs[0].bt;
    prs[0].tt = prs[0].bt;
    prs[0].wt = 0;

    for (i = 1; i < n; i++) {
        prs[i].ct = prs[i - 1].ct + prs[i].bt;
        prs[i].tt = prs[i].ct - prs[i].at;
        prs[i].wt = prs[i].tt - prs[i].bt;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", prs[i].p, prs[i].at, prs[i].bt, prs[i].ct, prs[i].wt, prs[i].tt);
    }

    return 0;
}

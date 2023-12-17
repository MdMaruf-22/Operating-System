#include<iostream>
#include<algorithm>
using namespace std;

struct Process {
    int id, bt, at, ct, tat, wt;
};

void input(Process*, int);
void calc(Process*, int);
void show(Process*, int);

int main() {
    int n;
    cout << "\nEnter the number of processes in your system:\n";
    cin >> n;
    Process *p = new Process[n];
    input(p, n);
    sort(p, p + n, [](const Process& a, const Process& b) {
        return a.at < b.at;
    });

    calc(p, n);
    show(p, n);

    delete[] p;
    return 0;
}

void input(Process* p, int n) {
    for (int i = 0; i < n; i++) {
        cout << "\nEnter arrival time for process " << i + 1 << ":\n";
        cin >> p[i].at;
        cout << "\nEnter burst time for process " << i + 1 << ":\n";
        cin >> p[i].bt;
        p[i].id = i + 1;
    }
}

void calc(Process* p, int n) {
    int sum = 0;
    sum = sum + p[0].at;
    for (int i = 0; i < n; i++) {
        sum = sum + p[i].bt;
        p[i].ct = sum;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        if (sum < p[i + 1].at) {
            int t = p[i + 1].at - sum;
            sum = sum + t;
        }
    }
}

void show(Process* p, int n) {
    cout << "Process\tArrival\tBurst\tWaiting\tTurn Around\tCompletion\n";
    for (int i = 0; i < n; i++) {
        cout << " P[" << p[i].id << "]\t " << p[i].at << "\t" << p[i].bt << "\t" << p[i].wt << "\t " << p[i].tat << "\t\t" << p[i].ct << "\n";
    }
}

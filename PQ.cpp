#include<iostream>
#include<limits>

using namespace std;

struct P {
    string n;
    int at;
    int bt;
    int p;
    int rt;
    int ct;
    int wt;
    int tat;
};

void initP(P &p) {
    p.rt = p.bt;
}

int main() {
    int np;
    cout << "Enter the number of processes: ";
    cin >> np;

    P p[np];

    for (int i = 0; i < np; i++) {
        p[i].n = "P" + to_string(i + 1);
        cout << "Enter Arrival Time for " << p[i].n << ": ";
        cin >> p[i].at;
        cout << "Enter Burst Time for " << p[i].n << ": ";
        cin >> p[i].bt;
        cout << "Enter Priority for " << p[i].n << ": ";
        cin >> p[i].p;

        initP(p[i]);
    }

    cout << "\n";

    for (int i = 0; i < np - 1; i++) {
        for (int j = i + 1; j < np; j++) {
            if (p[j].at < p[i].at) {
                P t = p[j];
                p[j] = p[i];
                p[i] = t;
            }
        }
    }

    int ct = 0;

    while (true) {
        int hi = -1;
        int hp = numeric_limits<int>::max();
        bool allC = true;

        for (int i = 0; i < np; i++) {
            if (p[i].rt > 0) {
                allC = false;
                if (p[i].at <= ct) {
                    if (p[i].p < hp) {
                        hp = p[i].p;
                        hi = i;
                    }
                }
            }
        }

        if (allC) {
            break;
        }

        p[hi].rt = 0;
        ct += p[hi].bt;
        p[hi].ct = ct;
    }

    cout << "Process\tArrival Time\tBurst Time\tPriority\tResponse Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";

    for (int i = 0; i < np; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        cout << p[i].n << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].p << "\t" << p[i].rt << "\t" << p[i].ct << "\t" << p[i].wt << "\t" << p[i].tat << endl;
    }

    return 0;
}

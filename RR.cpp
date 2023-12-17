#include<iostream>
#include<vector>
using namespace std;

struct Process {
    string pn;
    int bt;
    int at;
    int wt;
    int ct;
    int rt;
    int tt;

    void init() {
        wt = 0;
        rt = 0;
        tt = 0;
    }
};

int main() {
    int np;
    int tq;
    int ct = 0;

    cout << "\nEnter Time Quantum: ";
    cin >> tq;

    cout << "\nEnter no. of processes: ";
    cin >> np;

    vector<Process> p(np);

    for (int n = 0; n < np; n++) {
        p[n].pn = "p" + to_string(n + 1);
        cout << "Enter Arrival Time for " << p[n].pn << ": ";
        cin >> p[n].at;
        cout << "Enter Burst Time for " << p[n].pn << ": ";
        cin >> p[n].bt;
        p[n].init();
    }

    cout << "\n" << endl;

    int rp = np;

    for (int i = 0; i < np; i = (i + 1) % np) {
        if (p[i].rt > 0 && p[i].at <= ct) {
            if (p[i].rt == p[i].bt) {
                p[i].rt = ct;
            }

            if (p[i].rt <= tq) {
                ct += p[i].rt;
                p[i].ct = ct;
                p[i].rt = 0;
                rp--;
            } else {
                ct += tq;
                p[i].rt -= tq;
            }
        }

        if (rp == 0) {
            break;
        }
    }

    cout << "Process\tArrival Time\tBurst Time\tResponse Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int n = 0; n < np; n++) {
        p[n].tt = p[n].ct - p[n].at;
        p[n].wt = p[n].tt - p[n].bt;

        cout << p[n].pn << "\t" << p[n].at << "\t\t" << p[n].bt << "\t\t"
             << p[n].rt << "\t\t" << p[n].ct << "\t\t" << p[n].wt
             << "\t\t" << p[n].tt << "\n";
    }

    return 0;
}

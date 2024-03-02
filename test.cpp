#include <iostream>
#include <climits>
using namespace std;

struct Process {
    int AT, BT, WT, FT, TAT, RT, pos;
};

int quant;

int main() {
    int n, i, j;
    // Taking Input
    cout << "Enter the no. of processes: ";
    cin >> n;
    Process p[n];
    cout << "Enter the quantum: ";
    cin >> quant;
    for (i = 0; i < n; i++){
        p[i].pos = i+1;
        cout << "Enter the Arrival time of process " << p[i].pos << ": ";
        cin >> p[i].AT;
        cout << "Enter the Burst time of process " << p[i].pos << ": ";
        cin >> p[i].BT;
    }
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];

    // Initializing burst and arrival time arrays
    int index = -1;
    for (i = 0; i < n; i++) {
        b[i] = p[i].BT;
        a[i] = p[i].AT;
        for (j = 0; j < 20; j++) {
            s[i][j] = -1;
        }
    }

    int tot_wt = 0, tot_tat = 0, tot_rt = 0;
    bool flag = false;

    while (c != 0) {
        mini = INT_MAX;
        flag = false;

        for (i = 0; i < n; i++) {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0) {
                index = i;
                mini = a[i];
                flag = true;
            }
        }

        // if no process is ready to execute, just increment time
        if (!flag) {
            time++;
            continue;
        }

        // calculating start time
        j = 0;

        while (s[index][j] != -1) {
            j++;
        }

        if (s[index][j] == -1) {
            s[index][j] = time;
            p[index].RT = time - p[index].AT; // Response time calculation
        }

        if (b[index] <= quant) {
            time += b[index];
            b[index] = 0;
        } else {
            time += quant;
            b[index] -= quant;
        }

        if (b[index] > 0) {
            a[index] = time + 0.1;
        }

        // calculating arrival, burst, final times
        if (b[index] == 0) {
            c--;
            p[index].FT = time;
            p[index].WT = p[index].FT - p[index].AT - p[index].BT;
            tot_wt += p[index].WT;
            p[index].TAT = p[index].BT + p[index].WT;
            tot_tat += p[index].TAT;
            tot_rt += p[index].RT;
        }
    } // end of while loop

    // Printing output
    cout << "Process number ";
    cout << "Arrival time ";
    cout << "Burst time ";
    cout << "\tCompletion time";
    cout << "\tWaiting Time ";
    cout << "\tTurnAround Time ";
    cout << "\tResponse Time" << endl;

    for (i = 0; i < n; i++) {
        cout << p[i].pos << "\t\t";
        cout << p[i].AT << "\t\t";
        cout << p[i].BT << "\t";
        cout << p[i].FT << "\t\t";
        cout << p[i].WT << "\t\t";
        cout << p[i].TAT << "\t\t\t";
        cout << p[i].RT << endl;
    }

    // Calculating average wait time, turnaround time, and response time
    double avg_wt = static_cast<double>(tot_wt) / n;
    double avg_tat = static_cast<double>(tot_tat) / n;
    double avg_rt = static_cast<double>(tot_rt) / n;

    // Printing average wait time, turnaround time, and response time
    cout << "The average wait time is: " << avg_wt << endl;
    cout << "The average TurnAround time is: " << avg_tat << endl;
    cout << "The average Response time is: " << avg_rt << endl;

    return 0;
}

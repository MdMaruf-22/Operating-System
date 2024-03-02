#include <iostream>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    // Allocation Matrix
    int alloc[n][m];
    cout << "Enter resources currently allocated to each process:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "For process " << i << ": ";
        for (int j = 0; j < m; ++j) {
            cin >> alloc[i][j];
        }
    }

    // MAX Matrix
    int max[n][m];
    cout << "Enter maximum resources for each process:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "For process " << i << ": ";
        for (int j = 0; j < m; ++j) {
            cin >> max[i][j];
        }
    }

    // Available Resources
    int avail[m];
    cout << "Enter available resources: ";
    for (int i = 0; i < m; ++i) {
        cin >> avail[i];
    }

    int f[n] = {0}; // Finish array
    int ans[n], ind = 0; // Safe sequence array

    // Calculate the Need matrix
    int need[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; ++y) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    // Check if sequence is safe or not
    for (int i = 0; i < n; ++i) {
        if (f[i] == 0) {
            flag = 0;
            cout << "The given sequence is not safe" << endl;
            break;
        }
    }

    if (flag == 1) {
        cout << "Following is the SAFE Sequence" << endl;
        for (int i = 0; i < n - 1; ++i) {
            cout << " P" << ans[i] << " ->";
        }
        cout << " P" << ans[n - 1] << endl;
    }

    return 0;
}

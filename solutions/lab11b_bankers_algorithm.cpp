#include <iostream>
#include <vector>

using namespace std;

const int P = 5, R = 3;

bool check_safe(const int alloc[P][R], const int need[P][R], int avail[R], vector<int>& seq) {
    int work[R];
    for (int i = 0; i < R; i++) work[i] = avail[i];
    bool finish[P] = {false};
    seq.clear();

    for (int k = 0; k < P; k++) {
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) { possible = false; break; }
                }
                if (possible) {
                    for (int j = 0; j < R; j++) work[j] += alloc[i][j];
                    finish[i] = true;
                    seq.push_back(i);
                }
            }
        }
    }
    return seq.size() == P;
}

int main() {
    int alloc[P][R] = {
        {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}
    };
    int max[P][R] = {
        {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}
    };
    int avail[R] = {3, 3, 2};

    int need[P][R];
    cout << "Need Matrix:\n";
    for (int i = 0; i < P; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            cout << need[i][j] << " ";
        }
        cout << "\n";
    }

    vector<int> seq;
    if (check_safe(alloc, need, avail, seq)) {
        cout << "\nSystem is in a SAFE state.\nSafe sequence: ";
        for (size_t i = 0; i < seq.size(); i++) {
            cout << "P" << seq[i] << (i + 1 < seq.size() ? " -> " : "\n");
        }
    } else {
        cout << "\nSystem is in an UNSAFE state.\n";
    }

    // Request from P1: [1, 0, 2]
    cout << "\nSuppose P1 requests [1, 0, 2]:\n";
    int req[R] = {1, 0, 2};
    for (int j = 0; j < R; j++) {
        avail[j] -= req[j];
        alloc[1][j] += req[j];
        need[1][j] -= req[j];
    }

    if (check_safe(alloc, need, avail, seq)) {
        cout << "Request Granted. Resulting system is SAFE.\nSafe sequence: ";
        for (size_t i = 0; i < seq.size(); i++) {
            cout << "P" << seq[i] << (i + 1 < seq.size() ? " -> " : "\n");
        }
    } else {
        cout << "Request Denied. Would cause unsafe state.\n";
    }

    return 0;
}

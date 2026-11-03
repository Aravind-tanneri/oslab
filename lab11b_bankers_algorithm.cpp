#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int NUM_P = 5;
const int NUM_R = 3;

// Checks if the system is in a safe state and finds a safe sequence
bool is_safe_state(const vector<vector<int>>& alloc, const vector<vector<int>>& need, vector<int> avail, vector<int>& safe_seq) {
    vector<int> work = avail;
    vector<bool> finish(NUM_P, false);
    safe_seq.clear();

    for (int count = 0; count < NUM_P; count++) {
        bool found = false;
        for (int p = 0; p < NUM_P; p++) {
            if (!finish[p]) {
                bool can_allocate = true;
                for (int j = 0; j < NUM_R; j++) {
                    if (need[p][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < NUM_R; j++) {
                        work[j] += alloc[p][j];
                    }
                    finish[p] = true;
                    safe_seq.push_back(p);
                    found = true;
                    break;
                }
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    cout << "========================================================\n";
    cout << " Lab 11b: Deadlock Avoidance (Banker's Algorithm)\n";
    cout << "========================================================\n";

    // Data from Lab Task 11b specification
    vector<vector<int>> alloc = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    vector<vector<int>> max_claim = {
        {7, 5, 3}, // P0
        {3, 2, 2}, // P1
        {9, 0, 2}, // P2
        {2, 2, 2}, // P3
        {4, 3, 3}  // P4
    };

    vector<int> avail = {3, 3, 2};

    // Calculate Need Matrix = Max - Allocation
    vector<vector<int>> need(NUM_P, vector<int>(NUM_R));
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < NUM_P; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < NUM_R; j++) {
            need[i][j] = max_claim[i][j] - alloc[i][j];
            cout << need[i][j] << " ";
        }
        cout << "\n";
    }

    // Safety check
    vector<int> safe_seq;
    if (is_safe_state(alloc, need, avail, safe_seq)) {
        cout << "\nSystem is in a SAFE state.\nOne safe sequence: ";
        for (size_t i = 0; i < safe_seq.size(); i++) {
            cout << "P" << safe_seq[i] << (i + 1 < safe_seq.size() ? " -> " : "\n");
        }
    } else {
        cout << "\nSystem is in an UNSAFE state (Deadlock potential).\n";
    }

    // Additional experiment: Resource-Request Algorithm for P1: [1, 0, 2]
    cout << "\n---------------- Resource-Request Test ----------------\n";
    int req_proc = 1;
    vector<int> request = {1, 0, 2};
    cout << "Suppose process P" << req_proc << " requests: ["
         << request[0] << ", " << request[1] << ", " << request[2] << "]\n";

    // Step 1: Check if Request <= Need
    bool le_need = true;
    for (int j = 0; j < NUM_R; j++) {
        if (request[j] > need[req_proc][j]) le_need = false;
    }

    // Step 2: Check if Request <= Available
    bool le_avail = true;
    for (int j = 0; j < NUM_R; j++) {
        if (request[j] > avail[j]) le_avail = false;
    }

    if (!le_need) {
        cout << "Error: Process exceeded its maximum claim!\n";
    } else if (!le_avail) {
        cout << "Process must wait: Resources not currently available.\n";
    } else {
        // Pretend to allocate
        for (int j = 0; j < NUM_R; j++) {
            avail[j] -= request[j];
            alloc[req_proc][j] += request[j];
            need[req_proc][j] -= request[j];
        }

        vector<int> new_safe_seq;
        if (is_safe_state(alloc, need, avail, new_safe_seq)) {
            cout << "Request GRANTED immediately. Resulting state is SAFE.\n";
            cout << "Safe Sequence: ";
            for (size_t i = 0; i < new_safe_seq.size(); i++) {
                cout << "P" << new_safe_seq[i] << (i + 1 < new_safe_seq.size() ? " -> " : "\n");
            }
        } else {
            cout << "Request DENIED: Resulting state would be UNSAFE.\n";
        }
    }

    return 0;
}

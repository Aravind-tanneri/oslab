#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void first_fit(vector<int> block_sizes, const vector<int>& process_sizes) {
    int m = block_sizes.size();
    int n = process_sizes.size();
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (block_sizes[j] >= process_sizes[i]) {
                allocation[i] = j;
                block_sizes[j] -= process_sizes[i];
                break;
            }
        }
    }

    cout << "\n--- First-Fit Allocation ---\n";
    cout << left << setw(12) << "Process" << setw(15) << "Process Size" << setw(15) << "Block Allocated" << "\n";
    cout << "------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(12) << ("P" + to_string(i + 1)) << setw(15) << process_sizes[i];
        if (allocation[i] != -1) cout << setw(15) << ("Block " + to_string(allocation[i] + 1)) << "\n";
        else cout << setw(15) << "Not Allocated" << "\n";
    }
}

void best_fit(vector<int> block_sizes, const vector<int>& process_sizes) {
    int m = block_sizes.size();
    int n = process_sizes.size();
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        int best_idx = -1;
        for (int j = 0; j < m; j++) {
            if (block_sizes[j] >= process_sizes[i]) {
                if (best_idx == -1 || block_sizes[j] < block_sizes[best_idx]) {
                    best_idx = j;
                }
            }
        }
        if (best_idx != -1) {
            allocation[i] = best_idx;
            block_sizes[best_idx] -= process_sizes[i];
        }
    }

    cout << "\n--- Best-Fit Allocation ---\n";
    cout << left << setw(12) << "Process" << setw(15) << "Process Size" << setw(15) << "Block Allocated" << "\n";
    cout << "------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(12) << ("P" + to_string(i + 1)) << setw(15) << process_sizes[i];
        if (allocation[i] != -1) cout << setw(15) << ("Block " + to_string(allocation[i] + 1)) << "\n";
        else cout << setw(15) << "Not Allocated" << "\n";
    }
}

void worst_fit(vector<int> block_sizes, const vector<int>& process_sizes) {
    int m = block_sizes.size();
    int n = process_sizes.size();
    vector<int> allocation(n, -1);

    for (int i = 0; i < n; i++) {
        int worst_idx = -1;
        for (int j = 0; j < m; j++) {
            if (block_sizes[j] >= process_sizes[i]) {
                if (worst_idx == -1 || block_sizes[j] > block_sizes[worst_idx]) {
                    worst_idx = j;
                }
            }
        }
        if (worst_idx != -1) {
            allocation[i] = worst_idx;
            block_sizes[worst_idx] -= process_sizes[i];
        }
    }

    cout << "\n--- Worst-Fit Allocation ---\n";
    cout << left << setw(12) << "Process" << setw(15) << "Process Size" << setw(15) << "Block Allocated" << "\n";
    cout << "------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << left << setw(12) << ("P" + to_string(i + 1)) << setw(15) << process_sizes[i];
        if (allocation[i] != -1) cout << setw(15) << ("Block " + to_string(allocation[i] + 1)) << "\n";
        else cout << setw(15) << "Not Allocated" << "\n";
    }
}

int main() {
    cout << "========================================================\n";
    cout << " Lab 9: Memory Allocation (First-Fit, Best-Fit, Worst-Fit)\n";
    cout << "========================================================\n";

    vector<int> block_sizes = {100, 500, 200, 300, 600};
    vector<int> process_sizes = {212, 417, 112, 426};

    cout << "Default Blocks : {100, 500, 200, 300, 600}\n";
    cout << "Default Procs  : {212, 417, 112, 426}\n";

    first_fit(block_sizes, process_sizes);
    best_fit(block_sizes, process_sizes);
    worst_fit(block_sizes, process_sizes);

    return 0;
}

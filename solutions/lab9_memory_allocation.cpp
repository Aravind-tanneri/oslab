#include <iostream>
#include <vector>

using namespace std;

void allocate(string type, vector<int> blocks, const vector<int>& procs) {
    cout << "\n--- " << type << " ---\n";
    for (size_t i = 0; i < procs.size(); i++) {
        int best_idx = -1;
        for (size_t j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= procs[i]) {
                if (type == "First Fit") { best_idx = j; break; }
                if (type == "Best Fit") {
                    if (best_idx == -1 || blocks[j] < blocks[best_idx]) best_idx = j;
                }
                if (type == "Worst Fit") {
                    if (best_idx == -1 || blocks[j] > blocks[best_idx]) best_idx = j;
                }
            }
        }
        cout << "Process " << i + 1 << " (" << procs[i] << " KB) -> ";
        if (best_idx != -1) {
            cout << "Block " << best_idx + 1 << "\n";
            blocks[best_idx] -= procs[i];
        } else {
            cout << "Not Allocated\n";
        }
    }
}

int main() {
    vector<int> blocks = {100, 500, 200, 300, 600};
    vector<int> procs = {212, 417, 112, 426};

    allocate("First Fit", blocks, procs);
    allocate("Best Fit", blocks, procs);
    allocate("Worst Fit", blocks, procs);

    return 0;
}

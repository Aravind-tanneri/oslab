#include <iostream>
#include <vector>

using namespace std;

void fifo(const vector<int>& pages, int f) {
    vector<int> frames(f, -1);
    int faults = 0, ptr = 0;

    for (int p : pages) {
        bool hit = false;
        for (int x : frames) if (x == p) hit = true;
        if (!hit) {
            frames[ptr] = p;
            ptr = (ptr + 1) % f;
            faults++;
        }
    }
    cout << "FIFO:    Faults = " << faults << " | Hits = " << pages.size() - faults << "\n";
}

void optimal(const vector<int>& pages, int f) {
    vector<int> frames(f, -1);
    int faults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int p = pages[i];
        bool hit = false;
        for (int x : frames) if (x == p) hit = true;

        if (!hit) {
            faults++;
            int replace_idx = -1, farthest = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) { replace_idx = j; break; }
                int next_use = 1e9;
                for (size_t k = i + 1; k < pages.size(); k++) {
                    if (pages[k] == frames[j]) { next_use = k; break; }
                }
                if (next_use > farthest) {
                    farthest = next_use;
                    replace_idx = j;
                }
            }
            frames[replace_idx] = p;
        }
    }
    cout << "Optimal: Faults = " << faults << " | Hits = " << pages.size() - faults << "\n";
}

void lru(const vector<int>& pages, int f) {
    vector<int> frames(f, -1), last_used(f, -1);
    int faults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int p = pages[i];
        int hit_idx = -1;
        for (int j = 0; j < f; j++) {
            if (frames[j] == p) { hit_idx = j; break; }
        }

        if (hit_idx != -1) {
            last_used[hit_idx] = i;
        } else {
            faults++;
            int replace_idx = -1, lru_time = 1e9;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) { replace_idx = j; break; }
                if (last_used[j] < lru_time) {
                    lru_time = last_used[j];
                    replace_idx = j;
                }
            }
            frames[replace_idx] = p;
            last_used[replace_idx] = i;
        }
    }
    cout << "LRU:     Faults = " << faults << " | Hits = " << pages.size() - faults << "\n";
}

int main() {
    // Default reference string and frames from Lab 7
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frames = 3;

    cout << "Reference String: 7 0 1 2 0 3 0 4 2 3 0 3 2 (Frames = 3)\n\n";
    fifo(pages, frames);
    optimal(pages, frames);
    lru(pages, frames);

    return 0;
}

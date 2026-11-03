#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void print_table_header(int frames) {
    cout << left << setw(8) << "Page";
    for (int i = 1; i <= frames; i++) {
        cout << setw(10) << ("Frame " + to_string(i));
    }
    cout << setw(12) << "Hit/Fault" << "\n";
    cout << string(8 + frames * 10 + 12, '-') << "\n";
}

void print_row(int page, const vector<int>& fr, bool hit) {
    cout << left << setw(8) << page;
    for (int val : fr) {
        if (val == -1) cout << setw(10) << "-";
        else cout << setw(10) << val;
    }
    cout << setw(12) << (hit ? "Hit" : "Fault") << "\n";
}

int run_fifo(const vector<int>& pages, int num_frames) {
    cout << "\n================ Task 1: FIFO Page Replacement ================\n";
    print_table_header(num_frames);

    vector<int> frames(num_frames, -1);
    int pointer = 0;
    int faults = 0;

    for (int p : pages) {
        bool hit = false;
        for (int f : frames) {
            if (f == p) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            faults++;
            frames[pointer] = p;
            pointer = (pointer + 1) % num_frames;
        }

        print_row(p, frames, hit);
    }

    return faults;
}

int run_optimal(const vector<int>& pages, int num_frames) {
    cout << "\n================ Task 2: Optimal Page Replacement ================\n";
    print_table_header(num_frames);

    vector<int> frames(num_frames, -1);
    int faults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int p = pages[i];
        bool hit = false;
        for (int f : frames) {
            if (f == p) {
                hit = true;
                break;
            }
        }

        if (!hit) {
            faults++;
            // Check if there is an empty frame
            int replace_idx = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            // If no empty frame, find page used farthest in the future
            if (replace_idx == -1) {
                int farthest = -1;
                for (int j = 0; j < num_frames; j++) {
                    int next_use = 1e9;
                    for (size_t k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == frames[j]) {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        replace_idx = j;
                    }
                }
            }

            frames[replace_idx] = p;
        }

        print_row(p, frames, hit);
    }

    return faults;
}

int run_lru(const vector<int>& pages, int num_frames) {
    cout << "\n================ Task 3: LRU Page Replacement ================\n";
    print_table_header(num_frames);

    vector<int> frames(num_frames, -1);
    vector<int> last_used(num_frames, -1);
    int faults = 0;

    for (size_t i = 0; i < pages.size(); i++) {
        int p = pages[i];
        bool hit = false;
        int hit_idx = -1;

        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == p) {
                hit = true;
                hit_idx = j;
                break;
            }
        }

        if (hit) {
            last_used[hit_idx] = i;
        } else {
            faults++;
            int replace_idx = -1;
            // Empty frame?
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    replace_idx = j;
                    break;
                }
            }

            // Least recently used
            if (replace_idx == -1) {
                int min_time = 1e9;
                for (int j = 0; j < num_frames; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        replace_idx = j;
                    }
                }
            }

            frames[replace_idx] = p;
            last_used[replace_idx] = i;
        }

        print_row(p, frames, hit);
    }

    return faults;
}

int main() {
    cout << "=======================================================\n";
    cout << " Lab 7: Page Replacement Algorithms (FIFO, Optimal, LRU)\n";
    cout << "=======================================================\n";

    // Default reference string and frames from Lab 7 specification
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int num_frames = 3;

    cout << "Use default reference string (7 0 1 2 0 3 0 4 2 3 0 3 2) with 3 frames? (1=Yes, 0=Custom): ";
    int choice = 1;
    if (cin >> choice && choice == 0) {
        int n;
        cout << "Enter number of pages in reference string: ";
        cin >> n;
        pages.resize(n);
        cout << "Enter the reference string: ";
        for (int i = 0; i < n; i++) cin >> pages[i];
        cout << "Enter number of frames: ";
        cin >> num_frames;
    }

    int total_pages = pages.size();
    int fifo_faults = run_fifo(pages, num_frames);
    int opt_faults = run_optimal(pages, num_frames);
    int lru_faults = run_lru(pages, num_frames);

    cout << "\n================ Algorithm Comparison Summary ================\n";
    cout << left << setw(15) << "Algorithm" << setw(16) << "Page Faults" << setw(16) << "Page Hits" << "\n";
    cout << "-----------------------------------------------\n";
    cout << left << setw(15) << "FIFO" << setw(16) << fifo_faults << setw(16) << (total_pages - fifo_faults) << "\n";
    cout << left << setw(15) << "Optimal" << setw(16) << opt_faults << setw(16) << (total_pages - opt_faults) << "\n";
    cout << left << setw(15) << "LRU" << setw(16) << lru_faults << setw(16) << (total_pages - lru_faults) << "\n";

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt, rt;
};

void sjf_non_preemptive(vector<Process> p) {
    int n = p.size(), completed = 0, time = 0;
    vector<bool> done(n, false);
    double tot_tat = 0, tot_wt = 0;

    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        p[idx].rt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        done[idx] = true;
        completed++;
        tot_tat += p[idx].tat;
        tot_wt += p[idx].wt;
    }

    cout << "\n--- SJF (Non-Preemptive) ---\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &x : p) cout << "P" << x.id << "\t" << x.at << "\t" << x.bt << "\t" << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
    cout << "Avg TAT: " << tot_tat / n << " | Avg WT: " << tot_wt / n << "\n";
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    if (!(cin >> n) || n <= 0) return 0;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << " (AT & BT): ";
        cin >> p[i].at >> p[i].bt;
    }

    sjf_non_preemptive(p);
    return 0;
}

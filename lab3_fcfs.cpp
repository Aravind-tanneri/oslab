#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    if (!(cin >> n) || n <= 0) return 0;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << " (Arrival Time & Burst Time): ";
        cin >> p[i].at >> p[i].bt;
    }

    // Sort by arrival time
    sort(p.begin(), p.end(), [](Process a, Process b) { return a.at < b.at; });

    int current_time = 0;
    double total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) current_time = p[i].at;
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &x : p) {
        cout << "P" << x.id << "\t" << x.at << "\t" << x.bt << "\t"
             << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
    }

    cout << "\nGantt Chart:\n|";
    for (auto &x : p) cout << " P" << x.id << " |";
    cout << "\n0";
    for (auto &x : p) cout << "\t" << x.ct;

    cout << "\n\nAverage Turnaround Time = " << total_tat / n;
    cout << "\nAverage Waiting Time    = " << total_wt / n << "\n";

    return 0;
}

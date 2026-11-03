#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    string id;
    int at; // Arrival Time
    int bt; // Burst Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
};

int main() {
    int n;
    cout << "========================================\n";
    cout << " Lab 3: First-Come, First-Served (FCFS)\n";
    cout << "========================================\n";
    cout << "Enter number of processes (0 for default sample): ";
    if (!(cin >> n) || n <= 0) {
        // Use default sample
        cout << "Using sample processes (4 processes):\n";
        vector<Process> p = {
            {"P1", 0, 5, 0, 0, 0},
            {"P2", 1, 3, 0, 0, 0},
            {"P3", 2, 8, 0, 0, 0},
            {"P4", 3, 6, 0, 0, 0}
        };
        n = p.size();

        // Sort by arrival time
        sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
            return a.at < b.at;
        });

        vector<pair<string, int>> gantt;
        int current_time = 0;
        double total_wt = 0, total_tat = 0;

        for (int i = 0; i < n; i++) {
            if (current_time < p[i].at) {
                gantt.push_back({"Idle", p[i].at});
                current_time = p[i].at;
            }
            current_time += p[i].bt;
            p[i].ct = current_time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            total_wt += p[i].wt;
            total_tat += p[i].tat;
            gantt.push_back({p[i].id, current_time});
        }

        cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
        cout << "------------------------------------------\n";
        for (const auto& proc : p) {
            cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t"
                 << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\n";
        }

        cout << "\nGantt Chart:\n|";
        for (const auto& block : gantt) {
            cout << " " << block.first << " |";
        }
        cout << "\n0";
        for (const auto& block : gantt) {
            cout << setw(5) << block.second;
        }
        cout << "\n";

        cout << fixed << setprecision(2);
        cout << "\nAverage Turnaround Time = " << total_tat / n;
        cout << "\nAverage Waiting Time    = " << total_wt / n << "\n";
        return 0;
    }

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = "P" + to_string(i + 1);
        cout << "Enter Arrival Time and Burst Time for " << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt;
    }

    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
    });

    vector<pair<string, int>> gantt;
    int current_time = 0;
    double total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            gantt.push_back({"Idle", p[i].at});
            current_time = p[i].at;
        }
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        gantt.push_back({p[i].id, current_time});
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "------------------------------------------\n";
    for (const auto& proc : p) {
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\n";
    }

    cout << "\nGantt Chart:\n|";
    for (const auto& block : gantt) {
        cout << " " << block.first << " |";
    }
    cout << "\n0";
    for (const auto& block : gantt) {
        cout << setw(5) << block.second;
    }
    cout << "\n";

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time = " << total_tat / n;
    cout << "\nAverage Waiting Time    = " << total_wt / n << "\n";
    return 0;
}

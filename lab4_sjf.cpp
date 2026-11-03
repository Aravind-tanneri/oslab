#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    string id;
    int at;
    int bt;
    int remaining_bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int start_time;
    bool completed;
};

void run_sjf_non_preemptive(vector<Process> p) {
    int n = p.size();
    int completed_count = 0;
    int current_time = 0;
    int context_switches = 0;
    string last_process = "";
    vector<pair<string, int>> gantt;

    for (auto& proc : p) {
        proc.completed = false;
        proc.start_time = -1;
    }

    while (completed_count < n) {
        int idx = -1;
        int min_bt = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= current_time) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                } else if (p[i].bt == min_bt) {
                    // Tie-breaking: earlier AT, then smaller PID
                    if (p[i].at < p[idx].at || (p[i].at == p[idx].at && p[i].id < p[idx].id)) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // CPU Idle
            if (gantt.empty() || gantt.back().first != "Idle") {
                gantt.push_back({"Idle", current_time + 1});
            } else {
                gantt.back().second = current_time + 1;
            }
            current_time++;
        } else {
            if (last_process != "" && last_process != p[idx].id) {
                context_switches++;
            }
            last_process = p[idx].id;

            p[idx].start_time = current_time;
            p[idx].rt = p[idx].start_time - p[idx].at;
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = true;
            completed_count++;

            gantt.push_back({p[idx].id, current_time});
        }
    }

    cout << "\n--- Non-Preemptive SJF Results ---\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    cout << "---------------------------------------------------------\n";
    double avg_tat = 0, avg_wt = 0, avg_rt = 0;
    for (const auto& proc : p) {
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\t" << proc.rt << "\n";
        avg_tat += proc.tat;
        avg_wt += proc.wt;
        avg_rt += proc.rt;
    }

    cout << "\nGantt Chart:\n|";
    for (const auto& block : gantt) cout << " " << block.first << " |";
    cout << "\n0";
    for (const auto& block : gantt) cout << setw(5) << block.second;
    cout << "\n";

    cout << fixed << setprecision(2);
    cout << "Average TAT: " << avg_tat / n << ", Average WT: " << avg_wt / n
         << ", Average RT: " << avg_rt / n << "\n";
    cout << "Context Switches: " << context_switches << "\n";
}

void run_srtf_preemptive(vector<Process> p) {
    int n = p.size();
    for (auto& proc : p) {
        proc.remaining_bt = proc.bt;
        proc.start_time = -1;
        proc.completed = false;
    }

    int completed_count = 0;
    int current_time = 0;
    int context_switches = 0;
    string last_process = "";
    vector<pair<string, int>> gantt;

    while (completed_count < n) {
        int idx = -1;
        int min_rem = 1e9;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= current_time) {
                if (p[i].remaining_bt < min_rem) {
                    min_rem = p[i].remaining_bt;
                    idx = i;
                } else if (p[i].remaining_bt == min_rem) {
                    if (p[i].at < p[idx].at || (p[i].at == p[idx].at && p[i].id < p[idx].id)) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            if (gantt.empty() || gantt.back().first != "Idle") {
                gantt.push_back({"Idle", current_time + 1});
            } else {
                gantt.back().second = current_time + 1;
            }
            current_time++;
        } else {
            if (p[idx].start_time == -1) {
                p[idx].start_time = current_time;
                p[idx].rt = p[idx].start_time - p[idx].at;
            }

            if (last_process != "" && last_process != p[idx].id) {
                context_switches++;
            }
            last_process = p[idx].id;

            p[idx].remaining_bt--;
            current_time++;

            if (gantt.empty() || gantt.back().first != p[idx].id) {
                gantt.push_back({p[idx].id, current_time});
            } else {
                gantt.back().second = current_time;
            }

            if (p[idx].remaining_bt == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].completed = true;
                completed_count++;
            }
        }
    }

    cout << "\n--- Preemptive SJF (SRTF) Results ---\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    cout << "---------------------------------------------------------\n";
    double avg_tat = 0, avg_wt = 0, avg_rt = 0;
    for (const auto& proc : p) {
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\t" << proc.rt << "\n";
        avg_tat += proc.tat;
        avg_wt += proc.wt;
        avg_rt += proc.rt;
    }

    cout << "\nGantt Chart:\n|";
    for (const auto& block : gantt) cout << " " << block.first << " |";
    cout << "\n0";
    for (const auto& block : gantt) cout << setw(5) << block.second;
    cout << "\n";

    cout << fixed << setprecision(2);
    cout << "Average TAT: " << avg_tat / n << ", Average WT: " << avg_wt / n
         << ", Average RT: " << avg_rt / n << "\n";
    cout << "Context Switches: " << context_switches << "\n";
}

int main() {
    cout << "=============================================\n";
    cout << " Lab 4: SJF CPU Scheduling (Non-Preemptive & Preemptive/SRTF)\n";
    cout << "=============================================\n";

    int n;
    cout << "Enter number of processes (0 for sample): ";
    if (!(cin >> n) || n <= 0) {
        cout << "Using Sample Scenario (5 processes with different AT & BT):\n";
        vector<Process> sample = {
            {"P1", 0, 7, 7, 0, 0, 0, -1, -1, false},
            {"P2", 1, 4, 4, 0, 0, 0, -1, -1, false},
            {"P3", 2, 2, 2, 0, 0, 0, -1, -1, false},
            {"P4", 4, 5, 5, 0, 0, 0, -1, -1, false},
            {"P5", 5, 1, 1, 0, 0, 0, -1, -1, false}
        };
        run_sjf_non_preemptive(sample);
        run_srtf_preemptive(sample);
        return 0;
    }

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = "P" + to_string(i + 1);
        cout << "Enter Arrival Time and Burst Time for " << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].remaining_bt = p[i].bt;
        p[i].start_time = -1;
        p[i].completed = false;
    }

    run_sjf_non_preemptive(p);
    run_srtf_preemptive(p);
    return 0;
}

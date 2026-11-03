#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    string id;
    int at;
    int bt;
    int rem_bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int first_start;
};

struct Result {
    double avg_tat;
    double avg_wt;
    double avg_rt;
};

Result run_round_robin(vector<Process> p, int tq) {
    int n = p.size();
    for (auto& proc : p) {
        proc.rem_bt = proc.bt;
        proc.first_start = -1;
    }

    sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.at < b.at;
    });

    queue<int> q;
    vector<bool> in_queue(n, false);
    vector<pair<string, int>> gantt;

    int current_time = 0;
    int completed = 0;

    // Push initial processes
    for (int i = 0; i < n; i++) {
        if (p[i].at <= current_time) {
            q.push(i);
            in_queue[i] = true;
        }
    }

    while (completed < n) {
        if (q.empty()) {
            // Find next arriving process
            int next_at = 1e9;
            for (int i = 0; i < n; i++) {
                if (p[i].rem_bt > 0 && p[i].at < next_at) {
                    next_at = p[i].at;
                }
            }
            if (gantt.empty() || gantt.back().first != "Idle") {
                gantt.push_back({"Idle", next_at});
            } else {
                gantt.back().second = next_at;
            }
            current_time = next_at;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= current_time && !in_queue[i] && p[i].rem_bt > 0) {
                    q.push(i);
                    in_queue[i] = true;
                }
            }
        }

        int curr = q.front();
        q.pop();

        if (p[curr].first_start == -1) {
            p[curr].first_start = current_time;
            p[curr].rt = p[curr].first_start - p[curr].at;
        }

        int exec_time = min(tq, p[curr].rem_bt);
        current_time += exec_time;
        p[curr].rem_bt -= exec_time;
        gantt.push_back({p[curr].id, current_time});

        // Enqueue newly arrived processes during this time slice
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !in_queue[i] && p[i].rem_bt > 0) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        if (p[curr].rem_bt > 0) {
            q.push(curr);
        } else {
            p[curr].ct = current_time;
            p[curr].tat = p[curr].ct - p[curr].at;
            p[curr].wt = p[curr].tat - p[curr].bt;
            completed++;
        }
    }

    cout << "\n================ Part A: Round Robin (TQ = " << tq << ") ================\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    cout << "---------------------------------------------------------\n";
    double tot_tat = 0, tot_wt = 0, tot_rt = 0;
    for (const auto& proc : p) {
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\t" << proc.rt << "\n";
        tot_tat += proc.tat;
        tot_wt += proc.wt;
        tot_rt += proc.rt;
    }

    cout << "\nGantt Chart:\n|";
    for (const auto& b : gantt) cout << " " << b.first << " |";
    cout << "\n0";
    for (const auto& b : gantt) cout << setw(5) << b.second;
    cout << "\n";

    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time  = " << tot_tat / n << "\n";
    cout << "Average Waiting Time     = " << tot_wt / n << "\n";
    cout << "Average Response Time    = " << tot_rt / n << "\n";

    return {tot_tat / n, tot_wt / n, tot_rt / n};
}

Result run_strf(vector<Process> p) {
    int n = p.size();
    for (auto& proc : p) {
        proc.rem_bt = proc.bt;
        proc.first_start = -1;
    }

    int completed = 0, current_time = 0;
    vector<pair<string, int>> gantt;

    while (completed < n) {
        int idx = -1;
        int min_rem = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rem_bt > 0) {
                if (p[i].rem_bt < min_rem) {
                    min_rem = p[i].rem_bt;
                    idx = i;
                } else if (p[i].rem_bt == min_rem) {
                    if (p[i].at < p[idx].at || (p[i].at == p[idx].at && p[i].id < p[idx].id)) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            if (gantt.empty() || gantt.back().first != "Idle") gantt.push_back({"Idle", current_time + 1});
            else gantt.back().second = current_time + 1;
            current_time++;
        } else {
            if (p[idx].first_start == -1) {
                p[idx].first_start = current_time;
                p[idx].rt = p[idx].first_start - p[idx].at;
            }

            p[idx].rem_bt--;
            current_time++;

            if (gantt.empty() || gantt.back().first != p[idx].id) {
                gantt.push_back({p[idx].id, current_time});
            } else {
                gantt.back().second = current_time;
            }

            if (p[idx].rem_bt == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
    }

    cout << "\n================ Part B: Shortest Time Remaining First (STRF) ================\n";
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    cout << "---------------------------------------------------------\n";
    double tot_tat = 0, tot_wt = 0, tot_rt = 0;
    for (const auto& proc : p) {
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.ct << "\t" << proc.tat << "\t" << proc.wt << "\t" << proc.rt << "\n";
        tot_tat += proc.tat;
        tot_wt += proc.wt;
        tot_rt += proc.rt;
    }

    cout << "\nGantt Chart:\n|";
    for (const auto& b : gantt) cout << " " << b.first << " |";
    cout << "\n0";
    for (const auto& b : gantt) cout << setw(5) << b.second;
    cout << "\n";

    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time  = " << tot_tat / n << "\n";
    cout << "Average Waiting Time     = " << tot_wt / n << "\n";
    cout << "Average Response Time    = " << tot_rt / n << "\n";

    return {tot_tat / n, tot_wt / n, tot_rt / n};
}

int main() {
    cout << "========================================================\n";
    cout << " Lab 5: Round Robin (RR) and STRF Scheduling Comparison\n";
    cout << "========================================================\n";

    int n;
    cout << "Enter number of processes (0 for default sample): ";
    if (!(cin >> n) || n <= 0) {
        cout << "Using sample dataset from Lab 5 specification:\n";
        vector<Process> p = {
            {"P1", 0, 5, 5, 0, 0, 0, 0, -1},
            {"P2", 1, 4, 4, 0, 0, 0, 0, -1},
            {"P3", 2, 2, 2, 0, 0, 0, 0, -1},
            {"P4", 4, 3, 3, 0, 0, 0, 0, -1}
        };
        int tq = 2;

        Result r_rr = run_round_robin(p, tq);
        Result r_strf = run_strf(p);

        cout << "\n================ Task 3 & 4: Comparison ================\n";
        cout << left << setw(12) << "Algorithm" << setw(16) << "Avg WT" << setw(16) << "Avg TAT" << setw(16) << "Avg RT" << "\n";
        cout << "--------------------------------------------------------\n";
        cout << left << setw(12) << "RR (TQ=2)" << setw(16) << r_rr.avg_wt << setw(16) << r_rr.avg_tat << setw(16) << r_rr.avg_rt << "\n";
        cout << left << setw(12) << "STRF" << setw(16) << r_strf.avg_wt << setw(16) << r_strf.avg_tat << setw(16) << r_strf.avg_rt << "\n";

        cout << "\nObservations:\n";
        cout << "- Lower Average Waiting Time:    " << (r_strf.avg_wt < r_rr.avg_wt ? "STRF" : "RR") << "\n";
        cout << "- Lower Average Turnaround Time: " << (r_strf.avg_tat < r_rr.avg_tat ? "STRF" : "RR") << "\n";
        cout << "- Lower Response Time:           " << (r_strf.avg_rt < r_rr.avg_rt ? "STRF" : "RR") << "\n";
        return 0;
    }

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = "P" + to_string(i + 1);
        cout << "Enter AT and BT for " << p[i].id << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].rem_bt = p[i].bt;
        p[i].first_start = -1;
    }

    int tq;
    cout << "Enter Time Quantum for Round Robin: ";
    cin >> tq;

    Result r_rr = run_round_robin(p, tq);
    Result r_strf = run_strf(p);

    cout << "\n================ Task 3 & 4: Comparison ================\n";
    cout << left << setw(12) << "Algorithm" << setw(16) << "Avg WT" << setw(16) << "Avg TAT" << setw(16) << "Avg RT" << "\n";
    cout << "--------------------------------------------------------\n";
    cout << left << setw(12) << "Round Robin" << setw(16) << r_rr.avg_wt << setw(16) << r_rr.avg_tat << setw(16) << r_rr.avg_rt << "\n";
    cout << left << setw(12) << "STRF" << setw(16) << r_strf.avg_wt << setw(16) << r_strf.avg_tat << setw(16) << r_strf.avg_rt << "\n";
    return 0;
}

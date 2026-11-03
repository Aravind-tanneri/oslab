#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id, at, bt, rem_bt, ct, tat, wt, rt;
};

void round_robin(vector<Process> p, int tq) {
    int n = p.size(), time = 0, completed = 0;
    for (auto &x : p) { x.rem_bt = x.bt; x.rt = -1; }

    queue<int> q;
    vector<bool> in_q(n, false);

    // Push initial processes
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && !in_q[i]) { q.push(i); in_q[i] = true; }
    }

    while (completed < n) {
        if (q.empty()) {
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !in_q[i] && p[i].rem_bt > 0) {
                    q.push(i); in_q[i] = true;
                }
            }
            continue;
        }

        int curr = q.front();
        q.pop();

        if (p[curr].rt == -1) p[curr].rt = time - p[curr].at;

        int run_time = min(tq, p[curr].rem_bt);
        time += run_time;
        p[curr].rem_bt -= run_time;

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !in_q[i] && p[i].rem_bt > 0) {
                q.push(i); in_q[i] = true;
            }
        }

        if (p[curr].rem_bt > 0) {
            q.push(curr);
        } else {
            p[curr].ct = time;
            p[curr].tat = p[curr].ct - p[curr].at;
            p[curr].wt = p[curr].tat - p[curr].bt;
            completed++;
        }
    }

    double tot_tat = 0, tot_wt = 0;
    cout << "\n--- Round Robin (TQ=" << tq << ") ---\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &x : p) {
        cout << "P" << x.id << "\t" << x.at << "\t" << x.bt << "\t" << x.ct << "\t" << x.tat << "\t" << x.wt << "\n";
        tot_tat += x.tat;
        tot_wt += x.wt;
    }
    cout << "Avg TAT: " << tot_tat / n << " | Avg WT: " << tot_wt / n << "\n";
}

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    if (!(cin >> n) || n <= 0) return 0;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "P" << p[i].id << " (AT & BT): ";
        cin >> p[i].at >> p[i].bt;
    }
    cout << "Enter Time Quantum: ";
    cin >> tq;

    round_robin(p, tq);
    return 0;
}

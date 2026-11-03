#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void run_fcfs(vector<int> req, int head) {
    int total_seek = 0;
    int curr = head;
    cout << "\n--- FCFS Disk Scheduling ---\nSeek Sequence: " << curr;
    for (int r : req) {
        total_seek += abs(r - curr);
        curr = r;
        cout << " -> " << curr;
    }
    cout << "\nTotal Head Movement = " << total_seek << " cylinders\n";
}

void run_sstf(vector<int> req, int head) {
    int total_seek = 0;
    int curr = head;
    int n = req.size();
    vector<bool> visited(n, false);

    cout << "\n--- SSTF Disk Scheduling ---\nSeek Sequence: " << curr;
    for (int i = 0; i < n; i++) {
        int min_dist = 1e9;
        int next_idx = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && abs(req[j] - curr) < min_dist) {
                min_dist = abs(req[j] - curr);
                next_idx = j;
            }
        }
        visited[next_idx] = true;
        total_seek += min_dist;
        curr = req[next_idx];
        cout << " -> " << curr;
    }
    cout << "\nTotal Head Movement = " << total_seek << " cylinders\n";
}

void run_scan(vector<int> req, int head, int disk_size = 200) {
    int total_seek = 0;
    int curr = head;
    vector<int> left, right;

    for (int r : req) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    // Scan moving towards high end
    right.push_back(disk_size - 1);
    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end());

    cout << "\n--- SCAN Disk Scheduling (Moving High) ---\nSeek Sequence: " << curr;
    for (int r : right) {
        total_seek += abs(r - curr);
        curr = r;
        cout << " -> " << curr;
    }
    for (int r : left) {
        total_seek += abs(r - curr);
        curr = r;
        cout << " -> " << curr;
    }
    cout << "\nTotal Head Movement = " << total_seek << " cylinders\n";
}

int main() {
    cout << "=============================================\n";
    cout << " Lab 10: Disk Scheduling (FCFS, SSTF, SCAN)\n";
    cout << "=============================================\n";

    vector<int> req = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;

    cout << "Default Initial Head Position: " << head << "\n";
    cout << "Default Request Queue: {98, 183, 37, 122, 14, 124, 65, 67}\n";

    run_fcfs(req, head);
    run_sstf(req, head);
    run_scan(req, head);

    return 0;
}

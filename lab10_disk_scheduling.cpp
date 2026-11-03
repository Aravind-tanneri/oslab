#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void fcfs(vector<int> req, int head) {
    int seek = 0, curr = head;
    for (int r : req) { seek += abs(r - curr); curr = r; }
    cout << "FCFS Total Head Movement: " << seek << " cylinders\n";
}

void sstf(vector<int> req, int head) {
    int seek = 0, curr = head, n = req.size();
    vector<bool> done(n, false);

    for (int i = 0; i < n; i++) {
        int min_d = 1e9, idx = -1;
        for (int j = 0; j < n; j++) {
            if (!done[j] && abs(req[j] - curr) < min_d) {
                min_d = abs(req[j] - curr);
                idx = j;
            }
        }
        done[idx] = true;
        seek += min_d;
        curr = req[idx];
    }
    cout << "SSTF Total Head Movement: " << seek << " cylinders\n";
}

void scan(vector<int> req, int head, int disk_size = 200) {
    int seek = 0, curr = head;
    vector<int> left, right;
    for (int r : req) (r < head ? left : right).push_back(r);

    right.push_back(disk_size - 1);
    sort(right.begin(), right.end());
    sort(left.begin(), left.end(), greater<int>());

    for (int r : right) { seek += abs(r - curr); curr = r; }
    for (int r : left)  { seek += abs(r - curr); curr = r; }

    cout << "SCAN Total Head Movement: " << seek << " cylinders\n";
}

int main() {
    vector<int> req = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53;

    cout << "Initial Head: " << head << "\n";
    fcfs(req, head);
    sstf(req, head);
    scan(req, head);

    return 0;
}

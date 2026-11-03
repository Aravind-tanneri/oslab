#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex R1, R2;

// Deadlock Prevention: Both processes acquire resources in strict global order: R1 < R2
void process_task(string name) {
    cout << name << " requests R1: Granted\n";
    lock_guard<mutex> lock1(R1);

    cout << name << " requests R2: Granted\n";
    lock_guard<mutex> lock2(R2);

    cout << name << " releases R2 and R1\n";
}

int main() {
    cout << "Resource ordering: R1 < R2\n";

    thread p1(process_task, "P1");
    thread p2(process_task, "P2");

    p1.join();
    p2.join();

    cout << "Deadlock prevention using resource ordering completed successfully.\n";
    return 0;
}

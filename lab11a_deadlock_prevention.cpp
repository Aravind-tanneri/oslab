#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// Two resources represented as mutexes
mutex R1;
mutex R2;

// Deadlock Prevention function using strict global resource ordering: R1 < R2
void process_with_ordering(string proc_name) {
    cout << proc_name << " requests R1: Granted\n";
    lock_guard<mutex> lock1(R1);
    this_thread::sleep_for(chrono::milliseconds(50));

    cout << proc_name << " requests R2: Granted\n";
    lock_guard<mutex> lock2(R2);
    this_thread::sleep_for(chrono::milliseconds(50));

    cout << proc_name << " releases R2 and R1\n";
}

int main() {
    cout << "=======================================================\n";
    cout << " Lab 11a: Deadlock Prevention using Resource Ordering\n";
    cout << "=======================================================\n";

    cout << "\n[Background]: Deadlock requires 4 conditions:\n";
    cout << "1. Mutual Exclusion  2. Hold and Wait  3. No Preemption  4. Circular Wait\n";
    cout << "Strategy: Eliminate 'Circular Wait' by enforcing global ordering R1 < R2.\n";

    cout << "\nResource ordering: R1 < R2\n";

    // Both processes request resources in strict ascending order (R1 then R2)
    thread t1(process_with_ordering, "P1");
    thread t2(process_with_ordering, "P2");

    t1.join();
    t2.join();

    cout << "Deadlock prevention using resource ordering completed successfully.\n";
    return 0;
}

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

const int BUFFER_CAPACITY = 5;
const int TOTAL_ITEMS = 10;

vector<int> buffer;
mutex mtx;                 // Equivalent to binary semaphore 'mutex'
condition_variable cv_empty; // Signals when buffer has space (empty semaphore)
condition_variable cv_full;  // Signals when buffer has items (full semaphore)

void print_buffer() {
    cout << " [";
    for (size_t i = 0; i < buffer.size(); i++) {
        cout << buffer[i] << (i + 1 < buffer.size() ? ", " : "");
    }
    cout << "]\n";
}

void producer() {
    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        unique_lock<mutex> lock(mtx);

        // wait(empty): Wait until buffer is not full
        cv_empty.wait(lock, []() {
            return buffer.size() < BUFFER_CAPACITY;
        });

        // wait(mutex) acquired via unique_lock
        buffer.push_back(i);
        cout << "Produced: " << i << " | Buffer:";
        print_buffer();

        // signal(mutex) releases on unlock
        lock.unlock();

        // signal(full): Notify consumer that an item is available
        cv_full.notify_one();

        this_thread::sleep_for(chrono::milliseconds(40));
    }
}

void consumer() {
    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        unique_lock<mutex> lock(mtx);

        // wait(full): Wait until buffer has at least one item
        cv_full.wait(lock, []() {
            return !buffer.empty();
        });

        // wait(mutex) acquired via unique_lock
        int item = buffer.front();
        buffer.erase(buffer.begin());
        cout << "Consumed: " << item << " | Buffer:";
        print_buffer();

        // signal(mutex) releases on unlock
        lock.unlock();

        // signal(empty): Notify producer that a slot is free
        cv_empty.notify_one();

        this_thread::sleep_for(chrono::milliseconds(60));
    }
}

int main() {
    cout << "========================================================\n";
    cout << " Lab 11c: Producer-Consumer Synchronization (Bounded Buffer)\n";
    cout << "========================================================\n";
    cout << "Buffer Capacity: " << BUFFER_CAPACITY << "\n";
    cout << "Total Items to Produce/Consume: " << TOTAL_ITEMS << "\n\n";

    thread prod(producer);
    thread cons(consumer);

    prod.join();
    cons.join();

    cout << "\nProducer-Consumer execution completed successfully.\n";
    return 0;
}

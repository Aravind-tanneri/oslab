#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int CAPACITY = 5;
vector<int> buffer;
mutex mtx;
condition_variable cv_empty, cv_full;

void producer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(mtx);
        cv_empty.wait(lock, []() { return buffer.size() < CAPACITY; });

        buffer.push_back(i);
        cout << "Produced: " << i << " | Buffer size: " << buffer.size() << "\n";

        lock.unlock();
        cv_full.notify_one();
    }
}

void consumer() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(mtx);
        cv_full.wait(lock, []() { return !buffer.empty(); });

        int item = buffer.front();
        buffer.erase(buffer.begin());
        cout << "Consumed: " << item << " | Buffer size: " << buffer.size() << "\n";

        lock.unlock();
        cv_empty.notify_one();
    }
}

int main() {
    thread p(producer);
    thread c(consumer);

    p.join();
    c.join();

    cout << "Producer-Consumer finished.\n";
    return 0;
}

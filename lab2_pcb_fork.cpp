#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    cout << "Parent Process PID: " << getpid() << "\n";

    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed!\n";
        return 1;
    } 
    else if (pid == 0) {
        // Child Process
        cout << "[Child] PID: " << getpid() << " | Parent PID: " << getppid() << "\n";
        cout << "[Child] Running active work...\n";
        sleep(2);

        cout << "[Child] Sleeping for 15s. Check: cat /proc/" << getpid() << "/status\n";
        sleep(15);

        cout << "[Child] Resumed and terminating.\n";
        _exit(0);
    } 
    else {
        // Parent Process
        cout << "[Parent] Created child with PID: " << pid << "\n";
        cout << "[Parent] Waiting for child to terminate...\n";
        wait(NULL);
        cout << "[Parent] Child completed. Exiting.\n";
    }

    return 0;
}

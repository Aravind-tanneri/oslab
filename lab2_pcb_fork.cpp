#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

using namespace std;

#ifndef _WIN32
void display_proc_status(pid_t pid) {
    string path = "/proc/" + to_string(pid) + "/status";
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Could not open " << path << "\n";
        return;
    }
    cout << "\n--- PCB (/proc/" << pid << "/status key fields) ---\n";
    string line;
    while (getline(file, line)) {
        if (line.rfind("Name:", 0) == 0 ||
            line.rfind("State:", 0) == 0 ||
            line.rfind("Tgid:", 0) == 0 ||
            line.rfind("Pid:", 0) == 0 ||
            line.rfind("PPid:", 0) == 0 ||
            line.rfind("voluntary_ctxt_switches:", 0) == 0 ||
            line.rfind("nonvoluntary_ctxt_switches:", 0) == 0) {
            cout << "  " << line << "\n";
        }
    }
}
#endif

int main() {
    cout << "=====================================================\n";
    cout << " Lab 2: Process Creation & PCB (/proc) Investigation\n";
    cout << "=====================================================\n";

#ifndef _WIN32
    cout << "Parent PID: " << getpid() << "\n";
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child Process
        cout << "\n[Child] Created with PID: " << getpid() << " (Parent: " << getppid() << ")\n";
        cout << "[Child] Running active work for 2 seconds...\n";
        sleep(2);

        cout << "[Child] Going to sleep for 5 seconds (State: Sleeping/Interruptible)...\n";
        sleep(5);

        cout << "[Child] Resumed execution and now terminating.\n";
        _exit(0);
    } else {
        // Parent Process
        cout << "[Parent] Spawned Child with PID: " << pid << "\n";
        sleep(1);
        cout << "\n[Parent] Inspecting Child's PCB while running:";
        display_proc_status(pid);

        cout << "\n[Parent] Waiting for Child to complete...\n";
        wait(NULL);
        cout << "[Parent] Child process has terminated and cleaned up.\n";
    }
#else
    cout << "Process ID: " << GetCurrentProcessId() << "\n";
    cout << "Note: Run this file on Ubuntu/WSL to inspect fork() and /proc/<PID>/status.\n";
#endif

    return 0;
}

#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#endif

using namespace std;

int main() {
    cout << "========================================\n";
    cout << " Lab 1: Process Management & Monitoring\n";
    cout << "========================================\n";

#ifndef _WIN32
    pid_t pid = getpid();
    pid_t ppid = getppid();
    cout << "[Category 1] Current PID: " << pid << ", Parent PID: " << ppid << "\n";

    // Category 5: Priority
    int prio = getpriority(PRIO_PROCESS, 0);
    cout << "[Category 5] Current Process Nice Value: " << prio << "\n";
    nice(2);
    cout << "[Category 5] Modified Process Nice Value (+2): " << getpriority(PRIO_PROCESS, 0) << "\n";

    // Category 2, 3 & 4: Process Creation, Background execution & Termination
    cout << "\n[Category 2 & 3] Forking child process...\n";
    pid_t cpid = fork();
    if (cpid == 0) {
        cout << "  -> Child running in background. Child PID: " << getpid() << ", PPID: " << getppid() << "\n";
        sleep(1);
        cout << "  -> Child work finished. Exiting.\n";
        _exit(0);
    } else if (cpid > 0) {
        cout << "  -> Parent waiting for child PID " << cpid << " to terminate...\n";
        int status;
        waitpid(cpid, &status, 0);
        cout << "[Category 4] Child process successfully terminated and reaped.\n";
    }
#else
    cout << "Current PID: " << GetCurrentProcessId() << "\n";
    cout << "Priority Class: " << GetPriorityClass(GetCurrentProcess()) << "\n";
    cout << "Note: Run on Linux/Ubuntu to test fork(), getpriority(), and /proc details.\n";
#endif

    cout << "\nCommon Ubuntu Process Commands:\n";
    cout << "  ps aux               : View all running processes\n";
    cout << "  top / htop           : Real-time resource monitor\n";
    cout << "  pstree               : Display process hierarchy tree\n";
    cout << "  kill <PID>           : Terminate a process\n";
    cout << "  kill -9 <PID>        : Forcefully kill a process\n";
    cout << "  nice -n 10 ./prog    : Run with modified priority\n";
    cout << "  renice 5 -p <PID>    : Change priority of running process\n";
    return 0;
}

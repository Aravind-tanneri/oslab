# Lab Task 1: Process Management in Ubuntu

A comprehensive reference for process monitoring, creation, background execution, termination, and priority management commands.

---

## Category 1: Process Monitoring and Information Commands

* **`ps`**: Displays processes running in the current shell session.
* **`ps aux`**: Lists all active processes across the entire system with details (User, PID, %CPU, %MEM, VSZ, RSS, TTY, STAT, START, TIME, COMMAND).
* **`ps -ef`**: Standard Unix format listing all running processes, explicitly showing parent-child relationships via `PID` and `PPID`.
* **`top`**: Dynamic real-time monitoring tool showing system load, memory usage, and processes sorted by CPU consumption.
* **`htop`**: Enhanced interactive process viewer with colored visual bars for core/memory utilization.
* **`pstree`**: Visualizes running processes as a hierarchical tree structure starting from `systemd` (PID 1).
* **`pstree -p`**: Displays the process tree along with corresponding PIDs.

---

## Category 2: Process Creation and Execution Commands

* **`<command> &`**: Launches a process directly in the background (e.g., `sleep 60 &`), leaving the terminal free for further input.
* **`nohup <command> &`**: Runs an immune-to-hangups process in the background. It persists and continues executing even if the terminal session is closed or disconnected.
* **`pidof <program_name>`**: Returns the Process ID (PID) of an active application (e.g., `pidof bash`, `pidof chrome`).
* **`pgrep <pattern>`**: Searches for running processes matching the name or pattern and prints their PIDs.
* **`pgrep -l <pattern>`**: Lists both PIDs and names of matching processes.

---

## Category 3: Foreground and Background Process Management

* **`Ctrl + Z`**: Sends `SIGTSTP` to pause/suspend the current foreground process without terminating it.
* **`jobs`**: Lists all active, paused, and background jobs managed by the current shell, along with their Job IDs (`[1]`, `[2]`, etc.).
* **`jobs -l`**: Lists background and suspended jobs with their operating system PIDs.
* **`bg %<job_id>`**: Resumes a suspended job and allows it to run in the background (e.g., `bg %1`).
* **`fg %<job_id>`**: Brings a background or suspended job back to the foreground (e.g., `fg %1`).
* **`Ctrl + C`**: Sends `SIGINT` to gracefully terminate the current foreground process.

---

## Category 4: Process Termination Commands

* **`kill <PID>`**: Sends the default `SIGTERM` (Signal 15), requesting the process to clean up resources and terminate gracefully.
* **`kill -9 <PID>`**: Sends `SIGKILL` (Signal 9), forcefully and unconditionally terminating the process immediately.
* **`killall <process_name>`**: Kills all processes running under the specified command name (e.g., `killall python3`).
* **`pkill <pattern>`**: Terminates processes matching a specified regex or partial name (e.g., `pkill -9 sleep`).
* **`ps -p <PID>`**: Verifies whether a terminated process has been successfully removed from the process table.

---

## Category 5: Process Priority Management Commands

In Linux, process niceness ranges from **`-20`** (highest priority) to **`+19`** (lowest priority). Default nice value is `0`.

* **`ps -l`** or **`ps -o pid,ni,comm`**: Inspects the current nice level (`NI` column) of running processes.
* **`nice -n <val> <command>`**: Runs a new command with a modified priority (e.g., `nice -n 10 ./my_task`).
  > *Note: Only root/sudo can assign negative (higher priority) nice values (e.g., `sudo nice -n -5 ./critical_task`).*
* **`renice <val> -p <PID>`**: Alters the nice value of an existing running process dynamically (e.g., `renice 5 -p 1234`).
* **`renice -u <username>`**: Changes the priority of all processes owned by a specific user.

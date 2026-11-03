# OS Lab Tasks - Sample Inputs and Outputs

This document provides the standard sample inputs and corresponding expected outputs for all lab experiments (Lab 1 to Lab 11).

---

## Lab 1: Process Management & Monitoring
*File: [`lab1_process_management.md`](./lab1_process_management.md)*

### Sample Commands & Expected Terminal Outputs

#### 1. Process Monitoring (`ps -ef | head -5`)
```text
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 08:00 ?        00:00:01 /sbin/init
root           2       0  0 08:00 ?        00:00:00 [kthreadd]
root           3       2  0 08:00 ?        00:00:00 [rcu_gp]
user        1240    1230  0 08:15 pts/0    00:00:00 bash
```

#### 2. Process Tree Hierarchy (`pstree -p $$`)
```text
bash(1240)───pstree(1820)
```

#### 3. Background Job Control
```bash
$ sleep 60 &
[1] 1950

$ jobs -l
[1]+  1950 Running                 sleep 60 &

$ kill 1950
[1]+  Terminated              sleep 60
```

#### 4. Priority Management
```bash
$ nice -n 10 ./my_prog &
[1] 2045

$ ps -o pid,ni,comm -p 2045
    PID  NI COMMAND
   2045  10 my_prog

$ renice 15 -p 2045
2045 (process ID) old priority 10, new priority 15
```

---

## Lab 2: Process Creation and PCB Investigation
*File: [`lab2_pcb_fork.cpp`](./lab2_pcb_fork.cpp)*

### Execution & Output
```text
Parent Process PID: 2410
[Parent] Created child with PID: 2411
[Parent] Waiting for child to terminate...
[Child] PID: 2411 | Parent PID: 2410
[Child] Running active work...
[Child] Sleeping for 15s. Check: cat /proc/2411/status
```

#### Checking PCB via `/proc/2411/status` (in another terminal):
```text
Name:   a.out
State:  S (sleeping)
Tgid:   2411
Pid:    2411
PPid:   2410
Threads: 1
voluntary_ctxt_switches:    2
nonvoluntary_ctxt_switches: 0
```

#### Resuming and Cleanup:
```text
[Child] Resumed and terminating.
[Parent] Child completed. Exiting.
```

---

## Lab 3: First-Come, First-Served (FCFS) CPU Scheduling
*File: [`lab3_fcfs.cpp`](./lab3_fcfs.cpp)*

### Sample Input
```text
Enter number of processes: 4
P1 (Arrival Time & Burst Time): 0 5
P2 (Arrival Time & Burst Time): 1 3
P3 (Arrival Time & Burst Time): 2 8
P4 (Arrival Time & Burst Time): 3 6
```

### Expected Output
```text
PID     AT      BT      CT      TAT     WT
P1      0       5       5       5       0
P2      1       3       8       7       4
P3      2       8       16      14      6
P4      3       6       22      19      13

Gantt Chart:
| P1 | P2 | P3 | P4 |
0       5       8       16      22

Average Turnaround Time = 11.25
Average Waiting Time    = 5.75
```

---

## Lab 4: Shortest Job First (SJF) Scheduling (Non-Preemptive)
*File: [`lab4_sjf.cpp`](./lab4_sjf.cpp)*

### Sample Input
```text
Enter number of processes: 4
P1 (AT & BT): 0 8
P2 (AT & BT): 1 4
P3 (AT & BT): 2 2
P4 (AT & BT): 3 1
```

### Expected Output
```text
--- SJF (Non-Preemptive) ---
PID     AT      BT      CT      TAT     WT
P1      0       8       8       8       0
P2      1       4       15      14      10
P3      2       2       11      9       7
P4      3       1       9       6       5
Avg TAT: 9.25 | Avg WT: 5.5
```

---

## Lab 5: Round Robin (RR) and SRTF Comparison
*File: [`lab5_rr_srtf.cpp`](./lab5_rr_srtf.cpp)*

### Sample Input
```text
Enter number of processes: 4
P1 (AT & BT): 0 5
P2 (AT & BT): 1 4
P3 (AT & BT): 2 2
P4 (AT & BT): 4 3
Enter Time Quantum: 2
```

### Expected Output
```text
--- Round Robin (TQ=2) ---
PID     AT      BT      CT      TAT     WT
P1      0       5       14      14      9
P2      1       4       10      9       5
P3      2       2       6       4       2
P4      4       3       13      9       6
Avg TAT: 9.00 | Avg WT: 5.50
```

---

## Lab 6: Inter-Process Communication (IPC) Using Message Queues
*File: [`lab6_ipc_message_queue.cpp`](./lab6_ipc_message_queue.cpp)*

### Execution & Expected Output
```text
[Sender/Parent] Sending Message: "Hello from Sender via Message Queue!"
[Receiver/Child] Received Message: "Hello from Sender via Message Queue!"
[Sender/Parent] Message queue destroyed successfully.
```

---

## Lab 7: Page Replacement Algorithms
*File: [`lab7_page_replacement.cpp`](./lab7_page_replacement.cpp)*

### Input
* **Reference String:** `7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2`
* **Frames:** `3`

### Expected Output
```text
Reference String: 7 0 1 2 0 3 0 4 2 3 0 3 2 (Frames = 3)

FIFO:    Faults = 10 | Hits = 3
Optimal: Faults = 7  | Hits = 6
LRU:     Faults = 9  | Hits = 4
```

---

## Lab 8: Address Translation Using Paging
*File: [`lab8_paging_address_translation.cpp`](./lab8_paging_address_translation.cpp)*

### Input
* **Page Size:** `100 bytes`
* **Page Table Mapping:**
  * Page `0` $\rightarrow$ Frame `3`
  * Page `1` $\rightarrow$ Frame `0`
  * Page `2` $\rightarrow$ Frame `4`
  * Page `3` $\rightarrow$ Frame `1`
  * Page `4` $\rightarrow$ Frame `2`
* **Logical Addresses to Translate:** `50, 120, 250, 315, 425`

### Expected Output
```text
=== Lab 8: Address Translation Using Paging ===
Page Size = 100 bytes

Logical Page    Offset  Frame   Physical Address
------------------------------------------------
50      0       50      3       350
120     1       20      0       20
250     2       50      4       450
315     3       15      1       115
425     4       25      2       225
```

---

## Lab 9: Memory Allocation (First-Fit, Best-Fit, Worst-Fit)
*File: [`lab9_memory_allocation.cpp`](./lab9_memory_allocation.cpp)*

### Input
* **Memory Blocks:** `100 KB, 500 KB, 200 KB, 300 KB, 600 KB`
* **Processes:** `P1 (212 KB), P2 (417 KB), P3 (112 KB), P4 (426 KB)`

### Expected Output
```text
--- First Fit ---
Process 1 (212 KB) -> Block 2
Process 2 (417 KB) -> Block 5
Process 3 (112 KB) -> Block 2
Process 4 (426 KB) -> Not Allocated

--- Best Fit ---
Process 1 (212 KB) -> Block 4
Process 2 (417 KB) -> Block 2
Process 3 (112 KB) -> Block 3
Process 4 (426 KB) -> Block 5

--- Worst Fit ---
Process 1 (212 KB) -> Block 5
Process 2 (417 KB) -> Block 2
Process 3 (112 KB) -> Block 5
Process 4 (426 KB) -> Not Allocated
```

---

## Lab 10: Disk Scheduling (FCFS, SSTF, SCAN)
*File: [`lab10_disk_scheduling.cpp`](./lab10_disk_scheduling.cpp)*

### Input
* **Request Queue:** `98, 183, 37, 122, 14, 124, 65, 67`
* **Initial Head Position:** `53` (Disk range `0 - 199`)

### Expected Output
```text
Initial Head: 53
FCFS Total Head Movement: 640 cylinders
SSTF Total Head Movement: 236 cylinders
SCAN Total Head Movement: 331 cylinders
```

---

## Lab 11a: Deadlock Prevention
*File: [`lab11a_deadlock_prevention.cpp`](./lab11a_deadlock_prevention.cpp)*

### Expected Output
```text
Resource ordering: R1 < R2
P1 requests R1: Granted
P1 requests R2: Granted
P1 releases R2 and R1
P2 requests R1: Granted
P2 requests R2: Granted
P2 releases R2 and R1
Deadlock prevention using resource ordering completed successfully.
```

---

## Lab 11b: Deadlock Avoidance (Banker's Algorithm)
*File: [`lab11b_bankers_algorithm.cpp`](./lab11b_bankers_algorithm.cpp)*

### System Input
* **5 Processes ($P_0$ to $P_4$)**, **3 Resources ($A, B, C$)**
* **Available:** `[3, 3, 2]`
* **Allocation Matrix:**
  * $P_0$: `[0, 1, 0]`
  * $P_1$: `[2, 0, 0]`
  * $P_2$: `[3, 0, 2]`
  * $P_3$: `[2, 1, 1]`
  * $P_4$: `[0, 0, 2]`
* **Max Demand Matrix:**
  * $P_0$: `[7, 5, 3]`
  * $P_1$: `[3, 2, 2]`
  * $P_2$: `[9, 0, 2]`
  * $P_3$: `[2, 2, 2]`
  * $P_4$: `[4, 3, 3]`

### Expected Output
```text
Need Matrix:
P0: 7 4 3 
P1: 1 2 2 
P2: 6 0 0 
P3: 0 1 1 
P4: 4 3 1 

System is in a SAFE state.
Safe sequence: P1 -> P3 -> P0 -> P2 -> P4

Suppose P1 requests [1, 0, 2]:
Request Granted. Resulting system is SAFE.
Safe sequence: P1 -> P3 -> P0 -> P2 -> P4
```

---

## Lab 11c: Process Synchronization (Producer-Consumer)
*File: [`lab11c_producer_consumer.cpp`](./lab11c_producer_consumer.cpp)*

### Parameters
* **Buffer Capacity:** `5`
* **Total Items:** `10`

### Expected Output
```text
Produced: 1 | Buffer size: 1
Produced: 2 | Buffer size: 2
Consumed: 1 | Buffer size: 1
Produced: 3 | Buffer size: 2
Consumed: 2 | Buffer size: 1
Produced: 4 | Buffer size: 2
Consumed: 3 | Buffer size: 1
...
Produced: 10 | Buffer size: 1
Consumed: 10 | Buffer size: 0
Producer-Consumer finished.
```

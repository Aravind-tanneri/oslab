# Operating Systems Lab

Simple and minimalist C++ implementations Operating Systems lab (CS2022) coursework.

## Structure

* **`tasks/`** – Lab problem statements and assignments.
* **`solutions/`** – Clean C++ code and references for each task.

## Index

| Lab | Topic | Solution |
| :--- | :--- | :--- |
| **Lab 1** | Process Monitoring & Commands | [lab1_process_management.md](solutions/lab1_process_management.md) |
| **Lab 2** | Process Creation (`fork`) & PCB | [lab2_pcb_fork.cpp](solutions/lab2_pcb_fork.cpp) |
| **Lab 3** | FCFS Scheduling | [lab3_fcfs.cpp](solutions/lab3_fcfs.cpp) |
| **Lab 4** | SJF Scheduling (Non-Preemptive) | [lab4_sjf.cpp](solutions/lab4_sjf.cpp) |
| **Lab 5** | Round Robin & SRTF Scheduling | [lab5_rr_srtf.cpp](solutions/lab5_rr_srtf.cpp) |
| **Lab 6** | IPC via Message Queues | [lab6_ipc_message_queue.cpp](solutions/lab6_ipc_message_queue.cpp) |
| **Lab 7** | Page Replacement (FIFO, Optimal, LRU) | [lab7_page_replacement.cpp](solutions/lab7_page_replacement.cpp) |
| **Lab 8** | Paging & Address Translation | [lab8_paging_address_translation.cpp](solutions/lab8_paging_address_translation.cpp) |
| **Lab 9** | Memory Allocation (First, Best, Worst Fit) | [lab9_memory_allocation.cpp](solutions/lab9_memory_allocation.cpp) |
| **Lab 10** | Disk Scheduling (FCFS, SSTF, SCAN) | [lab10_disk_scheduling.cpp](solutions/lab10_disk_scheduling.cpp) |
| **Lab 11a** | Deadlock Prevention (Resource Ordering) | [lab11a_deadlock_prevention.cpp](solutions/lab11a_deadlock_prevention.cpp) |
| **Lab 11b** | Deadlock Avoidance (Banker's Algorithm) | [lab11b_bankers_algorithm.cpp](solutions/lab11b_bankers_algorithm.cpp) |
| **Lab 11c** | Producer-Consumer (Bounded Buffer) | [lab11c_producer_consumer.cpp](solutions/lab11c_producer_consumer.cpp) |

Sample runs and test cases are documented in [`solutions/sample_inputs_and_outputs.md`](solutions/sample_inputs_and_outputs.md).

## Running

```bash
g++ -std=c++17 solutions/<filename>.cpp
./a.out
```

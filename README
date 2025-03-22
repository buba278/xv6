# xv6 Lab 1 - SOFTENG370 2025 S1

## Overview
This repository contains my work for **Lab 1** of SOFTENG370 (Operating Systems). The lab focuses on exploring **xv6**, a re-implementation of Unix designed for teaching purposes. By working with xv6, I gained hands-on experience with system calls, kernel interactions, and Unix-based development.

## Lab Objectives
- Set up and build xv6 inside a virtualized environment.
- Run xv6 on an emulator (QEMU) and interact with the shell.
- Implement and test Unix based user programs within xv6.
- Work with system calls and inter-process communication.

## Installation & Setup
You can follow these steps to set up xv6 in your own environment:

1. **Install Ubuntu 24.04.2 LT** either through WSL or VirtualBox / any VM software
2. **Install necessary tools** for compiling xv6:
   ```sh
   sudo apt update
   sudo apt install build-essential qemu gcc-riscv64-unknown-elf gdb-multiarch
   ```
5. **Clone the repo**:
   ```sh
   https://github.com/buba278/xv6.git
   cd xv6-labs
   ```
6. **Compile and run xv6**:
   ```sh
   make qemu
   ```

## Tasks & Implementations

### Task 1: Implementing `sleep`
- Created `user/sleep.c`, which suspends execution for a given number of seconds using the `sleep` system call.
- Handled missing arguments and converted input to an integer using `atoi`.
- Added the program to `UPROGS` in `Makefile`.

### Task 2: Alternative `sleep` Implementation
- Implemented `user/sleep_2.c` **without using the `sleep` system call**.
- Provided justifications for differences in behavior (`task2.txt`).

### Task 3: Inter-process Communication - `pingpong`
- Created `user/pingpong.c`, where a parent process communicates with two child processes via pipes.
- The child processes respond with "ACK" messages after receiving "ping".

### Task 4: Implementing `getppid` System Call
- Modified **kernel files** (`syscall.c`, `sysproc.c`, `syscall.h`) to add `getppid`.
- Created `user/findppid.c` to demonstrate **process hierarchy** by printing parent-child relationships in a chain.

### Task 5: Concurrent Prime Sieve
- Implemented `user/primes.c`, a **multi-process** implementation of the **Sieve of Eratosthenes**.
- Used `fork()`, `pipe()`, and **message passing** to filter out prime numbers concurrently.

### Task 6: Consecutive Prime Sum
- Extended `primes.c` into `user/primes_sum.c` to calculate and display sums of consecutive primes.

## Running the Programs
To test the implemented programs in xv6, boot xv6 using:
```sh
make qemu
```
Then, within the xv6 shell, run:
```sh
$ sleep 10  # Sleeps for 10 seconds
$ pingpong  # Parent-child communication
$ findppid 5  # Displays parent-child process chain
$ primes 20  # Finds primes up to 20
$ primes_sum 20  # Computes sums of consecutive primes
```

## Learning Outcomes
This lab deepened my understanding of:
- **Kernel-level programming** and **system calls**.
- **Process creation** and **inter-process communication**.
- **Pipe-based concurrency** and **message passing**.
- **Unix-style user-level program development**.

---
### Acknowledgments
This work was completed as part of **SOFTENG370** at The Univeristy of Auckland. Special thanks to the course instructors and teaching assistants for their guidance.

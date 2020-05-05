# ELE 709: Real-Time Computer Controls Systems

## Clock and Time
### Objectives
Learn how to perform time measurement, 
Learn about the system clock and clock resolution, 
Demonstrate how time cannot be measured with exact certainty.

### exec_time.c
Computes the average execution time of a mathematical operation.

### sleep_time_duration.c
Computes the actual amount sleep time of the program for comparison
with the theoretical sleep time.

## POSIX Threads and Concurrent Programming
### Objectives
Introduce concurrent programming using the POSIX library,
Observe the effect of time-sharing on a program's execution time,
Practical applications of concurrent programming.

### concurrent_exec_time.c
Concurrent execution of mathematical operations using POSIX threads.

## Digital PID Controller
### Objectives
Design and implement a digital PID controller with anti-windup using 
concurrent POSIX threads to control the position of a DC motor. 

### Task 2.1: Proportional Control 
Proportional-only controller and system performance.

### Task 2.2: Design PID Parameters using Ultimate Sensitivity Method
System response and critical gain.

### Task 2.3: Basic PID Controller 
PID controller and system response.

### Task 2.4: Anti-Windup Design (PID+A Controller)
PID controller with anti-windup and system response.


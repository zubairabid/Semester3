# OS Assignment 4

## Question 1
Question to test concepts of multithreading and resource management.

Given an input n, the program had to walk through the allocation of games
to several people (processes) with necessary lock conditions.

### Approach
A quick summary of what's been done:
- Primary (time cycle, etc) control is done via a loop in the main thread
- Each person (referee/player) is a new thread
- The organizer is a mutex
- Each person (referee/player) thread manages everything the person does,
from entering the academy to setting up the equipment/warming up. The main
function/loop simply delegates tasks

Some more specifics:
- In order to get the timing of referee/players right, a custom semaphore-like
variable was introduced
- To ensure correct waiting for each thread, there is a condition associated
with each (possible) thread

### Results
1. Input n = 10: [Output for n = 10][]
2. Input n = 1: [Output for n = 1][]
3. Input n = 3: [Output for n = 3][]

## Question 2

## Question 3
Three implementations of mergesort were written and tested, namely:

1. [Normal Merge Sort](solution/3_normalmerge.c)
2. [Concurrent Merge Sort with Processes](solution/3_concurrentmerge.c)
3. [Concurrent Merge Sort with Threads](solution/3_threadmerge.c)

### Tests
#### Input files
Tests were run with 3 input files of 10^3, 10^4, and 10^5 inputs respectively.
They were generated with the commands `echo <number of test cases> > filename`
and `seq 1 <number of test cases> | sort -r >> filename`

#### Results
All times reported are an average of three tests each, in seconds

| Program  | Time on 10^3  | Time on 10^4  | Time on 10^5  |
|:-:|---|---|---|
| Normal  | [0.00][] | [0.01][]  | [0.10][]  |
| Process  | [0.20][]  | [2.56][]  | (Crashed) |
| Threaded  | [0.04][]  | [0.39][] | (Segfault) |

### General Observation:
The normal merge sort ran the fastest, while the concurrent merge sort based on
processes ran the slowest.

The process based program ran the slowest because of
1. Constant context switches
2. Generating new processes is a time consuming task



[Output for n = 10]: output/1_1
[Output for n = 1]: output/1_2
[Output for n = 3]: output/1_3

[0.00]: output/3normal1
[0.01]: output/3normal2
[0.10]: output/3normal3
[0.20]: output/3proc1
[2.56]: output/3proc2
[0.04]: output/3thread1
[0.39]: output/3thread2

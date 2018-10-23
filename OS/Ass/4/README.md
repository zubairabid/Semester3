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
Code not in a functional state

### Broad level, conceptual approach
The Booth has a list of all Voters (Robots) and EVMs associated with it.
Each Voter (robot) and EVM is a thread. At the start of the program, all
Booths and Voters and EVMs are allocated. The timeline from then is as
follows:
 - Voter waits for an EVM to be assigned to.
 If any are free (notification of such is received when a free EVM reports so), then all the slots are occupied by maximum voters possible.
 - Each EVM reports free slots, and takes occupation of voters. Then it begins
 the voting process.  
 - All the voters who are in an EVM and marked ready cast their vote.
 - When all voters in an EVM are done voting, report free EVM and repeat.

Implementation of timing is done by making each thread wait on conditional
variables with use of mutexes.

### Slightly more detail
`Booth`: struct, with array of Voter and EVM threads

`Voter`: Thread implementing and waiting for related functions

`EVM`: Thread implementing and waiting for related functions

**Main thread**:
 - Input number of booths, voters and EVMs for each
 - Start a thread for each booth

**Booth thread**:
 - Start all voter and EVM threads
 -

**Voter thread**:
 - Wait at voter_wait_for_evm
 - Enter an EVM slot and call voter_in_slot
 - Make a vote
 - Leave EVM, inform EVM.

**EVM thread**:
 - Assign random number of slots
 - Call polling_ready_evm
 - Wait till voters are assigned to it
 - Wait till all slots are empty
 - Repeat

## Question 3

[A report of the solution](report.md)

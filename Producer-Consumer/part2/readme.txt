Name  : Marlon Johnson
Date  : 4/25/2018
Class : CSC 415

Compile Instructions:
make pandc

Run Instructions:
./pandc 7 5 3 15 1 1

Project Description:
Implemented Producers and Consumer threads with a bounded buffer queue of N elements

Producer thread will  Enqueue X different numbers onto the queue  and wait for Ptime cycles in between each
call to Enqueue. Each Consumer thread will Dequeue P*X/C items from the queue  and wait for Ctime cycles
in between each call to Dequeue. The main program creates and initialize the Bounded Buffer Queue, print a
timestamp, spawn off C consumer threads & P producer threads, wait for all of the threads to finish and
then print off another timestamp & the duration of execution.

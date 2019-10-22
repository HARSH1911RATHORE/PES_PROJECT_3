### PES_PROJECT_3
##The README consists of a suite of memory tests, a pattern generator, a logger, an LED control, a main program to run an example test set, and μcUnit test case.
#Memory Test Suite:
The test includes allocated memory region through dynamic memory allocation when run on your development system Windows  but includes direct memory addressing (using the heap in your KL25Z memory map) when run on the KL25Z.
It Determines the memory bounds for the heap region to ensure valid addressing and doesnot exceed the memory bound.Functions does bounds checking and warn the user if they attempt to read or write memory outside the allocated range (or if no memory block has been allocated). Functions will return an error code to indicate issues have occurred (or not
#Executing the Memory Tests
#LED Control
#Logger

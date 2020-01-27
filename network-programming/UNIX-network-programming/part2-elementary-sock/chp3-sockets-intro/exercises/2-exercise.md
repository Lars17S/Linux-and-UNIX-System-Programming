# Part 2 : Elementary Sockets
## Chapter 3 : Sockets Introduction
### Exercise 3.2

__Question__

Why do both the readn and writen functions copy the void* pointer into a char* pointer?

__Answer__

The void* pointer is a general pointer, it is copied to a char* pointer because is the buffer
used by the functions readn and writen.
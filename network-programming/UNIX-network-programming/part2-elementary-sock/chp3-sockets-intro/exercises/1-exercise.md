# Part 2 : Elementary Sockets
## Chapter 3 : Sockets Introduction
### Exercise 3.1

__Question__

Why must value-result arguments such as the length of a socket address structure be passed by reference?

__Answer__


Because the kernel needs a socket address structure to copy data from the process into the kernel. Functions like _bind_, _connect_, and _sendto_ needs the reference to the socket structure due the operations requested by the kernel. Furthermore, these functions must have the size of the structure, only then system call function knows exactly how much data to copy from the process into the kernel (different transports implement different sockaddr_... structures, which have differente sizes and layouts). 

Four functions, _accept_, _recvfrom_, _getsockname_, and _geetpername_, have a pointer to an integer containing the size of the structure as argument. It is because the size is both a value when the function is called, it tells the kernel the size of the structure so that the kernel does not write past the end or to validate that the buffer is large enough to receive the client's actual sockaddr_... data structure before populating the buffer (in the case of accept()). The parameter is a result when the function returns (it tells the process how much information the kernel actually stored in the structure).

Assign an input value to a variable and pass it by-reference so the function can modify the variable with an output value. This saves having to pass a separate parameter for the output, or change the semantics of the function's return value.
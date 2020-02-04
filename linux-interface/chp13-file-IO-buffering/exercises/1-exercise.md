# Chapter 13 : File I/O Buffering
## Exercise 13.1

__Exercise__

13-1. Using the time built-in command of the shell, try timing the operation of the
program in Listing 4-1 (copy.c) on your system.

a) Experiment with different file and buffer sizes. You can set the buffer size
using the –DBUF_SIZE=nbytes option when compiling the program.

SIZE TEXT FILE: 976573 bytes

BUF_SIZE = 1

    real	0m4.046s
    user	0m0.903s
    sys     0m3.123s

BUF_SIZE = 10

    real	0m0.434s
    user	0m0.096s
    sys     0m0.338s

BUF_SIZE = 100

    real	0m0.073s
    user	0m0.020s
    sys	0m0.047s

BUF_SIZE = 1000

    real	0m0.034s
    user	0m0.005s
    sys     0m0.023s

BUF_SIZE = 10000

    real	0m0.009s
    user	0m0.001s
    sys	    0m0.008s

b) Modify the open() system call to include the O_SYNC flag. How much differ-
ence does this make to the speed for various buffer sizes?

O_SYNC provides a stronger guarantee. It guarantees not only that the file data has been written to disk but also the file metadata.

BUF_SIZE = 1

    TIME UNDEFINED

BUF_SIZE = 100

    TIME UNDEFINED

BUF_sIZE = 100000

    real	0m0.780s
    user	0m0.000s
    sys	    0m0.011s

c) Try performing these timing tests on a range of file systems (e.g., ext3, XFS,
Btrfs, and JFS). Are the results similar?

They differ due stability reasons.


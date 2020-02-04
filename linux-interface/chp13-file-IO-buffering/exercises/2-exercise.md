# Chapter 13 : File I/O Buffering
## Exercise 13.2

__Exercise__

13-2. Time the operation of the filebuff/write_bytes.c program (provided in the source code distribution for this book) for various buffer sizes and file systems.

time ./write_bytes test.txt 1000000 1

    real	0m2.481s
    user	0m0.552s
    sys     0m1.926s


time ./write_bytes test.txt 1000000 100

    real	0m0.117s
    user	0m0.024s
    sys     0m0.082s

time ./write_bytes test.txt 1000000 10000

    real	0m0.009s
    user	0m0.000s
    sys     0m0.009s



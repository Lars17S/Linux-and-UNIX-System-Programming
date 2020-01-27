# Chapter 10 : Time
## Exercise 10.1

__Question__

Assume a system where the value returned by the call sysconf(_SC_CLK_TCK) is 100.
Assuming that the clock_t value returned by times() is an unsigned 32-bit
integer, how long will it take before this value cycles so that it restarts at 0? Perform
the same calculation for the CLOCKS_PER_SEC value returned by clock().

__Answer__

The limit number for an unsigned 32-bit integer is 4,294,967,295 ticks. Therefore, the
necessary time to reach this limit will be:

    t = 4294967295 ticks / (100 ticks / sec)
      = 42949672.95 sec
      = 715827.8825 mins
      = 11930.4647 hours
      = 497.1026 days
      = 1.3619 years

For the second case (clocks() function and 1 million), the time will be:
    
    t = 4294967295 ticks / (1000000 ticks / sec)
    t = 4294.967295 sec
    t = 1.1930 hours
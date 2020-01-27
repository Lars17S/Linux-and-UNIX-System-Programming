/*  3.3 Write a new function named inet_pton_loose that handles these scenarios: If 
    the address family is AF_INET and inet_pton returns 0, call inet_aton and see 
    if it succeeds. Similarly, if the address family is AF_INET6 and inet_pton
    returns 0, call inet_aton and if it succeeds, return the IPv4-mapped IPv6 
    address. */

#include "3-exercise.h"

int inet_pton_loose(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 1) 
        return res;

    if ((af == AF_INET || af == AF_INET6) && inet_pton(af, src, dst) == 0) {
        return inet_aton(src, dst);
    }
}
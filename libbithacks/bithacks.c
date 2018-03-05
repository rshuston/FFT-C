/*
 * Sean Anderson's Bit Twiddling Hacks
 * https://graphics.stanford.edu/~seander/bithacks.html
 */

#include "bithacks.h"



/*
 * Find the log base 2 of an N-bit integer in O(lg(N)) operations using
 * multiply and lookup method
 */

unsigned log2_u(unsigned v)
{
    int r;      // result goes here

    static const int _multiplyDeBruijnBitPosition[32] =
    {
        0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    v |= v >> 1; // first round down to one less than a power of 2
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    r = _multiplyDeBruijnBitPosition[(unsigned)(v * 0x07C4ACDDU) >> 27];

    return r;
}



/*
 * Find the log base 2 of an N-bit integer in O(lg(N)) operations using
 * multiply and lookup method ...
 * ... and N-bit integer is already known to be a power of 2
 */

unsigned log2_u_p2(unsigned v)
{
    static const int _multiplyDeBruijnBitPosition2[32] =
    {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    unsigned r = _multiplyDeBruijnBitPosition2[(unsigned)(v * 0x077CB531U) >> 27];

    return r;
}

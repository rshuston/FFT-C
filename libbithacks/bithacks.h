/*
 * Sean Anderson's Bit Twiddling Hacks
 * https://graphics.stanford.edu/~seander/bithacks.html
 */

#ifndef _bithacks_h_
#define _bithacks_h_


#ifdef __cplusplus
extern "C" {
#endif


/*
 * Find the log base 2 of an N-bit integer in O(lg(N)) operations using
 * multiply and lookup method
 */

unsigned log2_u(unsigned v);


/*
 * Find the log base 2 of an N-bit integer in O(lg(N)) operations using
 * multiply and lookup method ...
 * ... and N-bit integer is already known to be a power of 2
 */

unsigned log2_u_p2(unsigned v);


#ifdef __cplusplus
}
#endif


#endif

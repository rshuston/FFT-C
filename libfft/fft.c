#include "fft.h"

#include <math.h>



void fft_f(complex_f data[], int N)
{
}



void fft_copy_shuffle_f(complex_f src[], complex_f dst[], int N)
{
    /*
     * Basic Bit-Reversal Scheme:
     *
     * The incrementing pattern operations used here correspond
     * to the logic operations of a synchronous counter.
     *
     * Incrementing a binary number simply flips a sequence of
     * least-significant bits, for example from 0111 to 1000.
     * So in order to compute the next bit-reversed index, we
     * have to flip a sequence of most-significant bits.
     */

    unsigned n = N;         /* unsigned copy of N */
    unsigned nd2 = n >> 1;  /* N/2 = number range midpoint */
    unsigned nm1 = n - 1;   /* N-1 = digit mask */
    unsigned i;             /* index for array elements */
    unsigned j;             /* index for next element swap */

    for (i = 0, j = 0; i < n; i++) {
        dst[j] = src[i];

        /*
         * Find least significant zero bit
         */

        unsigned lszb = ~i & (i + 1);

        /*
         * Use division to bit-reverse the single bit so that we now have
         * the most significant zero bit
         *
         * n = 2^r = 2^(2m)
         * nd2 = n/2 = 2^m
         * if lszb = 2^k, where k is within the range of 0...m, then
         *     mszb = Nd2 / lszb
         *          = 2^m / 2^n
         *          = 2^(m-n)
         *          = bit-reversed value of lszb
         */

        unsigned mszb = nd2 / lszb;

        /*
         * Toggle bits with bit-reverse mask
         */

        unsigned m = nm1 & ~(mszb - 1);
        j ^= m;
    }
}


void fft_shuffle_f(complex_f data[], int N)
{
    /*
     * Basic Bit-Reversal Scheme:
     *
     * The incrementing pattern operations used here correspond
     * to the logic operations of a synchronous counter.
     *
     * Incrementing a binary number simply flips a sequence of
     * least-significant bits, for example from 0111 to 1000.
     * So in order to compute the next bit-reversed index, we
     * have to flip a sequence of most-significant bits.
     */

    unsigned n = N;         /* unsigned copy of N */
    unsigned nd2 = n >> 1;  /* N/2 = number range midpoint */
    unsigned nm1 = n - 1;   /* N-1 = digit mask */
    unsigned i;             /* index for array elements */
    unsigned j;             /* index for next element swap */

    for (i = 0, j = 0; i < n; i++) {
        if (j > i) {
            complex_f tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }

        /*
         * Find least significant zero bit
         */

        unsigned lszb = ~i & (i + 1);

        /*
         * Use division to bit-reverse the single bit so that we now have
         * the most significant zero bit
         *
         * n = 2^r = 2^(2m)
         * nd2 = n/2 = 2^m
         * if lszb = 2^k, where k is within the range of 0...m, then
         *     mszb = Nd2 / lszb
         *          = 2^m / 2^n
         *          = 2^(m-n)
         *          = bit-reversed value of lszb
         */

        unsigned mszb = nd2 / lszb;

        /*
         * Toggle bits with bit-reverse mask
         */

        unsigned m = nm1 & ~(mszb - 1);
        j ^= m;
    }
}



void fft_evaluate_f(complex_f data[], int N)
{
}

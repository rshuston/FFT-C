#include "fft.h"

#include <math.h>



unsigned __log2_u(unsigned v)
{
    /*
     * Ref:
     * Sean Anderson's Bit Twiddling Hacks
     * https://graphics.stanford.edu/~seander/bithacks.html
     */

    static const int _multiplyDeBruijnBitPosition[32] =
    {
        0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
        31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
    };
    unsigned r = _multiplyDeBruijnBitPosition[(unsigned)(v * 0x077CB531U) >> 27];

    return r;
}


void fft_f(complex_f data[], int N)
{
    fft_shuffle_f(data, N);
    fft_evaluate_f(data, N);
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
    /*
     * In-place FFT butterfly algorithm
     *
     * input:
     *     A[] = array of N shuffled complex values where N is a power of 2
     * output:
     *     A[] = the DFT of input A[]
     *
     * for r = 1 to log2(N)
     *     m = 2^r
     *     Wm = exp(−j2π/m)
     *     for n = 0 to N-1 by m
     *         Wmk = 1
     *         for k = 0 to m/2 - 1
     *             u = A[n + k]
     *             t = Wmk * A[n + k + m/2]
     *             A[n + k]       = u + t
     *             A[n + k + m/2] = u - t
     *             Wmk = Wmk * Wm
     */

    unsigned log2_N;
    unsigned r;
    unsigned m, md2;
    unsigned n, k;
    unsigned i_e, i_o;
    double theta;       /* Use double for precision */
    complex_d Wm, Wmk;  /* Use double for precision */
    complex_d u, t;     /* Use double for precision */

    log2_N = __log2_u(N);
    for (r = 1; r <= log2_N; r++)
    {
        m = 1 << r;
        md2 = m / 2;
        theta = - (2 * M_PI) / m;
        Wm.re = cos(theta);
        Wm.im = sin(theta);
        for (n = 0; n < N; n += m)
        {
            Wmk.re = 1.f;
            Wmk.im = 0.f;
            for (k = 0; k < md2; k++)
            {
                i_e = n + k;
                i_o = i_e + md2;
                u.re = data[i_e].re;
                u.im = data[i_e].im;
                t.re = complex_mul_re(Wmk.re, Wmk.im, data[i_o].re, data[i_o].im);
                t.im = complex_mul_im(Wmk.re, Wmk.im, data[i_o].re, data[i_o].im);
                data[i_e].re = u.re + t.re;
                data[i_e].im = u.im + t.im;
                data[i_o].re = u.re - t.re;
                data[i_o].im = u.im - t.im;
                t.re = complex_mul_re(Wmk.re, Wmk.im, Wm.re, Wm.im);
                t.im = complex_mul_im(Wmk.re, Wmk.im, Wm.re, Wm.im);
                Wmk = t;
            }
        }
    }
}

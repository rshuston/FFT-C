#include "fft.h"

#include <math.h>

#include <stdio.h>
#include <stdlib.h>



/* ===== In-Place FFT ======================================================= */



void ffti_f(complex_f data[], unsigned log2_N)
{
    ffti_shuffle_f(data, log2_N);
    ffti_evaluate_f(data, log2_N);
}



void ffti_copy_shuffle_f(complex_f src[], complex_f dst[], unsigned log2_N)
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

    unsigned n = 1 << log2_N;   /* N */
    unsigned nd2 = n >> 1;      /* N/2 = number range midpoint */
    unsigned nm1 = n - 1;       /* N-1 = digit mask */
    unsigned i;                 /* index for array elements */
    unsigned j;                 /* index for next element swap */

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
         *     mszb = nd2 / lszb
         *          = 2^m / 2^k
         *          = 2^(m-k)
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



void ffti_shuffle_f(complex_f data[], unsigned log2_N)
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

    unsigned n = 1 << log2_N;   /* N */
    unsigned nd2 = n >> 1;      /* N/2 = number range midpoint */
    unsigned nm1 = n - 1;       /* N-1 = digit mask */
    unsigned i;                 /* index for array elements */
    unsigned j;                 /* index for next element swap */

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
         *     mszb = nd2 / lszb
         *          = 2^m / 2^k
         *          = 2^(m-k)
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



void ffti_evaluate_f(complex_f data[], unsigned log2_N)
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

    unsigned N;
    unsigned r;
    unsigned m, md2;
    unsigned n, k;
    unsigned i_e, i_o;
    double theta;       /* Use double for precision */
    complex_d Wm, Wmk;  /* Use double for precision */
    complex_d u, t;     /* Use double for precision */

    N = 1 << log2_N;
    for (r = 1; r <= log2_N; r++)
    {
        m = 1 << r;
        md2 = m >> 1;
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



/* ===== Recursive FFT ====================================================== */



void fftr_f(complex_f data[], unsigned log2_N)
{
    /*
     * fft(A[],N):
     *     if N == 1
     *         return
     *     for k = 0 to N/2-1
     *         e[k] = A[2*k]
     *         o[k] = A[2*k+1]
     *     fft(e, N/2)
     *     fft(o, N/2);
     *     WN = exp(−j2π/N)
     *     WNk = 1
     *     for k = 0 to N/2-1
     *         A[k]     = e[k] + WNk * o[k]
     *         A[k+N/2] = e[k] - WNk * o[k]
     *         WNk = WNk * WN
     */

    if (log2_N > 0)
    {
        unsigned log2_Nd2;
        unsigned Nd2;
        unsigned k;
        unsigned kpNd2;
        complex_f *evn, *odd;
        double theta;       /* Use double for precision */
        complex_d WN, WNk;  /* Use double for precision */
        complex_d u, t;     /* Use double for precision */

        log2_Nd2 = log2_N - 1;
        Nd2 = 1 << log2_Nd2;

        evn = malloc(Nd2 * sizeof(complex_f));
        odd = malloc(Nd2 * sizeof(complex_f));

        for (k = 0; k < Nd2; k++)
        {
            evn[k] = data[2*k];
            odd[k] = data[2*k+1];
        }

        fftr_f(evn, log2_Nd2);
        fftr_f(odd, log2_Nd2);

        theta = - M_PI / Nd2;  /* - (2 * M_PI) / N */
        WN.re = cos(theta);
        WN.im = sin(theta);

        WNk.re = 1.f;
        WNk.im = 0.f;
        for (k = 0; k < Nd2; k++)
        {
            kpNd2 = k + Nd2;

            u.re = evn[k].re;
            u.im = evn[k].im;
            t.re = complex_mul_re(WNk.re, WNk.im, odd[k].re, odd[k].im);
            t.im = complex_mul_im(WNk.re, WNk.im, odd[k].re, odd[k].im);
            data[k].re = u.re + t.re;
            data[k].im = u.im + t.im;
            data[kpNd2].re = u.re - t.re;
            data[kpNd2].im = u.im - t.im;

            t.re = complex_mul_re(WNk.re, WNk.im, WN.re, WN.im);
            t.im = complex_mul_im(WNk.re, WNk.im, WN.re, WN.im);
            WNk = t;
        }

        free(evn);
        free(odd);
    }
}



/* ===== Recursive FFT, user-supplied scratchpad buffer ===================== */



#if 0



/*
 * A more efficient version of the fftr_f() implementation, where a
 * user-supplied buffer is used to hold the even/odd decompositions
 */

void fftrb_f(complex_f data[], unsigned log2_N, complex_f scratch[])
{
    /*
     * fft(A[],N):
     *     if N == 1
     *         return
     *     for k = 0 to N/2-1
     *         e[k] = A[2*k]
     *         o[k] = A[2*k+1]
     *     fft(e, N/2)
     *     fft(o, N/2);
     *     WN = exp(−j2π/N)
     *     WNk = 1
     *     for k = 0 to N/2-1
     *         A[k]     = e[k] + WNk * o[k]
     *         A[k+N/2] = e[k] - WNk * o[k]
     *         WNk = WNk * WN
     */

    if (log2_N > 0)
    {
        unsigned log2_Nd2;
        unsigned Nd2;
        unsigned k;
        unsigned kpNd2;
        complex_f *evn, *odd;
        double theta;       /* Use double for precision */
        complex_d WN, WNk;  /* Use double for precision */
        complex_d u, t;     /* Use double for precision */

        log2_Nd2 = log2_N - 1;
        Nd2 = 1 << log2_Nd2;

        evn = scratch;
        odd = scratch + Nd2;

        for (k = 0; k < Nd2; k++)
        {
            evn[k] = data[2*k];
            odd[k] = data[2*k+1];
        }

        fftr_f(evn, log2_Nd2);
        fftr_f(odd, log2_Nd2);

        theta = - M_PI / Nd2;  /* - (2 * M_PI) / N */
        WN.re = cos(theta);
        WN.im = sin(theta);

        WNk.re = 1.f;
        WNk.im = 0.f;
        for (k = 0; k < Nd2; k++)
        {
            kpNd2 = k + Nd2;

            u.re = evn[k].re;
            u.im = evn[k].im;
            t.re = complex_mul_re(WNk.re, WNk.im, odd[k].re, odd[k].im);
            t.im = complex_mul_im(WNk.re, WNk.im, odd[k].re, odd[k].im);
            data[k].re = u.re + t.re;
            data[k].im = u.im + t.im;
            data[kpNd2].re = u.re - t.re;
            data[kpNd2].im = u.im - t.im;

            t.re = complex_mul_re(WNk.re, WNk.im, WN.re, WN.im);
            t.im = complex_mul_im(WNk.re, WNk.im, WN.re, WN.im);
            WNk = t;
        }
    }
}



#else



/*
 * A much more efficient version of the recursive FFT algorithm, where
 * the data and scratch buffers are commutated throughout the recursion
 * sequence, and index mapping is used to locate the correct values
 */

void _fftrb_f(complex_f data[], complex_f scratch[], int N, int stride)
{
    if (stride < N)
    {
        unsigned stride2;
        unsigned k;
        unsigned k_e, k_o;
        unsigned kd2, kpNd2;
        double theta;       /* Use double for precision */
        complex_d WN, WNk;  /* Use double for precision */
        complex_d u, t;     /* Use double for precision */

        stride2 = 2 * stride;

        /* Notice that the order of data and scratch buffers is swapped! */
        _fftrb_f(scratch         , data         , N, stride2);
        _fftrb_f(scratch + stride, data + stride, N, stride2);

        theta = - (stride2 * M_PI) / N;
        WN.re = cos(theta);
        WN.im = sin(theta);

        WNk.re = 1.f;
        WNk.im = 0.f;
        for (k = 0; k < N; k += stride2)
        {
            k_e = k;
            k_o = k + stride;
            kd2 = k >> 1;
            kpNd2 = (k + N) >> 1;

            u.re = scratch[k_e].re;
            u.im = scratch[k_e].im;
            t.re = complex_mul_re(WNk.re, WNk.im, scratch[k_o].re, scratch[k_o].im);
            t.im = complex_mul_im(WNk.re, WNk.im, scratch[k_o].re, scratch[k_o].im);

            data[kd2].re   = u.re + t.re;
            data[kd2].im   = u.im + t.im;
            data[kpNd2].re = u.re - t.re;
            data[kpNd2].im = u.im - t.im;

            t.re = complex_mul_re(WNk.re, WNk.im, WN.re, WN.im);
            t.im = complex_mul_im(WNk.re, WNk.im, WN.re, WN.im);
            WNk = t;
        }
    }
}



void fftrb_f(complex_f data[], unsigned log2_N, complex_f scratch[])
{
    unsigned N;
    unsigned k;

    N = 1 << log2_N;
    for (k = 0; k < N; k++)
        scratch[k] = data[k];

    _fftrb_f(data, scratch, N, 1);
}



#endif

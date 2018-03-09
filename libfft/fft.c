#include "fft.h"

#include <math.h>

#include <stdio.h>
#include <stdlib.h>



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



static void _fftr_f(complex_f v[], unsigned N)
{
    /*
     * fft(v,N):
     *     if N == 1
     *         return
     *     for k = 0 to N/2-1
     *         ve[k] = v[2*k]
     *         vo[k] = v[2*k+1]
     *     fft(ve, N/2)
     *     fft(vo, N/2);
     *     WN = exp(−j2π/N)
     *     WNk = 1
     *     for k = 0 to N/2-1
     *         v[k]     = ve[k] + WNk * vo[k]
     *         v[k+N/2] = ve[k] - WNk * vo[k]
     *         WNk = WNk * WN
     */

    if (N > 1)
    {
        unsigned Nd2;
        unsigned k;
        unsigned kpNd2;
        complex_f *ve, *vo;
        double theta;
        complex_d WN, WNk;
        complex_d u, t;

        Nd2 = N >> 1;

        ve = malloc(Nd2 * sizeof(complex_f));
        vo = malloc(Nd2 * sizeof(complex_f));

        for (k = 0; k < Nd2; k++)
        {
            ve[k] = v[2*k];
            vo[k] = v[2*k+1];
        }

        _fftr_f(ve, Nd2);
        _fftr_f(vo, Nd2);

        theta = - (2 * M_PI) / N;
        WN.re = cos(theta);
        WN.im = sin(theta);

        WNk.re = 1.f;
        WNk.im = 0.f;
        for (k = 0; k < Nd2; k++)
        {
            kpNd2 = k + Nd2;

            u.re = ve[k].re;
            u.im = ve[k].im;
            t.re = complex_mul_re(WNk.re, WNk.im, vo[k].re, vo[k].im);
            t.im = complex_mul_im(WNk.re, WNk.im, vo[k].re, vo[k].im);
            v[k].re = u.re + t.re;
            v[k].im = u.im + t.im;
            v[kpNd2].re = u.re - t.re;
            v[kpNd2].im = u.im - t.im;

            t.re = complex_mul_re(WNk.re, WNk.im, WN.re, WN.im);
            t.im = complex_mul_im(WNk.re, WNk.im, WN.re, WN.im);
            WNk = t;
        }

        free(ve);
        free(vo);
    }
}



void fftr_f(complex_f data[], unsigned log2_N)
{
    _fftr_f(data, 1 << log2_N);
}

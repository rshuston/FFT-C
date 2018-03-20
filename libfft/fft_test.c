#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "checkext.h"

#include "fft.h"



#define FLOAT_EQ_TOLERANCE 1.0e-5



/* ===== ffti_shuffle_f() =================================================== */

START_TEST (ffti_shuffle_f_shuffles_four_values)
{
    /*
     * 0: 00 -> 00 : 0
     * 1: 01 -> 10 : 2
     * 2: 10 -> 01 : 1
     * 3: 11 -> 11 : 3
     */

    complex_f data[4] = {
        { 1.f, -1.f},
        { 2.f, -2.f},
        { 3.f, -3.f},
        { 4.f, -4.f}
    };

    ffti_shuffle_f(data, 2);  /* 2 = log2(4) */

    ck_assert_flt_eq(data[0].re, 1.f);
    ck_assert_flt_eq(data[0].im, -1.f);

    ck_assert_flt_eq(data[1].re, 3.f);
    ck_assert_flt_eq(data[1].im, -3.f);

    ck_assert_flt_eq(data[2].re, 2.f);
    ck_assert_flt_eq(data[2].im, -2.f);

    ck_assert_flt_eq(data[3].re, 4.f);
    ck_assert_flt_eq(data[3].im, -4.f);
}
END_TEST

START_TEST (ffti_shuffle_f_shuffles_eight_values)
{
    /*
     * 0: 000 -> 000 : 0
     * 1: 001 -> 100 : 4
     * 2: 010 -> 010 : 2
     * 3: 011 -> 110 : 6
     * 4: 100 -> 001 : 1
     * 5: 101 -> 101 : 5
     * 6: 110 -> 011 : 3
     * 7: 111 -> 111 : 7
     */

    complex_f data[8] = {
        { 1.f, -1.f},
        { 2.f, -2.f},
        { 3.f, -3.f},
        { 4.f, -4.f},
        { 5.f, -5.f},
        { 6.f, -6.f},
        { 7.f, -7.f},
        { 8.f, -8.f}
    };

    ffti_shuffle_f(data, 3);  /* 3 = log2(8) */

    ck_assert_flt_eq(data[0].re, 1.f);
    ck_assert_flt_eq(data[0].im, -1.f);

    ck_assert_flt_eq(data[1].re, 5.f);
    ck_assert_flt_eq(data[1].im, -5.f);

    ck_assert_flt_eq(data[2].re, 3.f);
    ck_assert_flt_eq(data[2].im, -3.f);

    ck_assert_flt_eq(data[3].re, 7.f);
    ck_assert_flt_eq(data[3].im, -7.f);

    ck_assert_flt_eq(data[4].re, 2.f);
    ck_assert_flt_eq(data[4].im, -2.f);

    ck_assert_flt_eq(data[5].re, 6.f);
    ck_assert_flt_eq(data[5].im, -6.f);

    ck_assert_flt_eq(data[6].re, 4.f);
    ck_assert_flt_eq(data[6].im, -4.f);

    ck_assert_flt_eq(data[7].re, 8.f);
    ck_assert_flt_eq(data[7].im, -8.f);
}
END_TEST

START_TEST (ffti_shuffle_f_shuffles_sixteen_values)
{
    /*
     * 00: 0000 -> 0000 : 00
     * 01: 0001 -> 1000 : 08
     * 02: 0010 -> 0100 : 04
     * 03: 0011 -> 1100 : 12
     * 04: 0100 -> 0010 : 02
     * 05: 0101 -> 1010 : 10
     * 06: 0110 -> 0110 : 06
     * 07: 0111 -> 1110 : 14
     * 08: 1000 -> 0001 : 01
     * 09: 1001 -> 1001 : 09
     * 10: 1010 -> 0101 : 05
     * 11: 1011 -> 1101 : 13
     * 12: 1100 -> 0011 : 03
     * 13: 1101 -> 1011 : 11
     * 14: 1110 -> 0111 : 07
     * 15: 1111 -> 1111 : 15
     */

    complex_f data[16] = {
        { 1.f, -1.f},
        { 2.f, -2.f},
        { 3.f, -3.f},
        { 4.f, -4.f},
        { 5.f, -5.f},
        { 6.f, -6.f},
        { 7.f, -7.f},
        { 8.f, -8.f},
        { 9.f, -9.f},
        { 10.f, -10.f},
        { 11.f, -11.f},
        { 12.f, -12.f},
        { 13.f, -13.f},
        { 14.f, -14.f},
        { 15.f, -15.f},
        { 16.f, -16.f}
    };

    ffti_shuffle_f(data, 4);  /* 4 = log2(16) */

    ck_assert_flt_eq(data[0].re, 1.f);
    ck_assert_flt_eq(data[0].im, -1.f);

    ck_assert_flt_eq(data[1].re, 9.f);
    ck_assert_flt_eq(data[1].im, -9.f);

    ck_assert_flt_eq(data[2].re, 5.f);
    ck_assert_flt_eq(data[2].im, -5.f);

    ck_assert_flt_eq(data[3].re, 13.f);
    ck_assert_flt_eq(data[3].im, -13.f);

    ck_assert_flt_eq(data[4].re, 3.f);
    ck_assert_flt_eq(data[4].im, -3.f);

    ck_assert_flt_eq(data[5].re, 11.f);
    ck_assert_flt_eq(data[5].im, -11.f);

    ck_assert_flt_eq(data[6].re, 7.f);
    ck_assert_flt_eq(data[6].im, -7.f);

    ck_assert_flt_eq(data[7].re, 15.f);
    ck_assert_flt_eq(data[7].im, -15.f);

    ck_assert_flt_eq(data[8].re, 2.f);
    ck_assert_flt_eq(data[8].im, -2.f);

    ck_assert_flt_eq(data[9].re, 10.f);
    ck_assert_flt_eq(data[9].im, -10.f);

    ck_assert_flt_eq(data[10].re, 6.f);
    ck_assert_flt_eq(data[10].im, -6.f);

    ck_assert_flt_eq(data[11].re, 14.f);
    ck_assert_flt_eq(data[11].im, -14.f);

    ck_assert_flt_eq(data[12].re, 4.f);
    ck_assert_flt_eq(data[12].im, -4.f);

    ck_assert_flt_eq(data[13].re, 12.f);
    ck_assert_flt_eq(data[13].im, -12.f);

    ck_assert_flt_eq(data[14].re, 8.f);
    ck_assert_flt_eq(data[14].im, -8.f);

    ck_assert_flt_eq(data[15].re, 16.f);
    ck_assert_flt_eq(data[15].im, -16.f);
}
END_TEST

/* ===== ffti_copy_shuffle_f() ============================================== */

START_TEST (ffti_copy_shuffle_f_copies_four_shuffled_values)
{
    /*
     * 0: 00 -> 00 : 0
     * 1: 01 -> 10 : 2
     * 2: 10 -> 01 : 1
     * 3: 11 -> 11 : 3
     */

    complex_f src[4] = {
        { 1.f, -1.f},
        { 2.f, -2.f},
        { 3.f, -3.f},
        { 4.f, -4.f}
    };
    complex_f dst[4];
    int i;

    for (i = 0; i < 4; i++)
    {
        dst[i] = src[i];
    }

    ffti_copy_shuffle_f(src, dst, 2);  /* 2 = log2(4) */

    ck_assert_flt_eq(dst[0].re, 1.f);
    ck_assert_flt_eq(dst[0].im, -1.f);

    ck_assert_flt_eq(dst[1].re, 3.f);
    ck_assert_flt_eq(dst[1].im, -3.f);

    ck_assert_flt_eq(dst[2].re, 2.f);
    ck_assert_flt_eq(dst[2].im, -2.f);

    ck_assert_flt_eq(dst[3].re, 4.f);
    ck_assert_flt_eq(dst[3].im, -4.f);
}
END_TEST

START_TEST (ffti_copy_shuffle_f_copies_eight_shuffled_values)
{
    /*
     * 0: 000 -> 000 : 0
     * 1: 001 -> 100 : 4
     * 2: 010 -> 010 : 2
     * 3: 011 -> 110 : 6
     * 4: 100 -> 001 : 1
     * 5: 101 -> 101 : 5
     * 6: 110 -> 011 : 3
     * 7: 111 -> 111 : 7
     */

    complex_f src[8] = {
        { 1.f, -1.f},
        { 2.f, -2.f},
        { 3.f, -3.f},
        { 4.f, -4.f},
        { 5.f, -5.f},
        { 6.f, -6.f},
        { 7.f, -7.f},
        { 8.f, -8.f}
    };
    complex_f dst[8];
    int i;

    for (i = 0; i < 8; i++)
    {
        dst[i] = src[i];
    }

    ffti_copy_shuffle_f(src, dst, 3);  /* 3 = log2(8) */

    ck_assert_flt_eq(dst[0].re, 1.f);
    ck_assert_flt_eq(dst[0].im, -1.f);

    ck_assert_flt_eq(dst[1].re, 5.f);
    ck_assert_flt_eq(dst[1].im, -5.f);

    ck_assert_flt_eq(dst[2].re, 3.f);
    ck_assert_flt_eq(dst[2].im, -3.f);

    ck_assert_flt_eq(dst[3].re, 7.f);
    ck_assert_flt_eq(dst[3].im, -7.f);

    ck_assert_flt_eq(dst[4].re, 2.f);
    ck_assert_flt_eq(dst[4].im, -2.f);

    ck_assert_flt_eq(dst[5].re, 6.f);
    ck_assert_flt_eq(dst[5].im, -6.f);

    ck_assert_flt_eq(dst[6].re, 4.f);
    ck_assert_flt_eq(dst[6].im, -4.f);

    ck_assert_flt_eq(dst[7].re, 8.f);
    ck_assert_flt_eq(dst[7].im, -8.f);
}
END_TEST

START_TEST (ffti_copy_shuffle_f_copies_sixteen_shuffled_values)
{
    /*
     * 00: 0000 -> 0000 : 00
     * 01: 0001 -> 1000 : 08
     * 02: 0010 -> 0100 : 04
     * 03: 0011 -> 1100 : 12
     * 04: 0100 -> 0010 : 02
     * 05: 0101 -> 1010 : 10
     * 06: 0110 -> 0110 : 06
     * 07: 0111 -> 1110 : 14
     * 08: 1000 -> 0001 : 01
     * 09: 1001 -> 1001 : 09
     * 10: 1010 -> 0101 : 05
     * 11: 1011 -> 1101 : 13
     * 12: 1100 -> 0011 : 03
     * 13: 1101 -> 1011 : 11
     * 14: 1110 -> 0111 : 07
     * 15: 1111 -> 1111 : 15
     */

    complex_f src[16] = {
        { 1.f, -1.f},
        { 2.f, -2.f},
        { 3.f, -3.f},
        { 4.f, -4.f},
        { 5.f, -5.f},
        { 6.f, -6.f},
        { 7.f, -7.f},
        { 8.f, -8.f},
        { 9.f, -9.f},
        { 10.f, -10.f},
        { 11.f, -11.f},
        { 12.f, -12.f},
        { 13.f, -13.f},
        { 14.f, -14.f},
        { 15.f, -15.f},
        { 16.f, -16.f}
    };
    complex_f dst[16];
    int i;

    for (i = 0; i < 16; i++)
    {
        dst[i] = src[i];
    }

    ffti_copy_shuffle_f(src, dst, 4);  /* 4 = log2(16) */

    ck_assert_flt_eq(dst[0].re, 1.f);
    ck_assert_flt_eq(dst[0].im, -1.f);

    ck_assert_flt_eq(dst[1].re, 9.f);
    ck_assert_flt_eq(dst[1].im, -9.f);

    ck_assert_flt_eq(dst[2].re, 5.f);
    ck_assert_flt_eq(dst[2].im, -5.f);

    ck_assert_flt_eq(dst[3].re, 13.f);
    ck_assert_flt_eq(dst[3].im, -13.f);

    ck_assert_flt_eq(dst[4].re, 3.f);
    ck_assert_flt_eq(dst[4].im, -3.f);

    ck_assert_flt_eq(dst[5].re, 11.f);
    ck_assert_flt_eq(dst[5].im, -11.f);

    ck_assert_flt_eq(dst[6].re, 7.f);
    ck_assert_flt_eq(dst[6].im, -7.f);

    ck_assert_flt_eq(dst[7].re, 15.f);
    ck_assert_flt_eq(dst[7].im, -15.f);

    ck_assert_flt_eq(dst[8].re, 2.f);
    ck_assert_flt_eq(dst[8].im, -2.f);

    ck_assert_flt_eq(dst[9].re, 10.f);
    ck_assert_flt_eq(dst[9].im, -10.f);

    ck_assert_flt_eq(dst[10].re, 6.f);
    ck_assert_flt_eq(dst[10].im, -6.f);

    ck_assert_flt_eq(dst[11].re, 14.f);
    ck_assert_flt_eq(dst[11].im, -14.f);

    ck_assert_flt_eq(dst[12].re, 4.f);
    ck_assert_flt_eq(dst[12].im, -4.f);

    ck_assert_flt_eq(dst[13].re, 12.f);
    ck_assert_flt_eq(dst[13].im, -12.f);

    ck_assert_flt_eq(dst[14].re, 8.f);
    ck_assert_flt_eq(dst[14].im, -8.f);

    ck_assert_flt_eq(dst[15].re, 16.f);
    ck_assert_flt_eq(dst[15].im, -16.f);
}
END_TEST

/* ===== ffti_evaluate_f() ================================================== */

START_TEST (ffti_evaluate_f_performs_8pt_dft)
{
    complex_f f_t[8] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    complex_f data[8];
    int i;

    ffti_copy_shuffle_f(f_t, data, 3);  /* 3 = log2(8) */

    ffti_evaluate_f(data, 3, FFT_FORWARD);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_evaluate_f_performs_8pt_inverse_dft)
{
    complex_f F_w[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    complex_f expected_f_t_N[8] = {
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f data[8];
    int i;

    ffti_copy_shuffle_f(F_w, data, 3);  /* 3 = log2(8) */

    ffti_evaluate_f(data, 3, FFT_INVERSE);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_evaluate_f_performs_16pt_dft)
{
    complex_f f_t[16] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[16] = {
        { 5.000000f , 0.000000f },
        { 3.013670f , -3.013670f },
        { 0.000000f , -2.414214f },
        { -0.248303f , -0.248303f },
        { 1.000000f , 0.000000f },
        { 0.834089f , -0.834089f },
        { 0.000000f , -0.414214f },
        { 0.400544f , 0.400544f },
        { 1.000000f , 0.000000f },
        { 0.400544f , -0.400544f },
        { 0.000000f , 0.414214f },
        { 0.834089f , 0.834089f },
        { 1.000000f , 0.000000f },
        { -0.248303f , 0.248303f },
        { 0.000000f , 2.414214f },
        { 3.013670f , 3.013670f }
    };
    complex_f data[16];
    int i;

    ffti_copy_shuffle_f(f_t, data, 4);  /* 4 = log2(16) */

    ffti_evaluate_f(data, 4, FFT_FORWARD);  /* 4 = log2(16) */

    for (i = 0; i < 16; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_evaluate_f_performs_16pt_inverse_dft)
{
    complex_f F_w[16] = {
        { 5.000000f , 0.000000f },
        { 3.013670f , -3.013670f },
        { 0.000000f , -2.414214f },
        { -0.248303f , -0.248303f },
        { 1.000000f , 0.000000f },
        { 0.834089f , -0.834089f },
        { 0.000000f , -0.414214f },
        { 0.400544f , 0.400544f },
        { 1.000000f , 0.000000f },
        { 0.400544f , -0.400544f },
        { 0.000000f , 0.414214f },
        { 0.834089f , 0.834089f },
        { 1.000000f , 0.000000f },
        { -0.248303f , 0.248303f },
        { 0.000000f , 2.414214f },
        { 3.013670f , 3.013670f }
    };
    complex_f expected_f_t_N[16] = {
        { 16.0f , 0.0f },
        { 16.0f , 0.0f },
        { 16.0f , 0.0f },
        { 16.0f , 0.0f },
        { 16.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f data[16];
    int i;

    ffti_copy_shuffle_f(F_w, data, 4);  /* 4 = log2(16) */

    ffti_evaluate_f(data, 4, FFT_INVERSE);  /* 4 = log2(16) */

    for (i = 0; i < 16; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

/* ===== ffti_f() =========================================================== */

START_TEST (ffti_f_performs_4pt_inplace_DFT)
{
    complex_f data[4] = {
        { 1.0f , 0.0f },
        { 2.0f , 0.0f },
        { 3.0f , 0.0f },
        { 4.0f , 0.0f }
    };
    complex_f expected_F_w[4] = {
        { 10.0f , 0.0f },
        { -2.0f , 2.0f },
        { -2.0f , 0.0f },
        { -2.0f , -2.0f }
    };
    int i;

    ffti_f(data, 2, FFT_FORWARD);  /* 2 = log2(4) */

    for (i = 0; i < 4; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_f_performs_4pt_inplace_inverse_DFT)
{
    complex_f data[4] = {
        { 10.0f , 0.0f },
        { -2.0f , 2.0f },
        { -2.0f , 0.0f },
        { -2.0f , -2.0f }
    };
    complex_f expected_f_t_N[4] = {
        { 4.0f , 0.0f },
        { 8.0f , 0.0f },
        { 12.0f , 0.0f },
        { 16.0f , 0.0f }
    };
    int i;

    ffti_f(data, 2, FFT_INVERSE);  /* 2 = log2(4) */

    for (i = 0; i < 4; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_f_performs_8pt_inplace_DFT)
{
    complex_f data[8] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    int i;

    ffti_f(data, 3, FFT_FORWARD);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_f_performs_8pt_inplace_inverse_DFT)
{
    complex_f data[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    complex_f expected_f_t_N[8] = {
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    int i;

    ffti_f(data, 3, FFT_INVERSE);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_f_performs_32pt_inplace_DFT)
{
    complex_f data[32] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[32] = {
        { 5.000000f , 0.000000f },
        { 4.443241f , -1.840451f },
        { 3.013670f , -3.013670f },
        { 1.311956f , -3.167342f },
        { 0.000000f , -2.414214f },
        { -0.515005f , -1.243333f },
        { -0.248303f , -0.248303f },
        { 0.422747f , 0.175108f },
        { 1.000000f , 0.000000f },
        { 1.143707f , -0.473739f },
        { 0.834089f , -0.834089f },
        { 0.335425f , -0.809787f },
        { 0.000000f , -0.414214f },
        { 0.039197f , 0.094631f },
        { 0.400544f , 0.400544f },
        { 0.818731f , 0.339130f },
        { 1.000000f , 0.000000f },
        { 0.818731f , -0.339130f },
        { 0.400544f , -0.400544f },
        { 0.039197f , -0.094631f },
        { 0.000000f , 0.414214f },
        { 0.335425f , 0.809787f },
        { 0.834089f , 0.834089f },
        { 1.143707f , 0.473739f },
        { 1.000000f , 0.000000f },
        { 0.422747f , -0.175108f },
        { -0.248303f , 0.248303f },
        { -0.515005f , 1.243333f },
        { 0.000000f , 2.414214f },
        { 1.311956f , 3.167342f },
        { 3.013670f , 3.013670f },
        { 4.443241f , 1.840451f }
    };
    int i;

    ffti_f(data, 5, FFT_FORWARD);  /* 5 = log2(32) */

    for (i = 0; i < 32; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (ffti_f_performs_32pt_inplace_inverse_DFT)
{
    complex_f data[32] = {
        { 5.000000f , 0.000000f },
        { 4.443241f , -1.840451f },
        { 3.013670f , -3.013670f },
        { 1.311956f , -3.167342f },
        { 0.000000f , -2.414214f },
        { -0.515005f , -1.243333f },
        { -0.248303f , -0.248303f },
        { 0.422747f , 0.175108f },
        { 1.000000f , 0.000000f },
        { 1.143707f , -0.473739f },
        { 0.834089f , -0.834089f },
        { 0.335425f , -0.809787f },
        { 0.000000f , -0.414214f },
        { 0.039197f , 0.094631f },
        { 0.400544f , 0.400544f },
        { 0.818731f , 0.339130f },
        { 1.000000f , 0.000000f },
        { 0.818731f , -0.339130f },
        { 0.400544f , -0.400544f },
        { 0.039197f , -0.094631f },
        { 0.000000f , 0.414214f },
        { 0.335425f , 0.809787f },
        { 0.834089f , 0.834089f },
        { 1.143707f , 0.473739f },
        { 1.000000f , 0.000000f },
        { 0.422747f , -0.175108f },
        { -0.248303f , 0.248303f },
        { -0.515005f , 1.243333f },
        { 0.000000f , 2.414214f },
        { 1.311956f , 3.167342f },
        { 3.013670f , 3.013670f },
        { 4.443241f , 1.840451f }
    };
    complex_f expected_f_t_N[32] = {
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    int i;

    ffti_f(data, 5, FFT_INVERSE);  /* 5 = log2(32) */

    for (i = 0; i < 32; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

/* ===== fftr_f() =========================================================== */

START_TEST (fftr_f_performs_4pt_recursive_DFT)
{
    complex_f data[4] = {
        { 1.0f , 0.0f },
        { 2.0f , 0.0f },
        { 3.0f , 0.0f },
        { 4.0f , 0.0f }
    };
    complex_f expected_F_w[4] = {
        { 10.0f , 0.0f },
        { -2.0f , 2.0f },
        { -2.0f , 0.0f },
        { -2.0f , -2.0f }
    };
    int i;

    fftr_f(data, 2, FFT_FORWARD);  /* 2 = log2(4) */

    for (i = 0; i < 4; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftr_f_performs_4pt_recursive_inverse_DFT)
{
    complex_f data[4] = {
        { 10.0f , 0.0f },
        { -2.0f , 2.0f },
        { -2.0f , 0.0f },
        { -2.0f , -2.0f }
    };
    complex_f expected_f_t_N[4] = {
        { 4.0f , 0.0f },
        { 8.0f , 0.0f },
        { 12.0f , 0.0f },
        { 16.0f , 0.0f }
    };
    int i;

    fftr_f(data, 2, FFT_INVERSE);  /* 2 = log2(4) */

    for (i = 0; i < 4; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftr_f_performs_8pt_recursive_DFT)
{
    complex_f data[8] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    int i;

    fftr_f(data, 3, FFT_FORWARD);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftr_f_performs_8pt_recursive_inverse_DFT)
{
    complex_f data[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    complex_f expected_f_t_N[8] = {
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    int i;

    fftr_f(data, 3, FFT_INVERSE);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftr_f_performs_32pt_recursive_DFT)
{
    complex_f data[32] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[32] = {
        { 5.000000f , 0.000000f },
        { 4.443241f , -1.840451f },
        { 3.013670f , -3.013670f },
        { 1.311956f , -3.167342f },
        { 0.000000f , -2.414214f },
        { -0.515005f , -1.243333f },
        { -0.248303f , -0.248303f },
        { 0.422747f , 0.175108f },
        { 1.000000f , 0.000000f },
        { 1.143707f , -0.473739f },
        { 0.834089f , -0.834089f },
        { 0.335425f , -0.809787f },
        { 0.000000f , -0.414214f },
        { 0.039197f , 0.094631f },
        { 0.400544f , 0.400544f },
        { 0.818731f , 0.339130f },
        { 1.000000f , 0.000000f },
        { 0.818731f , -0.339130f },
        { 0.400544f , -0.400544f },
        { 0.039197f , -0.094631f },
        { 0.000000f , 0.414214f },
        { 0.335425f , 0.809787f },
        { 0.834089f , 0.834089f },
        { 1.143707f , 0.473739f },
        { 1.000000f , 0.000000f },
        { 0.422747f , -0.175108f },
        { -0.248303f , 0.248303f },
        { -0.515005f , 1.243333f },
        { 0.000000f , 2.414214f },
        { 1.311956f , 3.167342f },
        { 3.013670f , 3.013670f },
        { 4.443241f , 1.840451f }
    };
    int i;

    fftr_f(data, 5, FFT_FORWARD);  /* 5 = log2(32) */

    for (i = 0; i < 32; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftr_f_performs_32pt_recursive_inverse_DFT)
{
    complex_f data[32] = {
        { 5.000000f , 0.000000f },
        { 4.443241f , -1.840451f },
        { 3.013670f , -3.013670f },
        { 1.311956f , -3.167342f },
        { 0.000000f , -2.414214f },
        { -0.515005f , -1.243333f },
        { -0.248303f , -0.248303f },
        { 0.422747f , 0.175108f },
        { 1.000000f , 0.000000f },
        { 1.143707f , -0.473739f },
        { 0.834089f , -0.834089f },
        { 0.335425f , -0.809787f },
        { 0.000000f , -0.414214f },
        { 0.039197f , 0.094631f },
        { 0.400544f , 0.400544f },
        { 0.818731f , 0.339130f },
        { 1.000000f , 0.000000f },
        { 0.818731f , -0.339130f },
        { 0.400544f , -0.400544f },
        { 0.039197f , -0.094631f },
        { 0.000000f , 0.414214f },
        { 0.335425f , 0.809787f },
        { 0.834089f , 0.834089f },
        { 1.143707f , 0.473739f },
        { 1.000000f , 0.000000f },
        { 0.422747f , -0.175108f },
        { -0.248303f , 0.248303f },
        { -0.515005f , 1.243333f },
        { 0.000000f , 2.414214f },
        { 1.311956f , 3.167342f },
        { 3.013670f , 3.013670f },
        { 4.443241f , 1.840451f }
    };
    complex_f expected_f_t_N[32] = {
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    int i;

    fftr_f(data, 5, FFT_INVERSE);  /* 5 = log2(32) */

    for (i = 0; i < 32; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

/* ===== fftrb_f() =========================================================== */

START_TEST (fftrb_f_performs_4pt_recursive_DFT)
{
    complex_f data[4] = {
        { 1.0f , 0.0f },
        { 2.0f , 0.0f },
        { 3.0f , 0.0f },
        { 4.0f , 0.0f }
    };
    complex_f expected_F_w[4] = {
        { 10.0f , 0.0f },
        { -2.0f , 2.0f },
        { -2.0f , 0.0f },
        { -2.0f , -2.0f }
    };
    complex_f scratch[4];
    int i;

    fftrb_f(data, 2, FFT_FORWARD, scratch);  /* 2 = log2(4) */

    for (i = 0; i < 4; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftrb_f_performs_4pt_recursive_inverse_DFT)
{
    complex_f data[4] = {
        { 10.0f , 0.0f },
        { -2.0f , 2.0f },
        { -2.0f , 0.0f },
        { -2.0f , -2.0f }
    };
    complex_f expected_f_t_N[4] = {
        { 4.0f , 0.0f },
        { 8.0f , 0.0f },
        { 12.0f , 0.0f },
        { 16.0f , 0.0f }
    };
    complex_f scratch[4];
    int i;

    fftrb_f(data, 2, FFT_INVERSE, scratch);  /* 2 = log2(4) */

    for (i = 0; i < 4; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftrb_f_performs_8pt_recursive_DFT)
{
    complex_f data[8] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    complex_f scratch[8];
    int i;

    fftrb_f(data, 3, FFT_FORWARD, scratch);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftrb_f_performs_8pt_recursive_inverse_DFT)
{
    complex_f data[8] = {
        { 5.0f , 0.000000f },
        { 0.0f , -2.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , -0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 0.414214f },
        { 1.0f , 0.000000f },
        { 0.0f , 2.414214f }
    };
    complex_f expected_f_t_N[8] = {
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 8.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f scratch[8];
    int i;

    fftrb_f(data, 3, FFT_INVERSE, scratch);  /* 3 = log2(8) */

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftrb_f_performs_32pt_recursive_DFT)
{
    complex_f data[32] = {
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 1.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f expected_F_w[32] = {
        { 5.000000f , 0.000000f },
        { 4.443241f , -1.840451f },
        { 3.013670f , -3.013670f },
        { 1.311956f , -3.167342f },
        { 0.000000f , -2.414214f },
        { -0.515005f , -1.243333f },
        { -0.248303f , -0.248303f },
        { 0.422747f , 0.175108f },
        { 1.000000f , 0.000000f },
        { 1.143707f , -0.473739f },
        { 0.834089f , -0.834089f },
        { 0.335425f , -0.809787f },
        { 0.000000f , -0.414214f },
        { 0.039197f , 0.094631f },
        { 0.400544f , 0.400544f },
        { 0.818731f , 0.339130f },
        { 1.000000f , 0.000000f },
        { 0.818731f , -0.339130f },
        { 0.400544f , -0.400544f },
        { 0.039197f , -0.094631f },
        { 0.000000f , 0.414214f },
        { 0.335425f , 0.809787f },
        { 0.834089f , 0.834089f },
        { 1.143707f , 0.473739f },
        { 1.000000f , 0.000000f },
        { 0.422747f , -0.175108f },
        { -0.248303f , 0.248303f },
        { -0.515005f , 1.243333f },
        { 0.000000f , 2.414214f },
        { 1.311956f , 3.167342f },
        { 3.013670f , 3.013670f },
        { 4.443241f , 1.840451f }
    };
    complex_f scratch[32];
    int i;

    fftrb_f(data, 5, FFT_FORWARD, scratch);  /* 5 = log2(32) */

    for (i = 0; i < 32; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_F_w[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_F_w[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

START_TEST (fftrb_f_performs_32pt_recursive_inverse_DFT)
{

    complex_f data[32] = {
        { 5.000000f , 0.000000f },
        { 4.443241f , -1.840451f },
        { 3.013670f , -3.013670f },
        { 1.311956f , -3.167342f },
        { 0.000000f , -2.414214f },
        { -0.515005f , -1.243333f },
        { -0.248303f , -0.248303f },
        { 0.422747f , 0.175108f },
        { 1.000000f , 0.000000f },
        { 1.143707f , -0.473739f },
        { 0.834089f , -0.834089f },
        { 0.335425f , -0.809787f },
        { 0.000000f , -0.414214f },
        { 0.039197f , 0.094631f },
        { 0.400544f , 0.400544f },
        { 0.818731f , 0.339130f },
        { 1.000000f , 0.000000f },
        { 0.818731f , -0.339130f },
        { 0.400544f , -0.400544f },
        { 0.039197f , -0.094631f },
        { 0.000000f , 0.414214f },
        { 0.335425f , 0.809787f },
        { 0.834089f , 0.834089f },
        { 1.143707f , 0.473739f },
        { 1.000000f , 0.000000f },
        { 0.422747f , -0.175108f },
        { -0.248303f , 0.248303f },
        { -0.515005f , 1.243333f },
        { 0.000000f , 2.414214f },
        { 1.311956f , 3.167342f },
        { 3.013670f , 3.013670f },
        { 4.443241f , 1.840451f }
    };
    complex_f expected_f_t_N[32] = {
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 32.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f },
        { 0.0f , 0.0f }
    };
    complex_f scratch[32];
    int i;

    fftrb_f(data, 5, FFT_INVERSE, scratch);  /* 5 = log2(32) */

    for (i = 0; i < 32; i++)
    {
        ck_assert_flt_eq_eps(data[i].re, expected_f_t_N[i].re, FLOAT_EQ_TOLERANCE);
        ck_assert_flt_eq_eps(data[i].im, expected_f_t_N[i].im, FLOAT_EQ_TOLERANCE);
    }
}
END_TEST

/* ===== Test Suite ========================================================= */

Suite * unit_test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("fft");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, ffti_shuffle_f_shuffles_four_values);
    tcase_add_test(tc_core, ffti_shuffle_f_shuffles_eight_values);
    tcase_add_test(tc_core, ffti_shuffle_f_shuffles_sixteen_values);

    tcase_add_test(tc_core, ffti_copy_shuffle_f_copies_four_shuffled_values);
    tcase_add_test(tc_core, ffti_copy_shuffle_f_copies_eight_shuffled_values);
    tcase_add_test(tc_core, ffti_copy_shuffle_f_copies_sixteen_shuffled_values);

    tcase_add_test(tc_core, ffti_evaluate_f_performs_8pt_dft);
    tcase_add_test(tc_core, ffti_evaluate_f_performs_8pt_inverse_dft);
    tcase_add_test(tc_core, ffti_evaluate_f_performs_16pt_dft);
    tcase_add_test(tc_core, ffti_evaluate_f_performs_16pt_inverse_dft);

    tcase_add_test(tc_core, ffti_f_performs_4pt_inplace_DFT);
    tcase_add_test(tc_core, ffti_f_performs_4pt_inplace_inverse_DFT);
    tcase_add_test(tc_core, ffti_f_performs_8pt_inplace_DFT);
    tcase_add_test(tc_core, ffti_f_performs_8pt_inplace_inverse_DFT);
    tcase_add_test(tc_core, ffti_f_performs_32pt_inplace_DFT);
    tcase_add_test(tc_core, ffti_f_performs_32pt_inplace_inverse_DFT);

    tcase_add_test(tc_core, fftr_f_performs_4pt_recursive_DFT);
    tcase_add_test(tc_core, fftr_f_performs_4pt_recursive_inverse_DFT);
    tcase_add_test(tc_core, fftr_f_performs_8pt_recursive_DFT);
    tcase_add_test(tc_core, fftr_f_performs_8pt_recursive_inverse_DFT);
    tcase_add_test(tc_core, fftr_f_performs_32pt_recursive_DFT);
    tcase_add_test(tc_core, fftr_f_performs_32pt_recursive_inverse_DFT);

    tcase_add_test(tc_core, fftrb_f_performs_4pt_recursive_DFT);
    tcase_add_test(tc_core, fftrb_f_performs_4pt_recursive_inverse_DFT);
    tcase_add_test(tc_core, fftrb_f_performs_8pt_recursive_DFT);
    tcase_add_test(tc_core, fftrb_f_performs_8pt_recursive_inverse_DFT);
    tcase_add_test(tc_core, fftrb_f_performs_32pt_recursive_DFT);
    tcase_add_test(tc_core, fftrb_f_performs_32pt_recursive_inverse_DFT);

    suite_add_tcase(s, tc_core);

    return s;
}

/* ===== Test Driver ======================================================== */

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    putchar('\n');
    puts("-------------------------------------------------------------------------------");

    s = unit_test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    puts("-------------------------------------------------------------------------------");
    putchar('\n');

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

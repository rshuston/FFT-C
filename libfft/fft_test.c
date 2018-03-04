#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "checkext.h"

#include "fft.h"

/* ===== __log2_u() ========================================================= */

unsigned __log2_u(unsigned v);

START_TEST (__log2_u_1)
{
    unsigned log = __log2_u(1);

    ck_assert_uint_eq(log, 0);
}
END_TEST

START_TEST (__log2_u_2)
{
    unsigned log = __log2_u(2);

    ck_assert_uint_eq(log, 1);
}
END_TEST

START_TEST (__log2_u_4)
{
    unsigned log = __log2_u(4);

    ck_assert_uint_eq(log, 2);
}
END_TEST

START_TEST (__log2_u_1024)
{
    unsigned log = __log2_u(1024);

    ck_assert_uint_eq(log, 10);
}
END_TEST

START_TEST (__log2_u_65536)
{
    unsigned log = __log2_u(65536);

    ck_assert_uint_eq(log, 16);
}
END_TEST

/* ===== fft_shuffle_f() ==================================================== */

START_TEST (fft_shuffle_f_shuffles_four_values)
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

    fft_shuffle_f(data, 4);

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

START_TEST (fft_shuffle_f_shuffles_eight_values)
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

    fft_shuffle_f(data, 8);

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

START_TEST (fft_shuffle_f_shuffles_sixteen_values)
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

    fft_shuffle_f(data, 16);

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

/* ===== fft_copy_shuffle_f() =============================================== */

START_TEST (fft_copy_shuffle_f_copies_four_shuffled_values)
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

    fft_copy_shuffle_f(src, dst, 4);

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

START_TEST (fft_copy_shuffle_f_copies_eight_shuffled_values)
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

    fft_copy_shuffle_f(src, dst, 8);

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

START_TEST (fft_copy_shuffle_f_copies_sixteen_shuffled_values)
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

    fft_copy_shuffle_f(src, dst, 16);

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

/* ===== fft_evaluate_f() =================================================== */

START_TEST (fft_evaluate_f_performs_8pt_dft)
{
    complex_f f_t[8] = {
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f }
    };
    complex_f expected_F_w[8] = {
        { 5.000000f , 0.000000f },
        { 0.000000f , -2.414214f },
        { 1.000000f , 0.000000f },
        { 0.000000f , -0.414214f },
        { 1.000000f , 0.000000f },
        { -0.000000f , 0.414214f },
        { 1.000000f , 0.000000f },
        { -0.000000f , 2.414214f }
    };
    complex_f data[8];
    int i;

    fft_copy_shuffle_f(f_t, data, 8);

    fft_evaluate_f(data, 8);

    for (i = 0; i < 8; i++)
    {
        ck_assert_flt_eq(data[i].re, expected_F_w[i].re);
        ck_assert_flt_eq(data[i].im, expected_F_w[i].im);
    }
}
END_TEST

START_TEST (fft_evaluate_f_performs_16pt_dft)
{
    complex_f f_t[16] = {
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f }
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
        { -0.000000f , 0.414214f },
        { 0.834089f , 0.834089f },
        { 1.000000f , 0.000000f },
        { -0.248303f , 0.248303f },
        { -0.000000f , 2.414214f },
        { 3.013670f , 3.013670f }
    };
    complex_f data[16];
    int i;

    fft_copy_shuffle_f(f_t, data, 16);

    fft_evaluate_f(data, 16);

    for (i = 0; i < 16; i++)
    {
        ck_assert_flt_eq(data[i].re, expected_F_w[i].re);
        ck_assert_flt_eq(data[i].im, expected_F_w[i].im);
    }
}
END_TEST

/* ===== fft_f() ============================================================ */

START_TEST (fft_f_performs_32pt_inplace_DFT)
{
    complex_f data[32] = {
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 1.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f },
        { 0.000000f , 0.0f }
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
        { -0.000000f , 0.414214f },
        { 0.335425f , 0.809787f },
        { 0.834089f , 0.834089f },
        { 1.143707f , 0.473739f },
        { 1.000000f , 0.000000f },
        { 0.422747f , -0.175108f },
        { -0.248303f , 0.248303f },
        { -0.515005f , 1.243333f },
        { -0.000000f , 2.414214f },
        { 1.311956f , 3.167342f },
        { 3.013670f , 3.013670f },
        { 4.443241f , 1.840451f }
    };
    int i;

    fft_f(data, 32);

    for (i = 0; i < 32; i++)
    {
        ck_assert_flt_eq(data[i].re, expected_F_w[i].re);
        ck_assert_flt_eq(data[i].im, expected_F_w[i].im);
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

    tcase_add_test(tc_core, __log2_u_1);
    tcase_add_test(tc_core, __log2_u_2);
    tcase_add_test(tc_core, __log2_u_4);
    tcase_add_test(tc_core, __log2_u_1024);
    tcase_add_test(tc_core, __log2_u_65536);

    tcase_add_test(tc_core, fft_shuffle_f_shuffles_four_values);
    tcase_add_test(tc_core, fft_shuffle_f_shuffles_eight_values);
    tcase_add_test(tc_core, fft_shuffle_f_shuffles_sixteen_values);

    tcase_add_test(tc_core, fft_copy_shuffle_f_copies_four_shuffled_values);
    tcase_add_test(tc_core, fft_copy_shuffle_f_copies_eight_shuffled_values);
    tcase_add_test(tc_core, fft_copy_shuffle_f_copies_sixteen_shuffled_values);

    tcase_add_test(tc_core, fft_evaluate_f_performs_8pt_dft);
    tcase_add_test(tc_core, fft_evaluate_f_performs_16pt_dft);

    tcase_add_test(tc_core, fft_f_performs_32pt_inplace_DFT);

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

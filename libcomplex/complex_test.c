#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "checkext.h"

#include "complex.h"

/* ===== complex_mul_re() =================================================== */

START_TEST (test_complex_mul_re_multiplies_two_complex_f_numbers)
{
    complex_f z1 = { 2.0f, 3.0f };
    complex_f z2 = { 4.0f, 5.0f };
    complex_f z3;

    z3.re = complex_mul_re(z1.re, z1.im, z2.re, z2.im);
    z3.im = 0.0f;

    ck_assert_flt_eq(z3.re, -7.0f);
}
END_TEST

START_TEST (test_complex_mul_re_multiplies_two_more_complex_f_numbers)
{
    complex_f z1 = { 2.0f, -3.0f };
    complex_f z2 = { 4.0f, 5.0f };
    complex_f z3;

    z3.re = complex_mul_re(z1.re, z1.im, z2.re, z2.im);
    z3.im = 0.0f;

    ck_assert_flt_eq(z3.re, 23.0f);
}
END_TEST

START_TEST (test_complex_mul_re_multiplies_complex_f_and_complex_d_numbers)
{
    complex_f z1 = { 2.0f, -3.0f };
    complex_d z2 = { 4.0, 5.0 };
    complex_d z3;

    z3.re = complex_mul_re(z1.re, z1.im, z2.re, z2.im);
    z3.im = 0.0;

    ck_assert_dbl_eq(z3.re, 23.0);
}
END_TEST

/* ===== complex_mul_im() =================================================== */

START_TEST (test_complex_mul_im_multiplies_two_complex_f_numbers)
{
    complex_f z1 = { 2.0f, 3.0f };
    complex_f z2 = { 4.0f, 5.0f };
    complex_f z3;

    z3.re = 0.0f;
    z3.im = complex_mul_im(z1.re, z1.im, z2.re, z2.im);

    ck_assert_flt_eq(z3.im, 22.0f);
}
END_TEST

START_TEST (test_complex_mul_im_multiplies_two_more_complex_f_numbers)
{
    complex_f z1 = { 2.0f, -3.0f };
    complex_f z2 = { 4.0f, 5.0f };
    complex_f z3;

    z3.re = 0.0f;
    z3.im = complex_mul_im(z1.re, z1.im, z2.re, z2.im);

    ck_assert_flt_eq(z3.im, -2.0f);
}
END_TEST

START_TEST (test_complex_mul_im_multiplies_complex_f_and_complex_d_numbers)
{
    complex_f z1 = { 2.0f, -3.0f };
    complex_d z2 = { 4.0, 5.0 };
    complex_d z3;

    z3.re = 0.0;
    z3.im = complex_mul_im(z1.re, z1.im, z2.re, z2.im);

    ck_assert_dbl_eq(z3.im, -2.0);
}
END_TEST

/* ===== Test Suite ========================================================= */

Suite * unit_test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("complex");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_complex_mul_re_multiplies_two_complex_f_numbers);
    tcase_add_test(tc_core, test_complex_mul_re_multiplies_two_more_complex_f_numbers);
    tcase_add_test(tc_core, test_complex_mul_re_multiplies_complex_f_and_complex_d_numbers);

    tcase_add_test(tc_core, test_complex_mul_im_multiplies_two_complex_f_numbers);
    tcase_add_test(tc_core, test_complex_mul_im_multiplies_two_more_complex_f_numbers);
    tcase_add_test(tc_core, test_complex_mul_im_multiplies_complex_f_and_complex_d_numbers);

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

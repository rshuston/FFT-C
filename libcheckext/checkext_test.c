#include <stdio.h>
#include <stdlib.h>

#include <check.h>

#include "checkext.h"

/* ===== "Check" extensions ================================================= */

START_TEST (test_ck_assert_flt_extensions)
{
    float   x;
    float   y;

    /* ck_assert_flt_eq */

    x = 1.5;
    y = 1.5;
    ck_assert_flt_eq(x, y);

    x = -1.5;
    y = -1.5;
    ck_assert_flt_eq(x, y);

    x = 1e-7;
    y = x - 1e-6;
    ck_assert_flt_eq(x, y);

    /* ck_assert_flt_ne */

    x = 1.5;
    y = 1.6;
    ck_assert_flt_ne(x, y);

    x = -1.5;
    y = -1.6;
    ck_assert_flt_ne(x, y);

    x = 1.5;
    y = -1.5;
    ck_assert_flt_ne(x, y);

    /* ck_assert_flt_lt */

    x = 1.5;
    y = 1.6;
    ck_assert_flt_lt(x, y);

    x = -1.5;
    y = 1.6;
    ck_assert_flt_lt(x, y);

    /* ck_assert_flt_le */

    x = 1.5;
    y = 1.5;
    ck_assert_flt_le(x, y);

    x = -1.55;
    y = -1.5;
    ck_assert_flt_le(x, y);

    /* ck_assert_flt_gt */

    x = 1.6;
    y = 1.5;
    ck_assert_flt_gt(x, y);

    x = 1.5;
    y = -1.6;
    ck_assert_flt_gt(x, y);

    /* ck_assert_flt_ge */

    x = 1.5;
    y = 1.5;
    ck_assert_flt_ge(x, y);

    x = -1.5;
    y = -1.55;
    ck_assert_flt_ge(x, y);
}
END_TEST

START_TEST (test_ck_assert_flt_extensions_with_epsilon)
{
    float   x;
    float   y;

    /* ck_assert_flt_eq_eps */

    x = 1.5;
    y = 1.55;
    ck_assert_flt_eq_eps(x, y, 0.1);

    x = -1.5;
    y = -1.55;
    ck_assert_flt_eq_eps(x, y, 0.1);

    /* ck_assert_flt_ne_eps */

    x = 1.5;
    y = 1.7;
    ck_assert_flt_ne_eps(x, y, 0.1);

    x = -1.5;
    y = -1.65;
    ck_assert_flt_ne_eps(x, y, 0.1);

    /* ck_assert_flt_lt_eps */

    x = 1.5;
    y = 1.6;
    ck_assert_flt_lt_eps(x, y, 0.1);

    x = -1.5;
    y = 1.6;
    ck_assert_flt_lt_eps(x, y, 0.1);

    /* ck_assert_flt_le_eps */

    x = 1.55;
    y = 1.5;
    ck_assert_flt_le_eps(x, y, 0.1);

    x = -1.55;
    y = -1.5;
    ck_assert_flt_le_eps(x, y, 0.1);

    /* ck_assert_flt_gt_eps */

    x = 1.6;
    y = 1.5;
    ck_assert_flt_gt_eps(x, y, 0.1);

    x = 1.5;
    y = -1.6;
    ck_assert_flt_gt_eps(x, y, 0.1);

    /* ck_assert_flt_ge_eps */

    x = 1.55;
    y = 1.5;
    ck_assert_flt_ge_eps(x, y, 0.1);

    x = -1.5;
    y = -1.55;
    ck_assert_flt_ge_eps(x, y, 0.1);
}
END_TEST

START_TEST (test_ck_assert_dbl_extensions)
{
    double  x;
    double  y;

    /* ck_assert_dbl_eq */

    x = 1.5;
    y = 1.5;
    ck_assert_dbl_eq(x, y);

    x = -1.5;
    y = -1.5;
    ck_assert_dbl_eq(x, y);

    x = 1e-7;
    y = x - 1e-6;
    ck_assert_dbl_eq(x, y);

    /* ck_assert_dbl_ne */

    x = 1.5;
    y = 1.6;
    ck_assert_dbl_ne(x, y);

    x = -1.5;
    y = -1.6;
    ck_assert_dbl_ne(x, y);

    x = 1.5;
    y = -1.5;
    ck_assert_dbl_ne(x, y);

    /* ck_assert_dbl_lt */

    x = 1.5;
    y = 1.6;
    ck_assert_dbl_lt(x, y);

    x = -1.5;
    y = 1.6;
    ck_assert_dbl_lt(x, y);

    /* ck_assert_dbl_le */

    x = 1.5;
    y = 1.5;
    ck_assert_dbl_le(x, y);

    x = -1.55;
    y = -1.5;
    ck_assert_dbl_le(x, y);

    /* ck_assert_dbl_gt */

    x = 1.6;
    y = 1.5;
    ck_assert_dbl_gt(x, y);

    x = 1.5;
    y = -1.6;
    ck_assert_dbl_gt(x, y);

    /* ck_assert_dbl_ge */

    x = 1.5;
    y = 1.5;
    ck_assert_dbl_ge(x, y);

    x = -1.5;
    y = -1.55;
    ck_assert_dbl_ge(x, y);
}
END_TEST

START_TEST (test_ck_assert_dbl_extensions_with_epsilon)
{
    double  x;
    double  y;

    /* ck_assert_dbl_eq_eps */

    x = 1.5;
    y = 1.55;
    ck_assert_dbl_eq_eps(x, y, 0.1);

    x = -1.5;
    y = -1.55;
    ck_assert_dbl_eq_eps(x, y, 0.1);

    /* ck_assert_dbl_ne_eps */

    x = 1.5;
    y = 1.7;
    ck_assert_dbl_ne_eps(x, y, 0.1);

    x = -1.5;
    y = -1.65;
    ck_assert_dbl_ne_eps(x, y, 0.1);

    /* ck_assert_dbl_lt_eps */

    x = 1.5;
    y = 1.6;
    ck_assert_dbl_lt_eps(x, y, 0.1);

    x = -1.5;
    y = 1.6;
    ck_assert_dbl_lt_eps(x, y, 0.1);

    /* ck_assert_dbl_le_eps */

    x = 1.55;
    y = 1.5;
    ck_assert_dbl_le_eps(x, y, 0.1);

    x = -1.55;
    y = -1.5;
    ck_assert_dbl_le_eps(x, y, 0.1);

    /* ck_assert_dbl_gt_eps */

    x = 1.6;
    y = 1.5;
    ck_assert_dbl_gt_eps(x, y, 0.1);

    x = 1.5;
    y = -1.6;
    ck_assert_dbl_gt_eps(x, y, 0.1);

    /* ck_assert_dbl_ge_eps */

    x = 1.55;
    y = 1.5;
    ck_assert_dbl_ge_eps(x, y, 0.1);

    x = -1.5;
    y = -1.55;
    ck_assert_dbl_ge_eps(x, y, 0.1);
}
END_TEST

/* ===== Test Suite ========================================================= */

Suite * unit_test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("checkext");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_ck_assert_flt_extensions);
    tcase_add_test(tc_core, test_ck_assert_flt_extensions_with_epsilon);

    tcase_add_test(tc_core, test_ck_assert_dbl_extensions);
    tcase_add_test(tc_core, test_ck_assert_dbl_extensions_with_epsilon);

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

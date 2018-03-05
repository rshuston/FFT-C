#include <stdio.h>
#include <stdlib.h>

#include <check.h>
#include "checkext.h"

#include "bithacks.h"


/* ===== log2_u() ========================================================= */

START_TEST (log2_u_1)
{
    unsigned log = log2_u(1);

    ck_assert_uint_eq(log, 0);
}
END_TEST

START_TEST (log2_u_2)
{
    unsigned log = log2_u(2);

    ck_assert_uint_eq(log, 1);
}
END_TEST

START_TEST (log2_u_3)
{
    unsigned log = log2_u(3);

    ck_assert_uint_eq(log, 1);
}
END_TEST

START_TEST (log2_u_4)
{
    unsigned log = log2_u(4);

    ck_assert_uint_eq(log, 2);
}
END_TEST

START_TEST (log2_u_5)
{
    unsigned log = log2_u(5);

    ck_assert_uint_eq(log, 2);
}
END_TEST

START_TEST (log2_u_1023)
{
    unsigned log = log2_u(1023);

    ck_assert_uint_eq(log, 9);
}
END_TEST

START_TEST (log2_u_1024)
{
    unsigned log = log2_u(1024);

    ck_assert_uint_eq(log, 10);
}
END_TEST

START_TEST (log2_u_65535)
{
    unsigned log = log2_u(65535);

    ck_assert_uint_eq(log, 15);
}
END_TEST

START_TEST (log2_u_65536)
{
    unsigned log = log2_u(65536);

    ck_assert_uint_eq(log, 16);
}
END_TEST

START_TEST (log2_u_65537)
{
    unsigned log = log2_u(65537);

    ck_assert_uint_eq(log, 16);
}
END_TEST

/* ===== log2_u_p2() ====================================================== */

START_TEST (log2_u_p2_1)
{
    unsigned log = log2_u_p2(1);

    ck_assert_uint_eq(log, 0);
}
END_TEST

START_TEST (log2_u_p2_2)
{
    unsigned log = log2_u_p2(2);

    ck_assert_uint_eq(log, 1);
}
END_TEST

START_TEST (log2_u_p2_4)
{
    unsigned log = log2_u_p2(4);

    ck_assert_uint_eq(log, 2);
}
END_TEST

START_TEST (log2_u_p2_1024)
{
    unsigned log = log2_u_p2(1024);

    ck_assert_uint_eq(log, 10);
}
END_TEST

START_TEST (log2_u_p2_65536)
{
    unsigned log = log2_u_p2(65536);

    ck_assert_uint_eq(log, 16);
}
END_TEST

/* ===== Test Suite ========================================================= */

Suite * unit_test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("bithacks");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, log2_u_1);
    tcase_add_test(tc_core, log2_u_2);
    tcase_add_test(tc_core, log2_u_3);
    tcase_add_test(tc_core, log2_u_4);
    tcase_add_test(tc_core, log2_u_5);
    tcase_add_test(tc_core, log2_u_1023);
    tcase_add_test(tc_core, log2_u_1024);
    tcase_add_test(tc_core, log2_u_65535);
    tcase_add_test(tc_core, log2_u_65536);
    tcase_add_test(tc_core, log2_u_65537);

    tcase_add_test(tc_core, log2_u_p2_1);
    tcase_add_test(tc_core, log2_u_p2_2);
    tcase_add_test(tc_core, log2_u_p2_4);
    tcase_add_test(tc_core, log2_u_p2_1024);
    tcase_add_test(tc_core, log2_u_p2_65536);

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

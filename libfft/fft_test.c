#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>

#include "fft.h"


/* ===== fft_f() ============================================================ */

START_TEST (fft_r_does_something)
{
    ck_assert(1);
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

    tcase_add_test(tc_core, fft_r_does_something);

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

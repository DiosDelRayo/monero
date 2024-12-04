#include <check.h>
#include "../include/ots.h"
#include "../include/version.h"

START_TEST(test_context)
{
    ots_result_t ctx = ots_create_context();
    ck_assert_int_eq(ctx.error.code, 0);
    ots_free_context(&ctx);
}
END_TEST

START_TEST(test_version)
{
    char* version = ots_version();
    ck_assert_str_eq(version, OTS_VERSION_STRING);
    ots_free_version_string(version);
}
END_TEST

Suite* ots_suite(void)
{
    Suite* s = suite_create("OTS");
    TCase* tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_context);
    tcase_add_test(tc_core, test_version);
    suite_add_tcase(s, tc_core);
    
    return s;
}

int main(void)
{
    int number_failed;
    Suite* s = ots_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return number_failed;
}

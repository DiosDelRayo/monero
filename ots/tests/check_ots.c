#include <check.h>
#include "../include/ots.h"
#include "../include/version.h"

START_TEST(test_version)
{
    ots_result_t ctx = ots_create_context();
    ck_assert_int_eq(ctx.error.code, 0);
    ots_free_context(&ctx);
    char* version = ots_version();
    ck_assert_str_eq(version, OTS_VERSION_STRING);
}
END_TEST

// ... more tests

Suite* ots_suite(void)
{
    Suite* s = suite_create("OTS");
    TCase* tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_version);
    suite_add_tcase(s, tc_core);
    
    return s;
}

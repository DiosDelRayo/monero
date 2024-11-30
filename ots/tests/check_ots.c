#include <check.h>
#include "../include/ots.h"

START_TEST(test_seed_to_key)
{
    ots_result_t ctx = ots_create_context(OTS_V1);
    ck_assert_int_eq(ctx.error.code, 0);
    
    ots_free_context(&ctx);
}
END_TEST

// ... more tests

Suite* ots_suite(void)
{
    Suite* s = suite_create("OTS");
    TCase* tc_core = tcase_create("Core");
    
    tcase_add_test(tc_core, test_seed_to_key);
    suite_add_tcase(s, tc_core);
    
    return s;
}

// commit message qemu@bc7c08a2c3 (target=0, prob=0.02278315, correct=True): test-cutils: Clean up qemu_strtoul() result checks
/*0  */ static void test_qemu_strtoull_full_negative(void)      // (2) 0.1439
/*2  */ {                                                       // (7) 0.007576
/*4  */     const char *str = " \t -321";                       // (4) 0.1061
/*6  */     uint64_t res = 999;                                 // (5) 0.08333
/*8  */     int err;                                            // (6) 0.04545
/*12 */     err = qemu_strtoull(str, NULL, 0, &res);            // (1) 0.1742
/*16 */     g_assert_cmpint(err, ==, 0);                        // (3) 0.1212
/*18 */     g_assert_cmpint(res, ==, 18446744073709551295LLU);  // (0) 0.197
/*20 */ }                                                       // (8) 0.007576

// commit message qemu@bc7c08a2c3 (target=0, prob=0.04034035, correct=True): test-cutils: Clean up qemu_strtoul() result checks
/*0  */ static void test_qemu_strtoul_full_negative(void)  // (1) 0.1513
/*2  */ {                                                  // (7) 0.008403
/*4  */     const char *str = " \t -321";                  // (4) 0.1176
/*6  */     unsigned long res = 999;                       // (5) 0.07563
/*8  */     int err;                                       // (6) 0.05042
/*12 */     err = qemu_strtoul(str, NULL, 0, &res);        // (0) 0.1849
/*14 */     g_assert_cmpint(err, ==, 0);                   // (3) 0.1345
/*16 */     g_assert_cmpint(res, ==, -321ul);              // (2) 0.1513
/*18 */ }                                                  // (8) 0.008403

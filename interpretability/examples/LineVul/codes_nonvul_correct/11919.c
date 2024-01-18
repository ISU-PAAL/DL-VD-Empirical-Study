// commit message qemu@bc7c08a2c3 (target=0, prob=0.04645934, correct=True): test-cutils: Clean up qemu_strtoul() result checks
/*0  */ static void test_qemu_strtoul_decimal(void)      // (2) 0.06439
/*2  */ {                                                // (17) 0.003788
/*4  */     const char *str = "0123";                    // (9) 0.04545
/*6  */     char f = 'X';                                // (12) 0.03409
/*8  */     const char *endptr = &f;                     // (10) 0.04545
/*10 */     unsigned long res = 999;                     // (11) 0.03409
/*12 */     int err;                                     // (16) 0.02273
/*16 */     err = qemu_strtoul(str, &endptr, 10, &res);  // (0) 0.09091
/*20 */     g_assert_cmpint(err, ==, 0);                 // (5) 0.06061
/*22 */     g_assert_cmpint(res, ==, 123);               // (6) 0.06061
/*24 */     g_assert(endptr == str + strlen(str));       // (3) 0.06439
/*28 */     str = "123";                                 // (14) 0.0303
/*30 */     res = 999;                                   // (15) 0.02652
/*32 */     endptr = &f;                                 // (13) 0.03409
/*34 */     err = qemu_strtoul(str, &endptr, 0, &res);   // (1) 0.09091
/*38 */     g_assert_cmpint(err, ==, 0);                 // (7) 0.06061
/*40 */     g_assert_cmpint(res, ==, 123);               // (8) 0.06061
/*42 */     g_assert(endptr == str + strlen(str));       // (4) 0.06439
/*44 */ }                                                // (18) 0.003788

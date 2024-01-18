// commit message qemu@bc7c08a2c3 (target=0, prob=0.16580832, correct=True): test-cutils: Clean up qemu_strtoul() result checks
/*0  */ static void test_qemu_strtoull_overflow(void)                          // (3) 0.1017
/*2  */ {                                                                      // (10) 0.00565
/*4  */     const char *str = "99999999999999999999999999999999999999999999";  // (1) 0.1186
/*6  */     char f = 'X';                                                      // (8) 0.05085
/*8  */     const char *endptr = &f;                                           // (6) 0.0678
/*10 */     uint64_t res = 999;                                                // (7) 0.06215
/*12 */     int err;                                                           // (9) 0.0339
/*16 */     err = qemu_strtoull(str, &endptr, 0, &res);                        // (0) 0.1412
/*20 */     g_assert_cmpint(err, ==, -ERANGE);                                 // (4) 0.1017
/*22 */     g_assert_cmpint(res, ==, ULLONG_MAX);                              // (2) 0.113
/*24 */     g_assert(endptr == str + strlen(str));                             // (5) 0.09605
/*26 */ }                                                                      // (11) 0.00565

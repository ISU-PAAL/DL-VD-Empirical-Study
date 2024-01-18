// commit message qemu@47d4be12c3 (target=1, prob=0.45158035, correct=False): cutils: work around platform differences in strto{l,ul,ll,ull}
/*0  */ static void test_qemu_strtoll_whitespace(void)  // (1) 0.1132
/*2  */ {                                               // (10) 0.006289
/*4  */     const char *str = "  \t  ";                 // (4) 0.09434
/*6  */     char f = 'X';                               // (8) 0.0566
/*8  */     const char *endptr = &f;                    // (5) 0.07547
/*10 */     int64_t res = 999;                          // (7) 0.06918
/*12 */     int err;                                    // (9) 0.03774
/*16 */     err = qemu_strtoll(str, &endptr, 0, &res);  // (0) 0.1509
/*20 */     g_assert_cmpint(err, ==, 0);                // (2) 0.1006
/*22 */     g_assert_cmpint(res, ==, 0);                // (3) 0.1006
/*24 */     g_assert(endptr == str);                    // (6) 0.07547
/*26 */ }                                               // (11) 0.006289

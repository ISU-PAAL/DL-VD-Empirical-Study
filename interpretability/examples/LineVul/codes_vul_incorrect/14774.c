// commit message qemu@47d4be12c3 (target=1, prob=0.2299299, correct=False): cutils: work around platform differences in strto{l,ul,ll,ull}
/*0  */ static void test_qemu_strtol_invalid(void)     // (2) 0.1069
/*2  */ {                                              // (11) 0.006289
/*4  */     const char *str = "   xxxx  \t abc";       // (1) 0.1195
/*6  */     char f = 'X';                              // (7) 0.0566
/*8  */     const char *endptr = &f;                   // (5) 0.07547
/*10 */     long res = 999;                            // (8) 0.05031
/*12 */     int err;                                   // (9) 0.03774
/*16 */     err = qemu_strtol(str, &endptr, 0, &res);  // (0) 0.1509
/*20 */     g_assert_cmpint(err, ==, 0);               // (4) 0.1006
/*22 */     g_assert_cmpint(res, ==, 0);               // (3) 0.1006
/*24 */     g_assert(endptr == str);                   // (6) 0.07547
/*26 */ }                                              // (10) 0.006289

// commit message qemu@47d4be12c3 (target=1, prob=0.16676407, correct=False): cutils: work around platform differences in strto{l,ul,ll,ull}
/*0  */ static void test_qemu_strtoul_invalid(void)     // (2) 0.1189
/*2  */ {                                               // (9) 0.006993
/*4  */     const char *str = "   xxxx  \t abc";        // (1) 0.1329
/*6  */     char f = 'X';                               // (6) 0.06294
/*8  */     const char *endptr = &f;                    // (4) 0.08392
/*10 */     unsigned long res = 999;                    // (7) 0.06294
/*12 */     int err;                                    // (8) 0.04196
/*16 */     err = qemu_strtoul(str, &endptr, 0, &res);  // (0) 0.1678
/*20 */     g_assert_cmpint(err, ==, 0);                // (3) 0.1119
/*22 */     g_assert(endptr == str);                    // (5) 0.08392
/*24 */ }                                               // (10) 0.006993

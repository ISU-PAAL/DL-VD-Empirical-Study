// commit message qemu@f17fd4fdf0 (target=0, prob=0.02243846, correct=True): util/cutils: Return qemu_strtosz*() error and value separately
/*0  */ static void test_qemu_strtosz_metric(void)    // (1) 0.1488
/*2  */ {                                             // (7) 0.008264
/*4  */     const char *str = "12345k";               // (4) 0.1074
/*6  */     char *endptr = NULL;                      // (5) 0.08264
/*8  */     int64_t res;                              // (6) 0.07438
/*12 */     res = qemu_strtosz_metric(str, &endptr);  // (0) 0.1901
/*14 */     g_assert_cmpint(res, ==, 12345000);       // (2) 0.1488
/*16 */     g_assert(endptr == str + 6);              // (3) 0.1157
/*18 */ }                                             // (8) 0.008264

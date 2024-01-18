// commit message qemu@0fb6395c0c (target=0, prob=0.10179087, correct=True): Use error_is_set() only when necessary (again)
/*0  */ static void test_validate_fail_union_anon(TestInputVisitorData *data,  // (2) 0.1094
/*2  */                                           const void *unused)          // (0) 0.2448
/*4  */ {                                                                      // (9) 0.005208
/*6  */     UserDefAnonUnion *tmp = NULL;                                      // (6) 0.06771
/*8  */     Visitor *v;                                                        // (8) 0.04167
/*10 */     Error *errp = NULL;                                                // (7) 0.05208
/*14 */     v = validate_test_init(data, "3.14");                              // (3) 0.09375
/*18 */     visit_type_UserDefAnonUnion(v, &tmp, NULL, &errp);                 // (1) 0.125
/*20 */     g_assert(error_is_set(&errp));                                     // (4) 0.08333
/*22 */     qapi_free_UserDefAnonUnion(tmp);                                   // (5) 0.08333
/*24 */ }                                                                      // (10) 0.005208

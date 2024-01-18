// commit message qemu@68ab47e4b4 (target=1, prob=0.056854624, correct=False): qapi: Change visit_type_FOO() to no longer return partial objects
/*0  */ static void test_validate_fail_alternate(TestInputVisitorData *data,  // (2) 0.1105
/*2  */                                          const void *unused)          // (0) 0.2541
/*4  */ {                                                                     // (9) 0.005525
/*6  */     UserDefAlternate *tmp;                                            // (6) 0.05525
/*8  */     Visitor *v;                                                       // (8) 0.0442
/*10 */     Error *err = NULL;                                                // (7) 0.04972
/*14 */     v = validate_test_init(data, "3.14");                             // (3) 0.09945
/*18 */     visit_type_UserDefAlternate(v, NULL, &tmp, &err);                 // (1) 0.1215
/*20 */     error_free_or_abort(&err);                                        // (5) 0.07735
/*22 */     qapi_free_UserDefAlternate(tmp);                                  // (4) 0.08287
/*24 */ }                                                                     // (10) 0.005525

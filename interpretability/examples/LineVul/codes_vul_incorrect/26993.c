// commit message qemu@21f88d021d (target=1, prob=0.12257153, correct=False): qapi: Fix QemuOpts visitor regression on unvisited input
/*0  */ test_opts_dict_unvisited(void)                                                  // (6) 0.05628
/*2  */ {                                                                               // (12) 0.004329
/*4  */     QemuOpts *opts;                                                             // (7) 0.05195
/*6  */     Visitor *v;                                                                 // (11) 0.03463
/*8  */     UserDefOptions *userdef;                                                    // (9) 0.04329
/*12 */     opts = qemu_opts_parse(qemu_find_opts("userdef"), "i64x=0,bogus=1", false,  // (0) 0.1818
/*14 */                            &error_abort);                                       // (1) 0.1385
/*18 */     v = opts_visitor_new(opts);                                                 // (3) 0.06926
/*20 */     /* BUG: bogus should be diagnosed */                                        // (8) 0.05195
/*22 */     visit_type_UserDefOptions(v, NULL, &userdef, &error_abort);                 // (2) 0.1082
/*24 */     visit_free(v);                                                              // (10) 0.03896
/*26 */     qemu_opts_del(opts);                                                        // (4) 0.06494
/*28 */     qapi_free_UserDefOptions(userdef);                                          // (5) 0.06494
/*30 */ }                                                                               // (13) 0.004329

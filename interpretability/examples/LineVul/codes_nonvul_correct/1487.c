// commit message qemu@a9e1c28dda (target=0, prob=0.30287522, correct=True): check-qfloat: convert to gtest
/*0  */ int main(void)                                       // (9) 0.03597
/*2  */ {                                                    // (10) 0.007194
/*4  */     int nf;                                          // (8) 0.05036
/*6  */     Suite *s;                                        // (7) 0.05036
/*8  */     SRunner *sr;                                     // (6) 0.05755
/*12 */     s = qfloat_suite();                              // (4) 0.07914
/*14 */     sr = srunner_create(s);                          // (3) 0.08633
/*18 */     srunner_run_all(sr, CK_NORMAL);                  // (1) 0.1223
/*20 */     nf = srunner_ntests_failed(sr);                  // (2) 0.1151
/*22 */     srunner_free(sr);                                // (5) 0.07194
/*26 */     return (nf == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  // (0) 0.1799
/*28 */ }                                                    // (11) 0.007194

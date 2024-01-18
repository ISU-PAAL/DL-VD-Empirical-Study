// commit message qemu@a9e1c28dda (target=0, prob=0.0050877216, correct=True): check-qfloat: convert to gtest
/*0 */ START_TEST(qfloat_destroy_test)            // (1) 0.2407
/*2 */ {                                          // (3) 0.01852
/*4 */     QFloat *qf = qfloat_from_double(0.0);  // (0) 0.3704
/*6 */     QDECREF(qf);                           // (2) 0.1852
/*8 */ }                                          // (4) 0.01852

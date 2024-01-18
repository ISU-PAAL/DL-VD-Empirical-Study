// commit message qemu@65cdadd2e2 (target=0, prob=0.0062004454, correct=True): check-qint: convert to gtest
/*0  */ START_TEST(qint_get_int_test)                // (1) 0.163
/*2  */ {                                            // (6) 0.01087
/*4  */     QInt *qi;                                // (5) 0.08696
/*6  */     const int value = 123456;                // (3) 0.1087
/*10 */     qi = qint_from_int(value);               // (2) 0.163
/*12 */     fail_unless(qint_get_int(qi) == value);  // (0) 0.2065
/*16 */     QDECREF(qi);                             // (4) 0.09783
/*18 */ }                                            // (7) 0.01087

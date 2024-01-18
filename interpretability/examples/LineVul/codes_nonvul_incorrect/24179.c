// commit message qemu@29a6731afb (target=0, prob=0.5613114, correct=False): tests: Avoid qobject_from_jsonf("%"PRId64)
/*0  */ static void vararg_number(void)                     // (21) 0.02163
/*2  */ {                                                   // (25) 0.002404
/*4  */     QObject *obj;                                   // (24) 0.01923
/*6  */     QInt *qint;                                     // (22) 0.02163
/*8  */     QFloat *qfloat;                                 // (23) 0.02163
/*10 */     int value = 0x2342;                             // (14) 0.02644
/*12 */     int64_t value64 = 0x2342342343LL;               // (8) 0.04327
/*14 */     double valuef = 2.323423423;                    // (13) 0.03365
/*18 */     obj = qobject_from_jsonf("%d", value);          // (9) 0.04327
/*20 */     g_assert(obj != NULL);                          // (15) 0.02644
/*22 */     g_assert(qobject_type(obj) == QTYPE_QINT);      // (1) 0.05048
/*26 */     qint = qobject_to_qint(obj);                    // (10) 0.03846
/*28 */     g_assert(qint_get_int(qint) == value);          // (6) 0.04808
/*32 */     QDECREF(qint);                                  // (18) 0.02404
/*36 */     obj = qobject_from_jsonf("%" PRId64, value64);  // (2) 0.05048
/*38 */     g_assert(obj != NULL);                          // (16) 0.02644
/*40 */     g_assert(qobject_type(obj) == QTYPE_QINT);      // (3) 0.05048
/*44 */     qint = qobject_to_qint(obj);                    // (11) 0.03846
/*46 */     g_assert(qint_get_int(qint) == value64);        // (4) 0.05048
/*50 */     QDECREF(qint);                                  // (19) 0.02404
/*54 */     obj = qobject_from_jsonf("%f", valuef);         // (7) 0.04567
/*56 */     g_assert(obj != NULL);                          // (17) 0.02644
/*58 */     g_assert(qobject_type(obj) == QTYPE_QFLOAT);    // (0) 0.05529
/*62 */     qfloat = qobject_to_qfloat(obj);                // (12) 0.03846
/*64 */     g_assert(qfloat_get_double(qfloat) == valuef);  // (5) 0.05048
/*68 */     QDECREF(qfloat);                                // (20) 0.02404
/*70 */ }                                                   // (26) 0.002404

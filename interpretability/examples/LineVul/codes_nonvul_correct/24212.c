// commit message qemu@b3db211f3c (target=0, prob=0.027398413, correct=True): qapi: rename *qmp-*-visitor* to *qobject-*-visitor*
/*0  */ static void test_visitor_out_int(TestOutputVisitorData *data,        // (4) 0.1044
/*2  */                                  const void *unused)                 // (0) 0.2088
/*4  */ {                                                                    // (8) 0.005495
/*6  */     int64_t value = -42;                                             // (5) 0.06593
/*8  */     QObject *obj;                                                    // (7) 0.04396
/*12 */     visit_type_int(data->ov, NULL, &value, &error_abort);            // (2) 0.1319
/*16 */     obj = visitor_get(data);                                         // (6) 0.06044
/*18 */     g_assert(qobject_type(obj) == QTYPE_QINT);                       // (3) 0.1154
/*20 */     g_assert_cmpint(qint_get_int(qobject_to_qint(obj)), ==, value);  // (1) 0.1703
/*22 */ }                                                                    // (9) 0.005495

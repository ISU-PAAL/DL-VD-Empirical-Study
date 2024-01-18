// commit message qemu@3f66f764ee (target=0, prob=0.11480821, correct=True): qapi: Simplify non-error testing in test-qmp-*
/*0  */ static void test_visitor_out_string(TestOutputVisitorData *data,            // (5) 0.07851
/*2  */                                     const void *unused)                     // (0) 0.1694
/*4  */ {                                                                           // (12) 0.004132
/*6  */     char *string = (char *) "Q E M U";                                      // (6) 0.06612
/*8  */     Error *err = NULL;                                                      // (10) 0.03719
/*10 */     QObject *obj;                                                           // (11) 0.03306
/*14 */     visit_type_str(data->ov, &string, NULL, &err);                          // (3) 0.08678
/*16 */     g_assert(!err);                                                         // (9) 0.04132
/*20 */     obj = qmp_output_get_qobject(data->qov);                                // (4) 0.08264
/*22 */     g_assert(obj != NULL);                                                  // (7) 0.04545
/*24 */     g_assert(qobject_type(obj) == QTYPE_QSTRING);                           // (2) 0.09091
/*26 */     g_assert_cmpstr(qstring_get_str(qobject_to_qstring(obj)), ==, string);  // (1) 0.1281
/*30 */     qobject_decref(obj);                                                    // (8) 0.04545
/*32 */ }                                                                           // (13) 0.004132

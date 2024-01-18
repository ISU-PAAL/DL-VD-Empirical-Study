// commit message qemu@55e1819c50 (target=0, prob=0.015049697, correct=True): qobject: Simplify QObject
/*0  */ static void qstring_destroy_obj(QObject *obj)  // (1) 0.1707
/*2  */ {                                              // (6) 0.0122
/*4  */     QString *qs;                               // (5) 0.09756
/*8  */     assert(obj != NULL);                       // (3) 0.1098
/*10 */     qs = qobject_to_qstring(obj);              // (0) 0.1951
/*12 */     g_free(qs->string);                        // (2) 0.1341
/*14 */     g_free(qs);                                // (4) 0.1098
/*16 */ }                                              // (7) 0.0122

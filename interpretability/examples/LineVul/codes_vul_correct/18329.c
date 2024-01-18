// commit message qemu@a9fc37f6bc (target=1, prob=0.78510356, correct=True): qapi: Improve qobject input visitor error reporting
/*0  */ static void qobject_input_type_bool(Visitor *v, const char *name, bool *obj,  // (3) 0.08865
/*2  */                                     Error **errp)                             // (0) 0.1418
/*4  */ {                                                                             // (15) 0.003546
/*6  */     QObjectInputVisitor *qiv = to_qiv(v);                                     // (5) 0.06738
/*8  */     QObject *qobj = qobject_input_get_object(qiv, name, true, errp);          // (2) 0.09929
/*10 */     QBool *qbool;                                                             // (8) 0.03191
/*14 */     if (!qobj) {                                                              // (9) 0.03191
/*16 */         return;                                                               // (10) 0.03191
/*18 */     }                                                                         // (13) 0.01418
/*20 */     qbool = qobject_to_qbool(qobj);                                           // (6) 0.06028
/*22 */     if (!qbool) {                                                             // (11) 0.03191
/*24 */         error_setg(errp, QERR_INVALID_PARAMETER_TYPE, name ? name : "null",   // (1) 0.1312
/*26 */                    "boolean");                                                // (4) 0.07801
/*28 */         return;                                                               // (12) 0.03191
/*30 */     }                                                                         // (14) 0.01418
/*34 */     *obj = qbool_get_bool(qbool);                                             // (7) 0.05674
/*36 */ }                                                                             // (16) 0.003546

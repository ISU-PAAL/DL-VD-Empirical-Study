// commit message qemu@a9fc37f6bc (target=1, prob=0.24096215, correct=False): qapi: Improve qobject input visitor error reporting
/*0  */ static void qobject_input_start_list(Visitor *v, const char *name,           // (4) 0.0544
/*2  */                                      GenericList **list, size_t size,        // (0) 0.1192
/*4  */                                      Error **errp)                           // (1) 0.1062
/*6  */ {                                                                            // (21) 0.002591
/*8  */     QObjectInputVisitor *qiv = to_qiv(v);                                    // (8) 0.04922
/*10 */     QObject *qobj = qobject_input_get_object(qiv, name, true, errp);         // (3) 0.07254
/*12 */     const QListEntry *entry;                                                 // (11) 0.02591
/*16 */     if (list) {                                                              // (16) 0.02073
/*18 */         *list = NULL;                                                        // (10) 0.03109
/*20 */     }                                                                        // (17) 0.01036
/*22 */     if (!qobj) {                                                             // (13) 0.02332
/*24 */         return;                                                              // (14) 0.02332
/*26 */     }                                                                        // (18) 0.01036
/*28 */     if (qobject_type(qobj) != QTYPE_QLIST) {                                 // (5) 0.0544
/*30 */         error_setg(errp, QERR_INVALID_PARAMETER_TYPE, name ? name : "null",  // (2) 0.09585
/*32 */                    "list");                                                  // (6) 0.0544
/*34 */         return;                                                              // (15) 0.02332
/*36 */     }                                                                        // (19) 0.01036
/*40 */     entry = qobject_input_push(qiv, qobj, list);                             // (7) 0.05181
/*42 */     if (entry && list) {                                                     // (12) 0.02591
/*44 */         *list = g_malloc0(size);                                             // (9) 0.04663
/*46 */     }                                                                        // (20) 0.01036
/*48 */ }                                                                            // (22) 0.002591

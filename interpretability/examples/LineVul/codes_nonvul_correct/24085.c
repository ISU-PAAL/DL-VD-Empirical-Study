// commit message qemu@d9f62dde13 (target=0, prob=0.011784049, correct=True): qapi: Simplify semantics of visit_next_list()
/*0  */ static void qapi_dealloc_push(QapiDeallocVisitor *qov, void *value)  // (0) 0.1739
/*2  */ {                                                                    // (8) 0.007246
/*4  */     StackEntry *e = g_malloc0(sizeof(*e));                           // (2) 0.1377
/*8  */     e->value = value;                                                // (6) 0.06522
/*12 */     /* see if we're just pushing a list head tracker */              // (4) 0.1087
/*14 */     if (value == NULL) {                                             // (5) 0.07246
/*16 */         e->is_list_head = true;                                      // (3) 0.1232
/*18 */     }                                                                // (7) 0.02899
/*20 */     QTAILQ_INSERT_HEAD(&qov->stack, e, node);                        // (1) 0.1594
/*22 */ }                                                                    // (9) 0.007246

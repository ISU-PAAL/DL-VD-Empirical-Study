// commit message qemu@b3db211f3c (target=0, prob=0.014379531, correct=True): qapi: rename *qmp-*-visitor* to *qobject-*-visitor*
/*0  */ static void qmp_input_pop(Visitor *v, void **obj)  // (3) 0.1429
/*2  */ {                                                  // (7) 0.007937
/*4  */     QmpInputVisitor *qiv = to_qiv(v);              // (2) 0.1508
/*6  */     StackObject *tos = QSLIST_FIRST(&qiv->stack);  // (0) 0.1667
/*10 */     assert(tos && tos->qapi == obj);               // (5) 0.127
/*12 */     QSLIST_REMOVE_HEAD(&qiv->stack, node);         // (1) 0.1587
/*14 */     qmp_input_stack_object_free(tos);              // (4) 0.1349
/*16 */ }                                                  // (6) 0.007937

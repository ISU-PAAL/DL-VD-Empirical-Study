// commit message qemu@b3db211f3c (target=0, prob=0.010472247, correct=True): qapi: rename *qmp-*-visitor* to *qobject-*-visitor*
/*0  */ static void qmp_output_type_any(Visitor *v, const char *name, QObject **obj,  // (1) 0.208
/*2  */                                 Error **errp)                                 // (0) 0.288
/*4  */ {                                                                             // (5) 0.008
/*6  */     QmpOutputVisitor *qov = to_qov(v);                                        // (3) 0.152
/*8  */     qobject_incref(*obj);                                                     // (4) 0.088
/*10 */     qmp_output_add_obj(qov, name, *obj);                                      // (2) 0.16
/*12 */ }                                                                             // (6) 0.008

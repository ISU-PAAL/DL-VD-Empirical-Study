// commit message qemu@7d5e199ade (target=0, prob=0.008347663, correct=True): qapi: rename QmpOutputVisitor to QObjectOutputVisitor
/*0  */ static void qmp_output_type_number(Visitor *v, const char *name, double *obj,  // (1) 0.2101
/*2  */                                    Error **errp)                               // (0) 0.3277
/*4  */ {                                                                              // (4) 0.008403
/*6  */     QmpOutputVisitor *qov = to_qov(v);                                         // (3) 0.1597
/*8  */     qmp_output_add(qov, name, qfloat_from_double(*obj));                       // (2) 0.2017
/*10 */ }                                                                              // (5) 0.008403

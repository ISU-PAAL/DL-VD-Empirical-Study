// commit message qemu@15c2f669e3 (target=1, prob=0.011148743, correct=False): qapi: Split visit_end_struct() into pieces
/*0  */ static void qmp_output_end_struct(Visitor *v, Error **errp)  // (0) 0.2333
/*2  */ {                                                            // (4) 0.01111
/*4  */     QmpOutputVisitor *qov = to_qov(v);                       // (2) 0.2111
/*6  */     QObject *value = qmp_output_pop(qov);                    // (3) 0.2
/*8  */     assert(qobject_type(value) == QTYPE_QDICT);              // (1) 0.2222
/*10 */ }                                                            // (5) 0.01111

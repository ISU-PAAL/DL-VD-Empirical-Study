// commit message qemu@47c6d3ecdf (target=1, prob=0.024771487, correct=False): qapi: protect against NULL QObject in qmp_input_get_object
/*0  */ static const QObject *qmp_input_get_object(QmpInputVisitor *qiv,          // (6) 0.07797
/*2  */                                            const char *name)              // (0) 0.1593
/*4  */ {                                                                         // (14) 0.00339
/*6  */     const QObject *qobj;                                                  // (9) 0.0339
/*10 */     if (qiv->nb_stack == 0) {                                             // (7) 0.05085
/*12 */         qobj = qiv->obj;                                                  // (8) 0.05085
/*14 */     } else {                                                              // (11) 0.02034
/*16 */         qobj = qiv->stack[qiv->nb_stack - 1].obj;                         // (3) 0.08814
/*18 */     }                                                                     // (12) 0.01356
/*22 */     if (name && qobject_type(qobj) == QTYPE_QDICT) {                      // (5) 0.08136
/*24 */         return qdict_get(qobject_to_qdict(qobj), name);                   // (4) 0.08814
/*26 */     } else if (qiv->nb_stack > 0 && qobject_type(qobj) == QTYPE_QLIST) {  // (1) 0.1085
/*28 */         return qlist_entry_obj(qiv->stack[qiv->nb_stack - 1].entry);      // (2) 0.1051
/*30 */     }                                                                     // (13) 0.01356
/*34 */     return qobj;                                                          // (10) 0.02373
/*36 */ }                                                                         // (15) 0.00339

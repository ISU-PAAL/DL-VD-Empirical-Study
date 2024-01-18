// commit message qemu@15c2f669e3 (target=1, prob=0.015519019, correct=False): qapi: Split visit_end_struct() into pieces
/*0  */ static void qapi_dealloc_end_struct(Visitor *v, Error **errp)  // (0) 0.2222
/*2  */ {                                                              // (6) 0.0101
/*4  */     QapiDeallocVisitor *qov = to_qov(v);                       // (1) 0.202
/*6  */     void **obj = qapi_dealloc_pop(qov);                        // (2) 0.1818
/*8  */     if (obj) {                                                 // (4) 0.08081
/*10 */         g_free(*obj);                                          // (3) 0.1313
/*12 */     }                                                          // (5) 0.0404
/*14 */ }                                                              // (7) 0.0101

// commit message qemu@297a3646c2 (target=1, prob=0.9657835, correct=True): qapi: Replace uncommon use of the error API by the common one
/*0  */ void visit_end_implicit_struct(Visitor *v, Error **errp)  // (1) 0.2273
/*2  */ {                                                         // (5) 0.01136
/*4  */     assert(!error_is_set(errp));                          // (2) 0.1705
/*6  */     if (v->end_implicit_struct) {                         // (3) 0.1705
/*8  */         v->end_implicit_struct(v, errp);                  // (0) 0.2386
/*10 */     }                                                     // (4) 0.04545
/*12 */ }                                                         // (6) 0.01136

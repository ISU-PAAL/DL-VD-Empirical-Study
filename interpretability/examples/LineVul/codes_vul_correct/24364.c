// commit message qemu@297a3646c2 (target=1, prob=0.9907358, correct=True): qapi: Replace uncommon use of the error API by the common one
/*0  */ void visit_type_int(Visitor *v, int64_t *obj, const char *name, Error **errp)  // (0) 0.3537
/*2  */ {                                                                              // (4) 0.0122
/*4  */     if (!error_is_set(errp)) {                                                 // (2) 0.1829
/*6  */         v->type_int(v, obj, name, errp);                                       // (1) 0.2683
/*8  */     }                                                                          // (3) 0.04878
/*10 */ }                                                                              // (5) 0.0122

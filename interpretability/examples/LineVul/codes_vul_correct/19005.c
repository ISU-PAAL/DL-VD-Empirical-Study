// commit message qemu@297a3646c2 (target=1, prob=0.98907244, correct=True): qapi: Replace uncommon use of the error API by the common one
/*0  */ void visit_type_bool(Visitor *v, bool *obj, const char *name, Error **errp)  // (0) 0.3291
/*2  */ {                                                                            // (4) 0.01266
/*4  */     if (!error_is_set(errp)) {                                               // (2) 0.1899
/*6  */         v->type_bool(v, obj, name, errp);                                    // (1) 0.2785
/*8  */     }                                                                        // (3) 0.05063
/*10 */ }                                                                            // (5) 0.01266

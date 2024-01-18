// commit message qemu@09e68369a8 (target=0, prob=0.013338734, correct=True): qapi: rename QmpInputVisitor to QObjectInputVisitor
/*0 */ static QmpInputVisitor *to_qiv(Visitor *v)             // (1) 0.3778
/*2 */ {                                                      // (2) 0.02222
/*4 */     return container_of(v, QmpInputVisitor, visitor);  // (0) 0.4
/*6 */ }                                                      // (3) 0.02222

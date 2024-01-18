// commit message qemu@6a8f9661dc (target=0, prob=0.07633678, correct=True): block: Convert to new qapi union layout
/*0  */ static void blockdev_do_action(int kind, void *data, Error **errp)  // (0) 0.2019
/*2  */ {                                                                   // (8) 0.009615
/*4  */     TransactionAction action;                                       // (7) 0.06731
/*6  */     TransactionActionList list;                                     // (6) 0.07692
/*10 */     action.kind = kind;                                             // (3) 0.08654
/*12 */     action.data = data;                                             // (4) 0.08654
/*14 */     list.value = &action;                                           // (2) 0.09615
/*16 */     list.next = NULL;                                               // (5) 0.08654
/*18 */     qmp_transaction(&list, errp);                                   // (1) 0.1346
/*20 */ }                                                                   // (9) 0.009615

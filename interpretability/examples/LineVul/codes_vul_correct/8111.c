// commit message qemu@80fb34eda0 (target=1, prob=0.9991135, correct=True): io: fix possible double free of task error object
/*0  */ bool qio_task_propagate_error(QIOTask *task,  // (2) 0.1538
/*2  */                               Error **errp)   // (0) 0.2906
/*4  */ {                                             // (7) 0.008547
/*6  */     if (task->err) {                          // (3) 0.08547
/*8  */         error_propagate(errp, task->err);     // (1) 0.1624
/*11 */         return true;                          // (4) 0.08547
/*13 */     }                                         // (6) 0.03419
/*17 */     return false;                             // (5) 0.05128
/*19 */ }                                             // (8) 0.008547

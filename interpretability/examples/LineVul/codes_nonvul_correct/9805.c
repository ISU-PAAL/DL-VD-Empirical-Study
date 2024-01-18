// commit message qemu@0ab07c623c (target=0, prob=0.03479975, correct=True): Fix a few coding style violations in cpus.c
/*0  */ static void flush_queued_work(CPUState *env)  // (4) 0.08
/*2  */ {                                             // (11) 0.005714
/*4  */     struct qemu_work_item *wi;                // (5) 0.08
/*8  */     if (!env->queued_work_first)              // (6) 0.08
/*10 */         return;                               // (9) 0.05143
/*14 */     while ((wi = env->queued_work_first)) {   // (2) 0.09714
/*16 */         env->queued_work_first = wi->next;    // (0) 0.1143
/*18 */         wi->func(wi->data);                   // (3) 0.08571
/*20 */         wi->done = true;                      // (8) 0.07429
/*22 */     }                                         // (10) 0.02286
/*24 */     env->queued_work_last = NULL;             // (7) 0.08
/*26 */     qemu_cond_broadcast(&qemu_work_cond);     // (1) 0.1143
/*28 */ }                                             // (12) 0.005714

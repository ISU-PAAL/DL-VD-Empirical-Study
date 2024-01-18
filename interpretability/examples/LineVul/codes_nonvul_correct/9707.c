// commit message qemu@376692b9dc (target=0, prob=0.3104486, correct=True): cpus: protect work list with work_mutex
/*0  */ static void flush_queued_work(CPUState *cpu)  // (6) 0.06222
/*2  */ {                                             // (15) 0.004444
/*4  */     struct qemu_work_item *wi;                // (7) 0.06222
/*8  */     if (cpu->queued_work_first == NULL) {     // (3) 0.07556
/*10 */         return;                               // (11) 0.04
/*12 */     }                                         // (13) 0.01778
/*16 */     while ((wi = cpu->queued_work_first)) {   // (4) 0.07556
/*18 */         cpu->queued_work_first = wi->next;    // (0) 0.08889
/*20 */         wi->func(wi->data);                   // (5) 0.06667
/*22 */         wi->done = true;                      // (10) 0.05778
/*24 */         if (wi->free) {                       // (9) 0.06222
/*26 */             g_free(wi);                       // (2) 0.07556
/*28 */         }                                     // (12) 0.03556
/*30 */     }                                         // (14) 0.01778
/*32 */     cpu->queued_work_last = NULL;             // (8) 0.06222
/*34 */     qemu_cond_broadcast(&qemu_work_cond);     // (1) 0.08889
/*36 */ }                                             // (16) 0.004444

// commit message qemu@376692b9dc (target=0, prob=0.44975325, correct=True): cpus: protect work list with work_mutex
/*0  */ void run_on_cpu(CPUState *cpu, void (*func)(void *data), void *data)  // (1) 0.07186
/*2  */ {                                                                     // (23) 0.002994
/*4  */     struct qemu_work_item wi;                                         // (9) 0.03892
/*8  */     if (qemu_cpu_is_self(cpu)) {                                      // (4) 0.05389
/*10 */         func(data);                                                   // (11) 0.03293
/*12 */         return;                                                       // (13) 0.02695
/*14 */     }                                                                 // (20) 0.01198
/*18 */     wi.func = func;                                                   // (14) 0.02695
/*20 */     wi.data = data;                                                   // (15) 0.02695
/*22 */     wi.free = false;                                                  // (16) 0.02695
/*24 */     if (cpu->queued_work_first == NULL) {                             // (6) 0.0509
/*26 */         cpu->queued_work_first = &wi;                                 // (3) 0.05689
/*28 */     } else {                                                          // (19) 0.01796
/*30 */         cpu->queued_work_last->next = &wi;                            // (2) 0.06287
/*32 */     }                                                                 // (21) 0.01198
/*34 */     cpu->queued_work_last = &wi;                                      // (7) 0.04491
/*36 */     wi.next = NULL;                                                   // (17) 0.02695
/*38 */     wi.done = false;                                                  // (18) 0.02695
/*42 */     qemu_cpu_kick(cpu);                                               // (10) 0.03892
/*44 */     while (!wi.done) {                                                // (12) 0.02994
/*46 */         CPUState *self_cpu = current_cpu;                             // (5) 0.05389
/*50 */         qemu_cond_wait(&qemu_work_cond, &qemu_global_mutex);          // (0) 0.0988
/*52 */         current_cpu = self_cpu;                                       // (8) 0.04491
/*54 */     }                                                                 // (22) 0.01198
/*56 */ }                                                                     // (24) 0.002994

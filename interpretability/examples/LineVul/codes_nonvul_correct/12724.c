// commit message qemu@978f2205c7 (target=0, prob=0.02070705, correct=True): qemu-timer: make qemu_timer_mod_ns() and qemu_timer_del() thread-safe
/*0  */ bool timer_pending(QEMUTimer *ts)                                      // (3) 0.114
/*2  */ {                                                                      // (8) 0.008772
/*4  */     QEMUTimer *t;                                                      // (4) 0.08772
/*6  */     for (t = ts->timer_list->active_timers; t != NULL; t = t->next) {  // (0) 0.2544
/*8  */         if (t == ts) {                                                 // (1) 0.1228
/*10 */             return true;                                               // (2) 0.1228
/*12 */         }                                                              // (5) 0.07018
/*14 */     }                                                                  // (7) 0.03509
/*16 */     return false;                                                      // (6) 0.05263
/*18 */ }                                                                      // (9) 0.008772

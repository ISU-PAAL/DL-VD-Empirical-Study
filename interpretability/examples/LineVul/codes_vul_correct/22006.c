// commit message qemu@33bef0b994 (target=1, prob=0.5170216, correct=True): qemu-timer: fix off-by-one
/*0  */ bool timerlist_expired(QEMUTimerList *timer_list)                     // (6) 0.07203
/*2  */ {                                                                     // (13) 0.004237
/*4  */     int64_t expire_time;                                              // (8) 0.04661
/*8  */     if (!atomic_read(&timer_list->active_timers)) {                   // (5) 0.08051
/*10 */         return false;                                                 // (9) 0.04237
/*12 */     }                                                                 // (11) 0.01695
/*16 */     qemu_mutex_lock(&timer_list->active_timers_lock);                 // (3) 0.09746
/*18 */     if (!timer_list->active_timers) {                                 // (7) 0.06356
/*20 */         qemu_mutex_unlock(&timer_list->active_timers_lock);           // (0) 0.1186
/*22 */         return false;                                                 // (10) 0.04237
/*24 */     }                                                                 // (12) 0.01695
/*26 */     expire_time = timer_list->active_timers->expire_time;             // (4) 0.08898
/*28 */     qemu_mutex_unlock(&timer_list->active_timers_lock);               // (2) 0.1017
/*32 */     return expire_time < qemu_clock_get_ns(timer_list->clock->type);  // (1) 0.1102
/*34 */ }                                                                     // (14) 0.004237

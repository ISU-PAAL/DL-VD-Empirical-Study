// commit message qemu@158fd3ce98 (target=0, prob=0.2723276, correct=True): qemu-timer.c: Remove 250us timeouts
/*0  */ void qemu_run_all_timers(void)                // (5) 0.08092
/*2  */ {                                             // (11) 0.00578
/*4  */     alarm_timer->pending = 0;                 // (7) 0.06936
/*8  */     /* rearm timer, if not periodic */        // (8) 0.06936
/*10 */     if (alarm_timer->expired) {               // (6) 0.08092
/*12 */         alarm_timer->expired = 0;             // (2) 0.09249
/*14 */         qemu_rearm_alarm_timer(alarm_timer);  // (0) 0.1387
/*16 */     }                                         // (10) 0.02312
/*20 */     /* vm time timers */                      // (9) 0.04624
/*22 */     qemu_run_timers(vm_clock);                // (3) 0.09249
/*24 */     qemu_run_timers(rt_clock);                // (4) 0.09249
/*26 */     qemu_run_timers(host_clock);              // (1) 0.09249
/*28 */ }                                             // (12) 0.00578

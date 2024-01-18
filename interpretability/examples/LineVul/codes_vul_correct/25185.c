// commit message qemu@40f08e87f6 (target=1, prob=0.7500778, correct=True): qemu-timer: Fix limits for w32 mmtimer
/*0 */ static void mm_stop_timer(struct qemu_alarm_timer *t)  // (0) 0.3704
/*2 */ {                                                      // (3) 0.01852
/*4 */     timeKillEvent(mm_timer);                           // (2) 0.2037
/*6 */     timeEndPeriod(mm_period);                          // (1) 0.2222
/*8 */ }                                                      // (4) 0.01852

// commit message qemu@0fdddf80a8 (target=0, prob=0.73310155, correct=False): Rename QEMU_TIMER_* to QEMU_CLOCK_*
/*0  */ static void win32_rearm_timer(struct qemu_alarm_timer *t)            // (8) 0.05116
/*2  */ {                                                                    // (20) 0.002326
/*4  */     struct qemu_alarm_win32 *data = t->priv;                         // (9) 0.04651
/*6  */     uint64_t nearest_delta_us;                                       // (12) 0.03256
/*10 */     if (!active_timers[QEMU_TIMER_REALTIME] &&                       // (6) 0.05349
/*12 */                 !active_timers[QEMU_TIMER_VIRTUAL])                  // (1) 0.07674
/*14 */         return;                                                      // (18) 0.02093
/*18 */     nearest_delta_us = qemu_next_deadline_dyntick();                 // (7) 0.05349
/*20 */     nearest_delta_us /= 1000;                                        // (14) 0.03023
/*24 */     timeKillEvent(data->timerId);                                    // (15) 0.02791
/*28 */     data->timerId = timeSetEvent(1,                                  // (13) 0.03256
/*30 */                         data->period,                                // (5) 0.06279
/*32 */                         host_alarm_handler,                          // (2) 0.06977
/*34 */                         (DWORD)t,                                    // (4) 0.06744
/*36 */                         TIME_ONESHOT | TIME_PERIODIC);               // (0) 0.08372
/*40 */     if (!data->timerId) {                                            // (16) 0.02558
/*42 */         fprintf(stderr, "Failed to re-arm win32 alarm timer %ld\n",  // (3) 0.06977
/*44 */                 GetLastError());                                     // (10) 0.04419
/*48 */         timeEndPeriod(data->period);                                 // (11) 0.03721
/*50 */         exit(1);                                                     // (17) 0.02558
/*52 */     }                                                                // (19) 0.009302
/*54 */ }                                                                    // (21) 0.002326

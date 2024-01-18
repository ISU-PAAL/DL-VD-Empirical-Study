// commit message qemu@1828be316f (target=0, prob=0.45051634, correct=True): more alarm timer cleanup
/*0 */ static void quit_timers(void)        // (1) 0.2093
/*2 */ {                                    // (3) 0.02326
/*4 */     alarm_timer->stop(alarm_timer);  // (0) 0.3256
/*6 */     alarm_timer = NULL;              // (2) 0.2093
/*8 */ }                                    // (4) 0.02326

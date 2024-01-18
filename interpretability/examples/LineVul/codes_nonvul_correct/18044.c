// commit message qemu@7bd427d801 (target=0, prob=0.009440347, correct=True): change all rt_clock references to use millisecond resolution accessors
/*0  */ static SpiceTimer *timer_add(SpiceTimerFunc func, void *opaque)  // (2) 0.1802
/*2  */ {                                                                // (6) 0.009009
/*4  */     SpiceTimer *timer;                                           // (4) 0.07207
/*8  */     timer = qemu_mallocz(sizeof(*timer));                        // (3) 0.1622
/*10 */     timer->timer = qemu_new_timer(rt_clock, func, opaque);       // (0) 0.2072
/*12 */     QTAILQ_INSERT_TAIL(&timers, timer, next);                    // (1) 0.1892
/*14 */     return timer;                                                // (5) 0.05405
/*16 */ }                                                                // (7) 0.009009

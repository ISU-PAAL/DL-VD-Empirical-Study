// commit message qemu@c2b38b277a (target=0, prob=0.013561742, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0  */ static void qemu_clock_init(QEMUClockType type)                             // (5) 0.08586
/*2  */ {                                                                           // (10) 0.005051
/*4  */     QEMUClock *clock = qemu_clock_ptr(type);                                // (2) 0.101
/*8  */     /* Assert that the clock of type TYPE has not been initialized yet. */  // (3) 0.09596
/*10 */     assert(main_loop_tlg.tl[type] == NULL);                                 // (4) 0.09596
/*14 */     clock->type = type;                                                     // (9) 0.04545
/*16 */     clock->enabled = (type == QEMU_CLOCK_VIRTUAL ? false : true);           // (1) 0.1263
/*18 */     clock->last = INT64_MIN;                                                // (8) 0.06061
/*20 */     QLIST_INIT(&clock->timerlists);                                         // (7) 0.07071
/*22 */     notifier_list_init(&clock->reset_notifiers);                            // (6) 0.08586
/*24 */     main_loop_tlg.tl[type] = timerlist_new(type, NULL, NULL);               // (0) 0.1313
/*26 */ }                                                                           // (11) 0.005051

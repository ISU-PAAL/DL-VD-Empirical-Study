// commit message qemu@c2b38b277a (target=0, prob=0.005893543, correct=True): block: move AioContext, QEMUTimer, main-loop to libqemuutil
/*0 */ QEMUClockType timerlist_get_clock(QEMUTimerList *timer_list)  // (0) 0.5
/*2 */ {                                                             // (2) 0.02273
/*4 */     return timer_list->clock->type;                           // (1) 0.2727
/*6 */ }                                                             // (3) 0.02273

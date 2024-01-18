// commit message qemu@1828be316f (target=0, prob=0.038974673, correct=True): more alarm timer cleanup
/*0 */ static inline int alarm_has_dynticks(struct qemu_alarm_timer *t)  // (0) 0.5227
/*2 */ {                                                                 // (2) 0.02273
/*4 */     return t && t->rearm;                                         // (1) 0.25
/*6 */ }                                                                 // (3) 0.02273

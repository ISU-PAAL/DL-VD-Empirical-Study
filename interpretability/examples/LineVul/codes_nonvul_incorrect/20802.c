// commit message qemu@293d2a0014 (target=0, prob=0.5819952, correct=False): monitor: maintain at most one G_IO_OUT watch
/*0  */ static gboolean monitor_unblocked(GIOChannel *chan, GIOCondition cond,  // (1) 0.25
/*2  */                                   void *opaque)                         // (0) 0.4318
/*4  */ {                                                                       // (4) 0.01136
/*6  */     monitor_flush(opaque);                                              // (2) 0.1136
/*8  */     return FALSE;                                                       // (3) 0.06818
/*10 */ }                                                                       // (5) 0.01136

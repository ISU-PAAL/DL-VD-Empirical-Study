// commit message qemu@cbcfa0418f (target=0, prob=0.016571498, correct=True): link the main loop and its dependencies into the tools
/*0 */ void qemu_free_timer(QEMUTimer *ts)  // (0) 0.4571
/*2 */ {                                    // (2) 0.02857
/*4 */     g_free(ts);                      // (1) 0.2571
/*6 */ }                                    // (3) 0.02857

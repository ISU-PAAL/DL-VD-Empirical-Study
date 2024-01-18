// commit message qemu@8bd7f71d79 (target=0, prob=0.14620645, correct=True): replay: checkpoints
/*0  */ static int qemu_suspend_requested(void)  // (0) 0.2642
/*2  */ {                                        // (4) 0.01887
/*4  */     int r = suspend_requested;           // (1) 0.2075
/*6  */     suspend_requested = 0;               // (2) 0.1887
/*8  */     return r;                            // (3) 0.1132
/*10 */ }                                        // (5) 0.01887

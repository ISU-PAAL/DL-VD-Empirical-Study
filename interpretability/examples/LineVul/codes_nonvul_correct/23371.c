// commit message qemu@203d65a470 (target=0, prob=0.18634507, correct=True): hw/timer/imx_*: fix TIMER_MAX clash with system symbol
/*0  */ static void imx_epit_reset(DeviceState *dev)                          // (9) 0.04213
/*2  */ {                                                                     // (22) 0.002809
/*4  */     IMXEPITState *s = IMX_EPIT(dev);                                  // (5) 0.05337
/*8  */     /*                                                                // (20) 0.01124
/*10 */      * Soft reset doesn't touch some bits; hard reset clears them     // (7) 0.04775
/*12 */      */                                                               // (19) 0.01404
/*14 */     s->cr &= (CR_EN|CR_ENMOD|CR_STOPEN|CR_DOZEN|CR_WAITEN|CR_DBGEN);  // (0) 0.1152
/*16 */     s->sr = 0;                                                        // (15) 0.02528
/*18 */     s->lr = TIMER_MAX;                                                // (13) 0.03371
/*20 */     s->cmp = 0;                                                       // (16) 0.02528
/*22 */     s->cnt = 0;                                                       // (14) 0.02809
/*24 */     /* stop both timers */                                            // (17) 0.02247
/*26 */     ptimer_stop(s->timer_cmp);                                        // (11) 0.03933
/*28 */     ptimer_stop(s->timer_reload);                                     // (10) 0.04213
/*30 */     /* compute new frequency */                                       // (18) 0.02247
/*32 */     imx_epit_set_freq(s);                                             // (8) 0.04494
/*34 */     /* init both timers to TIMER_MAX */                               // (12) 0.03652
/*36 */     ptimer_set_limit(s->timer_cmp, TIMER_MAX, 1);                     // (2) 0.06461
/*38 */     ptimer_set_limit(s->timer_reload, TIMER_MAX, 1);                  // (1) 0.06742
/*40 */     if (s->freq && (s->cr & CR_EN)) {                                 // (4) 0.05618
/*42 */         /* if the timer is still enabled, restart it */               // (6) 0.05056
/*44 */         ptimer_run(s->timer_reload, 0);                               // (3) 0.05899
/*46 */     }                                                                 // (21) 0.01124
/*48 */ }                                                                     // (23) 0.002809

// commit message qemu@203d65a470 (target=0, prob=0.21217921, correct=True): hw/timer/imx_*: fix TIMER_MAX clash with system symbol
/*0  */ static void imx_gpt_reset(DeviceState *dev)                        // (8) 0.0344
/*2  */ {                                                                  // (28) 0.002294
/*4  */     IMXGPTState *s = IMX_GPT(dev);                                 // (4) 0.04358
/*8  */     /* stop timer */                                               // (24) 0.01606
/*10 */     ptimer_stop(s->timer);                                         // (15) 0.02752
/*14 */     /*                                                             // (26) 0.009174
/*16 */      * Soft reset doesn't touch some bits; hard reset clears them  // (6) 0.03899
/*18 */      */                                                            // (25) 0.01147
/*20 */     s->cr &= ~(GPT_CR_EN|GPT_CR_ENMOD|GPT_CR_STOPEN|GPT_CR_DOZEN|  // (0) 0.09862
/*22 */                GPT_CR_WAITEN|GPT_CR_DBGEN);                        // (1) 0.0711
/*24 */     s->sr = 0;                                                     // (20) 0.02064
/*26 */     s->pr = 0;                                                     // (21) 0.02064
/*28 */     s->ir = 0;                                                     // (22) 0.02064
/*30 */     s->cnt = 0;                                                    // (19) 0.02294
/*32 */     s->ocr1 = TIMER_MAX;                                           // (11) 0.02982
/*34 */     s->ocr2 = TIMER_MAX;                                           // (12) 0.02982
/*36 */     s->ocr3 = TIMER_MAX;                                           // (13) 0.02982
/*38 */     s->icr1 = 0;                                                   // (16) 0.02523
/*40 */     s->icr2 = 0;                                                   // (17) 0.02523
/*44 */     s->next_timeout = TIMER_MAX;                                   // (9) 0.03211
/*46 */     s->next_int = 0;                                               // (18) 0.02523
/*50 */     /* compute new freq */                                         // (23) 0.02064
/*52 */     imx_gpt_set_freq(s);                                           // (7) 0.0367
/*56 */     /* reset the limit to TIMER_MAX */                             // (14) 0.02982
/*58 */     ptimer_set_limit(s->timer, TIMER_MAX, 1);                      // (3) 0.04817
/*62 */     /* if the timer is still enabled, restart it */                // (10) 0.03211
/*64 */     if (s->freq && (s->cr & GPT_CR_EN)) {                          // (2) 0.05275
/*66 */         ptimer_run(s->timer, 1);                                   // (5) 0.04128
/*68 */     }                                                              // (27) 0.009174
/*70 */ }                                                                  // (29) 0.002294

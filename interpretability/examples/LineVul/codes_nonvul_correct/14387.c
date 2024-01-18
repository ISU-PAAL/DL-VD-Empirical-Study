// commit message qemu@a9cf98d939 (target=0, prob=0.12159103, correct=True): arm_timer: fix oneshot mode
/*0  */ static void arm_timer_recalibrate(arm_timer_state *s, int reload)  // (1) 0.1033
/*2  */ {                                                                  // (13) 0.004695
/*4  */     uint32_t limit;                                                // (9) 0.04225
/*8  */     if ((s->control & TIMER_CTRL_PERIODIC) == 0) {                 // (0) 0.1127
/*10 */         /* Free running.  */                                       // (8) 0.06103
/*12 */         if (s->control & TIMER_CTRL_32BIT)                         // (2) 0.1033
/*14 */             limit = 0xffffffff;                                    // (4) 0.08451
/*16 */         else                                                       // (10) 0.03756
/*18 */             limit = 0xffff;                                        // (5) 0.07981
/*20 */     } else {                                                       // (11) 0.02817
/*22 */           /* Periodic.  */                                         // (6) 0.07042
/*24 */           limit = s->limit;                                        // (7) 0.07042
/*26 */     }                                                              // (12) 0.01878
/*28 */     ptimer_set_limit(s->timer, limit, reload);                     // (3) 0.08451
/*30 */ }                                                                  // (14) 0.004695

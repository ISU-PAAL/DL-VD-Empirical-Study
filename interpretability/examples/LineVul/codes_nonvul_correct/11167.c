// commit message qemu@7bd427d801 (target=0, prob=0.033453196, correct=True): change all rt_clock references to use millisecond resolution accessors
/*0  */ static void omap_rtc_reset(struct omap_rtc_s *s)   // (1) 0.084
/*2  */ {                                                  // (16) 0.004
/*4  */     struct tm tm;                                  // (13) 0.036
/*8  */     s->interrupts = 0;                             // (8) 0.044
/*10 */     s->comp_reg = 0;                               // (9) 0.044
/*12 */     s->running = 0;                                // (14) 0.036
/*14 */     s->pm_am = 0;                                  // (10) 0.044
/*16 */     s->auto_comp = 0;                              // (11) 0.044
/*18 */     s->round = 0;                                  // (15) 0.036
/*20 */     s->tick = qemu_get_clock(rt_clock);            // (2) 0.076
/*22 */     memset(&s->alarm_tm, 0, sizeof(s->alarm_tm));  // (0) 0.096
/*24 */     s->alarm_tm.tm_mday = 0x01;                    // (3) 0.076
/*26 */     s->status = 1 << 7;                            // (12) 0.044
/*28 */     qemu_get_timedate(&tm, 0);                     // (4) 0.068
/*30 */     s->ti = mktimegm(&tm);                         // (6) 0.052
/*34 */     omap_rtc_alarm_update(s);                      // (5) 0.064
/*36 */     omap_rtc_tick(s);                              // (7) 0.052
/*38 */ }                                                  // (17) 0.004

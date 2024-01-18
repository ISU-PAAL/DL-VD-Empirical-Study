// commit message qemu@bab482d740 (target=0, prob=0.2260436, correct=True): s390x/css: ccw translation infrastructure
/*0  */ static void do_subchannel_work(SubchDev *sch, ORB *orb)  // (3) 0.07782
/*2  */ {                                                        // (14) 0.003891
/*6  */     SCSW *s = &sch->curr_status.scsw;                    // (5) 0.07393
/*10 */     if (s->ctrl & SCSW_FCTL_CLEAR_FUNC) {                // (2) 0.08949
/*12 */         sch_handle_clear_func(sch);                      // (8) 0.06615
/*14 */     } else if (s->ctrl & SCSW_FCTL_HALT_FUNC) {          // (0) 0.09728
/*16 */         sch_handle_halt_func(sch);                       // (7) 0.07004
/*18 */     } else if (s->ctrl & SCSW_FCTL_START_FUNC) {         // (1) 0.09728
/*20 */         /* Triggered by both ssch and rsch. */           // (4) 0.07782
/*22 */         sch_handle_start_func(sch, orb);                 // (6) 0.07393
/*24 */     } else {                                             // (12) 0.02335
/*26 */         /* Cannot happen. */                             // (10) 0.04669
/*28 */         return;                                          // (11) 0.03502
/*30 */     }                                                    // (13) 0.01556
/*32 */     css_inject_io_interrupt(sch);                        // (9) 0.06226
/*34 */ }                                                        // (15) 0.003891

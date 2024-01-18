// commit message qemu@107e4b352c (target=1, prob=0.7223248, correct=True): net/rocker: Remove the dead error handling
/*0  */ static OfDpaFlow *of_dpa_flow_alloc(uint64_t cookie)             // (2) 0.1167
/*2  */ {                                                                // (11) 0.005556
/*4  */     OfDpaFlow *flow;                                             // (5) 0.05556
/*6  */     int64_t now = qemu_clock_get_ms(QEMU_CLOCK_VIRTUAL) / 1000;  // (0) 0.1833
/*10 */     flow = g_new0(OfDpaFlow, 1);                                 // (4) 0.09444
/*12 */     if (!flow) {                                                 // (8) 0.04444
/*14 */         return NULL;                                             // (6) 0.05556
/*16 */     }                                                            // (10) 0.02222
/*20 */     flow->cookie = cookie;                                       // (7) 0.05
/*22 */     flow->mask.tbl_id = 0xffffffff;                              // (3) 0.09444
/*26 */     flow->stats.install_time = flow->stats.refresh_time = now;   // (1) 0.1222
/*30 */     return flow;                                                 // (9) 0.03333
/*32 */ }                                                                // (12) 0.005556

// commit message qemu@100f8f2608 (target=1, prob=0.4567715, correct=False): throttle: Add support for burst periods
/*0  */ void throttle_account(ThrottleState *ts, bool is_write, uint64_t size)           // (7) 0.07372
/*2  */ {                                                                                // (15) 0.003205
/*4  */     double units = 1.0;                                                          // (10) 0.03205
/*8  */     /* if cfg.op_size is defined and smaller than size we compute unit count */  // (8) 0.07051
/*10 */     if (ts->cfg.op_size && size > ts->cfg.op_size) {                             // (5) 0.07692
/*12 */         units = (double) size / ts->cfg.op_size;                                 // (9) 0.07051
/*14 */     }                                                                            // (13) 0.01282
/*18 */     ts->cfg.buckets[THROTTLE_BPS_TOTAL].level += size;                           // (4) 0.08013
/*20 */     ts->cfg.buckets[THROTTLE_OPS_TOTAL].level += units;                          // (6) 0.07692
/*24 */     if (is_write) {                                                              // (11) 0.03205
/*26 */         ts->cfg.buckets[THROTTLE_BPS_WRITE].level += size;                       // (0) 0.09295
/*28 */         ts->cfg.buckets[THROTTLE_OPS_WRITE].level += units;                      // (1) 0.08974
/*30 */     } else {                                                                     // (12) 0.01923
/*32 */         ts->cfg.buckets[THROTTLE_BPS_READ].level += size;                        // (2) 0.08974
/*34 */         ts->cfg.buckets[THROTTLE_OPS_READ].level += units;                       // (3) 0.08654
/*36 */     }                                                                            // (14) 0.01282
/*38 */ }                                                                                // (16) 0.003205

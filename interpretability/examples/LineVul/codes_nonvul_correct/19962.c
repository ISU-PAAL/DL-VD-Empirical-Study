// commit message qemu@d5851089a8 (target=0, prob=0.100973494, correct=True): throttle: Merge all functions that check the configuration into one
/*0  */ static bool check_throttle_config(ThrottleConfig *cfg, Error **errp)  // (1) 0.1409
/*2  */ {                                                                     // (11) 0.006711
/*4  */     if (throttle_conflicting(cfg, errp)) {                            // (2) 0.1208
/*6  */         return false;                                                 // (4) 0.06711
/*8  */     }                                                                 // (8) 0.02685
/*12 */     if (!throttle_is_valid(cfg, errp)) {                              // (3) 0.1208
/*14 */         return false;                                                 // (5) 0.06711
/*16 */     }                                                                 // (9) 0.02685
/*20 */     if (throttle_max_is_missing_limit(cfg, errp)) {                   // (0) 0.1477
/*22 */         return false;                                                 // (6) 0.06711
/*24 */     }                                                                 // (10) 0.02685
/*28 */     return true;                                                      // (7) 0.04027
/*30 */ }                                                                     // (12) 0.006711

// commit message FFmpeg@a026a3efae (target=1, prob=0.6847179, correct=True): avcodec/hevc_cabac: Check prefix so as to avoid invalid shifts in coeff_abs_level_remaining_decode()
/*0  */ static av_always_inline int coeff_abs_level_remaining_decode(HEVCContext *s, int rc_rice_param)  // (5) 0.06445
/*2  */ {                                                                                                // (21) 0.001953
/*4  */     int prefix = 0;                                                                              // (16) 0.01562
/*6  */     int suffix = 0;                                                                              // (17) 0.01562
/*8  */     int last_coeff_abs_level_remaining;                                                          // (12) 0.03125
/*10 */     int i;                                                                                       // (19) 0.01172
/*14 */     while (prefix < CABAC_MAX_BIN && get_cabac_bypass(&s->HEVClc->cc))                           // (4) 0.06641
/*16 */         prefix++;                                                                                // (15) 0.01758
/*20 */     if (prefix < 3) {                                                                            // (14) 0.01953
/*22 */         for (i = 0; i < rc_rice_param; i++)                                                      // (9) 0.04492
/*24 */             suffix = (suffix << 1) | get_cabac_bypass(&s->HEVClc->cc);                           // (2) 0.07422
/*26 */         last_coeff_abs_level_remaining = (prefix << rc_rice_param) + suffix;                     // (7) 0.06055
/*28 */     } else {                                                                                     // (20) 0.01172
/*30 */         int prefix_minus3 = prefix - 3;                                                          // (11) 0.0332
/*34 */         if (prefix == CABAC_MAX_BIN) {                                                           // (10) 0.04102
/*36 */             av_log(s->avctx, AV_LOG_ERROR, "CABAC_MAX_BIN : %d\n", prefix);                      // (1) 0.08398
/*38 */             return 0;                                                                            // (13) 0.02734
/*40 */         }                                                                                        // (18) 0.01562
/*44 */         for (i = 0; i < prefix_minus3 + rc_rice_param; i++)                                      // (8) 0.05469
/*46 */             suffix = (suffix << 1) | get_cabac_bypass(&s->HEVClc->cc);                           // (3) 0.07422
/*48 */         last_coeff_abs_level_remaining = (((1 << prefix_minus3) + 3 - 1)                         // (6) 0.06445
/*50 */                                               << rc_rice_param) + suffix;                        // (0) 0.1074
/*52 */     }                                                                                            // 0.0
/*54 */     return last_coeff_abs_level_remaining;                                                       // 0.0
/*56 */ }                                                                                                // 0.0

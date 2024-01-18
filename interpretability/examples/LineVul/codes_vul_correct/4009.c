// commit message FFmpeg@6f1b296771 (target=1, prob=0.9657995, correct=True): avcodec/lagarith: reenable buggy lag_decode_zero_run_line()
/*0   */ static int lag_decode_zero_run_line(LagarithContext *l, uint8_t *dst,            // (3) 0.05469
/*2   */                                     const uint8_t *src, const uint8_t *src_end,  // (0) 0.1035
/*4   */                                     int width, int esc_count)                    // (1) 0.08398
/*6   */ {                                                                                // (26) 0.001953
/*8   */     int i = 0;                                                                   // (21) 0.01562
/*10  */     int count;                                                                   // (23) 0.01172
/*12  */     uint8_t zero_run = 0;                                                        // (16) 0.02539
/*14  */     const uint8_t *src_start = src;                                              // (14) 0.0293
/*16  */     uint8_t mask1 = -(esc_count < 2);                                            // (8) 0.03516
/*18  */     uint8_t mask2 = -(esc_count < 3);                                            // (9) 0.03516
/*20  */     uint8_t *end = dst + (width - 2);                                            // (10) 0.0332
/*24  */     avpriv_request_sample(l->avctx, "zero_run_line");                            // (5) 0.04297
/*26  */     return AVERROR_PATCHWELCOME;                                                 // (15) 0.0293
/*30  */ output_zeros:                                                                    // (24) 0.009766
/*32  */     if (l->zeros_rem) {                                                          // (17) 0.02539
/*34  */         count = FFMIN(l->zeros_rem, width - i);                                  // (4) 0.04492
/*36  */         if (end - dst < count) {                                                 // (12) 0.03125
/*38  */             av_log(l->avctx, AV_LOG_ERROR, "Too many zeros remaining.\n");       // (2) 0.07031
/*40  */             return AVERROR_INVALIDDATA;                                          // (6) 0.04102
/*42  */         }                                                                        // (22) 0.01562
/*46  */         memset(dst, 0, count);                                                   // (11) 0.0332
/*48  */         l->zeros_rem -= count;                                                   // (13) 0.03125
/*50  */         dst += count;                                                            // (18) 0.02148
/*52  */     }                                                                            // (25) 0.007812
/*56  */     while (dst < end) {                                                          // (19) 0.02148
/*58  */         i = 0;                                                                   // (20) 0.02148
/*60  */         while (!zero_run && dst + i < end) {                                     // (7) 0.03906
/*62  */             i++;                                                                 // 0.0
/*64  */             if (i+2 >= src_end - src)                                            // 0.0
/*66  */                 return AVERROR_INVALIDDATA;                                      // 0.0
/*68  */             zero_run =                                                           // 0.0
/*70  */                 !(src[i] | (src[i + 1] & mask1) | (src[i + 2] & mask2));         // 0.0
/*72  */         }                                                                        // 0.0
/*74  */         if (zero_run) {                                                          // 0.0
/*76  */             zero_run = 0;                                                        // 0.0
/*78  */             i += esc_count;                                                      // 0.0
/*80  */             memcpy(dst, src, i);                                                 // 0.0
/*82  */             dst += i;                                                            // 0.0
/*84  */             l->zeros_rem = lag_calc_zero_run(src[i]);                            // 0.0
/*88  */             src += i + 1;                                                        // 0.0
/*90  */             goto output_zeros;                                                   // 0.0
/*92  */         } else {                                                                 // 0.0
/*94  */             memcpy(dst, src, i);                                                 // 0.0
/*96  */             src += i;                                                            // 0.0
/*98  */             dst += i;                                                            // 0.0
/*100 */         }                                                                        // 0.0
/*102 */     }                                                                            // 0.0
/*104 */     return  src - src_start;                                                     // 0.0
/*106 */ }                                                                                // 0.0

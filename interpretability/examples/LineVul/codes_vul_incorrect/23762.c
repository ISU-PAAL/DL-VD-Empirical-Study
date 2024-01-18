// commit message FFmpeg@5705dc5276 (target=1, prob=0.44204614, correct=False): avutil/imgutils: correctly check for negative SAR components
/*0  */ int av_image_check_sar(unsigned int w, unsigned int h, AVRational sar)    // (2) 0.09583
/*2  */ {                                                                         // (13) 0.004167
/*4  */     int64_t scaled_dim;                                                   // (8) 0.04583
/*8  */     if (!sar.den)                                                         // (9) 0.04167
/*10 */         return AVERROR(EINVAL);                                           // (4) 0.06667
/*14 */     if (!sar.num || sar.num == sar.den)                                   // (3) 0.075
/*16 */         return 0;                                                         // (10) 0.04167
/*20 */     if (sar.num < sar.den)                                                // (5) 0.05833
/*22 */         scaled_dim = av_rescale_rnd(w, sar.num, sar.den, AV_ROUND_ZERO);  // (0) 0.1542
/*24 */     else                                                                  // (12) 0.01667
/*26 */         scaled_dim = av_rescale_rnd(h, sar.den, sar.num, AV_ROUND_ZERO);  // (1) 0.1542
/*30 */     if (scaled_dim > 0)                                                   // (6) 0.05
/*32 */         return 0;                                                         // (11) 0.04167
/*36 */     return AVERROR(EINVAL);                                               // (7) 0.05
/*38 */ }                                                                         // (14) 0.004167

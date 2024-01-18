// commit message FFmpeg@2207ea44fb (target=0, prob=0.6795175, correct=False): ff_emulated_edge_mc: fix integer anomalies, fix out of array reads
/*0  */ static av_always_inline void emulated_edge_mc(uint8_t *buf, const uint8_t *src,  // (5) 0.05664
/*2  */                                               int linesize,                      // (4) 0.0957
/*4  */                                               int block_w, int block_h,          // (1) 0.1074
/*6  */                                               int src_x, int src_y,              // (2) 0.1074
/*8  */                                               int w, int h,                      // (3) 0.09961
/*10 */                                               emu_edge_core_func *core_fn)       // (0) 0.1133
/*12 */ {                                                                                // (17) 0.001953
/*14 */     int start_y, start_x, end_y, end_x, src_y_add = 0;                           // (6) 0.05469
/*18 */     if (src_y >= h) {                                                            // (15) 0.02344
/*20 */         src_y_add = h - 1 - src_y;                                               // (9) 0.04102
/*22 */         src_y     = h - 1;                                                       // (11) 0.03711
/*24 */     } else if (src_y <= -block_h) {                                              // (12) 0.0332
/*26 */         src_y_add = 1 - block_h - src_y;                                         // (7) 0.04492
/*28 */         src_y     = 1 - block_h;                                                 // (8) 0.04102
/*30 */     }                                                                            // (16) 0.007812
/*32 */     if (src_x >= w) {                                                            // (14) 0.02344
/*34 */         src   += w - 1 - src_x;                                                  // (10) 0.03711
/*36 */         src_x  = w - 1;                                                          // (13) 0.03125
/*38 */     } else if (src_x <= -block_w) {                                              // 0.0
/*40 */         src   += 1 - block_w - src_x;                                            // 0.0
/*42 */         src_x  = 1 - block_w;                                                    // 0.0
/*44 */     }                                                                            // 0.0
/*48 */     start_y = FFMAX(0, -src_y);                                                  // 0.0
/*50 */     start_x = FFMAX(0, -src_x);                                                  // 0.0
/*52 */     end_y   = FFMIN(block_h, h-src_y);                                           // 0.0
/*54 */     end_x   = FFMIN(block_w, w-src_x);                                           // 0.0
/*56 */     av_assert2(start_x < end_x && block_w > 0);                                  // 0.0
/*58 */     av_assert2(start_y < end_y && block_h > 0);                                  // 0.0
/*62 */     // fill in the to-be-copied part plus all above/below                        // 0.0
/*64 */     src += (src_y_add + start_y) * linesize + start_x;                           // 0.0
/*66 */     buf += start_x;                                                              // 0.0
/*68 */     core_fn(buf, src, linesize, start_y, end_y,                                  // 0.0
/*70 */             block_h, start_x, end_x, block_w);                                   // 0.0
/*72 */ }                                                                                // 0.0

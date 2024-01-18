// commit message FFmpeg@0c32e19d58 (target=0, prob=0.0072365133, correct=True): Move +52 from the loop filter to the alpha/beta offsets in the context. This should fix a segfault, also it might be faster on systems where the +52 wasnt free.
/*0  */ static void av_noinline filter_mb_edgev( uint8_t *pix, int stride, int16_t bS[4], unsigned int qp, H264Context *h) {  // (0) 0.1216
/*2  */     const unsigned int index_a = 52 + qp + h->slice_alpha_c0_offset;                                                  // (8) 0.07027
/*4  */     const int alpha = alpha_table[index_a];                                                                           // (9) 0.04054
/*6  */     const int beta  = (beta_table+52)[qp + h->slice_beta_offset];                                                     // (7) 0.07027
/*8  */     if (alpha ==0 || beta == 0) return;                                                                               // (10) 0.04054
/*12 */     if( bS[0] < 4 ) {                                                                                                 // (12) 0.03784
/*14 */         int8_t tc[4];                                                                                                 // (11) 0.04054
/*16 */         tc[0] = tc0_table[index_a][bS[0]];                                                                            // (3) 0.07297
/*18 */         tc[1] = tc0_table[index_a][bS[1]];                                                                            // (4) 0.07297
/*20 */         tc[2] = tc0_table[index_a][bS[2]];                                                                            // (5) 0.07297
/*22 */         tc[3] = tc0_table[index_a][bS[3]];                                                                            // (6) 0.07297
/*24 */         h->s.dsp.h264_h_loop_filter_luma(pix, stride, alpha, beta, tc);                                               // (2) 0.1
/*26 */     } else {                                                                                                          // (13) 0.01622
/*28 */         h->s.dsp.h264_h_loop_filter_luma_intra(pix, stride, alpha, beta);                                             // (1) 0.1027
/*30 */     }                                                                                                                 // (14) 0.01081
/*32 */ }                                                                                                                     // (15) 0.002703

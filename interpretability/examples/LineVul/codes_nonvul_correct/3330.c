// commit message FFmpeg@a4f6be86d6 (target=0, prob=0.007931625, correct=True): H.264: optimize intra/inter loopfilter decision
/*0  */ static void av_always_inline filter_mb_edgech( uint8_t *pix, int stride, const int16_t bS[4], unsigned int qp, H264Context *h ) {  // (0) 0.1122
/*2  */     const int qp_bd_offset = 6 * (h->sps.bit_depth_luma - 8);                                                                      // (5) 0.06921
/*4  */     const unsigned int index_a = qp - qp_bd_offset + h->slice_alpha_c0_offset;                                                     // (3) 0.07399
/*6  */     const int alpha = alpha_table[index_a];                                                                                        // (10) 0.0358
/*8  */     const int beta  = beta_table[qp - qp_bd_offset + h->slice_beta_offset];                                                        // (4) 0.0716
/*10 */     if (alpha ==0 || beta == 0) return;                                                                                            // (11) 0.0358
/*14 */     if( bS[0] < 4 ) {                                                                                                              // (13) 0.03341
/*16 */         int8_t tc[4];                                                                                                              // (12) 0.0358
/*18 */         tc[0] = tc0_table[index_a][bS[0]]+1;                                                                                       // (6) 0.06921
/*20 */         tc[1] = tc0_table[index_a][bS[1]]+1;                                                                                       // (7) 0.06921
/*22 */         tc[2] = tc0_table[index_a][bS[2]]+1;                                                                                       // (8) 0.06921
/*24 */         tc[3] = tc0_table[index_a][bS[3]]+1;                                                                                       // (9) 0.06921
/*26 */         h->h264dsp.h264_v_loop_filter_chroma(pix, stride, alpha, beta, tc);                                                        // (2) 0.08831
/*28 */     } else {                                                                                                                       // (14) 0.01432
/*30 */         h->h264dsp.h264_v_loop_filter_chroma_intra(pix, stride, alpha, beta);                                                      // (1) 0.09069
/*32 */     }                                                                                                                              // (15) 0.009547
/*34 */ }                                                                                                                                  // (16) 0.002387

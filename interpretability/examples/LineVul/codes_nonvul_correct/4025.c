// commit message FFmpeg@86b0d9cd58 (target=0, prob=0.006816984, correct=True): Make the h264 loop filter bit depth aware.
/*0  */ static void av_always_inline filter_mb_edgecv( uint8_t *pix, int stride, int16_t bS[4], unsigned int qp, H264Context *h ) {  // (0) 0.123
/*2  */     const unsigned int index_a = qp + h->slice_alpha_c0_offset;                                                              // (7) 0.06417
/*4  */     const int alpha = alpha_table[index_a];                                                                                  // (9) 0.04011
/*6  */     const int beta  = beta_table[qp + h->slice_beta_offset];                                                                 // (8) 0.0615
/*8  */     if (alpha ==0 || beta == 0) return;                                                                                      // (10) 0.04011
/*12 */     if( bS[0] < 4 ) {                                                                                                        // (12) 0.03743
/*14 */         int8_t tc[4];                                                                                                        // (11) 0.04011
/*16 */         tc[0] = tc0_table[index_a][bS[0]]+1;                                                                                 // (3) 0.07754
/*18 */         tc[1] = tc0_table[index_a][bS[1]]+1;                                                                                 // (4) 0.07754
/*20 */         tc[2] = tc0_table[index_a][bS[2]]+1;                                                                                 // (5) 0.07754
/*22 */         tc[3] = tc0_table[index_a][bS[3]]+1;                                                                                 // (6) 0.07754
/*24 */         h->h264dsp.h264_h_loop_filter_chroma(pix, stride, alpha, beta, tc);                                                  // (2) 0.09893
/*26 */     } else {                                                                                                                 // (13) 0.01604
/*28 */         h->h264dsp.h264_h_loop_filter_chroma_intra(pix, stride, alpha, beta);                                                // (1) 0.1016
/*30 */     }                                                                                                                        // (14) 0.0107
/*32 */ }                                                                                                                            // (15) 0.002674

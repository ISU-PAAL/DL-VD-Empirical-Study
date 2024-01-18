// commit message FFmpeg@dd561441b1 (target=0, prob=0.016707437, correct=True): h264: DSP'ize MBAFF loopfilter.
/*0  */ static av_always_inline av_flatten void h264_loop_filter_chroma_c(uint8_t *pix, int xstride, int ystride, int alpha, int beta, int8_t *tc0)  // (0) 0.1074
/*2  */ {                                                                                                                                            // (18) 0.001953
/*4  */     int i, d;                                                                                                                                // (16) 0.01562
/*6  */     for( i = 0; i < 4; i++ ) {                                                                                                               // (12) 0.0332
/*8  */         const int tc = tc0[i];                                                                                                               // (13) 0.03125
/*10 */         if( tc <= 0 ) {                                                                                                                      // (14) 0.02734
/*12 */             pix += 2*ystride;                                                                                                                // (11) 0.03906
/*14 */             continue;                                                                                                                        // (15) 0.02539
/*16 */         }                                                                                                                                    // (17) 0.01562
/*18 */         for( d = 0; d < 2; d++ ) {                                                                                                           // (10) 0.04102
/*20 */             const int p0 = pix[-1*xstride];                                                                                                  // (5) 0.05078
/*22 */             const int p1 = pix[-2*xstride];                                                                                                  // (6) 0.05078
/*24 */             const int q0 = pix[0];                                                                                                           // (9) 0.04102
/*26 */             const int q1 = pix[1*xstride];                                                                                                   // (8) 0.04883
/*30 */             if( FFABS( p0 - q0 ) < alpha &&                                                                                                  // (7) 0.05078
/*32 */                 FFABS( p1 - p0 ) < beta &&                                                                                                   // (4) 0.05469
/*34 */                 FFABS( q1 - q0 ) < beta ) {                                                                                                  // (3) 0.05664
/*38 */                 int delta = av_clip( (((q0 - p0 ) << 2) + (p1 - q1) + 4) >> 3, -tc, tc );                                                    // (1) 0.1016
/*42 */                 pix[-xstride] = av_clip_uint8( p0 + delta );    /* p0' */                                                                    // (2) 0.08594
/*44 */                 pix[0]        = av_clip_uint8( q0 - delta );    /* q0' */                                                                    // 0.0
/*46 */             }                                                                                                                                // 0.0
/*48 */             pix += ystride;                                                                                                                  // 0.0
/*50 */         }                                                                                                                                    // 0.0
/*52 */     }                                                                                                                                        // 0.0
/*54 */ }                                                                                                                                            // 0.0

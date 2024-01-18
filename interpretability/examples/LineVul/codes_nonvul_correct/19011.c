// commit message FFmpeg@dd561441b1 (target=0, prob=0.009661298, correct=True): h264: DSP'ize MBAFF loopfilter.
/*0  */ static av_always_inline av_flatten void h264_loop_filter_chroma_intra_c(uint8_t *pix, int xstride, int ystride, int alpha, int beta)  // (0) 0.1355
/*2  */ {                                                                                                                                     // (15) 0.00271
/*4  */     int d;                                                                                                                            // (13) 0.01626
/*6  */     for( d = 0; d < 8; d++ ) {                                                                                                        // (9) 0.04607
/*8  */         const int p0 = pix[-1*xstride];                                                                                               // (5) 0.05962
/*10 */         const int p1 = pix[-2*xstride];                                                                                               // (6) 0.05962
/*12 */         const int q0 = pix[0];                                                                                                        // (10) 0.04607
/*14 */         const int q1 = pix[1*xstride];                                                                                                // (8) 0.05691
/*18 */         if( FFABS( p0 - q0 ) < alpha &&                                                                                               // (7) 0.05962
/*20 */             FFABS( p1 - p0 ) < beta &&                                                                                                // (4) 0.06504
/*22 */             FFABS( q1 - q0 ) < beta ) {                                                                                               // (3) 0.06775
/*26 */             pix[-xstride] = ( 2*p1 + p0 + q1 + 2 ) >> 2;   /* p0' */                                                                  // (2) 0.1192
/*28 */             pix[0]        = ( 2*q1 + q0 + p1 + 2 ) >> 2;   /* q0' */                                                                  // (1) 0.1301
/*30 */         }                                                                                                                             // (12) 0.02168
/*32 */         pix += ystride;                                                                                                               // (11) 0.03794
/*34 */     }                                                                                                                                 // (14) 0.01084
/*36 */ }                                                                                                                                     // (16) 0.00271

// commit message FFmpeg@3ab9a2a557 (target=1, prob=0.55133325, correct=True): rv34: change most "int stride" into "ptrdiff_t stride".
/*0   */ static av_always_inline void rv40_strong_loop_filter(uint8_t *src,           // (6) 0.04688
/*2   */                                                      const int step,         // (5) 0.1094
/*4   */                                                      const int stride,       // (4) 0.1094
/*6   */                                                      const int alpha,        // (3) 0.1094
/*8   */                                                      const int lims,         // (0) 0.1113
/*10  */                                                      const int dmode,        // (2) 0.1113
/*12  */                                                      const int chroma)       // (1) 0.1113
/*14  */ {                                                                            // (14) 0.001953
/*16  */     int i;                                                                   // (13) 0.01172
/*20  */     for(i = 0; i < 4; i++, src += stride){                                   // (10) 0.03906
/*22  */         int sflag, p0, q0, p1, q1;                                           // (8) 0.04492
/*24  */         int t = src[0*step] - src[-1*step];                                  // (7) 0.04687
/*28  */         if (!t)                                                              // (12) 0.02148
/*30  */             continue;                                                        // (11) 0.02539
/*34  */         sflag = (alpha * FFABS(t)) >> 7;                                     // (9) 0.04297
/*36  */         if (sflag > 1)                                                       // 0.0
/*38  */             continue;                                                        // 0.0
/*42  */         p0 = (25*src[-3*step] + 26*src[-2*step] + 26*src[-1*step] +          // 0.0
/*44  */               26*src[ 0*step] + 25*src[ 1*step] +                            // 0.0
/*46  */               rv40_dither_l[dmode + i]) >> 7;                                // 0.0
/*50  */         q0 = (25*src[-2*step] + 26*src[-1*step] + 26*src[ 0*step] +          // 0.0
/*52  */               26*src[ 1*step] + 25*src[ 2*step] +                            // 0.0
/*54  */               rv40_dither_r[dmode + i]) >> 7;                                // 0.0
/*58  */         if (sflag) {                                                         // 0.0
/*60  */             p0 = av_clip(p0, src[-1*step] - lims, src[-1*step] + lims);      // 0.0
/*62  */             q0 = av_clip(q0, src[ 0*step] - lims, src[ 0*step] + lims);      // 0.0
/*64  */         }                                                                    // 0.0
/*68  */         p1 = (25*src[-4*step] + 26*src[-3*step] + 26*src[-2*step] + 26*p0 +  // 0.0
/*70  */               25*src[ 0*step] + rv40_dither_l[dmode + i]) >> 7;              // 0.0
/*72  */         q1 = (25*src[-1*step] + 26*q0 + 26*src[ 1*step] + 26*src[ 2*step] +  // 0.0
/*74  */               25*src[ 3*step] + rv40_dither_r[dmode + i]) >> 7;              // 0.0
/*78  */         if (sflag) {                                                         // 0.0
/*80  */             p1 = av_clip(p1, src[-2*step] - lims, src[-2*step] + lims);      // 0.0
/*82  */             q1 = av_clip(q1, src[ 1*step] - lims, src[ 1*step] + lims);      // 0.0
/*84  */         }                                                                    // 0.0
/*88  */         src[-2*step] = p1;                                                   // 0.0
/*90  */         src[-1*step] = p0;                                                   // 0.0
/*92  */         src[ 0*step] = q0;                                                   // 0.0
/*94  */         src[ 1*step] = q1;                                                   // 0.0
/*98  */         if(!chroma){                                                         // 0.0
/*100 */             src[-3*step] = (25*src[-1*step] + 26*src[-2*step] +              // 0.0
/*102 */                             51*src[-3*step] + 26*src[-4*step] + 64) >> 7;    // 0.0
/*104 */             src[ 2*step] = (25*src[ 0*step] + 26*src[ 1*step] +              // 0.0
/*106 */                             51*src[ 2*step] + 26*src[ 3*step] + 64) >> 7;    // 0.0
/*108 */         }                                                                    // 0.0
/*110 */     }                                                                        // 0.0
/*112 */ }                                                                            // 0.0

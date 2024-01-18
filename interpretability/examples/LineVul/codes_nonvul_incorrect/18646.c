// commit message FFmpeg@0a359cf157 (target=0, prob=0.98625493, correct=False): Faster VC-1 C loopfilter using lots of xor magic
/*0  */ static int vc1_filter_line(uint8_t* src, int stride, int pq){                                       // (9) 0.04688
/*2  */     int a0, a1, a2, a3, d, clip, filt3 = 0;                                                         // (7) 0.05078
/*4  */     uint8_t *cm = ff_cropTbl + MAX_NEG_CROP;                                                        // (8) 0.04688
/*8  */     a0     = (2*(src[-2*stride] - src[ 1*stride]) - 5*(src[-1*stride] - src[ 0*stride]) + 4) >> 3;  // (1) 0.1094
/*10 */     if(FFABS(a0) < pq){                                                                             // (13) 0.03125
/*12 */         a1 = (2*(src[-4*stride] - src[-1*stride]) - 5*(src[-3*stride] - src[-2*stride]) + 4) >> 3;  // (0) 0.1133
/*14 */         a2 = (2*(src[ 0*stride] - src[ 3*stride]) - 5*(src[ 1*stride] - src[ 2*stride]) + 4) >> 3;  // (2) 0.1055
/*16 */         a3 = FFMIN(FFABS(a1), FFABS(a2));                                                           // (6) 0.05273
/*18 */         if(a3 < FFABS(a0)){                                                                         // (12) 0.03906
/*20 */             d = 5 * ((a0 >=0 ? a3 : -a3) - a0) / 8;                                                 // (3) 0.06836
/*22 */             clip = (src[-1*stride] - src[ 0*stride])/2;                                             // (4) 0.06445
/*24 */             if(clip){                                                                               // (15) 0.0293
/*26 */                 filt3 = 1;                                                                          // (10) 0.04102
/*28 */                 if(clip > 0)                                                                        // (11) 0.04102
/*30 */                     d = av_clip(d, 0, clip);                                                        // (5) 0.06055
/*32 */                 else                                                                                // (14) 0.03125
/*34 */                     d = av_clip(d, clip, 0);                                                        // 0.0
/*36 */                 src[-1*stride] = cm[src[-1*stride] - d];                                            // 0.0
/*38 */                 src[ 0*stride] = cm[src[ 0*stride] + d];                                            // 0.0
/*40 */             }                                                                                       // 0.0
/*42 */         }                                                                                           // 0.0
/*44 */     }                                                                                               // 0.0
/*46 */     return filt3;                                                                                   // 0.0
/*48 */ }                                                                                                   // 0.0

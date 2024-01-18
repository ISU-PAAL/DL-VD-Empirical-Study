// commit message FFmpeg@3ab9a2a557 (target=1, prob=0.71713656, correct=True): rv34: change most "int stride" into "ptrdiff_t stride".
/*0  */ static av_always_inline void rv40_weak_loop_filter(uint8_t *src,         // (8) 0.04688
/*2  */                                                    const int step,       // (4) 0.1055
/*4  */                                                    const int stride,     // (6) 0.1055
/*6  */                                                    const int filter_p1,  // (1) 0.1113
/*8  */                                                    const int filter_q1,  // (2) 0.1113
/*10 */                                                    const int alpha,      // (7) 0.1055
/*12 */                                                    const int beta,       // (5) 0.1055
/*14 */                                                    const int lim_p0q0,   // (0) 0.1152
/*16 */                                                    const int lim_q1,     // (3) 0.1113
/*18 */                                                    const int lim_p1)     // 0.0
/*20 */ {                                                                        // 0.0
/*22 */     uint8_t *cm = ff_cropTbl + MAX_NEG_CROP;                             // 0.0
/*24 */     int i, t, u, diff;                                                   // 0.0
/*28 */     for (i = 0; i < 4; i++, src += stride) {                             // 0.0
/*30 */         int diff_p1p0 = src[-2*step] - src[-1*step];                     // 0.0
/*32 */         int diff_q1q0 = src[ 1*step] - src[ 0*step];                     // 0.0
/*34 */         int diff_p1p2 = src[-2*step] - src[-3*step];                     // 0.0
/*36 */         int diff_q1q2 = src[ 1*step] - src[ 2*step];                     // 0.0
/*40 */         t = src[0*step] - src[-1*step];                                  // 0.0
/*42 */         if (!t)                                                          // 0.0
/*44 */             continue;                                                    // 0.0
/*48 */         u = (alpha * FFABS(t)) >> 7;                                     // 0.0
/*50 */         if (u > 3 - (filter_p1 && filter_q1))                            // 0.0
/*52 */             continue;                                                    // 0.0
/*56 */         t <<= 2;                                                         // 0.0
/*58 */         if (filter_p1 && filter_q1)                                      // 0.0
/*60 */             t += src[-2*step] - src[1*step];                             // 0.0
/*64 */         diff = CLIP_SYMM((t + 4) >> 3, lim_p0q0);                        // 0.0
/*66 */         src[-1*step] = cm[src[-1*step] + diff];                          // 0.0
/*68 */         src[ 0*step] = cm[src[ 0*step] - diff];                          // 0.0
/*72 */         if (filter_p1 && FFABS(diff_p1p2) <= beta) {                     // 0.0
/*74 */             t = (diff_p1p0 + diff_p1p2 - diff) >> 1;                     // 0.0
/*76 */             src[-2*step] = cm[src[-2*step] - CLIP_SYMM(t, lim_p1)];      // 0.0
/*78 */         }                                                                // 0.0
/*82 */         if (filter_q1 && FFABS(diff_q1q2) <= beta) {                     // 0.0
/*84 */             t = (diff_q1q0 + diff_q1q2 + diff) >> 1;                     // 0.0
/*86 */             src[ 1*step] = cm[src[ 1*step] - CLIP_SYMM(t, lim_q1)];      // 0.0
/*88 */         }                                                                // 0.0
/*90 */     }                                                                    // 0.0
/*92 */ }                                                                        // 0.0

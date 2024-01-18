// commit message FFmpeg@a0e5f7f363 (target=1, prob=0.92472094, correct=True): avcodec/cavsdec: Fix undefined behavior from integer overflow
/*0  */ static inline void mv_pred_direct(AVSContext *h, cavs_vector *pmv_fw,                        // (6) 0.05804
/*2  */                                   cavs_vector *col_mv)                                       // (4) 0.09598
/*4  */ {                                                                                            // (15) 0.002232
/*6  */     cavs_vector *pmv_bw = pmv_fw + MV_BWD_OFFS;                                              // (5) 0.06027
/*8  */     int den = h->direct_den[col_mv->ref];                                                    // (7) 0.04241
/*10 */     int m = FF_SIGNBIT(col_mv->x);                                                           // (9) 0.04018
/*14 */     pmv_fw->dist = h->dist[1];                                                               // (12) 0.03571
/*16 */     pmv_bw->dist = h->dist[0];                                                               // (11) 0.03795
/*18 */     pmv_fw->ref = 1;                                                                         // (14) 0.02679
/*20 */     pmv_bw->ref = 0;                                                                         // (13) 0.02902
/*22 */     /* scale the co-located motion vector according to its temporal span */                  // (8) 0.04018
/*24 */     pmv_fw->x =     (((den + (den * col_mv->x * pmv_fw->dist ^ m) - m - 1) >> 14) ^ m) - m;  // (1) 0.1138
/*26 */     pmv_bw->x = m - (((den + (den * col_mv->x * pmv_bw->dist ^ m) - m - 1) >> 14) ^ m);      // (3) 0.1071
/*28 */     m = FF_SIGNBIT(col_mv->y);                                                               // (10) 0.03795
/*30 */     pmv_fw->y =     (((den + (den * col_mv->y * pmv_fw->dist ^ m) - m - 1) >> 14) ^ m) - m;  // (0) 0.1138
/*32 */     pmv_bw->y = m - (((den + (den * col_mv->y * pmv_bw->dist ^ m) - m - 1) >> 14) ^ m);      // (2) 0.1071
/*34 */ }                                                                                            // (16) 0.002232

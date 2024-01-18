// commit message FFmpeg@f1e173049e (target=0, prob=0.6718688, correct=False): avcodec/jpeg2000: Remove CBLK limit
/*0  */ static void dequantization_int(int x, int y, Jpeg2000Cblk *cblk,                                // (7) 0.05526
/*2  */                                Jpeg2000Component *comp,                                         // (3) 0.08177
/*4  */                                Jpeg2000T1Context *t1, Jpeg2000Band *band)                       // (1) 0.1039
/*6  */ {                                                                                               // (17) 0.002211
/*8  */     int i, j;                                                                                   // (14) 0.01768
/*10 */     int w = cblk->coord[0][1] - cblk->coord[0][0];                                              // (6) 0.05965
/*12 */     for (j = 0; j < (cblk->coord[1][1] - cblk->coord[1][0]); ++j) {                             // (4) 0.08175
/*14 */         int32_t *datap = &comp->i_data[(comp->coord[0][1] - comp->coord[0][0]) * (y + j) + x];  // (0) 0.1083
/*16 */         int *src = t1->data[j];                                                                 // (11) 0.03977
/*18 */         if (band->i_stepsize == 16384) {                                                        // (10) 0.04419
/*20 */             for (i = 0; i < w; ++i)                                                             // (9) 0.05303
/*22 */                 datap[i] = src[i] / 2;                                                          // (5) 0.06188
/*24 */         } else {                                                                                // (13) 0.02216
/*26 */             // This should be VERY uncommon                                                     // (12) 0.0385
/*28 */             for (i = 0; i < w; ++i)                                                             // (8) 0.05312
/*30 */                 datap[i] = (src[i] * (int64_t)band->i_stepsize) / 32768;                        // (2) 0.09722
/*32 */         }                                                                                       // (15) 0.01768
/*34 */     }                                                                                           // (16) 0.00884
/*36 */ }                                                                                               // (18) 0.00221

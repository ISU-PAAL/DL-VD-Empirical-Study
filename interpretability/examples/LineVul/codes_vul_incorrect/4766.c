// commit message FFmpeg@c23acbaed4 (target=1, prob=0.485928, correct=False): Don't use ff_cropTbl[] for IDCT.
/*0  */ void ff_vp3_idct_dc_add_c(uint8_t *dest/*align 8*/, int line_size, const DCTELEM *block/*align 16*/){  // (0) 0.1492
/*2  */     int i, dc = (block[0] + 15) >> 5;                                                                  // (2) 0.06441
/*4  */     const uint8_t *cm = ff_cropTbl + MAX_NEG_CROP + dc;                                                // (1) 0.09153
/*8  */     for(i = 0; i < 8; i++){                                                                            // (11) 0.05424
/*10 */         dest[0] = cm[dest[0]];                                                                         // (3) 0.06441
/*12 */         dest[1] = cm[dest[1]];                                                                         // (4) 0.06441
/*14 */         dest[2] = cm[dest[2]];                                                                         // (5) 0.06441
/*16 */         dest[3] = cm[dest[3]];                                                                         // (6) 0.06441
/*18 */         dest[4] = cm[dest[4]];                                                                         // (7) 0.06441
/*20 */         dest[5] = cm[dest[5]];                                                                         // (8) 0.06441
/*22 */         dest[6] = cm[dest[6]];                                                                         // (9) 0.06441
/*24 */         dest[7] = cm[dest[7]];                                                                         // (10) 0.06441
/*26 */         dest += line_size;                                                                             // (12) 0.04407
/*28 */     }                                                                                                  // (13) 0.01356
/*30 */ }                                                                                                      // (14) 0.00339

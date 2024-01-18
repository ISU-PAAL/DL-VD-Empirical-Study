// commit message FFmpeg@c23acbaed4 (target=1, prob=0.9686705, correct=True): Don't use ff_cropTbl[] for IDCT.
/*0  */ static void vc1_inv_trans_8x8_dc_c(uint8_t *dest, int linesize, DCTELEM *block)  // (0) 0.1135
/*2  */ {                                                                                // (18) 0.003067
/*4  */     int i;                                                                       // (16) 0.0184
/*6  */     int dc = block[0];                                                           // (15) 0.03067
/*8  */     const uint8_t *cm;                                                           // (14) 0.03374
/*10 */     dc = (3 * dc +  1) >> 1;                                                     // (10) 0.04908
/*12 */     dc = (3 * dc + 16) >> 5;                                                     // (12) 0.04601
/*14 */     cm = ff_cropTbl + MAX_NEG_CROP + dc;                                         // (1) 0.06442
/*16 */     for(i = 0; i < 8; i++){                                                      // (11) 0.04908
/*18 */         dest[0] = cm[dest[0]];                                                   // (2) 0.05828
/*20 */         dest[1] = cm[dest[1]];                                                   // (3) 0.05828
/*22 */         dest[2] = cm[dest[2]];                                                   // (4) 0.05828
/*24 */         dest[3] = cm[dest[3]];                                                   // (5) 0.05828
/*26 */         dest[4] = cm[dest[4]];                                                   // (6) 0.05828
/*28 */         dest[5] = cm[dest[5]];                                                   // (7) 0.05828
/*30 */         dest[6] = cm[dest[6]];                                                   // (8) 0.05828
/*32 */         dest[7] = cm[dest[7]];                                                   // (9) 0.05828
/*34 */         dest += linesize;                                                        // (13) 0.03681
/*36 */     }                                                                            // (17) 0.01227
/*38 */ }                                                                                // (19) 0.003067

// commit message FFmpeg@3176217c60 (target=0, prob=0.10866988, correct=True): h264: decouple h264_ps from the h264 decoder
/*0  */ void ff_h264_init_dequant_tables(H264Context *h)          // (6) 0.06452
/*2  */ {                                                         // (14) 0.003226
/*4  */     int i, x;                                             // (12) 0.02581
/*6  */     init_dequant4_coeff_table(h);                         // (10) 0.05161
/*8  */     if (h->pps.transform_8x8_mode)                        // (9) 0.05484
/*10 */         init_dequant8_coeff_table(h);                     // (7) 0.06452
/*12 */     if (h->sps.transform_bypass) {                        // (11) 0.05161
/*14 */         for (i = 0; i < 6; i++)                           // (8) 0.06129
/*16 */             for (x = 0; x < 16; x++)                      // (3) 0.07419
/*18 */                 h->dequant4_coeff[i][0][x] = 1 << 6;      // (1) 0.1129
/*20 */         if (h->pps.transform_8x8_mode)                    // (5) 0.06774
/*22 */             for (i = 0; i < 6; i++)                       // (4) 0.07419
/*24 */                 for (x = 0; x < 64; x++)                  // (2) 0.0871
/*26 */                     h->dequant8_coeff[i][0][x] = 1 << 6;  // (0) 0.1258
/*28 */     }                                                     // (13) 0.0129
/*30 */ }                                                         // (15) 0.003226

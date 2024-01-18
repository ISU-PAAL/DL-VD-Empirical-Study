// commit message FFmpeg@35dcc8a040 (target=1, prob=0.80244195, correct=True): avcodec/lagarith: fix integer overflow
/*0  */ static int lag_decode_prob(GetBitContext *gb, uint32_t *value)  // (1) 0.06336
/*2  */ {                                                               // (27) 0.002755
/*4  */     static const uint8_t series[] = { 1, 2, 3, 5, 8, 13, 21 };  // (0) 0.07438
/*6  */     int i;                                                      // (21) 0.01653
/*8  */     int bit     = 0;                                            // (10) 0.03306
/*10 */     int bits    = 0;                                            // (15) 0.0303
/*12 */     int prevbit = 0;                                            // (20) 0.02479
/*14 */     unsigned val;                                               // (22) 0.01653
/*18 */     for (i = 0; i < 7; i++) {                                   // (5) 0.04408
/*20 */         if (prevbit && bit)                                     // (7) 0.03857
/*22 */             break;                                              // (9) 0.03581
/*24 */         prevbit = bit;                                          // (11) 0.03306
/*26 */         bit = get_bits1(gb);                                    // (4) 0.04408
/*28 */         if (bit && !prevbit)                                    // (6) 0.04132
/*30 */             bits += series[i];                                  // (2) 0.04683
/*32 */     }                                                           // (25) 0.01102
/*34 */     bits--;                                                     // (23) 0.01653
/*36 */     if (bits < 0 || bits > 31) {                                // (8) 0.03857
/*38 */         *value = 0;                                             // (12) 0.03306
/*40 */         return -1;                                              // (16) 0.0303
/*42 */     } else if (bits == 0) {                                     // (13) 0.03306
/*44 */         *value = 0;                                             // (14) 0.03306
/*46 */         return 0;                                               // (18) 0.02755
/*48 */     }                                                           // (26) 0.01102
/*52 */     val  = get_bits_long(gb, bits);                             // (3) 0.04408
/*54 */     val |= 1 << bits;                                           // (17) 0.02755
/*58 */     *value = val - 1;                                           // (19) 0.02755
/*62 */     return 0;                                                   // (24) 0.01653
/*64 */ }                                                               // (28) 0.002755

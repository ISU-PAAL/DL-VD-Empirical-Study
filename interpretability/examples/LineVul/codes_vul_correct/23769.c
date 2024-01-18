// commit message FFmpeg@ba47d519e5 (target=1, prob=0.9543674, correct=True): avcodec/huffyuvdec: fix overread checks
/*0  */ static void decode_gray_bitstream(HYuvContext *s, int count)         // (5) 0.06618
/*2  */ {                                                                    // (14) 0.003676
/*4  */     int i;                                                           // (11) 0.02206
/*6  */     OPEN_READER(re, &s->gb);                                         // (7) 0.05515
/*8  */     count /= 2;                                                      // (8) 0.02941
/*12 */     if (count >= (get_bits_left(&s->gb)) / (32 * 2)) {               // (3) 0.09191
/*14 */         for (i = 0; i < count && get_bits_left(&s->gb) > 0; i++) {   // (2) 0.1213
/*16 */             READ_2PIX(s->temp[0][2 * i], s->temp[0][2 * i + 1], 0);  // (0) 0.1507
/*18 */         }                                                            // (9) 0.02941
/*20 */     } else {                                                         // (12) 0.02206
/*22 */         for (i = 0; i < count; i++) {                                // (4) 0.07353
/*24 */             READ_2PIX(s->temp[0][2 * i], s->temp[0][2 * i + 1], 0);  // (1) 0.1507
/*26 */         }                                                            // (10) 0.02941
/*28 */     }                                                                // (13) 0.01471
/*30 */     CLOSE_READER(re, &s->gb);                                        // (6) 0.05882
/*32 */ }                                                                    // (15) 0.003676

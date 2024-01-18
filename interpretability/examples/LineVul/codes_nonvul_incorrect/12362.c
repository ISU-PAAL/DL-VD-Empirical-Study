// commit message FFmpeg@11b4703813 (target=0, prob=0.95868754, correct=False): huffyuvdec: implement trick
/*0  */ static void decode_gray_bitstream(HYuvContext *s, int count)         // (5) 0.075
/*2  */ {                                                                    // (12) 0.004167
/*4  */     int i;                                                           // (9) 0.025
/*8  */     count/=2;                                                        // (6) 0.03333
/*12 */     if (count >= (get_bits_left(&s->gb)) / (31 * 2)) {               // (3) 0.1042
/*14 */         for (i = 0; i < count && get_bits_left(&s->gb) > 0; i++) {   // (2) 0.1375
/*16 */             READ_2PIX(s->temp[0][2 * i], s->temp[0][2 * i + 1], 0);  // (0) 0.1708
/*18 */         }                                                            // (7) 0.03333
/*20 */     } else {                                                         // (10) 0.025
/*22 */         for(i=0; i<count; i++){                                      // (4) 0.08333
/*24 */             READ_2PIX(s->temp[0][2 * i], s->temp[0][2 * i + 1], 0);  // (1) 0.1708
/*26 */         }                                                            // (8) 0.03333
/*28 */     }                                                                // (11) 0.01667
/*30 */ }                                                                    // (13) 0.004167

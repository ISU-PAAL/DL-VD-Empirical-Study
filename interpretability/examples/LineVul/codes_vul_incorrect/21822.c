// commit message FFmpeg@1a3598aae7 (target=1, prob=0.06256421, correct=False): jpeg2000: Use bytestream2
/*0  */ static int get_bits(Jpeg2000DecoderContext *s, int n)     // (3) 0.07792
/*2  */ {                                                         // (14) 0.004329
/*4  */     int res = 0;                                          // (10) 0.03463
/*6  */     if (s->buf_end - s->buf < ((n - s->bit_index) >> 8))  // (0) 0.1169
/*8  */         return AVERROR_INVALIDDATA;                       // (5) 0.07359
/*10 */     while (--n >= 0) {                                    // (9) 0.04762
/*12 */         res <<= 1;                                        // (8) 0.05195
/*14 */         if (s->bit_index == 0) {                          // (4) 0.07792
/*16 */             s->bit_index = 7 + (*s->buf != 0xff);         // (1) 0.1169
/*18 */             s->buf++;                                     // (6) 0.06494
/*20 */         }                                                 // (11) 0.03463
/*22 */         s->bit_index--;                                   // (7) 0.06061
/*24 */         res |= (*s->buf >> s->bit_index) & 1;             // (2) 0.1039
/*26 */     }                                                     // (13) 0.01732
/*28 */     return res;                                           // (12) 0.02597
/*30 */ }                                                         // (15) 0.004329

// commit message FFmpeg@5ff998a233 (target=1, prob=0.21330398, correct=False): flacenc: use uint64_t for bit counts
/*0  */ static int encode_frame(FlacEncodeContext *s)          // (4) 0.09272
/*2  */ {                                                      // (8) 0.006623
/*4  */     int ch, count;                                     // (6) 0.05298
/*8  */     count = count_frame_header(s);                     // (5) 0.08609
/*12 */     for (ch = 0; ch < s->channels; ch++)               // (3) 0.1192
/*14 */         count += encode_residual_ch(s, ch);            // (1) 0.1391
/*18 */     count += (8 - (count & 7)) & 7; // byte alignment  // (2) 0.1258
/*20 */     count += 16;                    // CRC-16          // (0) 0.1987
/*24 */     return count >> 3;                                 // (7) 0.05298
/*26 */ }                                                      // (9) 0.006623

// commit message FFmpeg@86ab6b6e08 (target=0, prob=0.6546848, correct=False): avcodec/scpr: check if total_freq is 0 in decode0
/*0  */ static void decode0(GetByteContext *gb, RangeCoder *rc, unsigned cumFreq, unsigned freq, unsigned total_freq)  // (1) 0.141
/*2  */ {                                                                                                              // (11) 0.004405
/*4  */     int t = rc->range * (uint64_t)cumFreq / total_freq;                                                        // (3) 0.1101
/*8  */     rc->code1 += t + 1;                                                                                        // (8) 0.05286
/*10 */     rc->range = rc->range * (uint64_t)(freq + cumFreq) / total_freq - (t + 1);                                 // (0) 0.1542
/*14 */     while (rc->range < TOP && bytestream2_get_bytes_left(gb) > 0) {                                            // (2) 0.1233
/*16 */         unsigned byte = bytestream2_get_byte(gb);                                                              // (4) 0.09251
/*18 */         rc->code = (rc->code << 8) | byte;                                                                     // (5) 0.09251
/*20 */         rc->code1 <<= 8;                                                                                       // (6) 0.06608
/*22 */         rc->range <<= 8;                                                                                       // (7) 0.06167
/*24 */     }                                                                                                          // (9) 0.01762
/*26 */ }                                                                                                              // (10) 0.004405

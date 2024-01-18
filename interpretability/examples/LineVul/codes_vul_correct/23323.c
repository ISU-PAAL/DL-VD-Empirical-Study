// commit message FFmpeg@3016e919d4 (target=1, prob=0.95961195, correct=True): avcodec/wavpack: Fix runtime error: left shift of negative value -5
/*0  */ static inline int wv_get_value_integer(WavpackFrameContext *s, uint32_t *crc,  // (5) 0.07865
/*2  */                                        int S)                                  // (0) 0.1152
/*4  */ {                                                                              // (16) 0.002809
/*6  */     unsigned bit;                                                              // (14) 0.01685
/*10 */     if (s->extra_bits) {                                                       // (10) 0.03371
/*12 */         S <<= s->extra_bits;                                                   // (9) 0.04494
/*16 */         if (s->got_extra_bits &&                                               // (7) 0.04775
/*18 */             get_bits_left(&s->gb_extra_bits) >= s->extra_bits) {               // (3) 0.0927
/*20 */             S   |= get_bits_long(&s->gb_extra_bits, s->extra_bits);            // (2) 0.1011
/*22 */             *crc = *crc * 9 + (S & 0xffff) * 3 + ((unsigned)S >> 16);          // (1) 0.1067
/*24 */         }                                                                      // (13) 0.02247
/*26 */     }                                                                          // (15) 0.01124
/*30 */     bit = (S & s->and) | s->or;                                                // (8) 0.04775
/*32 */     bit = ((S + bit) << s->shift) - bit;                                       // (6) 0.05056
/*36 */     if (s->hybrid)                                                             // (12) 0.02809
/*38 */         bit = av_clip(bit, s->hybrid_minclip, s->hybrid_maxclip);              // (4) 0.08708
/*42 */     return bit << s->post_shift;                                               // (11) 0.03371
/*44 */ }                                                                              // (17) 0.002809

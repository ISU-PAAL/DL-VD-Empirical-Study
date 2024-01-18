// commit message FFmpeg@beefafda63 (target=1, prob=0.98269606, correct=True): Fixed invalid access in wavpack decoder on corrupted extra bits sub-blocks.
/*0  */ static inline int wv_get_value_integer(WavpackFrameContext *s, uint32_t *crc, int S)  // (2) 0.1372
/*2  */ {                                                                                     // (11) 0.004425
/*4  */     int bit;                                                                          // (9) 0.02655
/*8  */     if(s->extra_bits){                                                                // (7) 0.04867
/*10 */         S <<= s->extra_bits;                                                          // (6) 0.0708
/*14 */         if(s->got_extra_bits){                                                        // (4) 0.07522
/*16 */             S |= get_bits(&s->gb_extra_bits, s->extra_bits);                          // (1) 0.1416
/*18 */             *crc = *crc * 9 + (S&0xffff) * 3 + ((unsigned)S>>16);                     // (0) 0.1681
/*20 */         }                                                                             // (8) 0.0354
/*22 */     }                                                                                 // (10) 0.0177
/*24 */     bit = (S & s->and) | s->or;                                                       // (5) 0.07522
/*26 */     return (((S + bit) << s->shift) - bit) << s->post_shift;                          // (3) 0.1106
/*28 */ }                                                                                     // (12) 0.004425

// commit message FFmpeg@0b42631641 (target=0, prob=0.8104212, correct=False): avcodec/jpeg2000dec: merge bytestream2 reading from j2kdec
/*0  */ static int get_coc(Jpeg2000DecoderContext *s, Jpeg2000CodingStyle *c,  // (0) 0.1269
/*2  */                    uint8_t *properties)                                // (1) 0.1269
/*4  */ {                                                                      // (11) 0.005076
/*6  */     int compno;                                                        // (9) 0.03553
/*10 */     if (s->buf_end - s->buf < 2)                                       // (4) 0.08629
/*12 */         return AVERROR(EINVAL);                                        // (5) 0.08122
/*16 */     compno = bytestream_get_byte(&s->buf);                             // (3) 0.09137
/*20 */     c      += compno;                                                  // (7) 0.06599
/*22 */     c->csty = bytestream_get_byte(&s->buf);                            // (2) 0.1015
/*24 */     get_cox(s, c);                                                     // (8) 0.05584
/*28 */     properties[compno] |= HAD_COC;                                     // (6) 0.08122
/*30 */     return 0;                                                          // (10) 0.03046
/*32 */ }                                                                      // (12) 0.005076

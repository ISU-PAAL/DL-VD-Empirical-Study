// commit message FFmpeg@55d7371fe0 (target=1, prob=0.6133983, correct=True): avcodec/vp568: Check that there is enough data for ff_vp56_init_range_decoder()
/*0  */ void ff_vp56_init_range_decoder(VP56RangeCoder *c, const uint8_t *buf, int buf_size)  // (0) 0.3063
/*2  */ {                                                                                     // (6) 0.009009
/*4  */     c->high = 255;                                                                    // (4) 0.08108
/*6  */     c->bits = -16;                                                                    // (3) 0.09009
/*8  */     c->buffer = buf;                                                                  // (5) 0.08108
/*10 */     c->end = buf + buf_size;                                                          // (2) 0.1171
/*12 */     c->code_word = bytestream_get_be24(&c->buffer);                                   // (1) 0.1982
/*14 */ }                                                                                     // (7) 0.009009

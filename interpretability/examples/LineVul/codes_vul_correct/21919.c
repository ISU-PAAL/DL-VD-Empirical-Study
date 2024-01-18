// commit message FFmpeg@8000d484b8 (target=1, prob=0.8493028, correct=True): avcodec/cabac: Check initial cabac decoder state
/*0  */ void ff_init_cabac_decoder(CABACContext *c, const uint8_t *buf, int buf_size){  // (0) 0.1658
/*2  */     c->bytestream_start=                                                        // (8) 0.057
/*4  */     c->bytestream= buf;                                                         // (7) 0.057
/*6  */     c->bytestream_end= buf + buf_size;                                          // (5) 0.08809
/*10 */ #if CABAC_BITS == 16                                                            // (9) 0.05182
/*12 */     c->low =  (*c->bytestream++)<<18;                                           // (2) 0.09327
/*14 */     c->low+=  (*c->bytestream++)<<10;                                           // (3) 0.09327
/*16 */ #else                                                                           // (11) 0.01036
/*18 */     c->low =  (*c->bytestream++)<<10;                                           // (4) 0.09326
/*20 */ #endif                                                                          // (10) 0.01036
/*22 */     c->low+= ((*c->bytestream++)<<2) + 2;                                       // (1) 0.1088
/*24 */     c->range= 0x1FE;                                                            // (6) 0.06218
/*26 */ }                                                                               // (12) 0.005182

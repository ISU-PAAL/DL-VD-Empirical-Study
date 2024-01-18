// commit message FFmpeg@68900bf16b (target=0, prob=0.38416773, correct=True): avcodec: Fix duration error after seek operation
/*0  */ static int cook_parse(AVCodecParserContext *s1, AVCodecContext *avctx,           // (4) 0.07904
/*2  */                       const uint8_t **poutbuf, int *poutbuf_size,                // (0) 0.134
/*4  */                       const uint8_t *buf, int buf_size)                          // (1) 0.1168
/*6  */ {                                                                                // (13) 0.003436
/*8  */     CookParseContext *s = s1->priv_data;                                         // (6) 0.05842
/*12 */     if (s->duration)                                                             // (11) 0.03093
/*14 */         s1->duration = s->duration;                                              // (7) 0.05498
/*16 */     else if (avctx->extradata && avctx->extradata_size >= 8 && avctx->channels)  // (3) 0.1031
/*18 */         s->duration = AV_RB16(avctx->extradata + 4) / avctx->channels;           // (2) 0.11
/*22 */     /* always return the full packet. this parser isn't doing any splitting or   // (5) 0.06186
/*24 */        combining, only setting packet duration */                                // (10) 0.04467
/*26 */     *poutbuf      = buf;                                                         // (8) 0.05155
/*28 */     *poutbuf_size = buf_size;                                                    // (9) 0.04811
/*30 */     return buf_size;                                                             // (12) 0.02749
/*32 */ }                                                                                // (14) 0.003436

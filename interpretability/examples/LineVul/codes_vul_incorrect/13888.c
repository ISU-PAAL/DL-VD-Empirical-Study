// commit message FFmpeg@374c907fb3 (target=1, prob=0.36578408, correct=False): avcodec/vorbis_parser: Move vp check
/*0  */ static int vorbis_parse(AVCodecParserContext *s1, AVCodecContext *avctx,        // (5) 0.06906
/*2  */                         const uint8_t **poutbuf, int *poutbuf_size,             // (0) 0.1133
/*4  */                         const uint8_t *buf, int buf_size)                       // (2) 0.09945
/*6  */ {                                                                               // (18) 0.002762
/*8  */     VorbisParseContext *s = s1->priv_data;                                      // (6) 0.05249
/*10 */     int duration;                                                               // (15) 0.01657
/*14 */     if (!s->vp && avctx->extradata && avctx->extradata_size) {                  // (4) 0.07182
/*16 */         s->vp = av_vorbis_parse_init(avctx->extradata, avctx->extradata_size);  // (1) 0.09945
/*18 */         if (!s->vp)                                                             // (12) 0.03591
/*20 */             goto end;                                                           // (9) 0.03867
/*22 */     }                                                                           // (16) 0.01105
/*26 */     if ((duration = av_vorbis_parse_frame(s->vp, buf, buf_size)) >= 0)          // (3) 0.08011
/*28 */         s1->duration = duration;                                                // (10) 0.03867
/*32 */ end:                                                                            // (17) 0.005525
/*34 */     /* always return the full packet. this parser isn't doing any splitting or  // (7) 0.04972
/*36 */        combining, only packet analysis */                                       // (13) 0.03315
/*38 */     *poutbuf      = buf;                                                        // (8) 0.04144
/*40 */     *poutbuf_size = buf_size;                                                   // (11) 0.03867
/*42 */     return buf_size;                                                            // (14) 0.0221
/*44 */ }                                                                               // (19) 0.002762

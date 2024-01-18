// commit message FFmpeg@d3b25383da (target=1, prob=0.7464011, correct=True): avcodec/012v: Check dimensions more completely
/*0   */ static int zero12v_decode_frame(AVCodecContext *avctx, void *data,           // (6) 0.04492
/*2   */                                 int *got_frame, AVPacket *avpkt)             // (0) 0.08789
/*4   */ {                                                                            // (25) 0.001953
/*6   */     int line = 0, ret;                                                       // (20) 0.01953
/*8   */     const int width = avctx->width;                                          // (17) 0.02344
/*10  */     AVFrame *pic = data;                                                     // (19) 0.01953
/*12  */     uint16_t *y, *u, *v;                                                     // (15) 0.03125
/*14  */     const uint8_t *line_end, *src = avpkt->data;                             // (8) 0.04297
/*16  */     int stride = avctx->width * 8 / 3;                                       // (16) 0.0293
/*20  */     if (width == 1) {                                                        // (22) 0.01953
/*22  */         av_log(avctx, AV_LOG_ERROR, "Width 1 not supported.\n");             // (3) 0.05664
/*24  */         return AVERROR_INVALIDDATA;                                          // (14) 0.0332
/*26  */     }                                                                        // (23) 0.007812
/*30  */     if (   avctx->codec_tag == MKTAG('0', '1', '2', 'v')                     // (2) 0.05664
/*32  */         && avpkt->size % avctx->height == 0                                  // (10) 0.03906
/*34  */         && avpkt->size / avctx->height * 3 >= width * 8)                     // (5) 0.04883
/*36  */         stride = avpkt->size / avctx->height;                                // (9) 0.03906
/*40  */     if (avpkt->size < avctx->height * stride) {                              // (12) 0.03711
/*42  */         av_log(avctx, AV_LOG_ERROR, "Packet too small: %d instead of %d\n",  // (1) 0.06836
/*44  */                avpkt->size, avctx->height * stride);                         // (4) 0.05273
/*46  */         return AVERROR_INVALIDDATA;                                          // (13) 0.0332
/*48  */     }                                                                        // (24) 0.007812
/*52  */     if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)                            // (7) 0.04492
/*54  */         return ret;                                                          // (21) 0.01953
/*58  */     pic->pict_type = AV_PICTURE_TYPE_I;                                      // (11) 0.03711
/*60  */     pic->key_frame = 1;                                                      // (18) 0.02148
/*64  */     y = (uint16_t *)pic->data[0];                                            // 0.0
/*66  */     u = (uint16_t *)pic->data[1];                                            // 0.0
/*68  */     v = (uint16_t *)pic->data[2];                                            // 0.0
/*70  */     line_end = avpkt->data + stride;                                         // 0.0
/*74  */     while (line++ < avctx->height) {                                         // 0.0
/*76  */         while (1) {                                                          // 0.0
/*78  */             uint32_t t = AV_RL32(src);                                       // 0.0
/*80  */             src += 4;                                                        // 0.0
/*82  */             *u++ = t <<  6 & 0xFFC0;                                         // 0.0
/*84  */             *y++ = t >>  4 & 0xFFC0;                                         // 0.0
/*86  */             *v++ = t >> 14 & 0xFFC0;                                         // 0.0
/*90  */             if (src >= line_end - 1) {                                       // 0.0
/*92  */                 *y = 0x80;                                                   // 0.0
/*94  */                 src++;                                                       // 0.0
/*96  */                 line_end += stride;                                          // 0.0
/*98  */                 y = (uint16_t *)(pic->data[0] + line * pic->linesize[0]);    // 0.0
/*100 */                 u = (uint16_t *)(pic->data[1] + line * pic->linesize[1]);    // 0.0
/*102 */                 v = (uint16_t *)(pic->data[2] + line * pic->linesize[2]);    // 0.0
/*104 */                 break;                                                       // 0.0
/*106 */             }                                                                // 0.0
/*110 */             t = AV_RL32(src);                                                // 0.0
/*112 */             src += 4;                                                        // 0.0
/*114 */             *y++ = t <<  6 & 0xFFC0;                                         // 0.0
/*116 */             *u++ = t >>  4 & 0xFFC0;                                         // 0.0
/*118 */             *y++ = t >> 14 & 0xFFC0;                                         // 0.0
/*120 */             if (src >= line_end - 2) {                                       // 0.0
/*122 */                 if (!(width & 1)) {                                          // 0.0
/*124 */                     *y = 0x80;                                               // 0.0
/*126 */                     src += 2;                                                // 0.0
/*128 */                 }                                                            // 0.0
/*130 */                 line_end += stride;                                          // 0.0
/*132 */                 y = (uint16_t *)(pic->data[0] + line * pic->linesize[0]);    // 0.0
/*134 */                 u = (uint16_t *)(pic->data[1] + line * pic->linesize[1]);    // 0.0
/*136 */                 v = (uint16_t *)(pic->data[2] + line * pic->linesize[2]);    // 0.0
/*138 */                 break;                                                       // 0.0
/*140 */             }                                                                // 0.0
/*144 */             t = AV_RL32(src);                                                // 0.0
/*146 */             src += 4;                                                        // 0.0
/*148 */             *v++ = t <<  6 & 0xFFC0;                                         // 0.0
/*150 */             *y++ = t >>  4 & 0xFFC0;                                         // 0.0
/*152 */             *u++ = t >> 14 & 0xFFC0;                                         // 0.0
/*156 */             if (src >= line_end - 1) {                                       // 0.0
/*158 */                 *y = 0x80;                                                   // 0.0
/*160 */                 src++;                                                       // 0.0
/*162 */                 line_end += stride;                                          // 0.0
/*164 */                 y = (uint16_t *)(pic->data[0] + line * pic->linesize[0]);    // 0.0
/*166 */                 u = (uint16_t *)(pic->data[1] + line * pic->linesize[1]);    // 0.0
/*168 */                 v = (uint16_t *)(pic->data[2] + line * pic->linesize[2]);    // 0.0
/*170 */                 break;                                                       // 0.0
/*172 */             }                                                                // 0.0
/*176 */             t = AV_RL32(src);                                                // 0.0
/*178 */             src += 4;                                                        // 0.0
/*180 */             *y++ = t <<  6 & 0xFFC0;                                         // 0.0
/*182 */             *v++ = t >>  4 & 0xFFC0;                                         // 0.0
/*184 */             *y++ = t >> 14 & 0xFFC0;                                         // 0.0
/*188 */             if (src >= line_end - 2) {                                       // 0.0
/*190 */                 if (width & 1) {                                             // 0.0
/*192 */                     *y = 0x80;                                               // 0.0
/*194 */                     src += 2;                                                // 0.0
/*196 */                 }                                                            // 0.0
/*198 */                 line_end += stride;                                          // 0.0
/*200 */                 y = (uint16_t *)(pic->data[0] + line * pic->linesize[0]);    // 0.0
/*202 */                 u = (uint16_t *)(pic->data[1] + line * pic->linesize[1]);    // 0.0
/*204 */                 v = (uint16_t *)(pic->data[2] + line * pic->linesize[2]);    // 0.0
/*206 */                 break;                                                       // 0.0
/*208 */             }                                                                // 0.0
/*210 */         }                                                                    // 0.0
/*212 */     }                                                                        // 0.0
/*216 */     *got_frame = 1;                                                          // 0.0
/*220 */     return avpkt->size;                                                      // 0.0
/*222 */ }                                                                            // 0.0

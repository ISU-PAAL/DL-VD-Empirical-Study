// commit message FFmpeg@cf6914e27f (target=0, prob=0.59766763, correct=False): cdxl: remove early check for bpp
/*0   */ static int cdxl_decode_frame(AVCodecContext *avctx, void *data,                  // (6) 0.04494
/*2   */                              int *data_size, AVPacket *pkt)                      // (0) 0.08007
/*4   */ {                                                                                // (24) 0.001957
/*6   */     CDXLVideoContext *c = avctx->priv_data;                                      // (12) 0.03321
/*8   */     AVFrame * const p = &c->frame;                                               // (19) 0.02735
/*10  */     int ret, w, h, encoding, format, buf_size = pkt->size;                       // (7) 0.04492
/*12  */     const uint8_t *buf = pkt->data;                                              // (18) 0.03125
/*16  */     if (buf_size < 32)                                                           // (23) 0.0215
/*18  */         return AVERROR_INVALIDDATA;                                              // (13) 0.0332
/*20  */     encoding        = buf[1] & 7;                                                // (10) 0.03711
/*22  */     format          = buf[1] & 0xE0;                                             // (5) 0.04687
/*24  */     w               = AV_RB16(&buf[14]);                                         // (2) 0.05468
/*26  */     h               = AV_RB16(&buf[16]);                                         // (1) 0.05468
/*28  */     c->bpp          = buf[19];                                                   // (8) 0.04101
/*30  */     c->palette_size = AV_RB16(&buf[20]);                                         // (9) 0.03711
/*32  */     c->palette      = buf + 32;                                                  // (14) 0.0332
/*34  */     c->video        = c->palette + c->palette_size;                              // (3) 0.05077
/*36  */     c->video_size   = buf_size - c->palette_size - 32;                           // (4) 0.04687
/*40  */     if (c->palette_size > 512)                                                   // (20) 0.02735
/*42  */         return AVERROR_INVALIDDATA;                                              // (15) 0.0332
/*44  */     if (buf_size < c->palette_size + 32)                                         // (11) 0.03515
/*46  */         return AVERROR_INVALIDDATA;                                              // (17) 0.0332
/*48  */     if (c->bpp < 1)                                                              // (22) 0.02343
/*50  */         return AVERROR_INVALIDDATA;                                              // (16) 0.0332
/*52  */     if (c->bpp > 8) {                                                            // (21) 0.02539
/*54  */         av_log_ask_for_sample(avctx, "unsupported pixel size: %d\n", c->bpp);    // 0.0
/*56  */         return AVERROR_PATCHWELCOME;                                             // 0.0
/*58  */     }                                                                            // 0.0
/*60  */     if (format) {                                                                // 0.0
/*62  */         av_log_ask_for_sample(avctx, "unsupported pixel format: %d\n", format);  // 0.0
/*64  */         return AVERROR_PATCHWELCOME;                                             // 0.0
/*66  */     }                                                                            // 0.0
/*70  */     if ((ret = av_image_check_size(w, h, 0, avctx)) < 0)                         // 0.0
/*72  */         return ret;                                                              // 0.0
/*74  */     if (w != avctx->width || h != avctx->height)                                 // 0.0
/*76  */         avcodec_set_dimensions(avctx, w, h);                                     // 0.0
/*80  */     if (c->video_size < FFALIGN(avctx->width, 16) * avctx->height * c->bpp / 8)  // 0.0
/*82  */         return AVERROR_INVALIDDATA;                                              // 0.0
/*84  */     if (!encoding && c->palette_size && c->bpp <= 8) {                           // 0.0
/*86  */         avctx->pix_fmt = PIX_FMT_PAL8;                                           // 0.0
/*88  */     } else if (encoding == 1 && (c->bpp == 6 || c->bpp == 8)) {                  // 0.0
/*90  */         if (c->palette_size != (1 << (c->bpp - 1)))                              // 0.0
/*92  */             return AVERROR_INVALIDDATA;                                          // 0.0
/*94  */         avctx->pix_fmt = PIX_FMT_BGR24;                                          // 0.0
/*96  */     } else {                                                                     // 0.0
/*98  */         av_log_ask_for_sample(avctx, "unsupported encoding %d and bpp %d\n",     // 0.0
/*100 */                               encoding, c->bpp);                                 // 0.0
/*102 */         return AVERROR_PATCHWELCOME;                                             // 0.0
/*104 */     }                                                                            // 0.0
/*108 */     if (p->data[0])                                                              // 0.0
/*110 */         avctx->release_buffer(avctx, p);                                         // 0.0
/*114 */     p->reference = 0;                                                            // 0.0
/*116 */     if ((ret = avctx->get_buffer(avctx, p)) < 0) {                               // 0.0
/*118 */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                    // 0.0
/*120 */         return ret;                                                              // 0.0
/*122 */     }                                                                            // 0.0
/*124 */     p->pict_type = AV_PICTURE_TYPE_I;                                            // 0.0
/*128 */     if (encoding) {                                                              // 0.0
/*130 */         av_fast_padded_malloc(&c->new_video, &c->new_video_size,                 // 0.0
/*132 */                               h * w + FF_INPUT_BUFFER_PADDING_SIZE);             // 0.0
/*134 */         if (!c->new_video)                                                       // 0.0
/*136 */             return AVERROR(ENOMEM);                                              // 0.0
/*138 */         if (c->bpp == 8)                                                         // 0.0
/*140 */             cdxl_decode_ham8(c);                                                 // 0.0
/*142 */         else                                                                     // 0.0
/*144 */             cdxl_decode_ham6(c);                                                 // 0.0
/*146 */     } else {                                                                     // 0.0
/*148 */         cdxl_decode_rgb(c);                                                      // 0.0
/*150 */     }                                                                            // 0.0
/*152 */     *data_size      = sizeof(AVFrame);                                           // 0.0
/*154 */     *(AVFrame*)data = c->frame;                                                  // 0.0
/*158 */     return buf_size;                                                             // 0.0
/*160 */ }                                                                                // 0.0

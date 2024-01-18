// commit message FFmpeg@dc64f203a6 (target=1, prob=0.9992011, correct=True): ptx: check for out of bound reads
/*0   */ static int ptx_decode_frame(AVCodecContext *avctx, void *data, int *data_size,  // (3) 0.05498
/*2   */                             AVPacket *avpkt) {                                  // (0) 0.07014
/*4   */     const uint8_t *buf = avpkt->data;                                           // (13) 0.03315
/*7   */     PTXContext * const s = avctx->priv_data;                                    // (12) 0.03412
/*9   */     AVFrame *picture = data;                                                    // (22) 0.01952
/*11  */     AVFrame * const p = &s->picture;                                            // (15) 0.02731
/*13  */     unsigned int offset, w, h, y, stride, bytes_per_pixel;                      // (9) 0.04094
/*15  */     uint8_t *ptr;                                                               // (21) 0.01957
/*21  */     offset          = AV_RL16(buf);                                             // (7) 0.04117
/*23  */     w               = AV_RL16(buf+8);                                           // (5) 0.05456
/*25  */     h               = AV_RL16(buf+10);                                          // (4) 0.05459
/*27  */     bytes_per_pixel = AV_RL16(buf+12) >> 3;                                     // (10) 0.04094
/*31  */     if (bytes_per_pixel != 2) {                                                 // (14) 0.02732
/*33  */         av_log_ask_for_sample(avctx, "Image format is not RGB15.\n");           // (1) 0.0604
/*35  */         return -1;                                                              // (19) 0.02144
/*37  */     }                                                                           // (24) 0.007815
/*41  */     avctx->pix_fmt = PIX_FMT_RGB555;                                            // (8) 0.04095
/*45  */     if (buf_end - buf < offset)                                                 // (16) 0.02539
/*48  */     if (offset != 0x2c)                                                         // (17) 0.02339
/*50  */         av_log_ask_for_sample(avctx, "offset != 0x2c\n");                       // (2) 0.05845
/*54  */     buf += offset;                                                              // (23) 0.01364
/*58  */     if (p->data[0])                                                             // (18) 0.02144
/*60  */         avctx->release_buffer(avctx, p);                                        // (11) 0.03702
/*64  */     if (av_image_check_size(w, h, 0, avctx))                                    // (6) 0.04287
/*66  */         return -1;                                                              // (20) 0.02143
/*68  */     if (w != avctx->width || h != avctx->height)                                // 0.0
/*70  */         avcodec_set_dimensions(avctx, w, h);                                    // 0.0
/*72  */     if (avctx->get_buffer(avctx, p) < 0) {                                      // 0.0
/*74  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                   // 0.0
/*76  */         return -1;                                                              // 0.0
/*78  */     }                                                                           // 0.0
/*82  */     p->pict_type = AV_PICTURE_TYPE_I;                                           // 0.0
/*86  */     ptr    = p->data[0];                                                        // 0.0
/*88  */     stride = p->linesize[0];                                                    // 0.0
/*92  */     for (y=0; y<h; y++) {                                                       // 0.0
/*94  */         if (buf_end - buf < w * bytes_per_pixel)                                // 0.0
/*96  */             break;                                                              // 0.0
/*98  */ #if HAVE_BIGENDIAN                                                              // 0.0
/*100 */         unsigned int x;                                                         // 0.0
/*102 */         for (x=0; x<w*bytes_per_pixel; x+=bytes_per_pixel)                      // 0.0
/*104 */             AV_WN16(ptr+x, AV_RL16(buf+x));                                     // 0.0
/*106 */ #else                                                                           // 0.0
/*108 */         memcpy(ptr, buf, w*bytes_per_pixel);                                    // 0.0
/*110 */ #endif                                                                          // 0.0
/*112 */         ptr += stride;                                                          // 0.0
/*114 */         buf += w*bytes_per_pixel;                                               // 0.0
/*116 */     }                                                                           // 0.0
/*120 */     *picture = s->picture;                                                      // 0.0
/*122 */     *data_size = sizeof(AVPicture);                                             // 0.0
/*126 */     return offset + w*h*bytes_per_pixel;                                        // 0.0
/*128 */ }                                                                               // 0.0

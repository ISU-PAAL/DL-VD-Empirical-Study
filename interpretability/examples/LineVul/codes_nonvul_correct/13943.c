// commit message FFmpeg@121be31060 (target=0, prob=0.46014157, correct=True): avcodec/cinepak: Check side data size before use
/*0  */ static int cinepak_decode_frame(AVCodecContext *avctx,                                   // (10) 0.03711
/*2  */                                 void *data, int *got_frame,                              // (1) 0.08008
/*4  */                                 AVPacket *avpkt)                                         // (2) 0.07617
/*6  */ {                                                                                        // (24) 0.001953
/*8  */     const uint8_t *buf = avpkt->data;                                                    // (13) 0.0332
/*10 */     int ret = 0, buf_size = avpkt->size;                                                 // (11) 0.03516
/*12 */     CinepakContext *s = avctx->priv_data;                                                // (12) 0.0332
/*16 */     s->data = buf;                                                                       // (20) 0.01758
/*18 */     s->size = buf_size;                                                                  // (17) 0.02148
/*22 */     if ((ret = ff_reget_buffer(avctx, s->frame)) < 0)                                    // (6) 0.04687
/*24 */         return ret;                                                                      // (18) 0.01953
/*28 */     if (s->palette_video) {                                                              // (14) 0.02539
/*30 */         const uint8_t *pal = av_packet_get_side_data(avpkt, AV_PKT_DATA_PALETTE, NULL);  // (0) 0.08594
/*32 */         if (pal) {                                                                       // (16) 0.02344
/*34 */             s->frame->palette_has_changed = 1;                                           // (7) 0.04687
/*36 */             memcpy(s->pal, pal, AVPALETTE_SIZE);                                         // (5) 0.05664
/*38 */         }                                                                                // (21) 0.01562
/*40 */     }                                                                                    // (22) 0.007812
/*44 */     if ((ret = cinepak_decode(s)) < 0) {                                                 // (9) 0.03906
/*46 */         av_log(avctx, AV_LOG_ERROR, "cinepak_decode failed\n");                          // (3) 0.06055
/*48 */     }                                                                                    // (23) 0.007812
/*52 */     if (s->palette_video)                                                                // (15) 0.02344
/*54 */         memcpy (s->frame->data[1], s->pal, AVPALETTE_SIZE);                              // (4) 0.06055
/*58 */     if ((ret = av_frame_ref(data, s->frame)) < 0)                                        // (8) 0.04297
/*60 */         return ret;                                                                      // (19) 0.01953
/*64 */     *got_frame = 1;                                                                      // 0.0
/*68 */     /* report that the buffer was completely consumed */                                 // 0.0
/*70 */     return buf_size;                                                                     // 0.0
/*72 */ }                                                                                        // 0.0

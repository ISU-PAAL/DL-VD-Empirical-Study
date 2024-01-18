// commit message FFmpeg@70f9661542 (target=0, prob=0.60255986, correct=False): jpeg2000dec: initialize static data just once
/*0   */ static int jpeg2000_decode_frame(AVCodecContext *avctx, void *data,                    // (9) 0.04005
/*2   */                                  int *got_frame, AVPacket *avpkt)                      // (1) 0.07722
/*4   */ {                                                                                      // (23) 0.002708
/*6   */     Jpeg2000DecoderContext *s = avctx->priv_data;                                      // (14) 0.03214
/*8   */     ThreadFrame frame = { .f = data };                                                 // (20) 0.02234
/*10  */     AVFrame *picture = data;                                                           // (21) 0.01707
/*12  */     int tileno, ret;                                                                   // (22) 0.01557
/*16  */     s->avctx     = avctx;                                                              // (18) 0.025
/*18  */     s->buf       = s->buf_start = avpkt->data;                                         // (7) 0.04146
/*20  */     s->buf_end   = s->buf_start + avpkt->size;                                         // (10) 0.03823
/*22  */     s->curtileno = 0; // TODO: only one tile in DCI JP2K. to implement for more tiles  // (2) 0.05944
/*26  */     // reduction factor, i.e number of resolution levels to skip                       // (4) 0.04886
/*28  */     s->reduction_factor = s->lowres;                                                   // (17) 0.02667
/*32  */     ff_jpeg2000_init_tier1_luts();                                                     // (15) 0.02993
/*36  */     if (s->buf_end - s->buf < 2)                                                       // (16) 0.02911
/*38  */         return AVERROR(EINVAL);                                                        // (13) 0.03359
/*42  */     // check if the image is in jp2 format                                             // (0) 0.09697
/*44  */     if ((AV_RB32(s->buf) == 12) &&                                                     // (11) 0.03741
/*46  */         (AV_RB32(s->buf + 4) == JP2_SIG_TYPE) &&                                       // (5) 0.0483
/*48  */         (AV_RB32(s->buf + 8) == JP2_SIG_VALUE)) {                                      // (6) 0.04817
/*50  */         if (!jp2_find_codestream(s)) {                                                 // (12) 0.03566
/*52  */             av_log(avctx, AV_LOG_ERROR,                                                // (8) 0.0401
/*54  */                    "couldn't find jpeg2k codestream atom\n");                          // (3) 0.05685
/*56  */             return -1;                                                                 // (19) 0.02488
/*58  */         }                                                                              // 0.0
/*60  */     }                                                                                  // 0.0
/*64  */     if (bytestream_get_be16(&s->buf) != JPEG2000_SOC) {                                // 0.0
/*66  */         av_log(avctx, AV_LOG_ERROR, "SOC marker not present\n");                       // 0.0
/*68  */         return -1;                                                                     // 0.0
/*70  */     }                                                                                  // 0.0
/*72  */     if (ret = jpeg2000_read_main_headers(s))                                           // 0.0
/*74  */         goto end;                                                                      // 0.0
/*78  */     /* get picture buffer */                                                           // 0.0
/*80  */     if ((ret = ff_thread_get_buffer(avctx, &frame, 0)) < 0) {                          // 0.0
/*82  */         av_log(avctx, AV_LOG_ERROR, "ff_thread_get_buffer() failed.\n");               // 0.0
/*84  */         goto end;                                                                      // 0.0
/*86  */     }                                                                                  // 0.0
/*88  */     picture->pict_type = AV_PICTURE_TYPE_I;                                            // 0.0
/*90  */     picture->key_frame = 1;                                                            // 0.0
/*94  */     if (ret = jpeg2000_read_bitstream_packets(s))                                      // 0.0
/*96  */         goto end;                                                                      // 0.0
/*98  */     for (tileno = 0; tileno < s->numXtiles * s->numYtiles; tileno++)                   // 0.0
/*100 */         if (ret = jpeg2000_decode_tile(s, s->tile + tileno, picture))                  // 0.0
/*102 */             goto end;                                                                  // 0.0
/*106 */     *got_frame = 1;                                                                    // 0.0
/*110 */ end:                                                                                   // 0.0
/*112 */     jpeg2000_dec_cleanup(s);                                                           // 0.0
/*114 */     return ret ? ret : s->buf - s->buf_start;                                          // 0.0
/*116 */ }                                                                                      // 0.0

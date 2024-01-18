// commit message FFmpeg@2862b63783 (target=0, prob=0.7062671, correct=False): lavc: Move prediction_method to codec private options
/*0  */ static int ljpeg_encode_frame(AVCodecContext *avctx, AVPacket *pkt,                              // (8) 0.05078
/*2  */                               const AVFrame *pict, int *got_packet)                              // (0) 0.08203
/*4  */ {                                                                                                // (22) 0.001953
/*6  */     LJpegEncContext *s = avctx->priv_data;                                                       // (13) 0.03516
/*8  */     PutBitContext pb;                                                                            // (18) 0.01758
/*10 */     const int width  = avctx->width;                                                             // (14) 0.02539
/*12 */     const int height = avctx->height;                                                            // (15) 0.02344
/*14 */     const int mb_width  = (width  + s->hsample[0] - 1) / s->hsample[0];                          // (3) 0.06445
/*16 */     const int mb_height = (height + s->vsample[0] - 1) / s->vsample[0];                          // (4) 0.06055
/*18 */     int max_pkt_size = AV_INPUT_BUFFER_MIN_SIZE;                                                 // (10) 0.04492
/*20 */     int ret, header_bits;                                                                        // (16) 0.01953
/*24 */     if (avctx->pix_fmt == AV_PIX_FMT_BGR24)                                                      // (9) 0.05078
/*26 */         max_pkt_size += width * height * 3 * 3;                                                  // (11) 0.04297
/*28 */     else {                                                                                       // (19) 0.009766
/*30 */         max_pkt_size += mb_width * mb_height * 3 * 4                                             // (7) 0.05273
/*32 */                         * s->hsample[0] * s->vsample[0];                                         // (2) 0.07617
/*34 */     }                                                                                            // (20) 0.007812
/*36 */     if ((ret = ff_alloc_packet(pkt, max_pkt_size)) < 0) {                                        // (6) 0.05469
/*38 */         av_log(avctx, AV_LOG_ERROR, "Error getting output packet of size %d.\n", max_pkt_size);  // (1) 0.07813
/*40 */         return ret;                                                                              // (17) 0.01953
/*42 */     }                                                                                            // (21) 0.007812
/*46 */     init_put_bits(&pb, pkt->data, pkt->size);                                                    // (12) 0.04102
/*50 */     ff_mjpeg_encode_picture_header(avctx, &pb, &s->scantable,                                    // (5) 0.05664
/*52 */                                    s->matrix);                                                   // 0.0
/*56 */     header_bits = put_bits_count(&pb);                                                           // 0.0
/*60 */     if (avctx->pix_fmt == AV_PIX_FMT_BGR24)                                                      // 0.0
/*62 */         ret = ljpeg_encode_bgr(avctx, &pb, pict);                                                // 0.0
/*64 */     else                                                                                         // 0.0
/*66 */         ret = ljpeg_encode_yuv(avctx, &pb, pict);                                                // 0.0
/*68 */     if (ret < 0)                                                                                 // 0.0
/*70 */         return ret;                                                                              // 0.0
/*74 */     emms_c();                                                                                    // 0.0
/*78 */     ff_mjpeg_encode_picture_trailer(&pb, header_bits);                                           // 0.0
/*82 */     flush_put_bits(&pb);                                                                         // 0.0
/*84 */     pkt->size   = put_bits_ptr(&pb) - pb.buf;                                                    // 0.0
/*86 */     pkt->flags |= AV_PKT_FLAG_KEY;                                                               // 0.0
/*88 */     *got_packet = 1;                                                                             // 0.0
/*92 */     return 0;                                                                                    // 0.0
/*94 */ }                                                                                                // 0.0

// commit message FFmpeg@bd255f9feb (target=0, prob=0.5515753, correct=False): lavc: set frame parameters after decoding only if necessary
/*0  */ int attribute_align_arg avcodec_decode_video2(AVCodecContext *avctx, AVFrame *picture,                                          // (8) 0.05664
/*2  */                                               int *got_picture_ptr,                                                             // (1) 0.1035
/*4  */                                               AVPacket *avpkt)                                                                  // (0) 0.1035
/*6  */ {                                                                                                                               // (16) 0.001953
/*8  */     int ret;                                                                                                                    // (15) 0.01172
/*12 */     *got_picture_ptr = 0;                                                                                                       // (12) 0.02344
/*14 */     if ((avctx->coded_width || avctx->coded_height) && av_image_check_size(avctx->coded_width, avctx->coded_height, 0, avctx))  // (3) 0.0918
/*16 */         return -1;                                                                                                              // (13) 0.02148
/*20 */     avctx->pkt = avpkt;                                                                                                         // (11) 0.02539
/*22 */     apply_param_change(avctx, avpkt);                                                                                           // (10) 0.03125
/*26 */     avcodec_get_frame_defaults(picture);                                                                                        // (9) 0.03125
/*30 */     if ((avctx->codec->capabilities & CODEC_CAP_DELAY) || avpkt->size || (avctx->active_thread_type & FF_THREAD_FRAME)) {       // (2) 0.09766
/*32 */         if (HAVE_THREADS && avctx->active_thread_type & FF_THREAD_FRAME)                                                        // (7) 0.06445
/*34 */             ret = ff_thread_decode_frame(avctx, picture, got_picture_ptr,                                                       // (5) 0.06445
/*36 */                                          avpkt);                                                                                // (4) 0.08594
/*38 */         else {                                                                                                                  // (14) 0.01758
/*40 */             ret = avctx->codec->decode(avctx, picture, got_picture_ptr,                                                         // (6) 0.06445
/*42 */                                        avpkt);                                                                                  // 0.0
/*44 */             picture->pkt_dts             = avpkt->dts;                                                                          // 0.0
/*46 */             picture->sample_aspect_ratio = avctx->sample_aspect_ratio;                                                          // 0.0
/*48 */             picture->width               = avctx->width;                                                                        // 0.0
/*50 */             picture->height              = avctx->height;                                                                       // 0.0
/*52 */             picture->format              = avctx->pix_fmt;                                                                      // 0.0
/*54 */         }                                                                                                                       // 0.0
/*58 */         emms_c(); //needed to avoid an emms_c() call before every return;                                                       // 0.0
/*62 */         if (*got_picture_ptr)                                                                                                   // 0.0
/*64 */             avctx->frame_number++;                                                                                              // 0.0
/*66 */     } else                                                                                                                      // 0.0
/*68 */         ret = 0;                                                                                                                // 0.0
/*72 */     /* many decoders assign whole AVFrames, thus overwriting extended_data;                                                     // 0.0
/*74 */      * make sure it's set correctly */                                                                                          // 0.0
/*76 */     picture->extended_data = picture->data;                                                                                     // 0.0
/*80 */     return ret;                                                                                                                 // 0.0
/*82 */ }                                                                                                                               // 0.0

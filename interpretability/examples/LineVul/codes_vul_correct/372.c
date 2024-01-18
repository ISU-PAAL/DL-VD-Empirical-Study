// commit message FFmpeg@1bc64c2814 (target=1, prob=0.99912137, correct=True): lavc: initialize output AVFrame before decoding.
/*0  */ int attribute_align_arg avcodec_decode_video2(AVCodecContext *avctx, AVFrame *picture,                                          // (9) 0.05664
/*1  */                                               int *got_picture_ptr,                                                             // (1) 0.1035
/*2  */                                               AVPacket *avpkt)                                                                  // (0) 0.1035
/*3  */ {                                                                                                                               // (16) 0.001953
/*4  */     int ret;                                                                                                                    // (15) 0.01172
/*5  */     *got_picture_ptr = 0;                                                                                                       // (12) 0.02344
/*6  */     if ((avctx->coded_width || avctx->coded_height) && av_image_check_size(avctx->coded_width, avctx->coded_height, 0, avctx))  // (3) 0.0918
/*7  */         return -1;                                                                                                              // (13) 0.02148
/*8  */     avctx->pkt = avpkt;                                                                                                         // (11) 0.02539
/*9  */     apply_param_change(avctx, avpkt);                                                                                           // (10) 0.03125
/*10 */     if ((avctx->codec->capabilities & CODEC_CAP_DELAY) || avpkt->size || (avctx->active_thread_type & FF_THREAD_FRAME)) {       // (2) 0.09766
/*11 */         if (HAVE_THREADS && avctx->active_thread_type & FF_THREAD_FRAME)                                                        // (8) 0.06445
/*12 */             ret = ff_thread_decode_frame(avctx, picture, got_picture_ptr,                                                       // (6) 0.06445
/*13 */                                          avpkt);                                                                                // (4) 0.08594
/*14 */         else {                                                                                                                  // (14) 0.01758
/*15 */             ret = avctx->codec->decode(avctx, picture, got_picture_ptr,                                                         // (7) 0.06445
/*16 */                                        avpkt);                                                                                  // (5) 0.08203
/*17 */             picture->pkt_dts             = avpkt->dts;                                                                          // 0.0
/*18 */             picture->sample_aspect_ratio = avctx->sample_aspect_ratio;                                                          // 0.0
/*19 */             picture->width               = avctx->width;                                                                        // 0.0
/*20 */             picture->height              = avctx->height;                                                                       // 0.0
/*21 */             picture->format              = avctx->pix_fmt;                                                                      // 0.0
/*22 */         }                                                                                                                       // 0.0
/*23 */         emms_c(); //needed to avoid an emms_c() call before every return;                                                       // 0.0
/*24 */         if (*got_picture_ptr)                                                                                                   // 0.0
/*25 */             avctx->frame_number++;                                                                                              // 0.0
/*26 */     } else                                                                                                                      // 0.0
/*27 */         ret = 0;                                                                                                                // 0.0
/*28 */     /* many decoders assign whole AVFrames, thus overwriting extended_data;                                                     // 0.0
/*29 */      * make sure it's set correctly */                                                                                          // 0.0
/*30 */     picture->extended_data = picture->data;                                                                                     // 0.0
/*31 */     return ret;                                                                                                                 // 0.0
/*32 */ }                                                                                                                               // 0.0

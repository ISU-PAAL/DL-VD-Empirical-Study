// commit message FFmpeg@3c5cf2a31b (target=0, prob=0.43056014, correct=True): screenpresso: Drop parameter change check
/*0   */ static int screenpresso_decode_frame(AVCodecContext *avctx, void *data,        // (7) 0.04492
/*2   */                                      int *got_frame, AVPacket *avpkt)          // (0) 0.09765
/*4   */ {                                                                              // (24) 0.001983
/*6   */     ScreenpressoContext *ctx = avctx->priv_data;                               // (11) 0.0332
/*8   */     AVFrame *frame = data;                                                     // (18) 0.01954
/*10  */     int keyframe;                                                              // (20) 0.01367
/*12  */     int ret;                                                                   // (21) 0.01172
/*16  */     /* Size check */                                                           // (19) 0.01367
/*18  */     if (avpkt->size < 3) {                                                     // (14) 0.02734
/*20  */         av_log(avctx, AV_LOG_ERROR, "Packet too small (%d)\n", avpkt->size);   // (1) 0.0703
/*22  */         return AVERROR_INVALIDDATA;                                            // (12) 0.0332
/*24  */     }                                                                          // (22) 0.007812
/*28  */     /* Basic sanity check, but not really harmful */                           // (16) 0.02539
/*30  */     if ((avpkt->data[0] != 0x73 && avpkt->data[0] != 0x72) ||                  // (4) 0.06249
/*32  */         avpkt->data[1] != 8) { // bpp probably                                 // (8) 0.04492
/*34  */         av_log(avctx, AV_LOG_WARNING, "Unknown header 0x%02X%02X\n",           // (3) 0.0664
/*36  */                avpkt->data[0], avpkt->data[1]);                                // (5) 0.05859
/*38  */     }                                                                          // (23) 0.007812
/*40  */     keyframe = (avpkt->data[0] == 0x73);                                       // (9) 0.03906
/*44  */     /* Resize deflate buffer and frame on resolution change */                 // (13) 0.02929
/*46  */     if (ctx->inflated_size != avctx->width * avctx->height * 3) {              // (6) 0.05077
/*48  */         av_frame_unref(ctx->current);                                          // (10) 0.03515
/*50  */         ret = ff_get_buffer(avctx, ctx->current, AV_GET_BUFFER_FLAG_REF);      // (2) 0.0664
/*52  */         if (ret < 0)                                                           // (17) 0.02539
/*54  */             return ret;                                                        // (15) 0.02734
/*58  */         /* If malloc fails, reset len to avoid preserving an invalid value */  // 0.0
/*60  */         ctx->inflated_size = avctx->width * avctx->height * 3;                 // 0.0
/*62  */         ret = av_reallocp(&ctx->inflated_buf, ctx->inflated_size);             // 0.0
/*64  */         if (ret < 0) {                                                         // 0.0
/*66  */             ctx->inflated_size = 0;                                            // 0.0
/*68  */             return ret;                                                        // 0.0
/*70  */         }                                                                      // 0.0
/*72  */     }                                                                          // 0.0
/*76  */     /* Inflate the frame after the 2 byte header */                            // 0.0
/*78  */     ret = uncompress(ctx->inflated_buf, &ctx->inflated_size,                   // 0.0
/*80  */                      avpkt->data + 2, avpkt->size - 2);                        // 0.0
/*82  */     if (ret) {                                                                 // 0.0
/*84  */         av_log(avctx, AV_LOG_ERROR, "Deflate error %d.\n", ret);               // 0.0
/*86  */         return AVERROR_UNKNOWN;                                                // 0.0
/*88  */     }                                                                          // 0.0
/*92  */     /* When a keyframe is found, copy it (flipped) */                          // 0.0
/*94  */     if (keyframe)                                                              // 0.0
/*96  */         av_image_copy_plane(ctx->current->data[0] +                            // 0.0
/*98  */                             ctx->current->linesize[0] * (avctx->height - 1),   // 0.0
/*100 */                             -1 * ctx->current->linesize[0],                    // 0.0
/*102 */                             ctx->inflated_buf, avctx->width * 3,               // 0.0
/*104 */                             avctx->width * 3, avctx->height);                  // 0.0
/*106 */     /* Otherwise sum the delta on top of the current frame */                  // 0.0
/*108 */     else                                                                       // 0.0
/*110 */         sum_delta_flipped(ctx->current->data[0], ctx->current->linesize[0],    // 0.0
/*112 */                           ctx->inflated_buf, avctx->width * 3,                 // 0.0
/*114 */                           avctx->width * 3, avctx->height);                    // 0.0
/*118 */     /* Frame is ready to be output */                                          // 0.0
/*120 */     ret = av_frame_ref(frame, ctx->current);                                   // 0.0
/*122 */     if (ret < 0)                                                               // 0.0
/*124 */         return ret;                                                            // 0.0
/*128 */     /* Usual properties */                                                     // 0.0
/*130 */     if (keyframe) {                                                            // 0.0
/*132 */         frame->pict_type = AV_PICTURE_TYPE_I;                                  // 0.0
/*134 */         frame->key_frame = 1;                                                  // 0.0
/*136 */     } else {                                                                   // 0.0
/*138 */         frame->pict_type = AV_PICTURE_TYPE_P;                                  // 0.0
/*140 */     }                                                                          // 0.0
/*142 */     *got_frame = 1;                                                            // 0.0
/*146 */     return 0;                                                                  // 0.0
/*148 */ }                                                                              // 0.0

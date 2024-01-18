// commit message FFmpeg@c8241e730f (target=0, prob=0.15009996, correct=True): vaapi_encode: Refactor initialisation
/*0  */ av_cold int ff_vaapi_encode_close(AVCodecContext *avctx)         // (2) 0.04857
/*2  */ {                                                                // (25) 0.002208
/*4  */     VAAPIEncodeContext *ctx = avctx->priv_data;                  // (11) 0.03974
/*6  */     VAAPIEncodePicture *pic, *next;                              // (17) 0.03091
/*10 */     for (pic = ctx->pic_start; pic; pic = next) {                // (5) 0.04636
/*12 */         next = pic->next;                                        // (19) 0.0287
/*14 */         vaapi_encode_free(avctx, pic);                           // (7) 0.04415
/*16 */     }                                                            // (23) 0.00883
/*20 */     if (ctx->va_context != VA_INVALID_ID) {                      // (8) 0.04415
/*22 */         vaDestroyContext(ctx->hwctx->display, ctx->va_context);  // (0) 0.05519
/*24 */         ctx->va_context = VA_INVALID_ID;                         // (3) 0.04857
/*26 */     }                                                            // (24) 0.00883
/*30 */     if (ctx->va_config != VA_INVALID_ID) {                       // (9) 0.04415
/*32 */         vaDestroyConfig(ctx->hwctx->display, ctx->va_config);    // (1) 0.05519
/*34 */         ctx->va_config = VA_INVALID_ID;                          // (4) 0.04857
/*36 */     }                                                            // (22) 0.00883
/*40 */     if (ctx->codec->close)                                       // (20) 0.02649
/*42 */         ctx->codec->close(avctx);                                // (12) 0.03974
/*46 */     av_buffer_pool_uninit(&ctx->output_buffer_pool);             // (6) 0.04415
/*50 */     av_freep(&ctx->codec_sequence_params);                       // (14) 0.03753
/*52 */     av_freep(&ctx->codec_picture_params);                        // (15) 0.03753
/*56 */     av_buffer_unref(&ctx->recon_frames_ref);                     // (10) 0.04194
/*58 */     av_buffer_unref(&ctx->input_frames_ref);                     // (13) 0.03974
/*60 */     av_buffer_unref(&ctx->device_ref);                           // (16) 0.03532
/*64 */     av_freep(&ctx->priv_data);                                   // (18) 0.03091
/*68 */     return 0;                                                    // (21) 0.01325
/*70 */ }                                                                // (26) 0.002208

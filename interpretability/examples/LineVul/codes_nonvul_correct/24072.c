// commit message FFmpeg@48e52e4edd (target=0, prob=0.3010244, correct=True): avcodec/nvenc: add some more error case checks
/*0  */ static int nvenc_find_free_reg_resource(AVCodecContext *avctx)                      // (10) 0.04409
/*2  */ {                                                                                   // (21) 0.002004
/*4  */     NvencContext *ctx = avctx->priv_data;                                           // (12) 0.03407
/*6  */     NvencDynLoadFunctions *dl_fn = &ctx->nvenc_dload_funcs;                         // (5) 0.05812
/*8  */     NV_ENCODE_API_FUNCTION_LIST *p_nvenc = &dl_fn->nvenc_funcs;                     // (2) 0.06814
/*12 */     int i;                                                                          // (18) 0.01202
/*16 */     if (ctx->nb_registered_frames == FF_ARRAY_ELEMS(ctx->registered_frames)) {      // (4) 0.05812
/*18 */         for (i = 0; i < ctx->nb_registered_frames; i++) {                           // (7) 0.05411
/*20 */             if (!ctx->registered_frames[i].mapped) {                                // (9) 0.0501
/*22 */                 if (ctx->registered_frames[i].regptr) {                             // (6) 0.05812
/*24 */                     p_nvenc->nvEncUnregisterResource(ctx->nvencoder,                // (1) 0.07615
/*26 */                                                 ctx->registered_frames[i].regptr);  // (0) 0.1182
/*28 */                     ctx->registered_frames[i].regptr = NULL;                        // (3) 0.06613
/*30 */                 }                                                                   // (14) 0.03206
/*32 */                 return i;                                                           // (11) 0.03607
/*34 */             }                                                                       // (16) 0.02405
/*36 */         }                                                                           // (17) 0.01603
/*38 */     } else {                                                                        // (19) 0.01202
/*40 */         return ctx->nb_registered_frames++;                                         // (13) 0.03407
/*42 */     }                                                                               // (20) 0.008016
/*46 */     av_log(avctx, AV_LOG_ERROR, "Too many registered CUDA frames\n");               // (8) 0.0521
/*48 */     return AVERROR(ENOMEM);                                                         // (15) 0.02405
/*50 */ }                                                                                   // (22) 0.002004

// commit message FFmpeg@bf238a6a3c (target=1, prob=0.47234094, correct=False): vf_hwupload: Add missing return value check
/*0   */ static int hwupload_query_formats(AVFilterContext *avctx)                        // (9) 0.03516
/*2   */ {                                                                                // (28) 0.001953
/*4   */     HWUploadContext *ctx = avctx->priv;                                          // (17) 0.02734
/*6   */     AVHWFramesConstraints *constraints = NULL;                                   // (10) 0.0332
/*8   */     const enum AVPixelFormat *input_pix_fmts, *output_pix_fmts;                  // (1) 0.05273
/*10  */     AVFilterFormats *input_formats = NULL;                                       // (15) 0.0293
/*12  */     int err, i;                                                                  // (24) 0.01563
/*16  */     if (!avctx->hw_device_ctx) {                                                 // (16) 0.0293
/*18  */         av_log(ctx, AV_LOG_ERROR, "A hardware device reference is required "     // (2) 0.05273
/*20  */                "to upload frames to.\n");                                        // (6) 0.04492
/*22  */         return AVERROR(EINVAL);                                                  // (13) 0.03125
/*24  */     }                                                                            // (26) 0.007812
/*28  */     ctx->hwdevice_ref = av_buffer_ref(avctx->hw_device_ctx);                     // (3) 0.05078
/*30  */     if (!ctx->hwdevice_ref)                                                      // (19) 0.02344
/*32  */         return AVERROR(ENOMEM);                                                  // (14) 0.03125
/*34  */     ctx->hwdevice = (AVHWDeviceContext*)ctx->hwdevice_ref->data;                 // (4) 0.04883
/*38  */     constraints = av_hwdevice_get_hwframe_constraints(ctx->hwdevice_ref, NULL);  // (0) 0.05469
/*40  */     if (!constraints) {                                                          // (23) 0.01953
/*42  */         err = AVERROR(EINVAL);                                                   // (12) 0.0332
/*44  */         goto fail;                                                               // (22) 0.01953
/*46  */     }                                                                            // (27) 0.007812
/*50  */     input_pix_fmts  = constraints->valid_sw_formats;                             // (7) 0.04102
/*52  */     output_pix_fmts = constraints->valid_hw_formats;                             // (8) 0.03906
/*56  */     input_formats = ff_make_format_list(output_pix_fmts);                        // (5) 0.04687
/*58  */     if (!input_formats) {                                                        // (20) 0.02148
/*60  */         err = AVERROR(ENOMEM);                                                   // (11) 0.0332
/*62  */         goto fail;                                                               // (21) 0.01953
/*64  */     }                                                                            // (25) 0.007813
/*66  */     if (input_pix_fmts) {                                                        // (18) 0.02734
/*68  */         for (i = 0; input_pix_fmts[i] != AV_PIX_FMT_NONE; i++) {                 // 0.0
/*70  */             err = ff_add_format(&input_formats, input_pix_fmts[i]);              // 0.0
/*72  */             if (err < 0) {                                                       // 0.0
/*74  */                 ff_formats_unref(&input_formats);                                // 0.0
/*76  */                 goto fail;                                                       // 0.0
/*78  */             }                                                                    // 0.0
/*80  */         }                                                                        // 0.0
/*82  */     }                                                                            // 0.0
/*86  */     ff_formats_ref(input_formats, &avctx->inputs[0]->out_formats);               // 0.0
/*90  */     ff_formats_ref(ff_make_format_list(output_pix_fmts),                         // 0.0
/*92  */                    &avctx->outputs[0]->in_formats);                              // 0.0
/*96  */     av_hwframe_constraints_free(&constraints);                                   // 0.0
/*98  */     return 0;                                                                    // 0.0
/*102 */ fail:                                                                            // 0.0
/*104 */     av_buffer_unref(&ctx->hwdevice_ref);                                         // 0.0
/*106 */     av_hwframe_constraints_free(&constraints);                                   // 0.0
/*108 */     return err;                                                                  // 0.0
/*110 */ }                                                                                // 0.0

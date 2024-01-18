// commit message FFmpeg@70143a3954 (target=0, prob=0.49895835, correct=True): dxva: add support for new dxva2 and d3d11 hwaccel APIs
/*0  */ static int dxva2_retrieve_data(AVCodecContext *s, AVFrame *frame)  // (2) 0.08745
/*2  */ {                                                                  // (15) 0.003802
/*4  */     InputStream        *ist = s->opaque;                           // (5) 0.07605
/*6  */     DXVA2Context       *ctx = ist->hwaccel_ctx;                    // (0) 0.09506
/*8  */     int                ret;                                        // (4) 0.07985
/*12 */     ret = av_hwframe_transfer_data(ctx->tmp_frame, frame, 0);      // (1) 0.09125
/*14 */     if (ret < 0)                                                   // (12) 0.03422
/*16 */         return ret;                                                // (9) 0.03802
/*20 */     ret = av_frame_copy_props(ctx->tmp_frame, frame);              // (3) 0.08365
/*22 */     if (ret < 0) {                                                 // (10) 0.03802
/*24 */         av_frame_unref(ctx->tmp_frame);                            // (6) 0.07605
/*26 */         return ret;                                                // (11) 0.03802
/*28 */     }                                                              // (14) 0.01521
/*32 */     av_frame_unref(frame);                                         // (8) 0.04563
/*34 */     av_frame_move_ref(frame, ctx->tmp_frame);                      // (7) 0.07605
/*38 */     return 0;                                                      // (13) 0.02281
/*40 */ }                                                                  // (16) 0.003802

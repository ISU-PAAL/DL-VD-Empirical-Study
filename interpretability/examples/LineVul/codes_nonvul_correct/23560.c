// commit message FFmpeg@70143a3954 (target=0, prob=0.045231342, correct=True): dxva: add support for new dxva2 and d3d11 hwaccel APIs
/*0  */ static int dxva2_get_buffer(AVCodecContext *s, AVFrame *frame, int flags)  // (0) 0.2604
/*2  */ {                                                                          // (4) 0.01042
/*4  */     InputStream  *ist = s->opaque;                                         // (3) 0.1458
/*6  */     DXVA2Context *ctx = ist->hwaccel_ctx;                                  // (2) 0.1979
/*10 */     return av_hwframe_get_buffer(ctx->hw_frames_ctx, frame, 0);            // (1) 0.2604
/*12 */ }                                                                          // (5) 0.01042

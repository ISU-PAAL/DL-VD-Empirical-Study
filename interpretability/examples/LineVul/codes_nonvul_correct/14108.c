// commit message FFmpeg@70143a3954 (target=0, prob=0.36494765, correct=True): dxva: add support for new dxva2 and d3d11 hwaccel APIs
/*0  */ int dxva2_init(AVCodecContext *s)                                                                 // (13) 0.02734
/*2  */ {                                                                                                 // (24) 0.001953
/*4  */     InputStream *ist = s->opaque;                                                                 // (16) 0.02539
/*6  */     int loglevel = (ist->hwaccel_id == HWACCEL_AUTO) ? AV_LOG_VERBOSE : AV_LOG_ERROR;             // (4) 0.07617
/*8  */     DXVA2Context *ctx;                                                                            // (18) 0.01953
/*10 */     int ret;                                                                                      // (20) 0.01172
/*14 */     if (!ist->hwaccel_ctx) {                                                                      // (14) 0.02734
/*16 */         ret = dxva2_alloc(s);                                                                     // (8) 0.0332
/*18 */         if (ret < 0)                                                                              // (17) 0.02539
/*20 */             return ret;                                                                           // (15) 0.02734
/*22 */     }                                                                                             // (23) 0.007812
/*24 */     ctx = ist->hwaccel_ctx;                                                                       // (12) 0.0293
/*28 */     if (s->codec_id == AV_CODEC_ID_H264 &&                                                        // (6) 0.04492
/*30 */         (s->profile & ~FF_PROFILE_H264_CONSTRAINED) > FF_PROFILE_H264_HIGH) {                     // (1) 0.07812
/*32 */         av_log(NULL, loglevel, "Unsupported H.264 profile for DXVA2 HWAccel: %d\n", s->profile);  // (0) 0.08008
/*34 */         return AVERROR(EINVAL);                                                                   // (11) 0.03125
/*36 */     }                                                                                             // (21) 0.007813
/*40 */     if (s->codec_id == AV_CODEC_ID_HEVC &&                                                        // (5) 0.04492
/*42 */         s->profile != FF_PROFILE_HEVC_MAIN && s->profile != FF_PROFILE_HEVC_MAIN_10) {            // (3) 0.07812
/*44 */         av_log(NULL, loglevel, "Unsupported HEVC profile for DXVA2 HWAccel: %d\n", s->profile);   // (2) 0.07812
/*46 */         return AVERROR(EINVAL);                                                                   // (10) 0.03125
/*48 */     }                                                                                             // (22) 0.007812
/*52 */     av_buffer_unref(&ctx->hw_frames_ctx);                                                         // (7) 0.03516
/*56 */     ret = dxva2_create_decoder(s);                                                                // (9) 0.03125
/*58 */     if (ret < 0) {                                                                                // (19) 0.01953
/*60 */         av_log(NULL, loglevel, "Error creating the DXVA2 decoder\n");                             // 0.0
/*62 */         return ret;                                                                               // 0.0
/*64 */     }                                                                                             // 0.0
/*68 */     return 0;                                                                                     // 0.0
/*70 */ }                                                                                                 // 0.0

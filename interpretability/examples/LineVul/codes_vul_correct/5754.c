// commit message FFmpeg@295b79b5d8 (target=1, prob=0.999057, correct=True): avcodec/roqvideoenc: Check for av_malloc_array() failure
/*0  */ static av_cold int roq_encode_init(AVCodecContext *avctx)                                                       // (8) 0.04117
/*1  */ {                                                                                                               // (23) 0.001953
/*2  */     RoqContext *enc = avctx->priv_data;                                                                         // (12) 0.03125
/*3  */     av_lfg_init(&enc->randctx, 1);                                                                              // (11) 0.03317
/*4  */     enc->framesSinceKeyframe = 0;                                                                               // (17) 0.02341
/*5  */     if ((avctx->width & 0xf) || (avctx->height & 0xf)) {                                                        // (6) 0.04682
/*6  */         av_log(avctx, AV_LOG_ERROR, "Dimensions must be divisible by 16\n");                                    // (4) 0.06243
/*7  */         return AVERROR(EINVAL);                                                                                 // (13) 0.03121
/*8  */     if (avctx->width > 65535 || avctx->height > 65535) {                                                        // (7) 0.04292
/*9  */         av_log(avctx, AV_LOG_ERROR, "Dimensions are max %d\n", enc->quake3_compat ? 32768 : 65535);             // (0) 0.08789
/*10 */         return AVERROR(EINVAL);                                                                                 // (14) 0.03121
/*11 */     if (((avctx->width)&(avctx->width-1))||((avctx->height)&(avctx->height-1)))                                 // (2) 0.07023
/*12 */         av_log(avctx, AV_LOG_ERROR, "Warning: dimensions not power of two, this is not supported by quake\n");  // (1) 0.07474
/*13 */     enc->width = avctx->width;                                                                                  // (16) 0.02341
/*14 */     enc->height = avctx->height;                                                                                // (18) 0.02341
/*15 */     enc->framesSinceKeyframe = 0;                                                                               // (19) 0.02341
/*16 */     enc->first_frame = 1;                                                                                       // (20) 0.02146
/*17 */     enc->last_frame    = av_frame_alloc();                                                                      // (10) 0.03512
/*18 */     enc->current_frame = av_frame_alloc();                                                                      // (15) 0.02926
/*19 */     if (!enc->last_frame || !enc->current_frame) {                                                              // (9) 0.03707
/*20 */     enc->tmpData      = av_malloc(sizeof(RoqTempdata));                                                         // (5) 0.05074
/*21 */     enc->this_motion4 =                                                                                         // (21) 0.01957
/*22 */         av_mallocz_array((enc->width*enc->height/16), sizeof(motion_vect));                                     // (3) 0.06246
/*23 */     enc->last_motion4 =                                                                                         // (22) 0.01956
/*24 */         av_malloc_array ((enc->width*enc->height/16), sizeof(motion_vect));                                     // 0.0
/*25 */     enc->this_motion8 =                                                                                         // 0.0
/*26 */         av_mallocz_array((enc->width*enc->height/64), sizeof(motion_vect));                                     // 0.0
/*27 */     enc->last_motion8 =                                                                                         // 0.0
/*28 */         av_malloc_array ((enc->width*enc->height/64), sizeof(motion_vect));                                     // 0.0
/*29 */     return 0;                                                                                                   // 0.0

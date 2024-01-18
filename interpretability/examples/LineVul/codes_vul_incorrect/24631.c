// commit message FFmpeg@a8bdf2405c (target=1, prob=0.10509531, correct=False): check for coded_frame allocation failure in several audio encoders
/*0  */ static av_cold int roq_dpcm_encode_init(AVCodecContext *avctx)          // (4) 0.07251
/*2  */ {                                                                       // (18) 0.003021
/*4  */     ROQDPCMContext *context = avctx->priv_data;                         // (7) 0.0574
/*8  */     if (avctx->channels > 2) {                                          // (10) 0.0423
/*10 */         av_log(avctx, AV_LOG_ERROR, "Audio must be mono or stereo\n");  // (1) 0.09063
/*12 */         return -1;                                                      // (11) 0.03323
/*14 */     }                                                                   // (15) 0.01208
/*16 */     if (avctx->sample_rate != 22050) {                                  // (9) 0.04834
/*18 */         av_log(avctx, AV_LOG_ERROR, "Audio must be 22050 Hz\n");        // (2) 0.09063
/*20 */         return -1;                                                      // (12) 0.03323
/*22 */     }                                                                   // (16) 0.01208
/*24 */     if (avctx->sample_fmt != AV_SAMPLE_FMT_S16) {                       // (3) 0.07553
/*26 */         av_log(avctx, AV_LOG_ERROR, "Audio must be signed 16-bit\n");   // (0) 0.09366
/*28 */         return -1;                                                      // (13) 0.03323
/*30 */     }                                                                   // (17) 0.01208
/*34 */     avctx->frame_size = ROQ_FIRST_FRAME_SIZE;                           // (5) 0.06344
/*38 */     context->lastSample[0] = context->lastSample[1] = 0;                // (6) 0.06344
/*42 */     avctx->coded_frame= avcodec_alloc_frame();                          // (8) 0.05438
/*48 */     return 0;                                                           // (14) 0.01813
/*50 */ }                                                                       // (19) 0.003021

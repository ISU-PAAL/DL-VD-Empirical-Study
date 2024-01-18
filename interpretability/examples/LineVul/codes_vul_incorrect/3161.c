// commit message FFmpeg@a8bdf2405c (target=1, prob=0.043258607, correct=False): check for coded_frame allocation failure in several audio encoders
/*0  */ static av_cold int amr_wb_encode_init(AVCodecContext *avctx)                  // (3) 0.07419
/*2  */ {                                                                             // (16) 0.003226
/*4  */     AMRWBContext *s = avctx->priv_data;                                       // (5) 0.05806
/*8  */     if (avctx->sample_rate != 16000) {                                        // (8) 0.05161
/*10 */         av_log(avctx, AV_LOG_ERROR, "Only 16000Hz sample rate supported\n");  // (1) 0.1
/*12 */         return AVERROR(ENOSYS);                                               // (9) 0.05161
/*14 */     }                                                                         // (14) 0.0129
/*18 */     if (avctx->channels != 1) {                                               // (11) 0.04516
/*20 */         av_log(avctx, AV_LOG_ERROR, "Only mono supported\n");                 // (2) 0.0871
/*22 */         return AVERROR(ENOSYS);                                               // (10) 0.05161
/*24 */     }                                                                         // (15) 0.0129
/*28 */     s->mode            = get_wb_bitrate_mode(avctx->bit_rate, avctx);         // (0) 0.1194
/*30 */     s->last_bitrate    = avctx->bit_rate;                                     // (4) 0.06452
/*34 */     avctx->frame_size  = 320;                                                 // (12) 0.04194
/*36 */     avctx->coded_frame = avcodec_alloc_frame();                               // (6) 0.05806
/*42 */     s->state     = E_IF_init();                                               // (7) 0.05484
/*46 */     return 0;                                                                 // (13) 0.01935
/*48 */ }                                                                             // (17) 0.003226

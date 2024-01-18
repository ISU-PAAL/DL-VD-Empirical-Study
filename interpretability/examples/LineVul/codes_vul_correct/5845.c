// commit message FFmpeg@a8bdf2405c (target=1, prob=0.9991511, correct=True): check for coded_frame allocation failure in several audio encoders
/*0  */ static av_cold int amr_nb_encode_init(AVCodecContext *avctx)                 // (4) 0.06319
/*2  */ {                                                                            // (20) 0.002747
/*4  */     AMRContext *s = avctx->priv_data;                                        // (8) 0.04396
/*8  */     if (avctx->sample_rate != 8000) {                                        // (11) 0.04121
/*10 */         av_log(avctx, AV_LOG_ERROR, "Only 8000Hz sample rate supported\n");  // (1) 0.08242
/*12 */         return AVERROR(ENOSYS);                                              // (10) 0.04396
/*14 */     }                                                                        // (19) 0.01099
/*18 */     if (avctx->channels != 1) {                                              // (12) 0.03846
/*20 */         av_log(avctx, AV_LOG_ERROR, "Only mono supported\n");                // (3) 0.07418
/*22 */         return AVERROR(ENOSYS);                                              // (9) 0.04396
/*24 */     }                                                                        // (17) 0.01099
/*28 */     avctx->frame_size  = 160;                                                // (13) 0.03571
/*30 */     avctx->coded_frame = avcodec_alloc_frame();                              // (6) 0.04945
/*36 */     s->enc_state = Encoder_Interface_init(s->enc_dtx);                       // (5) 0.06319
/*38 */     if (!s->enc_state) {                                                     // (14) 0.03297
/*40 */         av_log(avctx, AV_LOG_ERROR, "Encoder_Interface_init error\n");       // (0) 0.08516
/*43 */         return -1;                                                           // (15) 0.03022
/*45 */     }                                                                        // (18) 0.01099
/*49 */     s->enc_mode    = get_bitrate_mode(avctx->bit_rate, avctx);               // (2) 0.07967
/*51 */     s->enc_bitrate = avctx->bit_rate;                                        // (7) 0.0467
/*55 */     return 0;                                                                // (16) 0.01648
/*57 */ }                                                                            // (21) 0.002747

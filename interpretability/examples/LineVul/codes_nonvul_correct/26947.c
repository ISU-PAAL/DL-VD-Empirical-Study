// commit message FFmpeg@39f7620d76 (target=0, prob=0.23738955, correct=True): avcodec/dca: don't set initial sample_fmt
/*0  */ static av_cold int dcadec_init(AVCodecContext *avctx)                       // (6) 0.03711
/*2  */ {                                                                           // (27) 0.001953
/*4  */     DCAContext *s = avctx->priv_data;                                       // (11) 0.0332
/*8  */     s->avctx = avctx;                                                       // (23) 0.02148
/*10 */     s->core.avctx = avctx;                                                  // (21) 0.02539
/*12 */     s->exss.avctx = avctx;                                                  // (18) 0.02734
/*14 */     s->xll.avctx = avctx;                                                   // (19) 0.02734
/*16 */     s->lbr.avctx = avctx;                                                   // (20) 0.02734
/*20 */     ff_dca_init_vlcs();                                                     // (22) 0.02539
/*24 */     if (ff_dca_core_init(&s->core) < 0)                                     // (5) 0.04102
/*26 */         return AVERROR(ENOMEM);                                             // (15) 0.03125
/*30 */     if (ff_dca_lbr_init(&s->lbr) < 0)                                       // (4) 0.04492
/*32 */         return AVERROR(ENOMEM);                                             // (16) 0.03125
/*36 */     ff_dcadsp_init(&s->dcadsp);                                             // (12) 0.0332
/*38 */     s->core.dcadsp = &s->dcadsp;                                            // (10) 0.03516
/*40 */     s->xll.dcadsp = &s->dcadsp;                                             // (7) 0.03711
/*42 */     s->lbr.dcadsp = &s->dcadsp;                                             // (8) 0.03711
/*46 */     s->crctab = av_crc_get_table(AV_CRC_16_CCITT);                          // (2) 0.05469
/*50 */     switch (avctx->request_channel_layout & ~AV_CH_LAYOUT_NATIVE) {         // (3) 0.05273
/*52 */     case 0:                                                                 // (26) 0.01172
/*54 */         s->request_channel_layout = 0;                                      // (13) 0.0332
/*56 */         break;                                                              // (24) 0.01758
/*58 */     case AV_CH_LAYOUT_STEREO:                                               // (17) 0.0293
/*60 */     case AV_CH_LAYOUT_STEREO_DOWNMIX:                                       // (9) 0.03711
/*62 */         s->request_channel_layout = DCA_SPEAKER_LAYOUT_STEREO;              // (1) 0.05859
/*64 */         break;                                                              // (25) 0.01758
/*66 */     case AV_CH_LAYOUT_5POINT0:                                              // (14) 0.0332
/*68 */         s->request_channel_layout = DCA_SPEAKER_LAYOUT_5POINT0;             // (0) 0.0625
/*70 */         break;                                                              // 0.0
/*72 */     case AV_CH_LAYOUT_5POINT1:                                              // 0.0
/*74 */         s->request_channel_layout = DCA_SPEAKER_LAYOUT_5POINT1;             // 0.0
/*76 */         break;                                                              // 0.0
/*78 */     default:                                                                // 0.0
/*80 */         av_log(avctx, AV_LOG_WARNING, "Invalid request_channel_layout\n");  // 0.0
/*82 */         break;                                                              // 0.0
/*84 */     }                                                                       // 0.0
/*88 */     avctx->sample_fmt = AV_SAMPLE_FMT_S32P;                                 // 0.0
/*90 */     avctx->bits_per_raw_sample = 24;                                        // 0.0
/*94 */     return 0;                                                               // 0.0
/*96 */ }                                                                           // 0.0

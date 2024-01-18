// commit message FFmpeg@98b377004d (target=0, prob=0.55725783, correct=False): twinvq: make ibps check unsigned
/*0   */ static av_cold int twin_decode_init(AVCodecContext *avctx)                                                           // (11) 0.03906
/*2   */ {                                                                                                                    // (24) 0.001953
/*4   */     int ret;                                                                                                         // (20) 0.01172
/*6   */     TwinContext *tctx = avctx->priv_data;                                                                            // (17) 0.03125
/*8   */     int isampf, ibps;                                                                                                // (18) 0.02148
/*12  */     tctx->avctx       = avctx;                                                                                       // (13) 0.03516
/*14  */     avctx->sample_fmt = AV_SAMPLE_FMT_FLTP;                                                                          // (10) 0.04297
/*18  */     if (!avctx->extradata || avctx->extradata_size < 12) {                                                           // (9) 0.04687
/*20  */         av_log(avctx, AV_LOG_ERROR, "Missing or incomplete extradata\n");                                            // (1) 0.05664
/*22  */         return AVERROR_INVALIDDATA;                                                                                  // (16) 0.0332
/*24  */     }                                                                                                                // (21) 0.007812
/*26  */     avctx->channels = AV_RB32(avctx->extradata    ) + 1;                                                             // (4) 0.05273
/*28  */     avctx->bit_rate = AV_RB32(avctx->extradata + 4) * 1000;                                                          // (3) 0.05273
/*30  */     isampf          = AV_RB32(avctx->extradata + 8);                                                                 // (0) 0.05859
/*34  */     if (isampf < 8 || isampf > 44) {                                                                                 // (14) 0.03516
/*36  */         av_log(avctx, AV_LOG_ERROR, "Unsupported sample rate\n");                                                    // (2) 0.05469
/*38  */         return AVERROR_INVALIDDATA;                                                                                  // (15) 0.0332
/*40  */     }                                                                                                                // (22) 0.007812
/*42  */     switch (isampf) {                                                                                                // (19) 0.01953
/*44  */     case 44: avctx->sample_rate = 44100;         break;                                                              // (8) 0.05078
/*46  */     case 22: avctx->sample_rate = 22050;         break;                                                              // (6) 0.05078
/*48  */     case 11: avctx->sample_rate = 11025;         break;                                                              // (7) 0.05078
/*50  */     default: avctx->sample_rate = isampf * 1000; break;                                                              // (12) 0.03906
/*52  */     }                                                                                                                // (23) 0.007812
/*56  */     if (avctx->channels <= 0 || avctx->channels > CHANNELS_MAX) {                                                    // (5) 0.05078
/*58  */         av_log(avctx, AV_LOG_ERROR, "Unsupported number of channels: %i\n",                                          // 0.0
/*60  */                avctx->channels);                                                                                     // 0.0
/*62  */         return -1;                                                                                                   // 0.0
/*64  */     }                                                                                                                // 0.0
/*66  */     avctx->channel_layout = avctx->channels == 1 ? AV_CH_LAYOUT_MONO :                                               // 0.0
/*68  */                                                    AV_CH_LAYOUT_STEREO;                                              // 0.0
/*72  */     ibps = avctx->bit_rate / (1000 * avctx->channels);                                                               // 0.0
/*76  */     if (ibps > 255) {                                                                                                // 0.0
/*78  */         av_log(avctx, AV_LOG_ERROR, "unsupported per channel bitrate %dkbps\n", ibps);                               // 0.0
/*80  */         return AVERROR_INVALIDDATA;                                                                                  // 0.0
/*82  */     }                                                                                                                // 0.0
/*86  */     switch ((isampf << 8) +  ibps) {                                                                                 // 0.0
/*88  */     case (8 <<8) +  8: tctx->mtab = &mode_08_08; break;                                                              // 0.0
/*90  */     case (11<<8) +  8: tctx->mtab = &mode_11_08; break;                                                              // 0.0
/*92  */     case (11<<8) + 10: tctx->mtab = &mode_11_10; break;                                                              // 0.0
/*94  */     case (16<<8) + 16: tctx->mtab = &mode_16_16; break;                                                              // 0.0
/*96  */     case (22<<8) + 20: tctx->mtab = &mode_22_20; break;                                                              // 0.0
/*98  */     case (22<<8) + 24: tctx->mtab = &mode_22_24; break;                                                              // 0.0
/*100 */     case (22<<8) + 32: tctx->mtab = &mode_22_32; break;                                                              // 0.0
/*102 */     case (44<<8) + 40: tctx->mtab = &mode_44_40; break;                                                              // 0.0
/*104 */     case (44<<8) + 48: tctx->mtab = &mode_44_48; break;                                                              // 0.0
/*106 */     default:                                                                                                         // 0.0
/*108 */         av_log(avctx, AV_LOG_ERROR, "This version does not support %d kHz - %d kbit/s/ch mode.\n", isampf, isampf);  // 0.0
/*110 */         return -1;                                                                                                   // 0.0
/*112 */     }                                                                                                                // 0.0
/*116 */     ff_dsputil_init(&tctx->dsp, avctx);                                                                              // 0.0
/*118 */     avpriv_float_dsp_init(&tctx->fdsp, avctx->flags & CODEC_FLAG_BITEXACT);                                          // 0.0
/*120 */     if ((ret = init_mdct_win(tctx))) {                                                                               // 0.0
/*122 */         av_log(avctx, AV_LOG_ERROR, "Error initializing MDCT\n");                                                    // 0.0
/*124 */         twin_decode_close(avctx);                                                                                    // 0.0
/*126 */         return ret;                                                                                                  // 0.0
/*128 */     }                                                                                                                // 0.0
/*130 */     init_bitstream_params(tctx);                                                                                     // 0.0
/*134 */     memset_float(tctx->bark_hist[0][0], 0.1, FF_ARRAY_ELEMS(tctx->bark_hist));                                       // 0.0
/*138 */     avcodec_get_frame_defaults(&tctx->frame);                                                                        // 0.0
/*140 */     avctx->coded_frame = &tctx->frame;                                                                               // 0.0
/*144 */     return 0;                                                                                                        // 0.0
/*146 */ }                                                                                                                    // 0.0

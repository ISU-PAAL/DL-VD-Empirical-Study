// commit message FFmpeg@6f600ab354 (target=0, prob=0.44966608, correct=True): libvorbis: improve error checking in oggvorbis_encode_init()
/*0  */ static av_cold int oggvorbis_init_encoder(vorbis_info *vi, AVCodecContext *avccontext)         // (6) 0.0625
/*2  */ {                                                                                              // (17) 0.001953
/*4  */     OggVorbisContext *context = avccontext->priv_data;                                         // (10) 0.04102
/*6  */     double cfreq;                                                                              // (15) 0.01563
/*10 */     if (avccontext->flags & CODEC_FLAG_QSCALE) {                                               // (9) 0.04492
/*12 */         /* variable bitrate */                                                                 // (13) 0.02344
/*14 */         if (vorbis_encode_setup_vbr(vi, avccontext->channels,                                  // (7) 0.05859
/*16 */                                     avccontext->sample_rate,                                   // (3) 0.08594
/*18 */                                     avccontext->global_quality / (float)FF_QP2LAMBDA / 10.0))  // (0) 0.1191
/*20 */             return -1;                                                                         // (11) 0.0293
/*22 */     } else {                                                                                   // (16) 0.01172
/*24 */         int minrate = avccontext->rc_min_rate > 0 ? avccontext->rc_min_rate : -1;              // (4) 0.07422
/*26 */         int maxrate = avccontext->rc_min_rate > 0 ? avccontext->rc_max_rate : -1;              // (5) 0.07422
/*30 */         /* constant bitrate */                                                                 // (14) 0.02344
/*32 */         if (vorbis_encode_setup_managed(vi, avccontext->channels,                              // (8) 0.05664
/*34 */                                         avccontext->sample_rate, minrate,                      // (1) 0.09961
/*36 */                                         avccontext->bit_rate, maxrate))                        // (2) 0.09961
/*38 */             return -1;                                                                         // (12) 0.0293
/*42 */         /* variable bitrate by estimate, disable slow rate management */                       // 0.0
/*44 */         if (minrate == -1 && maxrate == -1)                                                    // 0.0
/*46 */             if (vorbis_encode_ctl(vi, OV_ECTL_RATEMANAGE2_SET, NULL))                          // 0.0
/*48 */                 return -1;                                                                     // 0.0
/*50 */     }                                                                                          // 0.0
/*54 */     /* cutoff frequency */                                                                     // 0.0
/*56 */     if (avccontext->cutoff > 0) {                                                              // 0.0
/*58 */         cfreq = avccontext->cutoff / 1000.0;                                                   // 0.0
/*60 */         if (vorbis_encode_ctl(vi, OV_ECTL_LOWPASS_SET, &cfreq))                                // 0.0
/*62 */             return -1;                                                                         // 0.0
/*64 */     }                                                                                          // 0.0
/*68 */     if (context->iblock) {                                                                     // 0.0
/*70 */         vorbis_encode_ctl(vi, OV_ECTL_IBLOCK_SET, &context->iblock);                           // 0.0
/*72 */     }                                                                                          // 0.0
/*76 */     return vorbis_encode_setup_init(vi);                                                       // 0.0
/*78 */ }                                                                                              // 0.0

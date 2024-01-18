// commit message FFmpeg@d6604b29ef (target=0, prob=0.43146142, correct=True): Gather all coded_frame allocations and free functions to a single place
/*0   */ static av_cold int libschroedinger_encode_init(AVCodecContext *avctx)                       // (5) 0.04688
/*2   */ {                                                                                           // (24) 0.001953
/*4   */     SchroEncoderParams *p_schro_params = avctx->priv_data;                                  // (6) 0.04492
/*6   */     SchroVideoFormatEnum preset;                                                            // (20) 0.01953
/*10  */     /* Initialize the libraries that libschroedinger depends on. */                         // (14) 0.03516
/*12  */     schro_init();                                                                           // (22) 0.01562
/*16  */     /* Create an encoder object. */                                                         // (17) 0.02148
/*18  */     p_schro_params->encoder = schro_encoder_new();                                          // (9) 0.04102
/*22  */     if (!p_schro_params->encoder) {                                                         // (15) 0.03125
/*24  */         av_log(avctx, AV_LOG_ERROR,                                                         // (10) 0.03906
/*26  */                "Unrecoverable Error: schro_encoder_new failed. ");                          // (2) 0.0625
/*28  */         return -1;                                                                          // (19) 0.02148
/*30  */     }                                                                                       // (23) 0.007812
/*34  */     /* Initialize the format. */                                                            // (21) 0.01953
/*36  */     preset = ff_get_schro_video_format_preset(avctx);                                       // (8) 0.04297
/*38  */     p_schro_params->format =                                                                // (16) 0.02344
/*40  */                     schro_encoder_get_video_format(p_schro_params->encoder);                // (0) 0.08008
/*42  */     schro_video_format_set_std_video_format(p_schro_params->format, preset);                // (3) 0.05664
/*44  */     p_schro_params->format->width  = avctx->width;                                          // (11) 0.03906
/*46  */     p_schro_params->format->height = avctx->height;                                         // (13) 0.03711
/*50  */     if (set_chroma_format(avctx) == -1)                                                     // (12) 0.03711
/*52  */         return -1;                                                                          // (18) 0.02148
/*56  */     if (avctx->color_primaries == AVCOL_PRI_BT709) {                                        // (7) 0.04492
/*58  */         p_schro_params->format->colour_primaries = SCHRO_COLOUR_PRIMARY_HDTV;               // (1) 0.06641
/*60  */     } else if (avctx->color_primaries == AVCOL_PRI_BT470BG) {                               // (4) 0.05078
/*62  */         p_schro_params->format->colour_primaries = SCHRO_COLOUR_PRIMARY_SDTV_625;           // 0.0
/*64  */     } else if (avctx->color_primaries == AVCOL_PRI_SMPTE170M) {                             // 0.0
/*66  */         p_schro_params->format->colour_primaries = SCHRO_COLOUR_PRIMARY_SDTV_525;           // 0.0
/*68  */     }                                                                                       // 0.0
/*72  */     if (avctx->colorspace == AVCOL_SPC_BT709) {                                             // 0.0
/*74  */         p_schro_params->format->colour_matrix = SCHRO_COLOUR_MATRIX_HDTV;                   // 0.0
/*76  */     } else if (avctx->colorspace == AVCOL_SPC_BT470BG) {                                    // 0.0
/*78  */         p_schro_params->format->colour_matrix = SCHRO_COLOUR_MATRIX_SDTV;                   // 0.0
/*80  */     }                                                                                       // 0.0
/*84  */     if (avctx->color_trc == AVCOL_TRC_BT709) {                                              // 0.0
/*86  */         p_schro_params->format->transfer_function = SCHRO_TRANSFER_CHAR_TV_GAMMA;           // 0.0
/*88  */     }                                                                                       // 0.0
/*92  */     if (ff_get_schro_frame_format(p_schro_params->format->chroma_format,                    // 0.0
/*94  */                                   &p_schro_params->frame_format) == -1) {                   // 0.0
/*96  */         av_log(avctx, AV_LOG_ERROR,                                                         // 0.0
/*98  */                "This codec currently supports only planar YUV 4:2:0, 4:2:2"                 // 0.0
/*100 */                " and 4:4:4 formats.\n");                                                    // 0.0
/*102 */         return -1;                                                                          // 0.0
/*104 */     }                                                                                       // 0.0
/*108 */     p_schro_params->format->frame_rate_numerator   = avctx->time_base.den;                  // 0.0
/*110 */     p_schro_params->format->frame_rate_denominator = avctx->time_base.num;                  // 0.0
/*114 */     p_schro_params->frame_size = avpicture_get_size(avctx->pix_fmt,                         // 0.0
/*116 */                                                     avctx->width,                           // 0.0
/*118 */                                                     avctx->height);                         // 0.0
/*122 */     avctx->coded_frame = av_frame_alloc();                                                  // 0.0
/*124 */     if (!avctx->coded_frame)                                                                // 0.0
/*126 */         return AVERROR(ENOMEM);                                                             // 0.0
/*130 */     if (!avctx->gop_size) {                                                                 // 0.0
/*132 */         schro_encoder_setting_set_double(p_schro_params->encoder,                           // 0.0
/*134 */                                          "gop_structure",                                   // 0.0
/*136 */                                          SCHRO_ENCODER_GOP_INTRA_ONLY);                     // 0.0
/*140 */         if (avctx->coder_type == FF_CODER_TYPE_VLC)                                         // 0.0
/*142 */             schro_encoder_setting_set_double(p_schro_params->encoder,                       // 0.0
/*144 */                                              "enable_noarith", 1);                          // 0.0
/*146 */     } else {                                                                                // 0.0
/*148 */         schro_encoder_setting_set_double(p_schro_params->encoder,                           // 0.0
/*150 */                                          "au_distance", avctx->gop_size);                   // 0.0
/*152 */         avctx->has_b_frames = 1;                                                            // 0.0
/*154 */         p_schro_params->dts = -1;                                                           // 0.0
/*156 */     }                                                                                       // 0.0
/*160 */     /* FIXME - Need to handle SCHRO_ENCODER_RATE_CONTROL_LOW_DELAY. */                      // 0.0
/*162 */     if (avctx->flags & CODEC_FLAG_QSCALE) {                                                 // 0.0
/*164 */         if (!avctx->global_quality) {                                                       // 0.0
/*166 */             /* lossless coding */                                                           // 0.0
/*168 */             schro_encoder_setting_set_double(p_schro_params->encoder,                       // 0.0
/*170 */                                              "rate_control",                                // 0.0
/*172 */                                              SCHRO_ENCODER_RATE_CONTROL_LOSSLESS);          // 0.0
/*174 */         } else {                                                                            // 0.0
/*176 */             int quality;                                                                    // 0.0
/*178 */             schro_encoder_setting_set_double(p_schro_params->encoder,                       // 0.0
/*180 */                                              "rate_control",                                // 0.0
/*182 */                                              SCHRO_ENCODER_RATE_CONTROL_CONSTANT_QUALITY);  // 0.0
/*186 */             quality = avctx->global_quality / FF_QP2LAMBDA;                                 // 0.0
/*188 */             if (quality > 10)                                                               // 0.0
/*190 */                 quality = 10;                                                               // 0.0
/*192 */             schro_encoder_setting_set_double(p_schro_params->encoder,                       // 0.0
/*194 */                                              "quality", quality);                           // 0.0
/*196 */         }                                                                                   // 0.0
/*198 */     } else {                                                                                // 0.0
/*200 */         schro_encoder_setting_set_double(p_schro_params->encoder,                           // 0.0
/*202 */                                          "rate_control",                                    // 0.0
/*204 */                                          SCHRO_ENCODER_RATE_CONTROL_CONSTANT_BITRATE);      // 0.0
/*208 */         schro_encoder_setting_set_double(p_schro_params->encoder,                           // 0.0
/*210 */                                          "bitrate", avctx->bit_rate);                       // 0.0
/*212 */     }                                                                                       // 0.0
/*216 */     if (avctx->flags & CODEC_FLAG_INTERLACED_ME)                                            // 0.0
/*218 */         /* All material can be coded as interlaced or progressive                           // 0.0
/*220 */            irrespective of the type of source material. */                                  // 0.0
/*222 */         schro_encoder_setting_set_double(p_schro_params->encoder,                           // 0.0
/*224 */                                          "interlaced_coding", 1);                           // 0.0
/*228 */     schro_encoder_setting_set_double(p_schro_params->encoder, "open_gop",                   // 0.0
/*230 */                                      !(avctx->flags & CODEC_FLAG_CLOSED_GOP));              // 0.0
/*234 */     /* FIXME: Signal range hardcoded to 8-bit data until both libschroedinger               // 0.0
/*236 */      * and libdirac support other bit-depth data. */                                        // 0.0
/*238 */     schro_video_format_set_std_signal_range(p_schro_params->format,                         // 0.0
/*240 */                                             SCHRO_SIGNAL_RANGE_8BIT_VIDEO);                 // 0.0
/*244 */     /* Set the encoder format. */                                                           // 0.0
/*246 */     schro_encoder_set_video_format(p_schro_params->encoder,                                 // 0.0
/*248 */                                    p_schro_params->format);                                 // 0.0
/*252 */     /* Set the debug level. */                                                              // 0.0
/*254 */     schro_debug_set_level(avctx->debug);                                                    // 0.0
/*258 */     schro_encoder_start(p_schro_params->encoder);                                           // 0.0
/*262 */     /* Initialize the encoded frame queue. */                                               // 0.0
/*264 */     ff_schro_queue_init(&p_schro_params->enc_frame_queue);                                  // 0.0
/*266 */     return 0;                                                                               // 0.0
/*268 */ }                                                                                           // 0.0

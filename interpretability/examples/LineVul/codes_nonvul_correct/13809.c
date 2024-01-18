// commit message FFmpeg@be00ec832c (target=0, prob=0.32796735, correct=True): lavc: Deprecate coder_type and its symbols
/*0   */ static av_cold int svc_encode_init(AVCodecContext *avctx)                                                                   // (9) 0.041
/*2   */ {                                                                                                                           // (26) 0.001954
/*4   */     SVCContext *s = avctx->priv_data;                                                                                       // (14) 0.03123
/*6   */     SEncParamExt param = { 0 };                                                                                             // (20) 0.02342
/*8   */     int err = AVERROR_UNKNOWN;                                                                                              // (17) 0.02538
/*10  */     int log_level;                                                                                                          // (21) 0.01562
/*12  */     WelsTraceCallback callback_function;                                                                                    // (19) 0.02342
/*14  */     AVCPBProperties *props;                                                                                                 // (18) 0.02343
/*18  */     // Mingw GCC < 4.7 on x86_32 uses an incorrect/buggy ABI for the WelsGetCodecVersion                                    // (2) 0.06259
/*20  */     // function (for functions returning larger structs), thus skip the check in those                                      // (10) 0.03719
/*22  */     // configurations.                                                                                                      // (22) 0.01173
/*24  */ #if !defined(_WIN32) || !defined(__GNUC__) || !ARCH_X86_32 || AV_GCC_VERSION_AT_LEAST(4, 7)                                 // (0) 0.08198
/*26  */     OpenH264Version libver = WelsGetCodecVersion();                                                                         // (12) 0.03318
/*28  */     if (memcmp(&libver, &g_stCodecVersion, sizeof(libver))) {                                                               // (5) 0.0488
/*30  */         av_log(avctx, AV_LOG_ERROR, "Incorrect library version loaded\n");                                                  // (4) 0.0566
/*32  */         return AVERROR(EINVAL);                                                                                             // (15) 0.03123
/*34  */     }                                                                                                                       // (24) 0.007807
/*36  */ #endif                                                                                                                      // (25) 0.003918
/*40  */     if (WelsCreateSVCEncoder(&s->encoder)) {                                                                                // (11) 0.03709
/*42  */         av_log(avctx, AV_LOG_ERROR, "Unable to create encoder\n");                                                          // (3) 0.05856
/*44  */         return AVERROR_UNKNOWN;                                                                                             // (16) 0.02928
/*46  */     }                                                                                                                       // (23) 0.007831
/*50  */     // Pass all libopenh264 messages to our callback, to allow ourselves to filter them.                                    // (7) 0.04312
/*52  */     log_level = WELS_LOG_DETAIL;                                                                                            // (13) 0.03123
/*54  */     (*s->encoder)->SetOption(s->encoder, ENCODER_OPTION_TRACE_LEVEL, &log_level);                                           // (1) 0.07223
/*58  */     // Set the logging callback function to one that uses av_log() (see implementation above).                              // (8) 0.04299
/*60  */     callback_function = (WelsTraceCallback) libopenh264_trace_callback;                                                     // (6) 0.0449
/*62  */     (*s->encoder)->SetOption(s->encoder, ENCODER_OPTION_TRACE_CALLBACK, (void *)&callback_function);                        // 0.0
/*66  */     // Set the AVCodecContext as the libopenh264 callback context so that it can be passed to av_log().                     // 0.0
/*68  */     (*s->encoder)->SetOption(s->encoder, ENCODER_OPTION_TRACE_CALLBACK_CONTEXT, (void *)&avctx);                            // 0.0
/*72  */     (*s->encoder)->GetDefaultParams(s->encoder, &param);                                                                    // 0.0
/*76  */     param.fMaxFrameRate              = avctx->time_base.den / avctx->time_base.num;                                         // 0.0
/*78  */     param.iPicWidth                  = avctx->width;                                                                        // 0.0
/*80  */     param.iPicHeight                 = avctx->height;                                                                       // 0.0
/*82  */     param.iTargetBitrate             = avctx->bit_rate;                                                                     // 0.0
/*84  */     param.iMaxBitrate                = FFMAX(avctx->rc_max_rate, avctx->bit_rate);                                          // 0.0
/*86  */     param.iRCMode                    = RC_QUALITY_MODE;                                                                     // 0.0
/*88  */     param.iTemporalLayerNum          = 1;                                                                                   // 0.0
/*90  */     param.iSpatialLayerNum           = 1;                                                                                   // 0.0
/*92  */     param.bEnableDenoise             = 0;                                                                                   // 0.0
/*94  */     param.bEnableBackgroundDetection = 1;                                                                                   // 0.0
/*96  */     param.bEnableAdaptiveQuant       = 1;                                                                                   // 0.0
/*98  */     param.bEnableFrameSkip           = s->skip_frames;                                                                      // 0.0
/*100 */     param.bEnableLongTermReference   = 0;                                                                                   // 0.0
/*102 */     param.iLtrMarkPeriod             = 30;                                                                                  // 0.0
/*104 */     param.uiIntraPeriod              = avctx->gop_size;                                                                     // 0.0
/*106 */ #if OPENH264_VER_AT_LEAST(1, 4)                                                                                             // 0.0
/*108 */     param.eSpsPpsIdStrategy          = CONSTANT_ID;                                                                         // 0.0
/*110 */ #else                                                                                                                       // 0.0
/*112 */     param.bEnableSpsPpsIdAddition    = 0;                                                                                   // 0.0
/*114 */ #endif                                                                                                                      // 0.0
/*116 */     param.bPrefixNalAddingCtrl       = 0;                                                                                   // 0.0
/*118 */     param.iLoopFilterDisableIdc      = !s->loopfilter;                                                                      // 0.0
/*120 */     param.iEntropyCodingModeFlag     = 0;                                                                                   // 0.0
/*122 */     param.iMultipleThreadIdc         = avctx->thread_count;                                                                 // 0.0
/*124 */     if (s->profile && !strcmp(s->profile, "main"))                                                                          // 0.0
/*126 */         param.iEntropyCodingModeFlag = 1;                                                                                   // 0.0
/*128 */     else if (!s->profile && avctx->coder_type == FF_CODER_TYPE_AC)                                                          // 0.0
/*130 */         param.iEntropyCodingModeFlag = 1;                                                                                   // 0.0
/*134 */     param.sSpatialLayers[0].iVideoWidth         = param.iPicWidth;                                                          // 0.0
/*136 */     param.sSpatialLayers[0].iVideoHeight        = param.iPicHeight;                                                         // 0.0
/*138 */     param.sSpatialLayers[0].fFrameRate          = param.fMaxFrameRate;                                                      // 0.0
/*140 */     param.sSpatialLayers[0].iSpatialBitrate     = param.iTargetBitrate;                                                     // 0.0
/*142 */     param.sSpatialLayers[0].iMaxSpatialBitrate  = param.iMaxBitrate;                                                        // 0.0
/*146 */     if ((avctx->slices > 1) && (s->max_nal_size)){                                                                          // 0.0
/*148 */         av_log(avctx,AV_LOG_ERROR,"Invalid combination -slices %d and -max_nal_size %d.\n",avctx->slices,s->max_nal_size);  // 0.0
/*150 */         goto fail;                                                                                                          // 0.0
/*152 */     }                                                                                                                       // 0.0
/*156 */     if (avctx->slices > 1)                                                                                                  // 0.0
/*158 */         s->slice_mode = SM_FIXEDSLCNUM_SLICE;                                                                               // 0.0
/*162 */     if (s->max_nal_size)                                                                                                    // 0.0
/*164 */         s->slice_mode = SM_DYN_SLICE;                                                                                       // 0.0
/*168 */     param.sSpatialLayers[0].sSliceCfg.uiSliceMode               = s->slice_mode;                                            // 0.0
/*170 */     param.sSpatialLayers[0].sSliceCfg.sSliceArgument.uiSliceNum = avctx->slices;                                            // 0.0
/*174 */     if (s->slice_mode == SM_DYN_SLICE) {                                                                                    // 0.0
/*176 */         if (s->max_nal_size){                                                                                               // 0.0
/*178 */             param.uiMaxNalSize = s->max_nal_size;                                                                           // 0.0
/*180 */             param.sSpatialLayers[0].sSliceCfg.sSliceArgument.uiSliceSizeConstraint = s->max_nal_size;                       // 0.0
/*182 */         } else {                                                                                                            // 0.0
/*184 */             if (avctx->rtp_payload_size) {                                                                                  // 0.0
/*186 */                 av_log(avctx,AV_LOG_DEBUG,"Using RTP Payload size for uiMaxNalSize");                                       // 0.0
/*188 */                 param.uiMaxNalSize = avctx->rtp_payload_size;                                                               // 0.0
/*190 */                 param.sSpatialLayers[0].sSliceCfg.sSliceArgument.uiSliceSizeConstraint = avctx->rtp_payload_size;           // 0.0
/*192 */             } else {                                                                                                        // 0.0
/*194 */                 av_log(avctx,AV_LOG_ERROR,"Invalid -max_nal_size, specify a valid max_nal_size to use -slice_mode dyn\n");  // 0.0
/*196 */                 goto fail;                                                                                                  // 0.0
/*198 */             }                                                                                                               // 0.0
/*200 */         }                                                                                                                   // 0.0
/*202 */     }                                                                                                                       // 0.0
/*206 */     if ((*s->encoder)->InitializeExt(s->encoder, &param) != cmResultSuccess) {                                              // 0.0
/*208 */         av_log(avctx, AV_LOG_ERROR, "Initialize failed\n");                                                                 // 0.0
/*210 */         goto fail;                                                                                                          // 0.0
/*212 */     }                                                                                                                       // 0.0
/*216 */     if (avctx->flags & AV_CODEC_FLAG_GLOBAL_HEADER) {                                                                       // 0.0
/*218 */         SFrameBSInfo fbi = { 0 };                                                                                           // 0.0
/*220 */         int i, size = 0;                                                                                                    // 0.0
/*222 */         (*s->encoder)->EncodeParameterSets(s->encoder, &fbi);                                                               // 0.0
/*224 */         for (i = 0; i < fbi.sLayerInfo[0].iNalCount; i++)                                                                   // 0.0
/*226 */             size += fbi.sLayerInfo[0].pNalLengthInByte[i];                                                                  // 0.0
/*228 */         avctx->extradata = av_mallocz(size + AV_INPUT_BUFFER_PADDING_SIZE);                                                 // 0.0
/*230 */         if (!avctx->extradata) {                                                                                            // 0.0
/*232 */             err = AVERROR(ENOMEM);                                                                                          // 0.0
/*234 */             goto fail;                                                                                                      // 0.0
/*236 */         }                                                                                                                   // 0.0
/*238 */         avctx->extradata_size = size;                                                                                       // 0.0
/*240 */         memcpy(avctx->extradata, fbi.sLayerInfo[0].pBsBuf, size);                                                           // 0.0
/*242 */     }                                                                                                                       // 0.0
/*246 */     props = ff_add_cpb_side_data(avctx);                                                                                    // 0.0
/*248 */     if (!props) {                                                                                                           // 0.0
/*250 */         err = AVERROR(ENOMEM);                                                                                              // 0.0
/*252 */         goto fail;                                                                                                          // 0.0
/*254 */     }                                                                                                                       // 0.0
/*256 */     props->max_bitrate = param.iMaxBitrate;                                                                                 // 0.0
/*258 */     props->avg_bitrate = param.iTargetBitrate;                                                                              // 0.0
/*262 */     return 0;                                                                                                               // 0.0
/*266 */ fail:                                                                                                                       // 0.0
/*268 */     svc_encode_close(avctx);                                                                                                // 0.0
/*270 */     return err;                                                                                                             // 0.0
/*272 */ }                                                                                                                           // 0.0

// commit message FFmpeg@c177f2ec4a (target=0, prob=0.37630737, correct=True): libfdk-aacenc: Actually check for upper bounds of cutoff
/*0   */ static av_cold int aac_encode_init(AVCodecContext *avctx)                                                            // (9) 0.04102
/*2   */ {                                                                                                                    // (23) 0.001955
/*4   */     AACContext *s = avctx->priv_data;                                                                                // (13) 0.0293
/*6   */     int ret = AVERROR(EINVAL);                                                                                       // (14) 0.02739
/*8   */     AACENC_InfoStruct info = { 0 };                                                                                  // (16) 0.02539
/*10  */     CHANNEL_MODE mode;                                                                                               // (17) 0.01953
/*12  */     AACENC_ERROR err;                                                                                                // (20) 0.01758
/*14  */     int aot = FF_PROFILE_AAC_LOW + 1;                                                                                // (10) 0.03906
/*16  */     int sce = 0, cpe = 0;                                                                                            // (15) 0.02734
/*20  */     if ((err = aacEncOpen(&s->handle, 0, avctx->channels)) != AACENC_OK) {                                           // (4) 0.06054
/*22  */         av_log(avctx, AV_LOG_ERROR, "Unable to open the encoder: %s\n",                                              // (3) 0.0664
/*24  */                aac_get_error(err));                                                                                  // (8) 0.04492
/*26  */         goto error;                                                                                                  // (18) 0.01953
/*28  */     }                                                                                                                // (21) 0.007812
/*32  */     if (avctx->profile != FF_PROFILE_UNKNOWN)                                                                        // (11) 0.03515
/*34  */         aot = avctx->profile + 1;                                                                                    // (12) 0.0332
/*38  */     if ((err = aacEncoder_SetParam(s->handle, AACENC_AOT, aot)) != AACENC_OK) {                                      // (2) 0.06835
/*40  */         av_log(avctx, AV_LOG_ERROR, "Unable to set the AOT %d: %s\n",                                                // (1) 0.07031
/*42  */                aot, aac_get_error(err));                                                                             // (7) 0.05078
/*44  */         goto error;                                                                                                  // (19) 0.01953
/*46  */     }                                                                                                                // (22) 0.007812
/*50  */     if (aot == FF_PROFILE_AAC_ELD + 1 && s->eld_sbr) {                                                               // (6) 0.05664
/*52  */         if ((err = aacEncoder_SetParam(s->handle, AACENC_SBR_MODE,                                                   // (5) 0.06054
/*54  */                                        1)) != AACENC_OK) {                                                           // (0) 0.09179
/*56  */             av_log(avctx, AV_LOG_ERROR, "Unable to enable SBR for ELD: %s\n",                                        // 0.0
/*58  */                    aac_get_error(err));                                                                              // 0.0
/*60  */             goto error;                                                                                              // 0.0
/*62  */         }                                                                                                            // 0.0
/*64  */     }                                                                                                                // 0.0
/*68  */     if ((err = aacEncoder_SetParam(s->handle, AACENC_SAMPLERATE,                                                     // 0.0
/*70  */                                    avctx->sample_rate)) != AACENC_OK) {                                              // 0.0
/*72  */         av_log(avctx, AV_LOG_ERROR, "Unable to set the sample rate %d: %s\n",                                        // 0.0
/*74  */                avctx->sample_rate, aac_get_error(err));                                                              // 0.0
/*76  */         goto error;                                                                                                  // 0.0
/*78  */     }                                                                                                                // 0.0
/*82  */     switch (avctx->channels) {                                                                                       // 0.0
/*84  */     case 1: mode = MODE_1;       sce = 1; cpe = 0; break;                                                            // 0.0
/*86  */     case 2: mode = MODE_2;       sce = 0; cpe = 1; break;                                                            // 0.0
/*88  */     case 3: mode = MODE_1_2;     sce = 1; cpe = 1; break;                                                            // 0.0
/*90  */     case 4: mode = MODE_1_2_1;   sce = 2; cpe = 1; break;                                                            // 0.0
/*92  */     case 5: mode = MODE_1_2_2;   sce = 1; cpe = 2; break;                                                            // 0.0
/*94  */     case 6: mode = MODE_1_2_2_1; sce = 2; cpe = 2; break;                                                            // 0.0
/*96  */     default:                                                                                                         // 0.0
/*98  */         av_log(avctx, AV_LOG_ERROR,                                                                                  // 0.0
/*100 */                "Unsupported number of channels %d\n", avctx->channels);                                              // 0.0
/*102 */         goto error;                                                                                                  // 0.0
/*104 */     }                                                                                                                // 0.0
/*108 */     if ((err = aacEncoder_SetParam(s->handle, AACENC_CHANNELMODE,                                                    // 0.0
/*110 */                                    mode)) != AACENC_OK) {                                                            // 0.0
/*112 */         av_log(avctx, AV_LOG_ERROR,                                                                                  // 0.0
/*114 */                "Unable to set channel mode %d: %s\n", mode, aac_get_error(err));                                     // 0.0
/*116 */         goto error;                                                                                                  // 0.0
/*118 */     }                                                                                                                // 0.0
/*122 */     if ((err = aacEncoder_SetParam(s->handle, AACENC_CHANNELORDER,                                                   // 0.0
/*124 */                                    1)) != AACENC_OK) {                                                               // 0.0
/*126 */         av_log(avctx, AV_LOG_ERROR,                                                                                  // 0.0
/*128 */                "Unable to set wav channel order %d: %s\n",                                                           // 0.0
/*130 */                mode, aac_get_error(err));                                                                            // 0.0
/*132 */         goto error;                                                                                                  // 0.0
/*134 */     }                                                                                                                // 0.0
/*138 */     if (avctx->flags & CODEC_FLAG_QSCALE || s->vbr) {                                                                // 0.0
/*140 */         int mode = s->vbr ? s->vbr : avctx->global_quality;                                                          // 0.0
/*142 */         if (mode <  1 || mode > 5) {                                                                                 // 0.0
/*144 */             av_log(avctx, AV_LOG_WARNING,                                                                            // 0.0
/*146 */                    "VBR quality %d out of range, should be 1-5\n", mode);                                            // 0.0
/*148 */             mode = av_clip(mode, 1, 5);                                                                              // 0.0
/*150 */         }                                                                                                            // 0.0
/*152 */         av_log(avctx, AV_LOG_WARNING,                                                                                // 0.0
/*154 */                "Note, the VBR setting is unsupported and only works with "                                           // 0.0
/*156 */                "some parameter combinations\n");                                                                     // 0.0
/*158 */         if ((err = aacEncoder_SetParam(s->handle, AACENC_BITRATEMODE,                                                // 0.0
/*160 */                                        mode)) != AACENC_OK) {                                                        // 0.0
/*162 */             av_log(avctx, AV_LOG_ERROR, "Unable to set the VBR bitrate mode %d: %s\n",                               // 0.0
/*164 */                    mode, aac_get_error(err));                                                                        // 0.0
/*166 */             goto error;                                                                                              // 0.0
/*168 */         }                                                                                                            // 0.0
/*170 */     } else {                                                                                                         // 0.0
/*172 */         if (avctx->bit_rate <= 0) {                                                                                  // 0.0
/*174 */             if (avctx->profile == FF_PROFILE_AAC_HE_V2) {                                                            // 0.0
/*176 */                 sce = 1;                                                                                             // 0.0
/*178 */                 cpe = 0;                                                                                             // 0.0
/*180 */             }                                                                                                        // 0.0
/*182 */             avctx->bit_rate = (96*sce + 128*cpe) * avctx->sample_rate / 44;                                          // 0.0
/*184 */             if (avctx->profile == FF_PROFILE_AAC_HE ||                                                               // 0.0
/*186 */                 avctx->profile == FF_PROFILE_AAC_HE_V2 ||                                                            // 0.0
/*188 */                 s->eld_sbr)                                                                                          // 0.0
/*190 */                 avctx->bit_rate /= 2;                                                                                // 0.0
/*192 */         }                                                                                                            // 0.0
/*194 */         if ((err = aacEncoder_SetParam(s->handle, AACENC_BITRATE,                                                    // 0.0
/*196 */                                        avctx->bit_rate)) != AACENC_OK) {                                             // 0.0
/*198 */             av_log(avctx, AV_LOG_ERROR, "Unable to set the bitrate %d: %s\n",                                        // 0.0
/*200 */                    avctx->bit_rate, aac_get_error(err));                                                             // 0.0
/*202 */             goto error;                                                                                              // 0.0
/*204 */         }                                                                                                            // 0.0
/*206 */     }                                                                                                                // 0.0
/*210 */     /* Choose bitstream format - if global header is requested, use                                                  // 0.0
/*212 */      * raw access units, otherwise use ADTS. */                                                                      // 0.0
/*214 */     if ((err = aacEncoder_SetParam(s->handle, AACENC_TRANSMUX,                                                       // 0.0
/*216 */                                    avctx->flags & CODEC_FLAG_GLOBAL_HEADER ? 0 : s->latm ? 10 : 2)) != AACENC_OK) {  // 0.0
/*218 */         av_log(avctx, AV_LOG_ERROR, "Unable to set the transmux format: %s\n",                                       // 0.0
/*220 */                aac_get_error(err));                                                                                  // 0.0
/*222 */         goto error;                                                                                                  // 0.0
/*224 */     }                                                                                                                // 0.0
/*228 */     if (s->latm && s->header_period) {                                                                               // 0.0
/*230 */         if ((err = aacEncoder_SetParam(s->handle, AACENC_HEADER_PERIOD,                                              // 0.0
/*232 */                                        s->header_period)) != AACENC_OK) {                                            // 0.0
/*234 */              av_log(avctx, AV_LOG_ERROR, "Unable to set header period: %s\n",                                        // 0.0
/*236 */                     aac_get_error(err));                                                                             // 0.0
/*238 */              goto error;                                                                                             // 0.0
/*240 */         }                                                                                                            // 0.0
/*242 */     }                                                                                                                // 0.0
/*246 */     /* If no signaling mode is chosen, use explicit hierarchical signaling                                           // 0.0
/*248 */      * if using mp4 mode (raw access units, with global header) and                                                  // 0.0
/*250 */      * implicit signaling if using ADTS. */                                                                          // 0.0
/*252 */     if (s->signaling < 0)                                                                                            // 0.0
/*254 */         s->signaling = avctx->flags & CODEC_FLAG_GLOBAL_HEADER ? 2 : 0;                                              // 0.0
/*258 */     if ((err = aacEncoder_SetParam(s->handle, AACENC_SIGNALING_MODE,                                                 // 0.0
/*260 */                                    s->signaling)) != AACENC_OK) {                                                    // 0.0
/*262 */         av_log(avctx, AV_LOG_ERROR, "Unable to set signaling mode %d: %s\n",                                         // 0.0
/*264 */                s->signaling, aac_get_error(err));                                                                    // 0.0
/*266 */         goto error;                                                                                                  // 0.0
/*268 */     }                                                                                                                // 0.0
/*272 */     if ((err = aacEncoder_SetParam(s->handle, AACENC_AFTERBURNER,                                                    // 0.0
/*274 */                                    s->afterburner)) != AACENC_OK) {                                                  // 0.0
/*276 */         av_log(avctx, AV_LOG_ERROR, "Unable to set afterburner to %d: %s\n",                                         // 0.0
/*278 */                s->afterburner, aac_get_error(err));                                                                  // 0.0
/*280 */         goto error;                                                                                                  // 0.0
/*282 */     }                                                                                                                // 0.0
/*286 */     if (avctx->cutoff > 0) {                                                                                         // 0.0
/*288 */         if (avctx->cutoff < (avctx->sample_rate + 255) >> 8) {                                                       // 0.0
/*290 */             av_log(avctx, AV_LOG_ERROR, "cutoff valid range is %d-20000\n",                                          // 0.0
/*292 */                    (avctx->sample_rate + 255) >> 8);                                                                 // 0.0
/*294 */             goto error;                                                                                              // 0.0
/*296 */         }                                                                                                            // 0.0
/*298 */         if ((err = aacEncoder_SetParam(s->handle, AACENC_BANDWIDTH,                                                  // 0.0
/*300 */                                        avctx->cutoff)) != AACENC_OK) {                                               // 0.0
/*302 */             av_log(avctx, AV_LOG_ERROR, "Unable to set the encoder bandwidth to %d: %s\n",                           // 0.0
/*304 */                    avctx->cutoff, aac_get_error(err));                                                               // 0.0
/*306 */             goto error;                                                                                              // 0.0
/*308 */         }                                                                                                            // 0.0
/*310 */     }                                                                                                                // 0.0
/*314 */     if ((err = aacEncEncode(s->handle, NULL, NULL, NULL, NULL)) != AACENC_OK) {                                      // 0.0
/*316 */         av_log(avctx, AV_LOG_ERROR, "Unable to initialize the encoder: %s\n",                                        // 0.0
/*318 */                aac_get_error(err));                                                                                  // 0.0
/*320 */         return AVERROR(EINVAL);                                                                                      // 0.0
/*322 */     }                                                                                                                // 0.0
/*326 */     if ((err = aacEncInfo(s->handle, &info)) != AACENC_OK) {                                                         // 0.0
/*328 */         av_log(avctx, AV_LOG_ERROR, "Unable to get encoder info: %s\n",                                              // 0.0
/*330 */                aac_get_error(err));                                                                                  // 0.0
/*332 */         goto error;                                                                                                  // 0.0
/*334 */     }                                                                                                                // 0.0
/*338 */ #if FF_API_OLD_ENCODE_AUDIO                                                                                          // 0.0
/*340 */     avctx->coded_frame = avcodec_alloc_frame();                                                                      // 0.0
/*342 */     if (!avctx->coded_frame) {                                                                                       // 0.0
/*344 */         ret = AVERROR(ENOMEM);                                                                                       // 0.0
/*346 */         goto error;                                                                                                  // 0.0
/*348 */     }                                                                                                                // 0.0
/*350 */ #endif                                                                                                               // 0.0
/*352 */     avctx->frame_size = info.frameLength;                                                                            // 0.0
/*354 */     avctx->delay      = info.encoderDelay;                                                                           // 0.0
/*356 */     ff_af_queue_init(avctx, &s->afq);                                                                                // 0.0
/*360 */     if (avctx->flags & CODEC_FLAG_GLOBAL_HEADER) {                                                                   // 0.0
/*362 */         avctx->extradata_size = info.confSize;                                                                       // 0.0
/*364 */         avctx->extradata      = av_mallocz(avctx->extradata_size +                                                   // 0.0
/*366 */                                            FF_INPUT_BUFFER_PADDING_SIZE);                                            // 0.0
/*368 */         if (!avctx->extradata) {                                                                                     // 0.0
/*370 */             ret = AVERROR(ENOMEM);                                                                                   // 0.0
/*372 */             goto error;                                                                                              // 0.0
/*374 */         }                                                                                                            // 0.0
/*378 */         memcpy(avctx->extradata, info.confBuf, info.confSize);                                                       // 0.0
/*380 */     }                                                                                                                // 0.0
/*382 */     return 0;                                                                                                        // 0.0
/*384 */ error:                                                                                                               // 0.0
/*386 */     aac_encode_close(avctx);                                                                                         // 0.0
/*388 */     return ret;                                                                                                      // 0.0
/*390 */ }                                                                                                                    // 0.0

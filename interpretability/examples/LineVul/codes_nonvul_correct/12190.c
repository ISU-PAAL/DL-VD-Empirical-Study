// commit message FFmpeg@1846a3eac8 (target=0, prob=0.48484692, correct=True): ffmpeg_vaapi: fix choice of decoder_format
/*0   */ static int vaapi_build_decoder_config(VAAPIDecoderContext *ctx,                  // (6) 0.04102
/*2   */                                       AVCodecContext *avctx,                     // (0) 0.08789
/*4   */                                       int fallback_allowed)                      // (1) 0.08398
/*6   */ {                                                                                // (26) 0.001953
/*8   */     AVVAAPIDeviceContext *hwctx = ctx->device->hwctx;                            // (4) 0.04297
/*10  */     AVVAAPIHWConfig *hwconfig = NULL;                                            // (15) 0.0293
/*12  */     AVHWFramesConstraints *constraints = NULL;                                   // (9) 0.0332
/*14  */     VAStatus vas;                                                                // (23) 0.01367
/*16  */     int err, i, j;                                                               // (20) 0.01953
/*18  */     int loglevel = fallback_allowed ? AV_LOG_VERBOSE : AV_LOG_ERROR;             // (2) 0.05273
/*20  */     const AVCodecDescriptor *codec_desc;                                         // (14) 0.03125
/*22  */     const AVPixFmtDescriptor *pix_desc;                                          // (8) 0.03516
/*24  */     enum AVPixelFormat pix_fmt;                                                  // (17) 0.02734
/*26  */     VAProfile profile, *profile_list = NULL;                                     // (16) 0.02734
/*28  */     int profile_count, exact_match, alt_profile;                                 // (12) 0.03126
/*32  */     codec_desc = avcodec_descriptor_get(avctx->codec_id);                        // (3) 0.04883
/*34  */     if (!codec_desc) {                                                           // (18) 0.02148
/*36  */         err = AVERROR(EINVAL);                                                   // (11) 0.0332
/*38  */         goto fail;                                                               // (21) 0.01953
/*40  */     }                                                                            // (24) 0.007812
/*44  */     profile_count = vaMaxNumProfiles(hwctx->display);                            // (7) 0.03516
/*46  */     profile_list = av_malloc(profile_count * sizeof(VAProfile));                 // (5) 0.04102
/*48  */     if (!profile_list) {                                                         // (19) 0.01953
/*50  */         err = AVERROR(ENOMEM);                                                   // (10) 0.0332
/*52  */         goto fail;                                                               // (22) 0.01953
/*54  */     }                                                                            // (25) 0.007812
/*58  */     vas = vaQueryConfigProfiles(hwctx->display,                                  // (13) 0.03125
/*60  */                                 profile_list, &profile_count);                   // 0.0
/*62  */     if (vas != VA_STATUS_SUCCESS) {                                              // 0.0
/*64  */         av_log(ctx, loglevel, "Failed to query profiles: %d (%s).\n",            // 0.0
/*66  */                vas, vaErrorStr(vas));                                            // 0.0
/*68  */         err = AVERROR(EIO);                                                      // 0.0
/*70  */         goto fail;                                                               // 0.0
/*72  */     }                                                                            // 0.0
/*76  */     profile = VAProfileNone;                                                     // 0.0
/*78  */     exact_match = 0;                                                             // 0.0
/*82  */     for (i = 0; i < FF_ARRAY_ELEMS(vaapi_profile_map); i++) {                    // 0.0
/*84  */         int profile_match = 0;                                                   // 0.0
/*86  */         if (avctx->codec_id != vaapi_profile_map[i].codec_id)                    // 0.0
/*88  */             continue;                                                            // 0.0
/*90  */         if (avctx->profile == vaapi_profile_map[i].codec_profile)                // 0.0
/*92  */             profile_match = 1;                                                   // 0.0
/*94  */         profile = vaapi_profile_map[i].va_profile;                               // 0.0
/*96  */         for (j = 0; j < profile_count; j++) {                                    // 0.0
/*98  */             if (profile == profile_list[j]) {                                    // 0.0
/*100 */                 exact_match = profile_match;                                     // 0.0
/*102 */                 break;                                                           // 0.0
/*104 */             }                                                                    // 0.0
/*106 */         }                                                                        // 0.0
/*108 */         if (j < profile_count) {                                                 // 0.0
/*110 */             if (exact_match)                                                     // 0.0
/*112 */                 break;                                                           // 0.0
/*114 */             alt_profile = vaapi_profile_map[i].codec_profile;                    // 0.0
/*116 */         }                                                                        // 0.0
/*118 */     }                                                                            // 0.0
/*120 */     av_freep(&profile_list);                                                     // 0.0
/*124 */     if (profile == VAProfileNone) {                                              // 0.0
/*126 */         av_log(ctx, loglevel, "No VAAPI support for codec %s.\n",                // 0.0
/*128 */                codec_desc->name);                                                // 0.0
/*130 */         err = AVERROR(ENOSYS);                                                   // 0.0
/*132 */         goto fail;                                                               // 0.0
/*134 */     }                                                                            // 0.0
/*136 */     if (!exact_match) {                                                          // 0.0
/*138 */         if (fallback_allowed || !hwaccel_lax_profile_check) {                    // 0.0
/*140 */             av_log(ctx, loglevel, "No VAAPI support for codec %s "               // 0.0
/*142 */                    "profile %d.\n", codec_desc->name, avctx->profile);           // 0.0
/*144 */             if (!fallback_allowed) {                                             // 0.0
/*146 */                 av_log(ctx, AV_LOG_WARNING, "If you want attempt decoding "      // 0.0
/*148 */                        "anyway with a possibly-incompatible profile, add "       // 0.0
/*150 */                        "the option -hwaccel_lax_profile_check.\n");              // 0.0
/*152 */             }                                                                    // 0.0
/*154 */             err = AVERROR(EINVAL);                                               // 0.0
/*156 */             goto fail;                                                           // 0.0
/*158 */         } else {                                                                 // 0.0
/*160 */             av_log(ctx, AV_LOG_WARNING, "No VAAPI support for codec %s "         // 0.0
/*162 */                    "profile %d: trying instead with profile %d.\n",              // 0.0
/*164 */                    codec_desc->name, avctx->profile, alt_profile);               // 0.0
/*166 */             av_log(ctx, AV_LOG_WARNING, "This may fail or give "                 // 0.0
/*168 */                    "incorrect results, depending on your hardware.\n");          // 0.0
/*170 */         }                                                                        // 0.0
/*172 */     }                                                                            // 0.0
/*176 */     ctx->va_profile = profile;                                                   // 0.0
/*178 */     ctx->va_entrypoint = VAEntrypointVLD;                                        // 0.0
/*182 */     vas = vaCreateConfig(hwctx->display, ctx->va_profile,                        // 0.0
/*184 */                          ctx->va_entrypoint, 0, 0, &ctx->va_config);             // 0.0
/*186 */     if (vas != VA_STATUS_SUCCESS) {                                              // 0.0
/*188 */         av_log(ctx, AV_LOG_ERROR, "Failed to create decode pipeline "            // 0.0
/*190 */                "configuration: %d (%s).\n", vas, vaErrorStr(vas));               // 0.0
/*192 */         err = AVERROR(EIO);                                                      // 0.0
/*194 */         goto fail;                                                               // 0.0
/*196 */     }                                                                            // 0.0
/*200 */     hwconfig = av_hwdevice_hwconfig_alloc(ctx->device_ref);                      // 0.0
/*202 */     if (!hwconfig) {                                                             // 0.0
/*204 */         err = AVERROR(ENOMEM);                                                   // 0.0
/*206 */         goto fail;                                                               // 0.0
/*208 */     }                                                                            // 0.0
/*210 */     hwconfig->config_id = ctx->va_config;                                        // 0.0
/*214 */     constraints = av_hwdevice_get_hwframe_constraints(ctx->device_ref,           // 0.0
/*216 */                                                       hwconfig);                 // 0.0
/*218 */     if (!constraints)                                                            // 0.0
/*220 */         goto fail;                                                               // 0.0
/*224 */     // Decide on the decoder target format.                                      // 0.0
/*226 */     // If the user specified something with -hwaccel_output_format then          // 0.0
/*228 */     // try to use that to minimise conversions later.                            // 0.0
/*230 */     ctx->decode_format = AV_PIX_FMT_NONE;                                        // 0.0
/*232 */     if (ctx->output_format != AV_PIX_FMT_NONE &&                                 // 0.0
/*234 */         ctx->output_format != AV_PIX_FMT_VAAPI) {                                // 0.0
/*236 */         for (i = 0; constraints->valid_sw_formats[i] != AV_PIX_FMT_NONE; i++) {  // 0.0
/*238 */             if (constraints->valid_sw_formats[i] == ctx->decode_format) {        // 0.0
/*240 */                 ctx->decode_format = ctx->output_format;                         // 0.0
/*242 */                 av_log(ctx, AV_LOG_DEBUG, "Using decode format %s (output "      // 0.0
/*244 */                        "format).\n", av_get_pix_fmt_name(ctx->decode_format));   // 0.0
/*246 */                 break;                                                           // 0.0
/*248 */             }                                                                    // 0.0
/*250 */         }                                                                        // 0.0
/*252 */     }                                                                            // 0.0
/*254 */     // Otherwise, we would like to try to choose something which matches the     // 0.0
/*256 */     // decoder output, but there isn't enough information available here to      // 0.0
/*258 */     // do so.  Assume for now that we are always dealing with YUV 4:2:0, so      // 0.0
/*260 */     // pick a format which does that.                                            // 0.0
/*262 */     if (ctx->decode_format == AV_PIX_FMT_NONE) {                                 // 0.0
/*264 */         for (i = 0; constraints->valid_sw_formats[i] != AV_PIX_FMT_NONE; i++) {  // 0.0
/*266 */             pix_fmt  = constraints->valid_sw_formats[i];                         // 0.0
/*268 */             pix_desc = av_pix_fmt_desc_get(pix_fmt);                             // 0.0
/*270 */             if (pix_desc->nb_components == 3 &&                                  // 0.0
/*272 */                 pix_desc->log2_chroma_w == 1 &&                                  // 0.0
/*274 */                 pix_desc->log2_chroma_h == 1) {                                  // 0.0
/*276 */                 ctx->decode_format = pix_fmt;                                    // 0.0
/*278 */                 av_log(ctx, AV_LOG_DEBUG, "Using decode format %s (format "      // 0.0
/*280 */                        "matched).\n", av_get_pix_fmt_name(ctx->decode_format));  // 0.0
/*282 */                 break;                                                           // 0.0
/*284 */             }                                                                    // 0.0
/*286 */         }                                                                        // 0.0
/*288 */     }                                                                            // 0.0
/*290 */     // Otherwise pick the first in the list and hope for the best.               // 0.0
/*292 */     if (ctx->decode_format == AV_PIX_FMT_NONE) {                                 // 0.0
/*294 */         ctx->decode_format = constraints->valid_sw_formats[0];                   // 0.0
/*296 */         av_log(ctx, AV_LOG_DEBUG, "Using decode format %s (first in list).\n",   // 0.0
/*298 */                av_get_pix_fmt_name(ctx->decode_format));                         // 0.0
/*300 */         if (i > 1) {                                                             // 0.0
/*302 */             // There was a choice, and we picked randomly.  Warn the user        // 0.0
/*304 */             // that they might want to choose intelligently instead.             // 0.0
/*306 */             av_log(ctx, AV_LOG_WARNING, "Using randomly chosen decode "          // 0.0
/*308 */                    "format %s.\n", av_get_pix_fmt_name(ctx->decode_format));     // 0.0
/*310 */         }                                                                        // 0.0
/*312 */     }                                                                            // 0.0
/*316 */     // Ensure the picture size is supported by the hardware.                     // 0.0
/*318 */     ctx->decode_width  = avctx->coded_width;                                     // 0.0
/*320 */     ctx->decode_height = avctx->coded_height;                                    // 0.0
/*322 */     if (ctx->decode_width  < constraints->min_width  ||                          // 0.0
/*324 */         ctx->decode_height < constraints->min_height ||                          // 0.0
/*326 */         ctx->decode_width  > constraints->max_width  ||                          // 0.0
/*328 */         ctx->decode_height >constraints->max_height) {                           // 0.0
/*330 */         av_log(ctx, AV_LOG_ERROR, "VAAPI hardware does not support image "       // 0.0
/*332 */                "size %dx%d (constraints: width %d-%d height %d-%d).\n",          // 0.0
/*334 */                ctx->decode_width, ctx->decode_height,                            // 0.0
/*336 */                constraints->min_width,  constraints->max_width,                  // 0.0
/*338 */                constraints->min_height, constraints->max_height);                // 0.0
/*340 */         err = AVERROR(EINVAL);                                                   // 0.0
/*342 */         goto fail;                                                               // 0.0
/*344 */     }                                                                            // 0.0
/*348 */     av_hwframe_constraints_free(&constraints);                                   // 0.0
/*350 */     av_freep(&hwconfig);                                                         // 0.0
/*354 */     // Decide how many reference frames we need.  This might be doable more      // 0.0
/*356 */     // nicely based on the codec and input stream?                               // 0.0
/*358 */     ctx->decode_surfaces = DEFAULT_SURFACES;                                     // 0.0
/*360 */     // For frame-threaded decoding, one additional surfaces is needed for        // 0.0
/*362 */     // each thread.                                                              // 0.0
/*364 */     if (avctx->active_thread_type & FF_THREAD_FRAME)                             // 0.0
/*366 */         ctx->decode_surfaces += avctx->thread_count;                             // 0.0
/*370 */     return 0;                                                                    // 0.0
/*374 */ fail:                                                                            // 0.0
/*376 */     av_hwframe_constraints_free(&constraints);                                   // 0.0
/*378 */     av_freep(&hwconfig);                                                         // 0.0
/*380 */     vaDestroyConfig(hwctx->display, ctx->va_config);                             // 0.0
/*382 */     av_freep(&profile_list);                                                     // 0.0
/*384 */     return err;                                                                  // 0.0
/*386 */ }                                                                                // 0.0

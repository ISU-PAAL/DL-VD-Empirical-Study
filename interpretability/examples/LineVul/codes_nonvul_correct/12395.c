// commit message FFmpeg@892bbbcdc1 (target=0, prob=0.23459336, correct=True): vaapi_encode: Check packed header capabilities
/*0   */ static av_cold int vaapi_encode_config_attributes(AVCodecContext *avctx)     // (2) 0.04688
/*2   */ {                                                                            // (30) 0.001953
/*4   */     VAAPIEncodeContext *ctx = avctx->priv_data;                              // (10) 0.03516
/*6   */     VAStatus vas;                                                            // (25) 0.01367
/*8   */     int i, n, err;                                                           // (20) 0.01953
/*10  */     VAProfile    *profiles    = NULL;                                        // (12) 0.0332
/*12  */     VAEntrypoint *entrypoints = NULL;                                        // (19) 0.02344
/*14  */     VAConfigAttrib attr[] = {                                                // (17) 0.02734
/*16  */         { VAConfigAttribRTFormat        },                                   // (3) 0.04687
/*18  */         { VAConfigAttribRateControl     },                                   // (7) 0.04102
/*20  */         { VAConfigAttribEncMaxRefFrames },                                   // (8) 0.03711
/*22  */     };                                                                       // (26) 0.007813
/*26  */     n = vaMaxNumProfiles(ctx->hwctx->display);                               // (11) 0.03516
/*28  */     profiles = av_malloc_array(n, sizeof(VAProfile));                        // (9) 0.03711
/*30  */     if (!profiles) {                                                         // (24) 0.01758
/*32  */         err = AVERROR(ENOMEM);                                               // (15) 0.0332
/*34  */         goto fail;                                                           // (21) 0.01953
/*36  */     }                                                                        // (27) 0.007812
/*38  */     vas = vaQueryConfigProfiles(ctx->hwctx->display, profiles, &n);          // (4) 0.04492
/*40  */     if (vas != VA_STATUS_SUCCESS) {                                          // (13) 0.0332
/*42  */         av_log(ctx, AV_LOG_ERROR, "Failed to query profiles: %d (%s).\n",    // (0) 0.06641
/*44  */                vas, vaErrorStr(vas));                                        // (6) 0.04297
/*46  */         err = AVERROR(ENOSYS);                                               // (14) 0.0332
/*48  */         goto fail;                                                           // (22) 0.01953
/*50  */     }                                                                        // (28) 0.007812
/*52  */     for (i = 0; i < n; i++) {                                                // (16) 0.03125
/*54  */         if (profiles[i] == ctx->va_profile)                                  // (5) 0.04297
/*56  */             break;                                                           // (18) 0.02539
/*58  */     }                                                                        // (29) 0.007812
/*60  */     if (i >= n) {                                                            // (23) 0.01953
/*62  */         av_log(ctx, AV_LOG_ERROR, "Encoding profile not found (%d).\n",      // (1) 0.06055
/*64  */                ctx->va_profile);                                             // 0.0
/*66  */         err = AVERROR(ENOSYS);                                               // 0.0
/*68  */         goto fail;                                                           // 0.0
/*70  */     }                                                                        // 0.0
/*74  */     n = vaMaxNumEntrypoints(ctx->hwctx->display);                            // 0.0
/*76  */     entrypoints = av_malloc_array(n, sizeof(VAEntrypoint));                  // 0.0
/*78  */     if (!entrypoints) {                                                      // 0.0
/*80  */         err = AVERROR(ENOMEM);                                               // 0.0
/*82  */         goto fail;                                                           // 0.0
/*84  */     }                                                                        // 0.0
/*86  */     vas = vaQueryConfigEntrypoints(ctx->hwctx->display, ctx->va_profile,     // 0.0
/*88  */                                    entrypoints, &n);                         // 0.0
/*90  */     if (vas != VA_STATUS_SUCCESS) {                                          // 0.0
/*92  */         av_log(ctx, AV_LOG_ERROR, "Failed to query entrypoints for "         // 0.0
/*94  */                "profile %u: %d (%s).\n", ctx->va_profile,                    // 0.0
/*96  */                vas, vaErrorStr(vas));                                        // 0.0
/*98  */         err = AVERROR(ENOSYS);                                               // 0.0
/*100 */         goto fail;                                                           // 0.0
/*102 */     }                                                                        // 0.0
/*104 */     for (i = 0; i < n; i++) {                                                // 0.0
/*106 */         if (entrypoints[i] == ctx->va_entrypoint)                            // 0.0
/*108 */             break;                                                           // 0.0
/*110 */     }                                                                        // 0.0
/*112 */     if (i >= n) {                                                            // 0.0
/*114 */         av_log(ctx, AV_LOG_ERROR, "Encoding entrypoint not found "           // 0.0
/*116 */                "(%d / %d).\n", ctx->va_profile, ctx->va_entrypoint);         // 0.0
/*118 */         err = AVERROR(ENOSYS);                                               // 0.0
/*120 */         goto fail;                                                           // 0.0
/*122 */     }                                                                        // 0.0
/*126 */     vas = vaGetConfigAttributes(ctx->hwctx->display,                         // 0.0
/*128 */                                 ctx->va_profile, ctx->va_entrypoint,         // 0.0
/*130 */                                 attr, FF_ARRAY_ELEMS(attr));                 // 0.0
/*132 */     if (vas != VA_STATUS_SUCCESS) {                                          // 0.0
/*134 */         av_log(avctx, AV_LOG_ERROR, "Failed to fetch config "                // 0.0
/*136 */                "attributes: %d (%s).\n", vas, vaErrorStr(vas));              // 0.0
/*138 */         return AVERROR(EINVAL);                                              // 0.0
/*140 */     }                                                                        // 0.0
/*144 */     for (i = 0; i < FF_ARRAY_ELEMS(attr); i++) {                             // 0.0
/*146 */         if (attr[i].value == VA_ATTRIB_NOT_SUPPORTED) {                      // 0.0
/*148 */             // Unfortunately we have to treat this as "don't know" and hope  // 0.0
/*150 */             // for the best, because the Intel MJPEG encoder returns this    // 0.0
/*152 */             // for all the interesting attributes.                           // 0.0
/*154 */             continue;                                                        // 0.0
/*156 */         }                                                                    // 0.0
/*158 */         switch (attr[i].type) {                                              // 0.0
/*160 */         case VAConfigAttribRTFormat:                                         // 0.0
/*162 */             if (!(ctx->va_rt_format & attr[i].value)) {                      // 0.0
/*164 */                 av_log(avctx, AV_LOG_ERROR, "Surface RT format %#x "         // 0.0
/*166 */                        "is not supported (mask %#x).\n",                     // 0.0
/*168 */                        ctx->va_rt_format, attr[i].value);                    // 0.0
/*170 */                 err = AVERROR(EINVAL);                                       // 0.0
/*172 */                 goto fail;                                                   // 0.0
/*174 */             }                                                                // 0.0
/*176 */             ctx->config_attributes[ctx->nb_config_attributes++] =            // 0.0
/*178 */                 (VAConfigAttrib) {                                           // 0.0
/*180 */                 .type  = VAConfigAttribRTFormat,                             // 0.0
/*182 */                 .value = ctx->va_rt_format,                                  // 0.0
/*184 */             };                                                               // 0.0
/*186 */             break;                                                           // 0.0
/*188 */         case VAConfigAttribRateControl:                                      // 0.0
/*190 */             if (!(ctx->va_rc_mode & attr[i].value)) {                        // 0.0
/*192 */                 av_log(avctx, AV_LOG_ERROR, "Rate control mode %#x "         // 0.0
/*194 */                        "is not supported (mask: %#x).\n",                    // 0.0
/*196 */                        ctx->va_rc_mode, attr[i].value);                      // 0.0
/*198 */                 err = AVERROR(EINVAL);                                       // 0.0
/*200 */                 goto fail;                                                   // 0.0
/*202 */             }                                                                // 0.0
/*204 */             ctx->config_attributes[ctx->nb_config_attributes++] =            // 0.0
/*206 */                 (VAConfigAttrib) {                                           // 0.0
/*208 */                 .type  = VAConfigAttribRateControl,                          // 0.0
/*210 */                 .value = ctx->va_rc_mode,                                    // 0.0
/*212 */             };                                                               // 0.0
/*214 */             break;                                                           // 0.0
/*216 */         case VAConfigAttribEncMaxRefFrames:                                  // 0.0
/*218 */         {                                                                    // 0.0
/*220 */             unsigned int ref_l0 = attr[i].value & 0xffff;                    // 0.0
/*222 */             unsigned int ref_l1 = (attr[i].value >> 16) & 0xffff;            // 0.0
/*226 */             if (avctx->gop_size > 1 && ref_l0 < 1) {                         // 0.0
/*228 */                 av_log(avctx, AV_LOG_ERROR, "P frames are not "              // 0.0
/*230 */                        "supported (%#x).\n", attr[i].value);                 // 0.0
/*232 */                 err = AVERROR(EINVAL);                                       // 0.0
/*234 */                 goto fail;                                                   // 0.0
/*236 */             }                                                                // 0.0
/*238 */             if (avctx->max_b_frames > 0 && ref_l1 < 1) {                     // 0.0
/*240 */                 av_log(avctx, AV_LOG_ERROR, "B frames are not "              // 0.0
/*242 */                        "supported (%#x).\n", attr[i].value);                 // 0.0
/*244 */                 err = AVERROR(EINVAL);                                       // 0.0
/*246 */                 goto fail;                                                   // 0.0
/*248 */             }                                                                // 0.0
/*250 */         }                                                                    // 0.0
/*252 */         break;                                                               // 0.0
/*254 */         default:                                                             // 0.0
/*256 */             av_assert0(0 && "Unexpected config attribute.");                 // 0.0
/*258 */         }                                                                    // 0.0
/*260 */     }                                                                        // 0.0
/*264 */     err = 0;                                                                 // 0.0
/*266 */ fail:                                                                        // 0.0
/*268 */     av_freep(&profiles);                                                     // 0.0
/*270 */     av_freep(&entrypoints);                                                  // 0.0
/*272 */     return err;                                                              // 0.0
/*274 */ }                                                                            // 0.0

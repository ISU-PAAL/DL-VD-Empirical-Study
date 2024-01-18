// commit message FFmpeg@0f8d3d8a46 (target=0, prob=0.38531888, correct=True): avcodec/ffv1enc: compute the max number of slices and limit by that
/*0   */ static av_cold int encode_init(AVCodecContext *avctx)                                                                              // (12) 0.0332
/*2   */ {                                                                                                                                  // (24) 0.001953
/*4   */     FFV1Context *s = avctx->priv_data;                                                                                             // (13) 0.0332
/*6   */     const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(avctx->pix_fmt);                                                          // (1) 0.07031
/*8   */     int i, j, k, m, ret;                                                                                                           // (16) 0.02734
/*12  */     if ((ret = ff_ffv1_common_init(avctx)) < 0)                                                                                    // (5) 0.04492
/*14  */         return ret;                                                                                                                // (19) 0.01953
/*18  */     s->version = 0;                                                                                                                // (20) 0.01758
/*22  */     if ((avctx->flags & (AV_CODEC_FLAG_PASS1 | AV_CODEC_FLAG_PASS2)) ||                                                            // (3) 0.0664
/*24  */         avctx->slices > 1)                                                                                                         // (14) 0.03125
/*26  */         s->version = FFMAX(s->version, 2);                                                                                         // (6) 0.03906
/*30  */     // Unspecified level & slices, we choose version 1.2+ to ensure multithreaded decodability                                     // (4) 0.0508
/*32  */     if (avctx->slices == 0 && avctx->level < 0 && avctx->width * avctx->height > 720*576)                                          // (2) 0.06836
/*34  */         s->version = FFMAX(s->version, 2);                                                                                         // (8) 0.03906
/*38  */     if (avctx->level <= 0 && s->version == 2) {                                                                                    // (10) 0.03711
/*40  */         s->version = 3;                                                                                                            // (17) 0.02539
/*42  */     }                                                                                                                              // (22) 0.007812
/*44  */     if (avctx->level >= 0 && avctx->level <= 4) {                                                                                  // (7) 0.03906
/*46  */         if (avctx->level < s->version) {                                                                                           // (11) 0.03711
/*48  */             av_log(avctx, AV_LOG_ERROR, "Version %d needed for requested features but %d requested\n", s->version, avctx->level);  // (0) 0.09375
/*50  */             return AVERROR(EINVAL);                                                                                                // (9) 0.03906
/*52  */         }                                                                                                                          // (21) 0.01562
/*54  */         s->version = avctx->level;                                                                                                 // (15) 0.03125
/*56  */     }                                                                                                                              // (23) 0.007812
/*60  */     if (s->ec < 0) {                                                                                                               // (18) 0.02344
/*62  */         s->ec = (s->version >= 3);                                                                                                 // 0.0
/*64  */     }                                                                                                                              // 0.0
/*68  */     if ((s->version == 2 || s->version>3) && avctx->strict_std_compliance > FF_COMPLIANCE_EXPERIMENTAL) {                          // 0.0
/*70  */         av_log(avctx, AV_LOG_ERROR, "Version 2 needed for requested features but version 2 is experimental and not enabled\n");    // 0.0
/*72  */         return AVERROR_INVALIDDATA;                                                                                                // 0.0
/*74  */     }                                                                                                                              // 0.0
/*78  */ #if FF_API_CODER_TYPE                                                                                                              // 0.0
/*80  */ FF_DISABLE_DEPRECATION_WARNINGS                                                                                                    // 0.0
/*82  */     if (avctx->coder_type != -1)                                                                                                   // 0.0
/*84  */         s->ac = avctx->coder_type > 0 ? AC_RANGE_CUSTOM_TAB : AC_GOLOMB_RICE;                                                      // 0.0
/*86  */     else                                                                                                                           // 0.0
/*88  */ FF_ENABLE_DEPRECATION_WARNINGS                                                                                                     // 0.0
/*90  */ #endif                                                                                                                             // 0.0
/*92  */     if (s->ac == 1) // Compatbility with common command line usage                                                                 // 0.0
/*94  */         s->ac = AC_RANGE_CUSTOM_TAB;                                                                                               // 0.0
/*96  */     else if (s->ac == AC_RANGE_DEFAULT_TAB_FORCE)                                                                                  // 0.0
/*98  */         s->ac = AC_RANGE_DEFAULT_TAB;                                                                                              // 0.0
/*102 */     s->plane_count = 3;                                                                                                            // 0.0
/*104 */     switch(avctx->pix_fmt) {                                                                                                       // 0.0
/*106 */     case AV_PIX_FMT_YUV444P9:                                                                                                      // 0.0
/*108 */     case AV_PIX_FMT_YUV422P9:                                                                                                      // 0.0
/*110 */     case AV_PIX_FMT_YUV420P9:                                                                                                      // 0.0
/*112 */     case AV_PIX_FMT_YUVA444P9:                                                                                                     // 0.0
/*114 */     case AV_PIX_FMT_YUVA422P9:                                                                                                     // 0.0
/*116 */     case AV_PIX_FMT_YUVA420P9:                                                                                                     // 0.0
/*118 */         if (!avctx->bits_per_raw_sample)                                                                                           // 0.0
/*120 */             s->bits_per_raw_sample = 9;                                                                                            // 0.0
/*122 */     case AV_PIX_FMT_GRAY10:                                                                                                        // 0.0
/*124 */     case AV_PIX_FMT_YUV444P10:                                                                                                     // 0.0
/*126 */     case AV_PIX_FMT_YUV420P10:                                                                                                     // 0.0
/*128 */     case AV_PIX_FMT_YUV422P10:                                                                                                     // 0.0
/*130 */     case AV_PIX_FMT_YUVA444P10:                                                                                                    // 0.0
/*132 */     case AV_PIX_FMT_YUVA422P10:                                                                                                    // 0.0
/*134 */     case AV_PIX_FMT_YUVA420P10:                                                                                                    // 0.0
/*136 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample)                                                                // 0.0
/*138 */             s->bits_per_raw_sample = 10;                                                                                           // 0.0
/*140 */     case AV_PIX_FMT_GRAY12:                                                                                                        // 0.0
/*142 */     case AV_PIX_FMT_YUV444P12:                                                                                                     // 0.0
/*144 */     case AV_PIX_FMT_YUV420P12:                                                                                                     // 0.0
/*146 */     case AV_PIX_FMT_YUV422P12:                                                                                                     // 0.0
/*148 */         s->packed_at_lsb = 1;                                                                                                      // 0.0
/*150 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample)                                                                // 0.0
/*152 */             s->bits_per_raw_sample = 12;                                                                                           // 0.0
/*154 */     case AV_PIX_FMT_GRAY16:                                                                                                        // 0.0
/*156 */     case AV_PIX_FMT_YUV444P16:                                                                                                     // 0.0
/*158 */     case AV_PIX_FMT_YUV422P16:                                                                                                     // 0.0
/*160 */     case AV_PIX_FMT_YUV420P16:                                                                                                     // 0.0
/*162 */     case AV_PIX_FMT_YUVA444P16:                                                                                                    // 0.0
/*164 */     case AV_PIX_FMT_YUVA422P16:                                                                                                    // 0.0
/*166 */     case AV_PIX_FMT_YUVA420P16:                                                                                                    // 0.0
/*168 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample) {                                                              // 0.0
/*170 */             s->bits_per_raw_sample = 16;                                                                                           // 0.0
/*172 */         } else if (!s->bits_per_raw_sample) {                                                                                      // 0.0
/*174 */             s->bits_per_raw_sample = avctx->bits_per_raw_sample;                                                                   // 0.0
/*176 */         }                                                                                                                          // 0.0
/*178 */         if (s->bits_per_raw_sample <= 8) {                                                                                         // 0.0
/*180 */             av_log(avctx, AV_LOG_ERROR, "bits_per_raw_sample invalid\n");                                                          // 0.0
/*182 */             return AVERROR_INVALIDDATA;                                                                                            // 0.0
/*184 */         }                                                                                                                          // 0.0
/*186 */         s->version = FFMAX(s->version, 1);                                                                                         // 0.0
/*188 */     case AV_PIX_FMT_GRAY8:                                                                                                         // 0.0
/*190 */     case AV_PIX_FMT_YA8:                                                                                                           // 0.0
/*192 */     case AV_PIX_FMT_YUV444P:                                                                                                       // 0.0
/*194 */     case AV_PIX_FMT_YUV440P:                                                                                                       // 0.0
/*196 */     case AV_PIX_FMT_YUV422P:                                                                                                       // 0.0
/*198 */     case AV_PIX_FMT_YUV420P:                                                                                                       // 0.0
/*200 */     case AV_PIX_FMT_YUV411P:                                                                                                       // 0.0
/*202 */     case AV_PIX_FMT_YUV410P:                                                                                                       // 0.0
/*204 */     case AV_PIX_FMT_YUVA444P:                                                                                                      // 0.0
/*206 */     case AV_PIX_FMT_YUVA422P:                                                                                                      // 0.0
/*208 */     case AV_PIX_FMT_YUVA420P:                                                                                                      // 0.0
/*210 */         s->chroma_planes = desc->nb_components < 3 ? 0 : 1;                                                                        // 0.0
/*212 */         s->colorspace = 0;                                                                                                         // 0.0
/*214 */         s->transparency = desc->nb_components == 4 || desc->nb_components == 2;                                                    // 0.0
/*216 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample)                                                                // 0.0
/*218 */             s->bits_per_raw_sample = 8;                                                                                            // 0.0
/*220 */         else if (!s->bits_per_raw_sample)                                                                                          // 0.0
/*222 */             s->bits_per_raw_sample = 8;                                                                                            // 0.0
/*224 */         break;                                                                                                                     // 0.0
/*226 */     case AV_PIX_FMT_RGB32:                                                                                                         // 0.0
/*228 */         s->colorspace = 1;                                                                                                         // 0.0
/*230 */         s->transparency = 1;                                                                                                       // 0.0
/*232 */         s->chroma_planes = 1;                                                                                                      // 0.0
/*234 */         s->bits_per_raw_sample = 8;                                                                                                // 0.0
/*236 */         break;                                                                                                                     // 0.0
/*238 */     case AV_PIX_FMT_RGB48:                                                                                                         // 0.0
/*240 */         s->colorspace = 1;                                                                                                         // 0.0
/*242 */         s->chroma_planes = 1;                                                                                                      // 0.0
/*244 */         s->bits_per_raw_sample = 16;                                                                                               // 0.0
/*246 */         s->use32bit = 1;                                                                                                           // 0.0
/*248 */         s->version = FFMAX(s->version, 1);                                                                                         // 0.0
/*250 */         if (avctx->strict_std_compliance > FF_COMPLIANCE_EXPERIMENTAL) {                                                           // 0.0
/*252 */             av_log(avctx, AV_LOG_ERROR, "16bit RGB is experimental and under development, only use it for experiments\n");         // 0.0
/*254 */             return AVERROR_INVALIDDATA;                                                                                            // 0.0
/*256 */         }                                                                                                                          // 0.0
/*258 */         break;                                                                                                                     // 0.0
/*260 */     case AV_PIX_FMT_0RGB32:                                                                                                        // 0.0
/*262 */         s->colorspace = 1;                                                                                                         // 0.0
/*264 */         s->chroma_planes = 1;                                                                                                      // 0.0
/*266 */         s->bits_per_raw_sample = 8;                                                                                                // 0.0
/*268 */         break;                                                                                                                     // 0.0
/*270 */     case AV_PIX_FMT_GBRP9:                                                                                                         // 0.0
/*272 */         if (!avctx->bits_per_raw_sample)                                                                                           // 0.0
/*274 */             s->bits_per_raw_sample = 9;                                                                                            // 0.0
/*276 */     case AV_PIX_FMT_GBRP10:                                                                                                        // 0.0
/*278 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample)                                                                // 0.0
/*280 */             s->bits_per_raw_sample = 10;                                                                                           // 0.0
/*282 */     case AV_PIX_FMT_GBRP12:                                                                                                        // 0.0
/*284 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample)                                                                // 0.0
/*286 */             s->bits_per_raw_sample = 12;                                                                                           // 0.0
/*288 */     case AV_PIX_FMT_GBRP14:                                                                                                        // 0.0
/*290 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample)                                                                // 0.0
/*292 */             s->bits_per_raw_sample = 14;                                                                                           // 0.0
/*294 */     case AV_PIX_FMT_GBRP16:                                                                                                        // 0.0
/*296 */         if (!avctx->bits_per_raw_sample && !s->bits_per_raw_sample)                                                                // 0.0
/*298 */             s->bits_per_raw_sample = 16;                                                                                           // 0.0
/*300 */         else if (!s->bits_per_raw_sample)                                                                                          // 0.0
/*302 */             s->bits_per_raw_sample = avctx->bits_per_raw_sample;                                                                   // 0.0
/*304 */         s->colorspace = 1;                                                                                                         // 0.0
/*306 */         s->chroma_planes = 1;                                                                                                      // 0.0
/*308 */         if (s->bits_per_raw_sample >= 16) {                                                                                        // 0.0
/*310 */             s->use32bit = 1;                                                                                                       // 0.0
/*312 */             if (avctx->strict_std_compliance > FF_COMPLIANCE_EXPERIMENTAL) {                                                       // 0.0
/*314 */                 av_log(avctx, AV_LOG_ERROR, "16bit RGB is experimental and under development, only use it for experiments\n");     // 0.0
/*316 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*318 */             }                                                                                                                      // 0.0
/*320 */         }                                                                                                                          // 0.0
/*322 */         s->version = FFMAX(s->version, 1);                                                                                         // 0.0
/*324 */         break;                                                                                                                     // 0.0
/*326 */     default:                                                                                                                       // 0.0
/*328 */         av_log(avctx, AV_LOG_ERROR, "format not supported\n");                                                                     // 0.0
/*330 */         return AVERROR(ENOSYS);                                                                                                    // 0.0
/*332 */     }                                                                                                                              // 0.0
/*334 */     av_assert0(s->bits_per_raw_sample >= 8);                                                                                       // 0.0
/*338 */     if (s->bits_per_raw_sample > 8) {                                                                                              // 0.0
/*340 */         if (s->ac == AC_GOLOMB_RICE) {                                                                                             // 0.0
/*342 */             av_log(avctx, AV_LOG_INFO,                                                                                             // 0.0
/*344 */                     "bits_per_raw_sample > 8, forcing range coder\n");                                                             // 0.0
/*346 */             s->ac = AC_RANGE_CUSTOM_TAB;                                                                                           // 0.0
/*348 */         }                                                                                                                          // 0.0
/*350 */     }                                                                                                                              // 0.0
/*352 */     if (s->transparency) {                                                                                                         // 0.0
/*354 */         av_log(avctx, AV_LOG_WARNING, "Storing alpha plane, this will require a recent FFV1 decoder to playback!\n");              // 0.0
/*356 */     }                                                                                                                              // 0.0
/*358 */ #if FF_API_PRIVATE_OPT                                                                                                             // 0.0
/*360 */ FF_DISABLE_DEPRECATION_WARNINGS                                                                                                    // 0.0
/*362 */     if (avctx->context_model)                                                                                                      // 0.0
/*364 */         s->context_model = avctx->context_model;                                                                                   // 0.0
/*366 */     if (avctx->context_model > 1U) {                                                                                               // 0.0
/*368 */         av_log(avctx, AV_LOG_ERROR, "Invalid context model %d, valid values are 0 and 1\n", avctx->context_model);                 // 0.0
/*370 */         return AVERROR(EINVAL);                                                                                                    // 0.0
/*372 */     }                                                                                                                              // 0.0
/*374 */ FF_ENABLE_DEPRECATION_WARNINGS                                                                                                     // 0.0
/*376 */ #endif                                                                                                                             // 0.0
/*380 */     if (s->ac == AC_RANGE_CUSTOM_TAB) {                                                                                            // 0.0
/*382 */         for (i = 1; i < 256; i++)                                                                                                  // 0.0
/*384 */             s->state_transition[i] = ver2_state[i];                                                                                // 0.0
/*386 */     } else {                                                                                                                       // 0.0
/*388 */         RangeCoder c;                                                                                                              // 0.0
/*390 */         ff_build_rac_states(&c, 0.05 * (1LL << 32), 256 - 8);                                                                      // 0.0
/*392 */         for (i = 1; i < 256; i++)                                                                                                  // 0.0
/*394 */             s->state_transition[i] = c.one_state[i];                                                                               // 0.0
/*396 */     }                                                                                                                              // 0.0
/*400 */     for (i = 0; i < 256; i++) {                                                                                                    // 0.0
/*402 */         s->quant_table_count = 2;                                                                                                  // 0.0
/*404 */         if (s->bits_per_raw_sample <= 8) {                                                                                         // 0.0
/*406 */             s->quant_tables[0][0][i]=           quant11[i];                                                                        // 0.0
/*408 */             s->quant_tables[0][1][i]=        11*quant11[i];                                                                        // 0.0
/*410 */             s->quant_tables[0][2][i]=     11*11*quant11[i];                                                                        // 0.0
/*412 */             s->quant_tables[1][0][i]=           quant11[i];                                                                        // 0.0
/*414 */             s->quant_tables[1][1][i]=        11*quant11[i];                                                                        // 0.0
/*416 */             s->quant_tables[1][2][i]=     11*11*quant5 [i];                                                                        // 0.0
/*418 */             s->quant_tables[1][3][i]=   5*11*11*quant5 [i];                                                                        // 0.0
/*420 */             s->quant_tables[1][4][i]= 5*5*11*11*quant5 [i];                                                                        // 0.0
/*422 */         } else {                                                                                                                   // 0.0
/*424 */             s->quant_tables[0][0][i]=           quant9_10bit[i];                                                                   // 0.0
/*426 */             s->quant_tables[0][1][i]=        11*quant9_10bit[i];                                                                   // 0.0
/*428 */             s->quant_tables[0][2][i]=     11*11*quant9_10bit[i];                                                                   // 0.0
/*430 */             s->quant_tables[1][0][i]=           quant9_10bit[i];                                                                   // 0.0
/*432 */             s->quant_tables[1][1][i]=        11*quant9_10bit[i];                                                                   // 0.0
/*434 */             s->quant_tables[1][2][i]=     11*11*quant5_10bit[i];                                                                   // 0.0
/*436 */             s->quant_tables[1][3][i]=   5*11*11*quant5_10bit[i];                                                                   // 0.0
/*438 */             s->quant_tables[1][4][i]= 5*5*11*11*quant5_10bit[i];                                                                   // 0.0
/*440 */         }                                                                                                                          // 0.0
/*442 */     }                                                                                                                              // 0.0
/*444 */     s->context_count[0] = (11 * 11 * 11        + 1) / 2;                                                                           // 0.0
/*446 */     s->context_count[1] = (11 * 11 * 5 * 5 * 5 + 1) / 2;                                                                           // 0.0
/*448 */     memcpy(s->quant_table, s->quant_tables[s->context_model],                                                                      // 0.0
/*450 */            sizeof(s->quant_table));                                                                                                // 0.0
/*454 */     for (i = 0; i < s->plane_count; i++) {                                                                                         // 0.0
/*456 */         PlaneContext *const p = &s->plane[i];                                                                                      // 0.0
/*460 */         memcpy(p->quant_table, s->quant_table, sizeof(p->quant_table));                                                            // 0.0
/*462 */         p->quant_table_index = s->context_model;                                                                                   // 0.0
/*464 */         p->context_count     = s->context_count[p->quant_table_index];                                                             // 0.0
/*466 */     }                                                                                                                              // 0.0
/*470 */     if ((ret = ff_ffv1_allocate_initial_states(s)) < 0)                                                                            // 0.0
/*472 */         return ret;                                                                                                                // 0.0
/*476 */ #if FF_API_CODED_FRAME                                                                                                             // 0.0
/*478 */ FF_DISABLE_DEPRECATION_WARNINGS                                                                                                    // 0.0
/*480 */     avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;                                                                             // 0.0
/*482 */ FF_ENABLE_DEPRECATION_WARNINGS                                                                                                     // 0.0
/*484 */ #endif                                                                                                                             // 0.0
/*488 */     if (!s->transparency)                                                                                                          // 0.0
/*490 */         s->plane_count = 2;                                                                                                        // 0.0
/*492 */     if (!s->chroma_planes && s->version > 3)                                                                                       // 0.0
/*494 */         s->plane_count--;                                                                                                          // 0.0
/*498 */     avcodec_get_chroma_sub_sample(avctx->pix_fmt, &s->chroma_h_shift, &s->chroma_v_shift);                                         // 0.0
/*500 */     s->picture_number = 0;                                                                                                         // 0.0
/*504 */     if (avctx->flags & (AV_CODEC_FLAG_PASS1 | AV_CODEC_FLAG_PASS2)) {                                                              // 0.0
/*506 */         for (i = 0; i < s->quant_table_count; i++) {                                                                               // 0.0
/*508 */             s->rc_stat2[i] = av_mallocz(s->context_count[i] *                                                                      // 0.0
/*510 */                                         sizeof(*s->rc_stat2[i]));                                                                  // 0.0
/*512 */             if (!s->rc_stat2[i])                                                                                                   // 0.0
/*514 */                 return AVERROR(ENOMEM);                                                                                            // 0.0
/*516 */         }                                                                                                                          // 0.0
/*518 */     }                                                                                                                              // 0.0
/*520 */     if (avctx->stats_in) {                                                                                                         // 0.0
/*522 */         char *p = avctx->stats_in;                                                                                                 // 0.0
/*524 */         uint8_t (*best_state)[256] = av_malloc_array(256, 256);                                                                    // 0.0
/*526 */         int gob_count = 0;                                                                                                         // 0.0
/*528 */         char *next;                                                                                                                // 0.0
/*530 */         if (!best_state)                                                                                                           // 0.0
/*532 */             return AVERROR(ENOMEM);                                                                                                // 0.0
/*536 */         av_assert0(s->version >= 2);                                                                                               // 0.0
/*540 */         for (;;) {                                                                                                                 // 0.0
/*542 */             for (j = 0; j < 256; j++)                                                                                              // 0.0
/*544 */                 for (i = 0; i < 2; i++) {                                                                                          // 0.0
/*546 */                     s->rc_stat[j][i] = strtol(p, &next, 0);                                                                        // 0.0
/*548 */                     if (next == p) {                                                                                               // 0.0
/*550 */                         av_log(avctx, AV_LOG_ERROR,                                                                                // 0.0
/*552 */                                "2Pass file invalid at %d %d [%s]\n", j, i, p);                                                     // 0.0
/*554 */                         av_freep(&best_state);                                                                                     // 0.0
/*556 */                         return AVERROR_INVALIDDATA;                                                                                // 0.0
/*558 */                     }                                                                                                              // 0.0
/*560 */                     p = next;                                                                                                      // 0.0
/*562 */                 }                                                                                                                  // 0.0
/*564 */             for (i = 0; i < s->quant_table_count; i++)                                                                             // 0.0
/*566 */                 for (j = 0; j < s->context_count[i]; j++) {                                                                        // 0.0
/*568 */                     for (k = 0; k < 32; k++)                                                                                       // 0.0
/*570 */                         for (m = 0; m < 2; m++) {                                                                                  // 0.0
/*572 */                             s->rc_stat2[i][j][k][m] = strtol(p, &next, 0);                                                         // 0.0
/*574 */                             if (next == p) {                                                                                       // 0.0
/*576 */                                 av_log(avctx, AV_LOG_ERROR,                                                                        // 0.0
/*578 */                                        "2Pass file invalid at %d %d %d %d [%s]\n",                                                 // 0.0
/*580 */                                        i, j, k, m, p);                                                                             // 0.0
/*582 */                                 av_freep(&best_state);                                                                             // 0.0
/*584 */                                 return AVERROR_INVALIDDATA;                                                                        // 0.0
/*586 */                             }                                                                                                      // 0.0
/*588 */                             p = next;                                                                                              // 0.0
/*590 */                         }                                                                                                          // 0.0
/*592 */                 }                                                                                                                  // 0.0
/*594 */             gob_count = strtol(p, &next, 0);                                                                                       // 0.0
/*596 */             if (next == p || gob_count <= 0) {                                                                                     // 0.0
/*598 */                 av_log(avctx, AV_LOG_ERROR, "2Pass file invalid\n");                                                               // 0.0
/*600 */                 av_freep(&best_state);                                                                                             // 0.0
/*602 */                 return AVERROR_INVALIDDATA;                                                                                        // 0.0
/*604 */             }                                                                                                                      // 0.0
/*606 */             p = next;                                                                                                              // 0.0
/*608 */             while (*p == '\n' || *p == ' ')                                                                                        // 0.0
/*610 */                 p++;                                                                                                               // 0.0
/*612 */             if (p[0] == 0)                                                                                                         // 0.0
/*614 */                 break;                                                                                                             // 0.0
/*616 */         }                                                                                                                          // 0.0
/*618 */         if (s->ac == AC_RANGE_CUSTOM_TAB)                                                                                          // 0.0
/*620 */             sort_stt(s, s->state_transition);                                                                                      // 0.0
/*624 */         find_best_state(best_state, s->state_transition);                                                                          // 0.0
/*628 */         for (i = 0; i < s->quant_table_count; i++) {                                                                               // 0.0
/*630 */             for (k = 0; k < 32; k++) {                                                                                             // 0.0
/*632 */                 double a=0, b=0;                                                                                                   // 0.0
/*634 */                 int jp = 0;                                                                                                        // 0.0
/*636 */                 for (j = 0; j < s->context_count[i]; j++) {                                                                        // 0.0
/*638 */                     double p = 128;                                                                                                // 0.0
/*640 */                     if (s->rc_stat2[i][j][k][0] + s->rc_stat2[i][j][k][1] > 200 && j || a+b > 200) {                               // 0.0
/*642 */                         if (a+b)                                                                                                   // 0.0
/*644 */                             p = 256.0 * b / (a + b);                                                                               // 0.0
/*646 */                         s->initial_states[i][jp][k] =                                                                              // 0.0
/*648 */                             best_state[av_clip(round(p), 1, 255)][av_clip_uint8((a + b) / gob_count)];                             // 0.0
/*650 */                         for(jp++; jp<j; jp++)                                                                                      // 0.0
/*652 */                             s->initial_states[i][jp][k] = s->initial_states[i][jp-1][k];                                           // 0.0
/*654 */                         a=b=0;                                                                                                     // 0.0
/*656 */                     }                                                                                                              // 0.0
/*658 */                     a += s->rc_stat2[i][j][k][0];                                                                                  // 0.0
/*660 */                     b += s->rc_stat2[i][j][k][1];                                                                                  // 0.0
/*662 */                     if (a+b) {                                                                                                     // 0.0
/*664 */                         p = 256.0 * b / (a + b);                                                                                   // 0.0
/*666 */                     }                                                                                                              // 0.0
/*668 */                     s->initial_states[i][j][k] =                                                                                   // 0.0
/*670 */                         best_state[av_clip(round(p), 1, 255)][av_clip_uint8((a + b) / gob_count)];                                 // 0.0
/*672 */                 }                                                                                                                  // 0.0
/*674 */             }                                                                                                                      // 0.0
/*676 */         }                                                                                                                          // 0.0
/*678 */         av_freep(&best_state);                                                                                                     // 0.0
/*680 */     }                                                                                                                              // 0.0
/*684 */     if (s->version > 1) {                                                                                                          // 0.0
/*686 */         int plane_count = 1 + 2*s->chroma_planes + s->transparency;                                                                // 0.0
/*688 */         s->num_v_slices = (avctx->width > 352 || avctx->height > 288 || !avctx->slices) ? 2 : 1;                                   // 0.0
/*692 */         if (avctx->height < 5)                                                                                                     // 0.0
/*694 */             s->num_v_slices = 1;                                                                                                   // 0.0
/*698 */         for (; s->num_v_slices < 32; s->num_v_slices++) {                                                                          // 0.0
/*700 */             for (s->num_h_slices = s->num_v_slices; s->num_h_slices < 2*s->num_v_slices; s->num_h_slices++) {                      // 0.0
/*702 */                 int maxw = (avctx->width  + s->num_h_slices - 1) / s->num_h_slices;                                                // 0.0
/*704 */                 int maxh = (avctx->height + s->num_v_slices - 1) / s->num_v_slices;                                                // 0.0
/*706 */                 if (s->num_h_slices > avctx->width || s->num_v_slices > avctx->height)                                             // 0.0
/*708 */                     continue;                                                                                                      // 0.0
/*710 */                 if (maxw * maxh * (int64_t)(s->bits_per_raw_sample+1) * plane_count > 8<<24)                                       // 0.0
/*712 */                     continue;                                                                                                      // 0.0
/*714 */                 if (avctx->slices == s->num_h_slices * s->num_v_slices && avctx->slices <= MAX_SLICES || !avctx->slices)           // 0.0
/*716 */                     goto slices_ok;                                                                                                // 0.0
/*718 */             }                                                                                                                      // 0.0
/*720 */         }                                                                                                                          // 0.0
/*722 */         av_log(avctx, AV_LOG_ERROR,                                                                                                // 0.0
/*724 */                "Unsupported number %d of slices requested, please specify a "                                                      // 0.0
/*726 */                "supported number with -slices (ex:4,6,9,12,16, ...)\n",                                                            // 0.0
/*728 */                avctx->slices);                                                                                                     // 0.0
/*730 */         return AVERROR(ENOSYS);                                                                                                    // 0.0
/*732 */ slices_ok:                                                                                                                         // 0.0
/*734 */         if ((ret = write_extradata(s)) < 0)                                                                                        // 0.0
/*736 */             return ret;                                                                                                            // 0.0
/*738 */     }                                                                                                                              // 0.0
/*742 */     if ((ret = ff_ffv1_init_slice_contexts(s)) < 0)                                                                                // 0.0
/*744 */         return ret;                                                                                                                // 0.0
/*746 */     s->slice_count = s->max_slice_count;                                                                                           // 0.0
/*748 */     if ((ret = ff_ffv1_init_slices_state(s)) < 0)                                                                                  // 0.0
/*750 */         return ret;                                                                                                                // 0.0
/*754 */ #define STATS_OUT_SIZE 1024 * 1024 * 6                                                                                             // 0.0
/*756 */     if (avctx->flags & AV_CODEC_FLAG_PASS1) {                                                                                      // 0.0
/*758 */         avctx->stats_out = av_mallocz(STATS_OUT_SIZE);                                                                             // 0.0
/*760 */         if (!avctx->stats_out)                                                                                                     // 0.0
/*762 */             return AVERROR(ENOMEM);                                                                                                // 0.0
/*764 */         for (i = 0; i < s->quant_table_count; i++)                                                                                 // 0.0
/*766 */             for (j = 0; j < s->max_slice_count; j++) {                                                                             // 0.0
/*768 */                 FFV1Context *sf = s->slice_context[j];                                                                             // 0.0
/*770 */                 av_assert0(!sf->rc_stat2[i]);                                                                                      // 0.0
/*772 */                 sf->rc_stat2[i] = av_mallocz(s->context_count[i] *                                                                 // 0.0
/*774 */                                              sizeof(*sf->rc_stat2[i]));                                                            // 0.0
/*776 */                 if (!sf->rc_stat2[i])                                                                                              // 0.0
/*778 */                     return AVERROR(ENOMEM);                                                                                        // 0.0
/*780 */             }                                                                                                                      // 0.0
/*782 */     }                                                                                                                              // 0.0
/*786 */     return 0;                                                                                                                      // 0.0
/*788 */ }                                                                                                                                  // 0.0

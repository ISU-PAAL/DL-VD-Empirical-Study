// commit message FFmpeg@b52b398c30 (target=0, prob=0.4369849, correct=True): vc2enc: decrease default strictness level
/*0   */ static av_cold int vc2_encode_init(AVCodecContext *avctx)                                   // (8) 0.04311
/*2   */ {                                                                                           // (27) 0.002005
/*4   */     Plane *p;                                                                               // (26) 0.01368
/*6   */     SubBand *b;                                                                             // (25) 0.01565
/*8   */     int i, j, level, o, shift;                                                              // (12) 0.02744
/*10  */     const AVPixFmtDescriptor *fmt = av_pix_fmt_desc_get(avctx->pix_fmt);                    // (1) 0.07221
/*12  */     const int depth = fmt->comp[0].depth;                                                   // (10) 0.02927
/*14  */     VC2EncContext *s = avctx->priv_data;                                                    // (9) 0.03318
/*18  */     s->picture_number = 0;                                                                  // (20) 0.02147
/*22  */     /* Total allowed quantization range */                                                  // (23) 0.01952
/*24  */     s->q_ceil    = DIRAC_MAX_QUANT_INDEX;                                                   // (6) 0.04879
/*28  */     s->ver.major = 2;                                                                       // (21) 0.02147
/*30  */     s->ver.minor = 0;                                                                       // (18) 0.02342
/*32  */     s->profile   = 3;                                                                       // (22) 0.02147
/*34  */     s->level     = 3;                                                                       // (13) 0.02537
/*38  */     s->base_vf   = -1;                                                                      // (11) 0.02927
/*40  */     s->strict_compliance = 1;                                                               // (17) 0.02342
/*44  */     s->q_avg = 0;                                                                           // (19) 0.02342
/*46  */     s->slice_max_bytes = 0;                                                                 // (15) 0.02537
/*48  */     s->slice_min_bytes = 0;                                                                 // (14) 0.02537
/*52  */     /* Mark unknown as progressive */                                                       // (24) 0.01757
/*54  */     s->interlaced = !((avctx->field_order == AV_FIELD_UNKNOWN) ||                           // (3) 0.05074
/*56  */                       (avctx->field_order == AV_FIELD_PROGRESSIVE));                        // (0) 0.07415
/*60  */     for (i = 0; i < base_video_fmts_len; i++) {                                             // (7) 0.04488
/*62  */         const VC2BaseVideoFormat *fmt = &base_video_fmts[i];                                // (2) 0.05269
/*64  */         if (avctx->pix_fmt != fmt->pix_fmt)                                                 // (4) 0.05074
/*66  */             continue;                                                                       // (16) 0.02537
/*68  */         if (avctx->time_base.num != fmt->time_base.num)                                     // (5) 0.05074
/*70  */             continue;                                                                       // 0.0
/*72  */         if (avctx->time_base.den != fmt->time_base.den)                                     // 0.0
/*74  */             continue;                                                                       // 0.0
/*76  */         if (avctx->width != fmt->width)                                                     // 0.0
/*78  */             continue;                                                                       // 0.0
/*80  */         if (avctx->height != fmt->height)                                                   // 0.0
/*82  */             continue;                                                                       // 0.0
/*84  */         if (s->interlaced != fmt->interlaced)                                               // 0.0
/*86  */             continue;                                                                       // 0.0
/*88  */         s->base_vf = i;                                                                     // 0.0
/*90  */         s->level   = base_video_fmts[i].level;                                              // 0.0
/*92  */         break;                                                                              // 0.0
/*94  */     }                                                                                       // 0.0
/*98  */     if (s->interlaced)                                                                      // 0.0
/*100 */         av_log(avctx, AV_LOG_WARNING, "Interlacing enabled!\n");                            // 0.0
/*104 */     if ((s->slice_width  & (s->slice_width  - 1)) ||                                        // 0.0
/*106 */         (s->slice_height & (s->slice_height - 1))) {                                        // 0.0
/*108 */         av_log(avctx, AV_LOG_ERROR, "Slice size is not a power of two!\n");                 // 0.0
/*110 */         return AVERROR_UNKNOWN;                                                             // 0.0
/*112 */     }                                                                                       // 0.0
/*116 */     if ((s->slice_width > avctx->width) ||                                                  // 0.0
/*118 */         (s->slice_height > avctx->height)) {                                                // 0.0
/*120 */         av_log(avctx, AV_LOG_ERROR, "Slice size is bigger than the image!\n");              // 0.0
/*122 */         return AVERROR_UNKNOWN;                                                             // 0.0
/*124 */     }                                                                                       // 0.0
/*128 */     if (s->base_vf <= 0) {                                                                  // 0.0
/*130 */         if (avctx->strict_std_compliance <= FF_COMPLIANCE_UNOFFICIAL) {                     // 0.0
/*132 */             s->strict_compliance = s->base_vf = 0;                                          // 0.0
/*134 */             av_log(avctx, AV_LOG_WARNING, "Disabling strict compliance\n");                 // 0.0
/*136 */         } else {                                                                            // 0.0
/*138 */             av_log(avctx, AV_LOG_WARNING, "Given format does not strictly comply with "     // 0.0
/*140 */                    "the specifications, please add a -strict -1 flag to use it\n");         // 0.0
/*142 */             return AVERROR_UNKNOWN;                                                         // 0.0
/*144 */         }                                                                                   // 0.0
/*146 */     } else {                                                                                // 0.0
/*148 */         av_log(avctx, AV_LOG_INFO, "Selected base video format = %i (%s)\n",                // 0.0
/*150 */                s->base_vf, base_video_fmts[s->base_vf].name);                               // 0.0
/*152 */     }                                                                                       // 0.0
/*156 */     /* Chroma subsampling */                                                                // 0.0
/*158 */     avcodec_get_chroma_sub_sample(avctx->pix_fmt, &s->chroma_x_shift, &s->chroma_y_shift);  // 0.0
/*162 */     /* Bit depth and color range index */                                                   // 0.0
/*164 */     if (depth == 8 && avctx->color_range == AVCOL_RANGE_JPEG) {                             // 0.0
/*166 */         s->bpp = 1;                                                                         // 0.0
/*168 */         s->bpp_idx = 1;                                                                     // 0.0
/*170 */         s->diff_offset = 128;                                                               // 0.0
/*172 */     } else if (depth == 8 && (avctx->color_range == AVCOL_RANGE_MPEG ||                     // 0.0
/*174 */                avctx->color_range == AVCOL_RANGE_UNSPECIFIED)) {                            // 0.0
/*176 */         s->bpp = 1;                                                                         // 0.0
/*178 */         s->bpp_idx = 2;                                                                     // 0.0
/*180 */         s->diff_offset = 128;                                                               // 0.0
/*182 */     } else if (depth == 10) {                                                               // 0.0
/*184 */         s->bpp = 2;                                                                         // 0.0
/*186 */         s->bpp_idx = 3;                                                                     // 0.0
/*188 */         s->diff_offset = 512;                                                               // 0.0
/*190 */     } else {                                                                                // 0.0
/*192 */         s->bpp = 2;                                                                         // 0.0
/*194 */         s->bpp_idx = 4;                                                                     // 0.0
/*196 */         s->diff_offset = 2048;                                                              // 0.0
/*198 */     }                                                                                       // 0.0
/*202 */     /* Planes initialization */                                                             // 0.0
/*204 */     for (i = 0; i < 3; i++) {                                                               // 0.0
/*206 */         int w, h;                                                                           // 0.0
/*208 */         p = &s->plane[i];                                                                   // 0.0
/*210 */         p->width      = avctx->width  >> (i ? s->chroma_x_shift : 0);                       // 0.0
/*212 */         p->height     = avctx->height >> (i ? s->chroma_y_shift : 0);                       // 0.0
/*214 */         if (s->interlaced)                                                                  // 0.0
/*216 */             p->height >>= 1;                                                                // 0.0
/*218 */         p->dwt_width  = w = FFALIGN(p->width,  (1 << s->wavelet_depth));                    // 0.0
/*220 */         p->dwt_height = h = FFALIGN(p->height, (1 << s->wavelet_depth));                    // 0.0
/*222 */         p->coef_stride = FFALIGN(p->dwt_width, 32);                                         // 0.0
/*224 */         p->coef_buf = av_malloc(p->coef_stride*p->dwt_height*sizeof(dwtcoef));              // 0.0
/*226 */         if (!p->coef_buf)                                                                   // 0.0
/*228 */             goto alloc_fail;                                                                // 0.0
/*230 */         for (level = s->wavelet_depth-1; level >= 0; level--) {                             // 0.0
/*232 */             w = w >> 1;                                                                     // 0.0
/*234 */             h = h >> 1;                                                                     // 0.0
/*236 */             for (o = 0; o < 4; o++) {                                                       // 0.0
/*238 */                 b = &p->band[level][o];                                                     // 0.0
/*240 */                 b->width  = w;                                                              // 0.0
/*242 */                 b->height = h;                                                              // 0.0
/*244 */                 b->stride = p->coef_stride;                                                 // 0.0
/*246 */                 shift = (o > 1)*b->height*b->stride + (o & 1)*b->width;                     // 0.0
/*248 */                 b->buf = p->coef_buf + shift;                                               // 0.0
/*250 */             }                                                                               // 0.0
/*252 */         }                                                                                   // 0.0
/*256 */         /* DWT init */                                                                      // 0.0
/*258 */         if (ff_vc2enc_init_transforms(&s->transform_args[i].t,                              // 0.0
/*260 */                                       s->plane[i].coef_stride,                              // 0.0
/*262 */                                       s->plane[i].dwt_height))                              // 0.0
/*264 */             goto alloc_fail;                                                                // 0.0
/*266 */     }                                                                                       // 0.0
/*270 */     /* Slices */                                                                            // 0.0
/*272 */     s->num_x = s->plane[0].dwt_width/s->slice_width;                                        // 0.0
/*274 */     s->num_y = s->plane[0].dwt_height/s->slice_height;                                      // 0.0
/*278 */     s->slice_args = av_calloc(s->num_x*s->num_y, sizeof(SliceArgs));                        // 0.0
/*280 */     if (!s->slice_args)                                                                     // 0.0
/*282 */         goto alloc_fail;                                                                    // 0.0
/*286 */     /* Lookup tables */                                                                     // 0.0
/*288 */     s->coef_lut_len = av_malloc(COEF_LUT_TAB*(s->q_ceil+1)*sizeof(*s->coef_lut_len));       // 0.0
/*290 */     if (!s->coef_lut_len)                                                                   // 0.0
/*292 */         goto alloc_fail;                                                                    // 0.0
/*296 */     s->coef_lut_val = av_malloc(COEF_LUT_TAB*(s->q_ceil+1)*sizeof(*s->coef_lut_val));       // 0.0
/*298 */     if (!s->coef_lut_val)                                                                   // 0.0
/*300 */         goto alloc_fail;                                                                    // 0.0
/*304 */     for (i = 0; i < s->q_ceil; i++) {                                                       // 0.0
/*306 */         uint8_t  *len_lut = &s->coef_lut_len[i*COEF_LUT_TAB];                               // 0.0
/*308 */         uint32_t *val_lut = &s->coef_lut_val[i*COEF_LUT_TAB];                               // 0.0
/*310 */         for (j = 0; j < COEF_LUT_TAB; j++) {                                                // 0.0
/*312 */             get_vc2_ue_uint(QUANT(j, ff_dirac_qscale_tab[i]),                               // 0.0
/*314 */                             &len_lut[j], &val_lut[j]);                                      // 0.0
/*316 */             if (len_lut[j] != 1) {                                                          // 0.0
/*318 */                 len_lut[j] += 1;                                                            // 0.0
/*320 */                 val_lut[j] <<= 1;                                                           // 0.0
/*322 */             } else {                                                                        // 0.0
/*324 */                 val_lut[j] = 1;                                                             // 0.0
/*326 */             }                                                                               // 0.0
/*328 */         }                                                                                   // 0.0
/*330 */     }                                                                                       // 0.0
/*334 */     return 0;                                                                               // 0.0
/*338 */ alloc_fail:                                                                                 // 0.0
/*340 */     vc2_encode_end(avctx);                                                                  // 0.0
/*342 */     av_log(avctx, AV_LOG_ERROR, "Unable to allocate memory!\n");                            // 0.0
/*344 */     return AVERROR(ENOMEM);                                                                 // 0.0
/*346 */ }                                                                                           // 0.0

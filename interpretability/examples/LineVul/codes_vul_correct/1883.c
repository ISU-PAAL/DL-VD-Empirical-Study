// commit message FFmpeg@1577526b47 (target=1, prob=0.99903595, correct=True): libopenjpegenc: add NULL check for img before accessing it
/*0  */ static opj_image_t *mj2_create_image(AVCodecContext *avctx, opj_cparameters_t *parameters)  // (0) 0.07113
/*1  */ {                                                                                           // (27) 0.001955
/*2  */     const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(avctx->pix_fmt);                   // (1) 0.07027
/*3  */     opj_image_cmptparm_t cmptparm[4] = {{0}};                                               // (4) 0.05081
/*4  */     opj_image_t *img;                                                                       // (21) 0.02359
/*5  */     int i;                                                                                  // (26) 0.0117
/*6  */     int sub_dx[4];                                                                          // (22) 0.0195
/*7  */     int sub_dy[4];                                                                          // (23) 0.0195
/*8  */     int numcomps;                                                                           // (25) 0.0156
/*9  */     OPJ_COLOR_SPACE color_space = CLRSPC_UNKNOWN;                                           // (5) 0.04097
/*10 */     sub_dx[0] = sub_dx[3] = 1;                                                              // (7) 0.03705
/*11 */     sub_dy[0] = sub_dy[3] = 1;                                                              // (6) 0.03705
/*12 */     sub_dx[1] = sub_dx[2] = 1 << desc->log2_chroma_w;                                       // (2) 0.05657
/*13 */     sub_dy[1] = sub_dy[2] = 1 << desc->log2_chroma_h;                                       // (3) 0.05656
/*14 */     numcomps = desc->nb_components;                                                         // (20) 0.02731
/*15 */     switch (avctx->pix_fmt) {                                                               // (16) 0.02926
/*16 */     case AV_PIX_FMT_GRAY8:                                                                  // (11) 0.03122
/*17 */     case AV_PIX_FMT_YA8:                                                                    // (18) 0.02925
/*18 */     case AV_PIX_FMT_GRAY16:                                                                 // (13) 0.0312
/*19 */     case AV_PIX_FMT_YA16:                                                                   // (19) 0.02925
/*20 */         color_space = CLRSPC_GRAY;                                                          // (8) 0.03511
/*21 */         break;                                                                              // (24) 0.01755
/*22 */     case AV_PIX_FMT_RGB24:                                                                  // (15) 0.02926
/*23 */     case AV_PIX_FMT_RGBA:                                                                   // (17) 0.02926
/*24 */     case AV_PIX_FMT_RGB48:                                                                  // (14) 0.02926
/*25 */     case AV_PIX_FMT_RGBA64:                                                                 // (12) 0.03121
/*26 */     case AV_PIX_FMT_GBR24P:                                                                 // (9) 0.03317
/*27 */     case AV_PIX_FMT_GBRP9:                                                                  // (10) 0.03125
/*28 */     case AV_PIX_FMT_GBRP10:                                                                 // 0.0
/*29 */     case AV_PIX_FMT_GBRP12:                                                                 // 0.0
/*30 */     case AV_PIX_FMT_GBRP14:                                                                 // 0.0
/*31 */     case AV_PIX_FMT_GBRP16:                                                                 // 0.0
/*32 */     case AV_PIX_FMT_XYZ12:                                                                  // 0.0
/*33 */         color_space = CLRSPC_SRGB;                                                          // 0.0
/*34 */         break;                                                                              // 0.0
/*35 */     case AV_PIX_FMT_YUV410P:                                                                // 0.0
/*36 */     case AV_PIX_FMT_YUV411P:                                                                // 0.0
/*37 */     case AV_PIX_FMT_YUV420P:                                                                // 0.0
/*38 */     case AV_PIX_FMT_YUV422P:                                                                // 0.0
/*39 */     case AV_PIX_FMT_YUV440P:                                                                // 0.0
/*40 */     case AV_PIX_FMT_YUV444P:                                                                // 0.0
/*41 */     case AV_PIX_FMT_YUVA420P:                                                               // 0.0
/*42 */     case AV_PIX_FMT_YUVA422P:                                                               // 0.0
/*43 */     case AV_PIX_FMT_YUVA444P:                                                               // 0.0
/*44 */     case AV_PIX_FMT_YUV420P9:                                                               // 0.0
/*45 */     case AV_PIX_FMT_YUV422P9:                                                               // 0.0
/*46 */     case AV_PIX_FMT_YUV444P9:                                                               // 0.0
/*47 */     case AV_PIX_FMT_YUVA420P9:                                                              // 0.0
/*48 */     case AV_PIX_FMT_YUVA422P9:                                                              // 0.0
/*49 */     case AV_PIX_FMT_YUVA444P9:                                                              // 0.0
/*50 */     case AV_PIX_FMT_YUV420P10:                                                              // 0.0
/*51 */     case AV_PIX_FMT_YUV422P10:                                                              // 0.0
/*52 */     case AV_PIX_FMT_YUV444P10:                                                              // 0.0
/*53 */     case AV_PIX_FMT_YUVA420P10:                                                             // 0.0
/*54 */     case AV_PIX_FMT_YUVA422P10:                                                             // 0.0
/*55 */     case AV_PIX_FMT_YUVA444P10:                                                             // 0.0
/*56 */     case AV_PIX_FMT_YUV420P12:                                                              // 0.0
/*57 */     case AV_PIX_FMT_YUV422P12:                                                              // 0.0
/*58 */     case AV_PIX_FMT_YUV444P12:                                                              // 0.0
/*59 */     case AV_PIX_FMT_YUV420P14:                                                              // 0.0
/*60 */     case AV_PIX_FMT_YUV422P14:                                                              // 0.0
/*61 */     case AV_PIX_FMT_YUV444P14:                                                              // 0.0
/*62 */     case AV_PIX_FMT_YUV420P16:                                                              // 0.0
/*63 */     case AV_PIX_FMT_YUV422P16:                                                              // 0.0
/*64 */     case AV_PIX_FMT_YUV444P16:                                                              // 0.0
/*65 */     case AV_PIX_FMT_YUVA420P16:                                                             // 0.0
/*66 */     case AV_PIX_FMT_YUVA422P16:                                                             // 0.0
/*67 */     case AV_PIX_FMT_YUVA444P16:                                                             // 0.0
/*68 */         color_space = CLRSPC_SYCC;                                                          // 0.0
/*69 */         break;                                                                              // 0.0
/*70 */     default:                                                                                // 0.0
/*71 */         av_log(avctx, AV_LOG_ERROR,                                                         // 0.0
/*72 */                "The requested pixel format '%s' is not supported\n",                        // 0.0
/*73 */                av_get_pix_fmt_name(avctx->pix_fmt));                                        // 0.0
/*74 */     }                                                                                       // 0.0
/*75 */     for (i = 0; i < numcomps; i++) {                                                        // 0.0
/*76 */         cmptparm[i].prec = desc->comp[i].depth_minus1 + 1;                                  // 0.0
/*77 */         cmptparm[i].bpp  = desc->comp[i].depth_minus1 + 1;                                  // 0.0
/*78 */         cmptparm[i].sgnd = 0;                                                               // 0.0
/*79 */         cmptparm[i].dx = sub_dx[i];                                                         // 0.0
/*80 */         cmptparm[i].dy = sub_dy[i];                                                         // 0.0
/*81 */         cmptparm[i].w = (avctx->width + sub_dx[i] - 1) / sub_dx[i];                         // 0.0
/*82 */         cmptparm[i].h = (avctx->height + sub_dy[i] - 1) / sub_dy[i];                        // 0.0
/*83 */     }                                                                                       // 0.0
/*84 */     img = opj_image_create(numcomps, cmptparm, color_space);                                // 0.0
/*85 */     // x0, y0 is the top left corner of the image                                           // 0.0
/*86 */     // x1, y1 is the width, height of the reference grid                                    // 0.0
/*87 */     img->x0 = 0;                                                                            // 0.0
/*88 */     img->y0 = 0;                                                                            // 0.0
/*89 */     img->x1 = (avctx->width  - 1) * parameters->subsampling_dx + 1;                         // 0.0
/*90 */     img->y1 = (avctx->height - 1) * parameters->subsampling_dy + 1;                         // 0.0
/*91 */     return img;                                                                             // 0.0
/*92 */ }                                                                                           // 0.0

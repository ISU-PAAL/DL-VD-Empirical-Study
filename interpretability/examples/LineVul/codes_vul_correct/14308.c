// commit message FFmpeg@a824685140 (target=1, prob=0.7446109, correct=True): avcodec/ivi: Use av_image_check_size2()
/*0   */ av_cold int ff_ivi_init_planes(IVIPlaneDesc *planes, const IVIPicConfig *cfg,          // (5) 0.05664
/*2   */                                int is_indeo4)                                          // (0) 0.07422
/*4   */ {                                                                                      // (21) 0.001953
/*6   */     int p, b;                                                                          // (20) 0.01563
/*8   */     uint32_t b_width, b_height, align_fac, width_aligned,                              // (8) 0.04492
/*10  */              height_aligned, buf_size;                                                 // (9) 0.03906
/*12  */     IVIBandDesc *band;                                                                 // (19) 0.01953
/*16  */     ivi_free_buffers(planes);                                                          // (18) 0.02539
/*20  */     if (av_image_check_size(cfg->pic_width, cfg->pic_height, 0, NULL) < 0 ||           // (3) 0.06445
/*22  */         cfg->luma_bands < 1 || cfg->chroma_bands < 1)                                  // (6) 0.05273
/*24  */         return AVERROR_INVALIDDATA;                                                    // (13) 0.0332
/*28  */     /* fill in the descriptor of the luminance plane */                                // (17) 0.02734
/*30  */     planes[0].width     = cfg->pic_width;                                              // (10) 0.03906
/*32  */     planes[0].height    = cfg->pic_height;                                             // (11) 0.03711
/*34  */     planes[0].num_bands = cfg->luma_bands;                                             // (12) 0.03711
/*38  */     /* fill in the descriptors of the chrominance planes */                            // (15) 0.0293
/*40  */     planes[1].width     = planes[2].width     = (cfg->pic_width  + 3) >> 2;            // (2) 0.07031
/*42  */     planes[1].height    = planes[2].height    = (cfg->pic_height + 3) >> 2;            // (4) 0.06445
/*44  */     planes[1].num_bands = planes[2].num_bands = cfg->chroma_bands;                     // (7) 0.05273
/*48  */     for (p = 0; p < 3; p++) {                                                          // (14) 0.03125
/*50  */         planes[p].bands = av_mallocz_array(planes[p].num_bands, sizeof(IVIBandDesc));  // (1) 0.07031
/*52  */         if (!planes[p].bands)                                                          // (16) 0.0293
/*54  */             return AVERROR(ENOMEM);                                                    // 0.0
/*58  */         /* select band dimensions: if there is only one band then it                   // 0.0
/*60  */          *  has the full size, if there are several bands each of them                 // 0.0
/*62  */          *  has only half size */                                                      // 0.0
/*64  */         b_width  = planes[p].num_bands == 1 ? planes[p].width                          // 0.0
/*66  */                                             : (planes[p].width  + 1) >> 1;             // 0.0
/*68  */         b_height = planes[p].num_bands == 1 ? planes[p].height                         // 0.0
/*70  */                                             : (planes[p].height + 1) >> 1;             // 0.0
/*74  */         /* luma   band buffers will be aligned on 16x16 (max macroblock size) */       // 0.0
/*76  */         /* chroma band buffers will be aligned on   8x8 (max macroblock size) */       // 0.0
/*78  */         align_fac       = p ? 8 : 16;                                                  // 0.0
/*80  */         width_aligned   = FFALIGN(b_width , align_fac);                                // 0.0
/*82  */         height_aligned  = FFALIGN(b_height, align_fac);                                // 0.0
/*84  */         buf_size        = width_aligned * height_aligned * sizeof(int16_t);            // 0.0
/*88  */         for (b = 0; b < planes[p].num_bands; b++) {                                    // 0.0
/*90  */             band = &planes[p].bands[b]; /* select appropriate plane/band */            // 0.0
/*92  */             band->plane    = p;                                                        // 0.0
/*94  */             band->band_num = b;                                                        // 0.0
/*96  */             band->width    = b_width;                                                  // 0.0
/*98  */             band->height   = b_height;                                                 // 0.0
/*100 */             band->pitch    = width_aligned;                                            // 0.0
/*102 */             band->aheight  = height_aligned;                                           // 0.0
/*104 */             band->bufs[0]  = av_mallocz(buf_size);                                     // 0.0
/*106 */             band->bufs[1]  = av_mallocz(buf_size);                                     // 0.0
/*108 */             band->bufsize  = buf_size/2;                                               // 0.0
/*110 */             if (!band->bufs[0] || !band->bufs[1])                                      // 0.0
/*112 */                 return AVERROR(ENOMEM);                                                // 0.0
/*116 */             /* allocate the 3rd band buffer for scalability mode */                    // 0.0
/*118 */             if (cfg->luma_bands > 1) {                                                 // 0.0
/*120 */                 band->bufs[2] = av_mallocz(buf_size);                                  // 0.0
/*122 */                 if (!band->bufs[2])                                                    // 0.0
/*124 */                     return AVERROR(ENOMEM);                                            // 0.0
/*126 */             }                                                                          // 0.0
/*128 */             if (is_indeo4) {                                                           // 0.0
/*130 */                 band->bufs[3]  = av_mallocz(buf_size);                                 // 0.0
/*132 */                 if (!band->bufs[3])                                                    // 0.0
/*134 */                     return AVERROR(ENOMEM);                                            // 0.0
/*136 */             }                                                                          // 0.0
/*138 */             /* reset custom vlc */                                                     // 0.0
/*140 */             planes[p].bands[0].blk_vlc.cust_desc.num_rows = 0;                         // 0.0
/*142 */         }                                                                              // 0.0
/*144 */     }                                                                                  // 0.0
/*148 */     return 0;                                                                          // 0.0
/*150 */ }                                                                                      // 0.0

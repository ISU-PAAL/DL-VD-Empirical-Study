// commit message FFmpeg@607ad990d3 (target=0, prob=0.6820432, correct=False): dvbsubdec: check memory allocations and propagate errors
/*0   */ static int dvbsub_display_end_segment(AVCodecContext *avctx, const uint8_t *buf,          // (2) 0.05859
/*2   */                                         int buf_size, AVSubtitle *sub)                    // (0) 0.09766
/*4   */ {                                                                                         // (28) 0.001953
/*6   */     DVBSubContext *ctx = avctx->priv_data;                                                // (8) 0.0332
/*8   */     DVBSubDisplayDefinition *display_def = ctx->display_definition;                       // (5) 0.03906
/*12  */     DVBSubRegion *region;                                                                 // (19) 0.01953
/*14  */     DVBSubRegionDisplay *display;                                                         // (18) 0.02148
/*16  */     AVSubtitleRect *rect;                                                                 // (21) 0.01953
/*18  */     DVBSubCLUT *clut;                                                                     // (17) 0.02344
/*20  */     uint32_t *clut_table;                                                                 // (16) 0.02539
/*22  */     int i;                                                                                // (26) 0.01172
/*24  */     int offset_x=0, offset_y=0;                                                           // (13) 0.03125
/*28  */     sub->rects = NULL;                                                                    // (22) 0.01953
/*30  */     sub->start_display_time = 0;                                                          // (15) 0.02539
/*32  */     sub->end_display_time = ctx->time_out * 1000;                                         // (6) 0.03906
/*34  */     sub->format = 0;                                                                      // (24) 0.01758
/*38  */     if (display_def) {                                                                    // (20) 0.01953
/*40  */         offset_x = display_def->x;                                                        // (10) 0.0332
/*42  */         offset_y = display_def->y;                                                        // (11) 0.0332
/*44  */     }                                                                                     // (27) 0.007812
/*48  */     sub->num_rects = ctx->display_list_size;                                              // (7) 0.03711
/*50  */     if (sub->num_rects <= 0)                                                              // (14) 0.02734
/*52  */         return AVERROR_INVALIDDATA;                                                       // (9) 0.0332
/*56  */     sub->rects = av_mallocz_array(sub->num_rects * sub->num_rects,                        // (3) 0.05859
/*58  */                                   sizeof(*sub->rects));                                   // (1) 0.07812
/*60  */     if (!sub->rects)                                                                      // (23) 0.01953
/*62  */         return AVERROR(ENOMEM);                                                           // (12) 0.03125
/*66  */     i = 0;                                                                                // (25) 0.01367
/*70  */     for (display = ctx->display_list; display; display = display->next) {                 // (4) 0.04492
/*72  */         region = get_region(ctx, display->region_id);                                     // 0.0
/*74  */         rect = sub->rects[i];                                                             // 0.0
/*78  */         if (!region)                                                                      // 0.0
/*80  */             continue;                                                                     // 0.0
/*84  */         rect->x = display->x_pos + offset_x;                                              // 0.0
/*86  */         rect->y = display->y_pos + offset_y;                                              // 0.0
/*88  */         rect->w = region->width;                                                          // 0.0
/*90  */         rect->h = region->height;                                                         // 0.0
/*92  */         rect->nb_colors = 16;                                                             // 0.0
/*94  */         rect->type      = SUBTITLE_BITMAP;                                                // 0.0
/*96  */         rect->pict.linesize[0] = region->width;                                           // 0.0
/*100 */         clut = get_clut(ctx, region->clut);                                               // 0.0
/*104 */         if (!clut)                                                                        // 0.0
/*106 */             clut = &default_clut;                                                         // 0.0
/*110 */         switch (region->depth) {                                                          // 0.0
/*112 */         case 2:                                                                           // 0.0
/*114 */             clut_table = clut->clut4;                                                     // 0.0
/*116 */             break;                                                                        // 0.0
/*118 */         case 8:                                                                           // 0.0
/*120 */             clut_table = clut->clut256;                                                   // 0.0
/*122 */             break;                                                                        // 0.0
/*124 */         case 4:                                                                           // 0.0
/*126 */         default:                                                                          // 0.0
/*128 */             clut_table = clut->clut16;                                                    // 0.0
/*130 */             break;                                                                        // 0.0
/*132 */         }                                                                                 // 0.0
/*136 */         rect->pict.data[1] = av_mallocz(AVPALETTE_SIZE);                                  // 0.0
/*138 */         if (!rect->pict.data[1]) {                                                        // 0.0
/*140 */             av_free(sub->rects);                                                          // 0.0
/*142 */             return AVERROR(ENOMEM);                                                       // 0.0
/*144 */         }                                                                                 // 0.0
/*146 */         memcpy(rect->pict.data[1], clut_table, (1 << region->depth) * sizeof(uint32_t));  // 0.0
/*150 */         rect->pict.data[0] = av_malloc(region->buf_size);                                 // 0.0
/*152 */         if (!rect->pict.data[0]) {                                                        // 0.0
/*154 */             av_free(rect->pict.data[1]);                                                  // 0.0
/*156 */             av_free(sub->rects);                                                          // 0.0
/*158 */             return AVERROR(ENOMEM);                                                       // 0.0
/*160 */         }                                                                                 // 0.0
/*162 */         memcpy(rect->pict.data[0], region->pbuf, region->buf_size);                       // 0.0
/*166 */         i++;                                                                              // 0.0
/*168 */     }                                                                                     // 0.0
/*172 */     sub->num_rects = i;                                                                   // 0.0
/*176 */ #ifdef DEBUG                                                                              // 0.0
/*178 */     save_display_set(ctx);                                                                // 0.0
/*180 */ #endif                                                                                    // 0.0
/*184 */     return 1;                                                                             // 0.0
/*186 */ }                                                                                         // 0.0

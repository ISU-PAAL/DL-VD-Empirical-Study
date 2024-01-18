// commit message FFmpeg@229843aa35 (target=0, prob=0.9390448, correct=False): Replace av_dlog with ff_dlog.
/*0   */ static int gen_sub_bitmap(TeletextContext *ctx, AVSubtitleRect *sub_rect, vbi_page *page, int chop_top)  // (1) 0.07031
/*2   */ {                                                                                                        // (23) 0.001953
/*4   */     int resx = page->columns * BITMAP_CHAR_WIDTH;                                                        // (10) 0.04102
/*6   */     int resy = (page->rows - chop_top) * BITMAP_CHAR_HEIGHT;                                             // (6) 0.04883
/*8   */     uint8_t ci, cmax = 0;                                                                                // (14) 0.0293
/*10  */     int ret;                                                                                             // (20) 0.01172
/*12  */     vbi_char *vc = page->text + (chop_top * page->columns);                                              // (7) 0.04883
/*14  */     vbi_char *vcend = page->text + (page->rows * page->columns);                                         // (5) 0.04883
/*18  */     for (; vc < vcend; vc++) {                                                                           // (13) 0.03125
/*20  */         if (vc->opacity != VBI_TRANSPARENT_SPACE) {                                                      // (4) 0.05273
/*22  */             cmax = VBI_NB_COLORS;                                                                        // (9) 0.04297
/*24  */             break;                                                                                       // (15) 0.02539
/*26  */         }                                                                                                // (19) 0.01562
/*28  */     }                                                                                                    // (22) 0.007812
/*32  */     if (cmax == 0) {                                                                                     // (16) 0.02148
/*34  */         av_log(ctx, AV_LOG_DEBUG, "dropping empty page %3x\n", page->pgno);                              // (2) 0.06641
/*36  */         sub_rect->type = SUBTITLE_NONE;                                                                  // (11) 0.03906
/*38  */         return 0;                                                                                        // (18) 0.01953
/*40  */     }                                                                                                    // (21) 0.007812
/*44  */     if ((ret = avpicture_alloc(&sub_rect->pict, AV_PIX_FMT_PAL8, resx, resy)) < 0)                       // (0) 0.07617
/*46  */         return ret;                                                                                      // (17) 0.01953
/*48  */     // Yes, we want to allocate the palette on our own because AVSubtitle works this way                 // (8) 0.04297
/*50  */     sub_rect->pict.data[1] = NULL;                                                                       // (12) 0.03125
/*54  */     vbi_draw_vt_page_region(page, VBI_PIXFMT_PAL8,                                                       // (3) 0.05469
/*56  */                             sub_rect->pict.data[0], sub_rect->pict.linesize[0],                          // 0.0
/*58  */                             0, chop_top, page->columns, page->rows - chop_top,                           // 0.0
/*60  */                             /*reveal*/ 1, /*flash*/ 1);                                                  // 0.0
/*64  */     fix_transparency(ctx, sub_rect, page, chop_top, cmax, resx, resy);                                   // 0.0
/*66  */     sub_rect->x = ctx->x_offset;                                                                         // 0.0
/*68  */     sub_rect->y = ctx->y_offset + chop_top * BITMAP_CHAR_HEIGHT;                                         // 0.0
/*70  */     sub_rect->w = resx;                                                                                  // 0.0
/*72  */     sub_rect->h = resy;                                                                                  // 0.0
/*74  */     sub_rect->nb_colors = (int)cmax + 1;                                                                 // 0.0
/*76  */     sub_rect->pict.data[1] = av_mallocz(AVPALETTE_SIZE);                                                 // 0.0
/*78  */     if (!sub_rect->pict.data[1]) {                                                                       // 0.0
/*80  */         av_freep(&sub_rect->pict.data[0]);                                                               // 0.0
/*82  */         return AVERROR(ENOMEM);                                                                          // 0.0
/*84  */     }                                                                                                    // 0.0
/*86  */     for (ci = 0; ci < cmax; ci++) {                                                                      // 0.0
/*88  */         int r, g, b, a;                                                                                  // 0.0
/*92  */         r = VBI_R(page->color_map[ci]);                                                                  // 0.0
/*94  */         g = VBI_G(page->color_map[ci]);                                                                  // 0.0
/*96  */         b = VBI_B(page->color_map[ci]);                                                                  // 0.0
/*98  */         a = VBI_A(page->color_map[ci]);                                                                  // 0.0
/*100 */         ((uint32_t *)sub_rect->pict.data[1])[ci] = RGBA(r, g, b, a);                                     // 0.0
/*102 */         av_dlog(ctx, "palette %0x\n", ((uint32_t *)sub_rect->pict.data[1])[ci]);                         // 0.0
/*104 */     }                                                                                                    // 0.0
/*106 */     ((uint32_t *)sub_rect->pict.data[1])[cmax] = RGBA(0, 0, 0, 0);                                       // 0.0
/*108 */     sub_rect->type = SUBTITLE_BITMAP;                                                                    // 0.0
/*110 */     return 0;                                                                                            // 0.0
/*112 */ }                                                                                                        // 0.0

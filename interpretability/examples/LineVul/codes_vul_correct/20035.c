// commit message FFmpeg@55d7371fe0 (target=1, prob=0.52710587, correct=True): avcodec/vp568: Check that there is enough data for ff_vp56_init_range_decoder()
/*0   */ static int vp9_decode_frame(AVCodecContext *ctx, void *frame,                                                    // (9) 0.04297
/*2   */                             int *got_frame, AVPacket *pkt)                                                       // (1) 0.07812
/*4   */ {                                                                                                                // (22) 0.001953
/*6   */     const uint8_t *data = pkt->data;                                                                             // (13) 0.03125
/*8   */     int size = pkt->size;                                                                                        // (17) 0.02148
/*10  */     VP9Context *s = ctx->priv_data;                                                                              // (12) 0.03125
/*12  */     int res, tile_row, tile_col, i, ref, row, col;                                                               // (8) 0.04297
/*14  */     int retain_segmap_ref = s->s.frames[REF_FRAME_SEGMAP].segmentation_map &&                                    // (3) 0.06445
/*16  */                             (!s->s.h.segmentation.enabled || !s->s.h.segmentation.update_map);                   // (0) 0.1074
/*18  */     ptrdiff_t yoff, uvoff, ls_y, ls_uv;                                                                          // (10) 0.04297
/*20  */     AVFrame *f;                                                                                                  // (19) 0.01562
/*22  */     int bytesperpixel;                                                                                           // (20) 0.01562
/*26  */     if ((res = decode_frame_header(ctx, data, size, &ref)) < 0) {                                                // (5) 0.05078
/*28  */         return res;                                                                                              // (18) 0.01953
/*30  */     } else if (res == 0) {                                                                                       // (15) 0.02344
/*32  */         if (!s->s.refs[ref].f->buf[0]) {                                                                         // (6) 0.04883
/*34  */             av_log(ctx, AV_LOG_ERROR, "Requested reference %d not available\n", ref);                            // (2) 0.07031
/*36  */             return AVERROR_INVALIDDATA;                                                                          // (11) 0.04102
/*38  */         }                                                                                                        // (21) 0.01562
/*40  */         if ((res = av_frame_ref(frame, s->s.refs[ref].f)) < 0)                                                   // (4) 0.06445
/*42  */             return res;                                                                                          // (14) 0.02734
/*44  */         ((AVFrame *)frame)->pts = pkt->pts;                                                                      // (7) 0.04492
/*46  */ #if FF_API_PKT_PTS                                                                                               // (16) 0.02148
/*48  */ FF_DISABLE_DEPRECATION_WARNINGS                                                                                  // 0.0
/*50  */         ((AVFrame *)frame)->pkt_pts = pkt->pts;                                                                  // 0.0
/*52  */ FF_ENABLE_DEPRECATION_WARNINGS                                                                                   // 0.0
/*54  */ #endif                                                                                                           // 0.0
/*56  */         ((AVFrame *)frame)->pkt_dts = pkt->dts;                                                                  // 0.0
/*58  */         for (i = 0; i < 8; i++) {                                                                                // 0.0
/*60  */             if (s->next_refs[i].f->buf[0])                                                                       // 0.0
/*62  */                 ff_thread_release_buffer(ctx, &s->next_refs[i]);                                                 // 0.0
/*64  */             if (s->s.refs[i].f->buf[0] &&                                                                        // 0.0
/*66  */                 (res = ff_thread_ref_frame(&s->next_refs[i], &s->s.refs[i])) < 0)                                // 0.0
/*68  */                 return res;                                                                                      // 0.0
/*70  */         }                                                                                                        // 0.0
/*72  */         *got_frame = 1;                                                                                          // 0.0
/*74  */         return pkt->size;                                                                                        // 0.0
/*76  */     }                                                                                                            // 0.0
/*78  */     data += res;                                                                                                 // 0.0
/*80  */     size -= res;                                                                                                 // 0.0
/*84  */     if (!retain_segmap_ref || s->s.h.keyframe || s->s.h.intraonly) {                                             // 0.0
/*86  */         if (s->s.frames[REF_FRAME_SEGMAP].tf.f->buf[0])                                                          // 0.0
/*88  */             vp9_unref_frame(ctx, &s->s.frames[REF_FRAME_SEGMAP]);                                                // 0.0
/*90  */         if (!s->s.h.keyframe && !s->s.h.intraonly && !s->s.h.errorres && s->s.frames[CUR_FRAME].tf.f->buf[0] &&  // 0.0
/*92  */             (res = vp9_ref_frame(ctx, &s->s.frames[REF_FRAME_SEGMAP], &s->s.frames[CUR_FRAME])) < 0)             // 0.0
/*94  */             return res;                                                                                          // 0.0
/*96  */     }                                                                                                            // 0.0
/*98  */     if (s->s.frames[REF_FRAME_MVPAIR].tf.f->buf[0])                                                              // 0.0
/*100 */         vp9_unref_frame(ctx, &s->s.frames[REF_FRAME_MVPAIR]);                                                    // 0.0
/*102 */     if (!s->s.h.intraonly && !s->s.h.keyframe && !s->s.h.errorres && s->s.frames[CUR_FRAME].tf.f->buf[0] &&      // 0.0
/*104 */         (res = vp9_ref_frame(ctx, &s->s.frames[REF_FRAME_MVPAIR], &s->s.frames[CUR_FRAME])) < 0)                 // 0.0
/*106 */         return res;                                                                                              // 0.0
/*108 */     if (s->s.frames[CUR_FRAME].tf.f->buf[0])                                                                     // 0.0
/*110 */         vp9_unref_frame(ctx, &s->s.frames[CUR_FRAME]);                                                           // 0.0
/*112 */     if ((res = vp9_alloc_frame(ctx, &s->s.frames[CUR_FRAME])) < 0)                                               // 0.0
/*114 */         return res;                                                                                              // 0.0
/*116 */     f = s->s.frames[CUR_FRAME].tf.f;                                                                             // 0.0
/*118 */     f->key_frame = s->s.h.keyframe;                                                                              // 0.0
/*120 */     f->pict_type = (s->s.h.keyframe || s->s.h.intraonly) ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;                // 0.0
/*122 */     ls_y = f->linesize[0];                                                                                       // 0.0
/*124 */     ls_uv =f->linesize[1];                                                                                       // 0.0
/*128 */     if (s->s.frames[REF_FRAME_SEGMAP].tf.f->buf[0] &&                                                            // 0.0
/*130 */         (s->s.frames[REF_FRAME_MVPAIR].tf.f->width  != s->s.frames[CUR_FRAME].tf.f->width ||                     // 0.0
/*132 */          s->s.frames[REF_FRAME_MVPAIR].tf.f->height != s->s.frames[CUR_FRAME].tf.f->height)) {                   // 0.0
/*134 */         vp9_unref_frame(ctx, &s->s.frames[REF_FRAME_SEGMAP]);                                                    // 0.0
/*136 */     }                                                                                                            // 0.0
/*140 */     // ref frame setup                                                                                           // 0.0
/*142 */     for (i = 0; i < 8; i++) {                                                                                    // 0.0
/*144 */         if (s->next_refs[i].f->buf[0])                                                                           // 0.0
/*146 */             ff_thread_release_buffer(ctx, &s->next_refs[i]);                                                     // 0.0
/*148 */         if (s->s.h.refreshrefmask & (1 << i)) {                                                                  // 0.0
/*150 */             res = ff_thread_ref_frame(&s->next_refs[i], &s->s.frames[CUR_FRAME].tf);                             // 0.0
/*152 */         } else if (s->s.refs[i].f->buf[0]) {                                                                     // 0.0
/*154 */             res = ff_thread_ref_frame(&s->next_refs[i], &s->s.refs[i]);                                          // 0.0
/*156 */         }                                                                                                        // 0.0
/*158 */         if (res < 0)                                                                                             // 0.0
/*160 */             return res;                                                                                          // 0.0
/*162 */     }                                                                                                            // 0.0
/*166 */     if (ctx->hwaccel) {                                                                                          // 0.0
/*168 */         res = ctx->hwaccel->start_frame(ctx, NULL, 0);                                                           // 0.0
/*170 */         if (res < 0)                                                                                             // 0.0
/*172 */             return res;                                                                                          // 0.0
/*174 */         res = ctx->hwaccel->decode_slice(ctx, pkt->data, pkt->size);                                             // 0.0
/*176 */         if (res < 0)                                                                                             // 0.0
/*178 */             return res;                                                                                          // 0.0
/*180 */         res = ctx->hwaccel->end_frame(ctx);                                                                      // 0.0
/*182 */         if (res < 0)                                                                                             // 0.0
/*184 */             return res;                                                                                          // 0.0
/*186 */         goto finish;                                                                                             // 0.0
/*188 */     }                                                                                                            // 0.0
/*192 */     // main tile decode loop                                                                                     // 0.0
/*194 */     bytesperpixel = s->bytesperpixel;                                                                            // 0.0
/*196 */     memset(s->above_partition_ctx, 0, s->cols);                                                                  // 0.0
/*198 */     memset(s->above_skip_ctx, 0, s->cols);                                                                       // 0.0
/*200 */     if (s->s.h.keyframe || s->s.h.intraonly) {                                                                   // 0.0
/*202 */         memset(s->above_mode_ctx, DC_PRED, s->cols * 2);                                                         // 0.0
/*204 */     } else {                                                                                                     // 0.0
/*206 */         memset(s->above_mode_ctx, NEARESTMV, s->cols);                                                           // 0.0
/*208 */     }                                                                                                            // 0.0
/*210 */     memset(s->above_y_nnz_ctx, 0, s->sb_cols * 16);                                                              // 0.0
/*212 */     memset(s->above_uv_nnz_ctx[0], 0, s->sb_cols * 16 >> s->ss_h);                                               // 0.0
/*214 */     memset(s->above_uv_nnz_ctx[1], 0, s->sb_cols * 16 >> s->ss_h);                                               // 0.0
/*216 */     memset(s->above_segpred_ctx, 0, s->cols);                                                                    // 0.0
/*218 */     s->pass = s->s.frames[CUR_FRAME].uses_2pass =                                                                // 0.0
/*220 */         ctx->active_thread_type == FF_THREAD_FRAME && s->s.h.refreshctx && !s->s.h.parallelmode;                 // 0.0
/*222 */     if ((res = update_block_buffers(ctx)) < 0) {                                                                 // 0.0
/*224 */         av_log(ctx, AV_LOG_ERROR,                                                                                // 0.0
/*226 */                "Failed to allocate block buffers\n");                                                            // 0.0
/*228 */         return res;                                                                                              // 0.0
/*230 */     }                                                                                                            // 0.0
/*232 */     if (s->s.h.refreshctx && s->s.h.parallelmode) {                                                              // 0.0
/*234 */         int j, k, l, m;                                                                                          // 0.0
/*238 */         for (i = 0; i < 4; i++) {                                                                                // 0.0
/*240 */             for (j = 0; j < 2; j++)                                                                              // 0.0
/*242 */                 for (k = 0; k < 2; k++)                                                                          // 0.0
/*244 */                     for (l = 0; l < 6; l++)                                                                      // 0.0
/*246 */                         for (m = 0; m < 6; m++)                                                                  // 0.0
/*248 */                             memcpy(s->prob_ctx[s->s.h.framectxid].coef[i][j][k][l][m],                           // 0.0
/*250 */                                    s->prob.coef[i][j][k][l][m], 3);                                              // 0.0
/*252 */             if (s->s.h.txfmmode == i)                                                                            // 0.0
/*254 */                 break;                                                                                           // 0.0
/*256 */         }                                                                                                        // 0.0
/*258 */         s->prob_ctx[s->s.h.framectxid].p = s->prob.p;                                                            // 0.0
/*260 */         ff_thread_finish_setup(ctx);                                                                             // 0.0
/*262 */     } else if (!s->s.h.refreshctx) {                                                                             // 0.0
/*264 */         ff_thread_finish_setup(ctx);                                                                             // 0.0
/*266 */     }                                                                                                            // 0.0
/*270 */     do {                                                                                                         // 0.0
/*272 */         yoff = uvoff = 0;                                                                                        // 0.0
/*274 */         s->b = s->b_base;                                                                                        // 0.0
/*276 */         s->block = s->block_base;                                                                                // 0.0
/*278 */         s->uvblock[0] = s->uvblock_base[0];                                                                      // 0.0
/*280 */         s->uvblock[1] = s->uvblock_base[1];                                                                      // 0.0
/*282 */         s->eob = s->eob_base;                                                                                    // 0.0
/*284 */         s->uveob[0] = s->uveob_base[0];                                                                          // 0.0
/*286 */         s->uveob[1] = s->uveob_base[1];                                                                          // 0.0
/*290 */         for (tile_row = 0; tile_row < s->s.h.tiling.tile_rows; tile_row++) {                                     // 0.0
/*292 */             set_tile_offset(&s->tile_row_start, &s->tile_row_end,                                                // 0.0
/*294 */                             tile_row, s->s.h.tiling.log2_tile_rows, s->sb_rows);                                 // 0.0
/*296 */             if (s->pass != 2) {                                                                                  // 0.0
/*298 */                 for (tile_col = 0; tile_col < s->s.h.tiling.tile_cols; tile_col++) {                             // 0.0
/*300 */                     int64_t tile_size;                                                                           // 0.0
/*304 */                     if (tile_col == s->s.h.tiling.tile_cols - 1 &&                                               // 0.0
/*306 */                         tile_row == s->s.h.tiling.tile_rows - 1) {                                               // 0.0
/*308 */                         tile_size = size;                                                                        // 0.0
/*310 */                     } else {                                                                                     // 0.0
/*312 */                         tile_size = AV_RB32(data);                                                               // 0.0
/*314 */                         data += 4;                                                                               // 0.0
/*316 */                         size -= 4;                                                                               // 0.0
/*318 */                     }                                                                                            // 0.0
/*320 */                     if (tile_size > size) {                                                                      // 0.0
/*322 */                         ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, INT_MAX, 0);                       // 0.0
/*324 */                         return AVERROR_INVALIDDATA;                                                              // 0.0
/*326 */                     }                                                                                            // 0.0
/*328 */                     ff_vp56_init_range_decoder(&s->c_b[tile_col], data, tile_size);                              // 0.0
/*330 */                     if (vp56_rac_get_prob_branchy(&s->c_b[tile_col], 128)) { // marker bit                       // 0.0
/*332 */                         ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, INT_MAX, 0);                       // 0.0
/*334 */                         return AVERROR_INVALIDDATA;                                                              // 0.0
/*336 */                     }                                                                                            // 0.0
/*338 */                     data += tile_size;                                                                           // 0.0
/*340 */                     size -= tile_size;                                                                           // 0.0
/*342 */                 }                                                                                                // 0.0
/*344 */             }                                                                                                    // 0.0
/*348 */             for (row = s->tile_row_start; row < s->tile_row_end;                                                 // 0.0
/*350 */                  row += 8, yoff += ls_y * 64, uvoff += ls_uv * 64 >> s->ss_v) {                                  // 0.0
/*352 */                 struct VP9Filter *lflvl_ptr = s->lflvl;                                                          // 0.0
/*354 */                 ptrdiff_t yoff2 = yoff, uvoff2 = uvoff;                                                          // 0.0
/*358 */                 for (tile_col = 0; tile_col < s->s.h.tiling.tile_cols; tile_col++) {                             // 0.0
/*360 */                     set_tile_offset(&s->tile_col_start, &s->tile_col_end,                                        // 0.0
/*362 */                                     tile_col, s->s.h.tiling.log2_tile_cols, s->sb_cols);                         // 0.0
/*366 */                     if (s->pass != 2) {                                                                          // 0.0
/*368 */                         memset(s->left_partition_ctx, 0, 8);                                                     // 0.0
/*370 */                         memset(s->left_skip_ctx, 0, 8);                                                          // 0.0
/*372 */                         if (s->s.h.keyframe || s->s.h.intraonly) {                                               // 0.0
/*374 */                             memset(s->left_mode_ctx, DC_PRED, 16);                                               // 0.0
/*376 */                         } else {                                                                                 // 0.0
/*378 */                             memset(s->left_mode_ctx, NEARESTMV, 8);                                              // 0.0
/*380 */                         }                                                                                        // 0.0
/*382 */                         memset(s->left_y_nnz_ctx, 0, 16);                                                        // 0.0
/*384 */                         memset(s->left_uv_nnz_ctx, 0, 32);                                                       // 0.0
/*386 */                         memset(s->left_segpred_ctx, 0, 8);                                                       // 0.0
/*390 */                         memcpy(&s->c, &s->c_b[tile_col], sizeof(s->c));                                          // 0.0
/*392 */                     }                                                                                            // 0.0
/*396 */                     for (col = s->tile_col_start;                                                                // 0.0
/*398 */                          col < s->tile_col_end;                                                                  // 0.0
/*400 */                          col += 8, yoff2 += 64 * bytesperpixel,                                                  // 0.0
/*402 */                          uvoff2 += 64 * bytesperpixel >> s->ss_h, lflvl_ptr++) {                                 // 0.0
/*404 */                         // FIXME integrate with lf code (i.e. zero after each                                    // 0.0
/*406 */                         // use, similar to invtxfm coefficients, or similar)                                     // 0.0
/*408 */                         if (s->pass != 1) {                                                                      // 0.0
/*410 */                             memset(lflvl_ptr->mask, 0, sizeof(lflvl_ptr->mask));                                 // 0.0
/*412 */                         }                                                                                        // 0.0
/*416 */                         if (s->pass == 2) {                                                                      // 0.0
/*418 */                             decode_sb_mem(ctx, row, col, lflvl_ptr,                                              // 0.0
/*420 */                                           yoff2, uvoff2, BL_64X64);                                              // 0.0
/*422 */                         } else {                                                                                 // 0.0
/*424 */                             decode_sb(ctx, row, col, lflvl_ptr,                                                  // 0.0
/*426 */                                       yoff2, uvoff2, BL_64X64);                                                  // 0.0
/*428 */                         }                                                                                        // 0.0
/*430 */                     }                                                                                            // 0.0
/*432 */                     if (s->pass != 2) {                                                                          // 0.0
/*434 */                         memcpy(&s->c_b[tile_col], &s->c, sizeof(s->c));                                          // 0.0
/*436 */                     }                                                                                            // 0.0
/*438 */                 }                                                                                                // 0.0
/*442 */                 if (s->pass == 1) {                                                                              // 0.0
/*444 */                     continue;                                                                                    // 0.0
/*446 */                 }                                                                                                // 0.0
/*450 */                 // backup pre-loopfilter reconstruction data for intra                                           // 0.0
/*452 */                 // prediction of next row of sb64s                                                               // 0.0
/*454 */                 if (row + 8 < s->rows) {                                                                         // 0.0
/*456 */                     memcpy(s->intra_pred_data[0],                                                                // 0.0
/*458 */                            f->data[0] + yoff + 63 * ls_y,                                                        // 0.0
/*460 */                            8 * s->cols * bytesperpixel);                                                         // 0.0
/*462 */                     memcpy(s->intra_pred_data[1],                                                                // 0.0
/*464 */                            f->data[1] + uvoff + ((64 >> s->ss_v) - 1) * ls_uv,                                   // 0.0
/*466 */                            8 * s->cols * bytesperpixel >> s->ss_h);                                              // 0.0
/*468 */                     memcpy(s->intra_pred_data[2],                                                                // 0.0
/*470 */                            f->data[2] + uvoff + ((64 >> s->ss_v) - 1) * ls_uv,                                   // 0.0
/*472 */                            8 * s->cols * bytesperpixel >> s->ss_h);                                              // 0.0
/*474 */                 }                                                                                                // 0.0
/*478 */                 // loopfilter one row                                                                            // 0.0
/*480 */                 if (s->s.h.filter.level) {                                                                       // 0.0
/*482 */                     yoff2 = yoff;                                                                                // 0.0
/*484 */                     uvoff2 = uvoff;                                                                              // 0.0
/*486 */                     lflvl_ptr = s->lflvl;                                                                        // 0.0
/*488 */                     for (col = 0; col < s->cols;                                                                 // 0.0
/*490 */                          col += 8, yoff2 += 64 * bytesperpixel,                                                  // 0.0
/*492 */                          uvoff2 += 64 * bytesperpixel >> s->ss_h, lflvl_ptr++) {                                 // 0.0
/*494 */                         loopfilter_sb(ctx, lflvl_ptr, row, col, yoff2, uvoff2);                                  // 0.0
/*496 */                     }                                                                                            // 0.0
/*498 */                 }                                                                                                // 0.0
/*502 */                 // FIXME maybe we can make this more finegrained by running the                                  // 0.0
/*504 */                 // loopfilter per-block instead of after each sbrow                                              // 0.0
/*506 */                 // In fact that would also make intra pred left preparation easier?                              // 0.0
/*508 */                 ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, row >> 3, 0);                              // 0.0
/*510 */             }                                                                                                    // 0.0
/*512 */         }                                                                                                        // 0.0
/*516 */         if (s->pass < 2 && s->s.h.refreshctx && !s->s.h.parallelmode) {                                          // 0.0
/*518 */             adapt_probs(s);                                                                                      // 0.0
/*520 */             ff_thread_finish_setup(ctx);                                                                         // 0.0
/*522 */         }                                                                                                        // 0.0
/*524 */     } while (s->pass++ == 1);                                                                                    // 0.0
/*526 */     ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, INT_MAX, 0);                                           // 0.0
/*530 */ finish:                                                                                                          // 0.0
/*532 */     // ref frame setup                                                                                           // 0.0
/*534 */     for (i = 0; i < 8; i++) {                                                                                    // 0.0
/*536 */         if (s->s.refs[i].f->buf[0])                                                                              // 0.0
/*538 */             ff_thread_release_buffer(ctx, &s->s.refs[i]);                                                        // 0.0
/*540 */         if (s->next_refs[i].f->buf[0] &&                                                                         // 0.0
/*542 */             (res = ff_thread_ref_frame(&s->s.refs[i], &s->next_refs[i])) < 0)                                    // 0.0
/*544 */             return res;                                                                                          // 0.0
/*546 */     }                                                                                                            // 0.0
/*550 */     if (!s->s.h.invisible) {                                                                                     // 0.0
/*552 */         if ((res = av_frame_ref(frame, s->s.frames[CUR_FRAME].tf.f)) < 0)                                        // 0.0
/*554 */             return res;                                                                                          // 0.0
/*556 */         *got_frame = 1;                                                                                          // 0.0
/*558 */     }                                                                                                            // 0.0
/*562 */     return pkt->size;                                                                                            // 0.0
/*564 */ }                                                                                                                // 0.0

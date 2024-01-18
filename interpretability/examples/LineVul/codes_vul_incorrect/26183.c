// commit message FFmpeg@0114c571d4 (target=1, prob=0.407491, correct=False): mpegvideo: dont call draw edges on lowres
/*0   */ void ff_MPV_frame_end(MpegEncContext *s)                                                                       // (13) 0.03321
/*2   */ {                                                                                                              // (17) 0.001953
/*4   */     int i;                                                                                                     // (16) 0.01172
/*6   */     /* redraw edges for the frame if decoding didn't complete */                                               // (14) 0.03125
/*8   */     // just to make sure that all data is rendered.                                                            // (15) 0.02734
/*10  */     if (CONFIG_MPEG_XVMC_DECODER && s->avctx->xvmc_acceleration) {                                             // (6) 0.06445
/*12  */         ff_xvmc_field_end(s);                                                                                  // (12) 0.03711
/*14  */    } else if((s->error_count || s->encoding || !(s->avctx->codec->capabilities&CODEC_CAP_DRAW_HORIZ_BAND)) &&  // (0) 0.0918
/*16  */               !s->avctx->hwaccel &&                                                                            // (9) 0.04492
/*18  */               !(s->avctx->codec->capabilities & CODEC_CAP_HWACCEL_VDPAU) &&                                    // (3) 0.08203
/*20  */               s->unrestricted_mv &&                                                                            // (10) 0.04101
/*22  */               s->current_picture.f.reference &&                                                                // (8) 0.04492
/*24  */               !s->intra_only &&                                                                                // (11) 0.04101
/*26  */               !(s->flags & CODEC_FLAG_EMU_EDGE)) {                                                             // (7) 0.0625
/*28  */         int hshift = av_pix_fmt_descriptors[s->avctx->pix_fmt].log2_chroma_w;                                  // (2) 0.08203
/*30  */         int vshift = av_pix_fmt_descriptors[s->avctx->pix_fmt].log2_chroma_h;                                  // (4) 0.08203
/*32  */         s->dsp.draw_edges(s->current_picture.f.data[0], s->current_picture.f.linesize[0],                      // (1) 0.08203
/*34  */                           s->h_edge_pos, s->v_edge_pos,                                                        // (5) 0.08008
/*36  */                           EDGE_WIDTH, EDGE_WIDTH,                                                              // 0.0
/*38  */                           EDGE_TOP | EDGE_BOTTOM);                                                             // 0.0
/*40  */         s->dsp.draw_edges(s->current_picture.f.data[1], s->current_picture.f.linesize[1],                      // 0.0
/*42  */                           s->h_edge_pos >> hshift, s->v_edge_pos >> vshift,                                    // 0.0
/*44  */                           EDGE_WIDTH >> hshift, EDGE_WIDTH >> vshift,                                          // 0.0
/*46  */                           EDGE_TOP | EDGE_BOTTOM);                                                             // 0.0
/*48  */         s->dsp.draw_edges(s->current_picture.f.data[2], s->current_picture.f.linesize[2],                      // 0.0
/*50  */                           s->h_edge_pos >> hshift, s->v_edge_pos >> vshift,                                    // 0.0
/*52  */                           EDGE_WIDTH >> hshift, EDGE_WIDTH >> vshift,                                          // 0.0
/*54  */                           EDGE_TOP | EDGE_BOTTOM);                                                             // 0.0
/*56  */     }                                                                                                          // 0.0
/*60  */     emms_c();                                                                                                  // 0.0
/*64  */     s->last_pict_type                 = s->pict_type;                                                          // 0.0
/*66  */     s->last_lambda_for [s->pict_type] = s->current_picture_ptr->f.quality;                                     // 0.0
/*68  */     if (s->pict_type!= AV_PICTURE_TYPE_B) {                                                                    // 0.0
/*70  */         s->last_non_b_pict_type = s->pict_type;                                                                // 0.0
/*72  */     }                                                                                                          // 0.0
/*74  */ #if 0                                                                                                          // 0.0
/*76  */     /* copy back current_picture variables */                                                                  // 0.0
/*78  */     for (i = 0; i < MAX_PICTURE_COUNT; i++) {                                                                  // 0.0
/*80  */         if (s->picture[i].f.data[0] == s->current_picture.f.data[0]) {                                         // 0.0
/*82  */             s->picture[i] = s->current_picture;                                                                // 0.0
/*84  */             break;                                                                                             // 0.0
/*86  */         }                                                                                                      // 0.0
/*88  */     }                                                                                                          // 0.0
/*90  */     assert(i < MAX_PICTURE_COUNT);                                                                             // 0.0
/*92  */ #endif                                                                                                         // 0.0
/*96  */     if (s->encoding) {                                                                                         // 0.0
/*98  */         /* release non-reference frames */                                                                     // 0.0
/*100 */         for (i = 0; i < s->picture_count; i++) {                                                               // 0.0
/*102 */             if (s->picture[i].f.data[0] && !s->picture[i].f.reference                                          // 0.0
/*104 */                 /* && s->picture[i].type != FF_BUFFER_TYPE_SHARED */) {                                        // 0.0
/*106 */                 free_frame_buffer(s, &s->picture[i]);                                                          // 0.0
/*108 */             }                                                                                                  // 0.0
/*110 */         }                                                                                                      // 0.0
/*112 */     }                                                                                                          // 0.0
/*114 */     // clear copies, to avoid confusion                                                                        // 0.0
/*116 */ #if 0                                                                                                          // 0.0
/*118 */     memset(&s->last_picture,    0, sizeof(Picture));                                                           // 0.0
/*120 */     memset(&s->next_picture,    0, sizeof(Picture));                                                           // 0.0
/*122 */     memset(&s->current_picture, 0, sizeof(Picture));                                                           // 0.0
/*124 */ #endif                                                                                                         // 0.0
/*126 */     s->avctx->coded_frame = &s->current_picture_ptr->f;                                                        // 0.0
/*130 */     if (s->codec_id != AV_CODEC_ID_H264 && s->current_picture.f.reference) {                                   // 0.0
/*132 */         ff_thread_report_progress(&s->current_picture_ptr->f, INT_MAX, 0);                                     // 0.0
/*134 */     }                                                                                                          // 0.0
/*136 */ }                                                                                                              // 0.0

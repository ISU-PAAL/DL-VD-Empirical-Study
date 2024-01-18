// commit message FFmpeg@cf1e0786ed (target=0, prob=0.22886708, correct=True): error_resilience: move the MECmpContext initialization into ER code
/*0   */ static int is_intra_more_likely(ERContext *s)                                       // (14) 0.03125
/*2   */ {                                                                                   // (24) 0.001953
/*4   */     int is_intra_likely, i, j, undamaged_count, skip_amount, mb_x, mb_y;            // (0) 0.06836
/*8   */     if (!s->last_pic.f || !s->last_pic.f->data[0])                                  // (4) 0.05078
/*10  */         return 1; // no previous frame available -> use spatial prediction          // (11) 0.03711
/*14  */     undamaged_count = 0;                                                            // (16) 0.02148
/*16  */     for (i = 0; i < s->mb_num; i++) {                                               // (9) 0.03906
/*18  */         const int mb_xy = s->mb_index2xy[i];                                        // (5) 0.04688
/*20  */         const int error = s->error_status_table[mb_xy];                             // (6) 0.04492
/*22  */         if (!((error & ER_DC_ERROR) && (error & ER_MV_ERROR)))                      // (3) 0.05664
/*24  */             undamaged_count++;                                                      // (13) 0.0332
/*26  */     }                                                                               // (23) 0.007812
/*30  */     if (s->avctx->codec_id == AV_CODEC_ID_H264 && s->ref_count <= 0)                // (1) 0.06641
/*32  */         return 1;                                                                   // (20) 0.01953
/*36  */     if (undamaged_count < 5)                                                        // (15) 0.02539
/*38  */         return 0; // almost all MBs damaged -> use temporal prediction              // (8) 0.03906
/*42  */ #if FF_API_XVMC                                                                     // (22) 0.01758
/*44  */ FF_DISABLE_DEPRECATION_WARNINGS                                                     // (17) 0.02148
/*46  */     // prevent dsp.sad() check, that requires access to the image                   // (12) 0.03711
/*48  */     if (CONFIG_MPEG_XVMC_DECODER    &&                                              // (7) 0.04297
/*50  */         s->avctx->xvmc_acceleration &&                                              // (10) 0.03906
/*52  */         s->cur_pic.f->pict_type == AV_PICTURE_TYPE_I)                               // (2) 0.05664
/*54  */         return 1;                                                                   // (21) 0.01953
/*56  */ FF_ENABLE_DEPRECATION_WARNINGS                                                      // (18) 0.02148
/*58  */ #endif /* FF_API_XVMC */                                                            // (19) 0.02148
/*62  */     skip_amount     = FFMAX(undamaged_count / 50, 1); // check only up to 50 MBs    // 0.0
/*64  */     is_intra_likely = 0;                                                            // 0.0
/*68  */     j = 0;                                                                          // 0.0
/*70  */     for (mb_y = 0; mb_y < s->mb_height - 1; mb_y++) {                               // 0.0
/*72  */         for (mb_x = 0; mb_x < s->mb_width; mb_x++) {                                // 0.0
/*74  */             int error;                                                              // 0.0
/*76  */             const int mb_xy = mb_x + mb_y * s->mb_stride;                           // 0.0
/*80  */             error = s->error_status_table[mb_xy];                                   // 0.0
/*82  */             if ((error & ER_DC_ERROR) && (error & ER_MV_ERROR))                     // 0.0
/*84  */                 continue; // skip damaged                                           // 0.0
/*88  */             j++;                                                                    // 0.0
/*90  */             // skip a few to speed things up                                        // 0.0
/*92  */             if ((j % skip_amount) != 0)                                             // 0.0
/*94  */                 continue;                                                           // 0.0
/*98  */             if (s->cur_pic.f->pict_type == AV_PICTURE_TYPE_I) {                     // 0.0
/*100 */                 int *linesize = s->cur_pic.f->linesize;                             // 0.0
/*102 */                 uint8_t *mb_ptr      = s->cur_pic.f->data[0] +                      // 0.0
/*104 */                                        mb_x * 16 + mb_y * 16 * linesize[0];         // 0.0
/*106 */                 uint8_t *last_mb_ptr = s->last_pic.f->data[0] +                     // 0.0
/*108 */                                        mb_x * 16 + mb_y * 16 * linesize[0];         // 0.0
/*112 */                 if (s->avctx->codec_id == AV_CODEC_ID_H264) {                       // 0.0
/*114 */                     // FIXME                                                        // 0.0
/*116 */                 } else {                                                            // 0.0
/*118 */                     ff_thread_await_progress(s->last_pic.tf, mb_y, 0);              // 0.0
/*120 */                 }                                                                   // 0.0
/*122 */                 is_intra_likely += s->mecc->sad[0](NULL, last_mb_ptr, mb_ptr,       // 0.0
/*124 */                                                    linesize[0], 16);                // 0.0
/*126 */                 is_intra_likely -= s->mecc->sad[0](NULL, last_mb_ptr,               // 0.0
/*128 */                                                    last_mb_ptr + linesize[0] * 16,  // 0.0
/*130 */                                                    linesize[0], 16);                // 0.0
/*132 */             } else {                                                                // 0.0
/*134 */                 if (IS_INTRA(s->cur_pic.mb_type[mb_xy]))                            // 0.0
/*136 */                    is_intra_likely++;                                               // 0.0
/*138 */                 else                                                                // 0.0
/*140 */                    is_intra_likely--;                                               // 0.0
/*142 */             }                                                                       // 0.0
/*144 */         }                                                                           // 0.0
/*146 */     }                                                                               // 0.0
/*148 */     return is_intra_likely > 0;                                                     // 0.0
/*150 */ }                                                                                   // 0.0

// commit message FFmpeg@15ea222778 (target=0, prob=0.6819186, correct=False): vf_interlace: merge FIELD_LOWER check
/*0  */ static void copy_picture_field(InterlaceContext *s,                                  // (17) 0.02734
/*2  */                                AVFrame *src_frame, AVFrame *dst_frame,               // (0) 0.08789
/*4  */                                AVFilterLink *inlink, enum FieldType field_type,      // (1) 0.08594
/*6  */                                int lowpass)                                          // (4) 0.06641
/*8  */ {                                                                                    // (19) 0.001953
/*10 */     const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);            // (5) 0.0625
/*12 */     int hsub = desc->log2_chroma_w;                                                  // (15) 0.0332
/*14 */     int vsub = desc->log2_chroma_h;                                                  // (16) 0.0332
/*16 */     int plane, j;                                                                    // (18) 0.01562
/*20 */     for (plane = 0; plane < desc->nb_components; plane++) {                          // (11) 0.04102
/*22 */         int cols  = (plane == 1 || plane == 2) ? -(-inlink->w) >> hsub : inlink->w;  // (2) 0.07422
/*24 */         int lines = (plane == 1 || plane == 2) ? -(-inlink->h) >> vsub : inlink->h;  // (3) 0.07031
/*26 */         uint8_t *dstp = dst_frame->data[plane];                                      // (7) 0.04687
/*28 */         const uint8_t *srcp = src_frame->data[plane];                                // (8) 0.04687
/*32 */         av_assert0(cols >= 0 || lines >= 0);                                         // (12) 0.04102
/*36 */         lines = (lines + (field_type == FIELD_UPPER)) / 2;                           // (6) 0.05078
/*38 */         if (field_type == FIELD_LOWER)                                               // (13) 0.03711
/*40 */             srcp += src_frame->linesize[plane];                                      // (10) 0.04492
/*42 */         if (field_type == FIELD_LOWER)                                               // (14) 0.03711
/*44 */             dstp += dst_frame->linesize[plane];                                      // (9) 0.04492
/*46 */         if (lowpass) {                                                               // 0.0
/*48 */             int srcp_linesize = src_frame->linesize[plane] * 2;                      // 0.0
/*50 */             int dstp_linesize = dst_frame->linesize[plane] * 2;                      // 0.0
/*52 */             for (j = lines; j > 0; j--) {                                            // 0.0
/*54 */                 const uint8_t *srcp_above = srcp - src_frame->linesize[plane];       // 0.0
/*56 */                 const uint8_t *srcp_below = srcp + src_frame->linesize[plane];       // 0.0
/*58 */                 if (j == lines)                                                      // 0.0
/*60 */                     srcp_above = srcp; // there is no line above                     // 0.0
/*62 */                 if (j == 1)                                                          // 0.0
/*64 */                     srcp_below = srcp; // there is no line below                     // 0.0
/*66 */                 s->lowpass_line(dstp, cols, srcp, srcp_above, srcp_below);           // 0.0
/*68 */                 dstp += dstp_linesize;                                               // 0.0
/*70 */                 srcp += srcp_linesize;                                               // 0.0
/*72 */             }                                                                        // 0.0
/*74 */         } else {                                                                     // 0.0
/*76 */             av_image_copy_plane(dstp, dst_frame->linesize[plane] * 2,                // 0.0
/*78 */                                 srcp, src_frame->linesize[plane] * 2,                // 0.0
/*80 */                                 cols, lines);                                        // 0.0
/*82 */         }                                                                            // 0.0
/*84 */     }                                                                                // 0.0
/*86 */ }                                                                                    // 0.0

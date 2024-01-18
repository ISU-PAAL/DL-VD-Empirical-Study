// commit message FFmpeg@ae93965359 (target=1, prob=0.48952988, correct=False): avcodec/hevc_refs: fix potential use of uninitialized min_idx
/*0   */ int ff_hevc_output_frame(HEVCContext *s, AVFrame *out, int flush)                                 // (10) 0.04688
/*2   */ {                                                                                                 // (19) 0.001953
/*4   */     do {                                                                                          // (18) 0.009766
/*6   */         int nb_output = 0;                                                                        // (15) 0.0293
/*8   */         int min_poc   = INT_MAX;                                                                  // (12) 0.03711
/*10  */         int i, min_idx, ret;                                                                      // (13) 0.0332
/*14  */         if (s->sh.no_output_of_prior_pics_flag == 1) {                                            // (5) 0.05859
/*16  */             for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {                                        // (2) 0.07031
/*18  */                 HEVCFrame *frame = &s->DPB[i];                                                    // (7) 0.05664
/*20  */                 if (!(frame->flags & HEVC_FRAME_FLAG_BUMPING) && frame->poc != s->poc &&          // (0) 0.08789
/*22  */                         frame->sequence == s->seq_output) {                                       // (3) 0.06641
/*24  */                     ff_hevc_unref_frame(s, frame, HEVC_FRAME_FLAG_OUTPUT);                        // (1) 0.08789
/*26  */                 }                                                                                 // (14) 0.03125
/*28  */             }                                                                                     // (16) 0.02344
/*30  */         }                                                                                         // (17) 0.01562
/*34  */         for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {                                            // (4) 0.0625
/*36  */             HEVCFrame *frame = &s->DPB[i];                                                        // (9) 0.04883
/*38  */             if ((frame->flags & HEVC_FRAME_FLAG_OUTPUT) &&                                        // (6) 0.05859
/*40  */                 frame->sequence == s->seq_output) {                                               // (8) 0.05078
/*42  */                 nb_output++;                                                                      // (11) 0.03906
/*44  */                 if (frame->poc < min_poc) {                                                       // 0.0
/*46  */                     min_poc = frame->poc;                                                         // 0.0
/*48  */                     min_idx = i;                                                                  // 0.0
/*50  */                 }                                                                                 // 0.0
/*52  */             }                                                                                     // 0.0
/*54  */         }                                                                                         // 0.0
/*58  */         /* wait for more frames before output */                                                  // 0.0
/*60  */         if (!flush && s->seq_output == s->seq_decode && s->sps &&                                 // 0.0
/*62  */             nb_output <= s->sps->temporal_layer[s->sps->max_sub_layers - 1].num_reorder_pics)     // 0.0
/*64  */             return 0;                                                                             // 0.0
/*68  */         if (nb_output) {                                                                          // 0.0
/*70  */             HEVCFrame *frame = &s->DPB[min_idx];                                                  // 0.0
/*72  */             AVFrame *dst = out;                                                                   // 0.0
/*74  */             AVFrame *src = frame->frame;                                                          // 0.0
/*76  */             const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(src->format);                    // 0.0
/*78  */             int pixel_shift = !!(desc->comp[0].depth_minus1 > 7);                                 // 0.0
/*82  */             ret = av_frame_ref(out, src);                                                         // 0.0
/*84  */             if (frame->flags & HEVC_FRAME_FLAG_BUMPING)                                           // 0.0
/*86  */                 ff_hevc_unref_frame(s, frame, HEVC_FRAME_FLAG_OUTPUT | HEVC_FRAME_FLAG_BUMPING);  // 0.0
/*88  */             else                                                                                  // 0.0
/*90  */                 ff_hevc_unref_frame(s, frame, HEVC_FRAME_FLAG_OUTPUT);                            // 0.0
/*92  */             if (ret < 0)                                                                          // 0.0
/*94  */                 return ret;                                                                       // 0.0
/*98  */             for (i = 0; i < 3; i++) {                                                             // 0.0
/*100 */                 int hshift = (i > 0) ? desc->log2_chroma_w : 0;                                   // 0.0
/*102 */                 int vshift = (i > 0) ? desc->log2_chroma_h : 0;                                   // 0.0
/*104 */                 int off = ((frame->window.left_offset >> hshift) << pixel_shift) +                // 0.0
/*106 */                           (frame->window.top_offset   >> vshift) * dst->linesize[i];              // 0.0
/*108 */                 dst->data[i] += off;                                                              // 0.0
/*110 */             }                                                                                     // 0.0
/*112 */             av_log(s->avctx, AV_LOG_DEBUG,                                                        // 0.0
/*114 */                    "Output frame with POC %d.\n", frame->poc);                                    // 0.0
/*116 */             return 1;                                                                             // 0.0
/*118 */         }                                                                                         // 0.0
/*122 */         if (s->seq_output != s->seq_decode)                                                       // 0.0
/*124 */             s->seq_output = (s->seq_output + 1) & 0xff;                                           // 0.0
/*126 */         else                                                                                      // 0.0
/*128 */             break;                                                                                // 0.0
/*130 */     } while (1);                                                                                  // 0.0
/*134 */     return 0;                                                                                     // 0.0
/*136 */ }                                                                                                 // 0.0

// commit message FFmpeg@a52f443714 (target=1, prob=0.85319394, correct=True): avcodec/vc1dec: fix is_intra block vs. mb bug
/*0   */ static av_always_inline void vc1_apply_p_h_loop_filter(VC1Context *v, int block_num)                               // (7) 0.0625
/*2   */ {                                                                                                                  // (17) 0.001953
/*4   */     MpegEncContext *s  = &v->s;                                                                                    // (11) 0.03125
/*6   */     int mb_cbp         = v->cbp[s->mb_x - 1 - s->mb_stride],                                                       // (4) 0.07422
/*8   */         block_cbp      = mb_cbp      >> (block_num * 4), right_cbp,                                                // (2) 0.07812
/*10  */         mb_is_intra    = v->is_intra[s->mb_x - 1 - s->mb_stride],                                                  // (3) 0.07812
/*12  */         block_is_intra = mb_is_intra >> (block_num * 4), right_is_intra;                                           // (5) 0.07031
/*14  */     int idx, linesize  = block_num > 3 ? s->uvlinesize : s->linesize, ttblk;                                       // (6) 0.06445
/*16  */     uint8_t *dst;                                                                                                  // (14) 0.02148
/*20  */     if (block_num > 3) {                                                                                           // (13) 0.02344
/*22  */         dst = s->dest[block_num - 3] - 8 * linesize;                                                               // (9) 0.04883
/*24  */     } else {                                                                                                       // (15) 0.01172
/*26  */         dst = s->dest[0] + (block_num & 1) * 8 + ((block_num & 2) * 4 - 16) * linesize - 8;                        // (1) 0.08594
/*28  */     }                                                                                                              // (16) 0.007813
/*32  */     if (s->mb_x != s->mb_width || !(block_num & 5)) {                                                              // (8) 0.05078
/*34  */         int16_t (*mv)[2];                                                                                          // (10) 0.0332
/*38  */         if (block_num > 3) {                                                                                       // (12) 0.03125
/*40  */             right_cbp      = v->cbp[s->mb_x - s->mb_stride] >> (block_num * 4);                                    // (0) 0.0918
/*42  */             right_is_intra = v->is_intra[s->mb_x - s->mb_stride] >> (block_num * 4);                               // 0.0
/*44  */             mv             = &v->luma_mv[s->mb_x - s->mb_stride - 1];                                              // 0.0
/*46  */         } else {                                                                                                   // 0.0
/*48  */             right_cbp      = (block_num & 1) ? (v->cbp[s->mb_x - s->mb_stride]      >> ((block_num - 1) * 4))      // 0.0
/*50  */                                              : (mb_cbp                              >> ((block_num + 1) * 4));     // 0.0
/*52  */             right_is_intra = (block_num & 1) ? (v->is_intra[s->mb_x - s->mb_stride] >> ((block_num - 1) * 4))      // 0.0
/*54  */                                              : (mb_is_intra                         >> ((block_num + 1) * 4));     // 0.0
/*56  */             mv             = &s->current_picture.motion_val[0][s->block_index[block_num] - s->b8_stride * 2 - 2];  // 0.0
/*58  */         }                                                                                                          // 0.0
/*60  */         if (block_is_intra & 1 || right_is_intra & 1 || mv[0][0] != mv[1][0] || mv[0][1] != mv[1][1]) {            // 0.0
/*62  */             v->vc1dsp.vc1_h_loop_filter8(dst, linesize, v->pq);                                                    // 0.0
/*64  */         } else {                                                                                                   // 0.0
/*66  */             idx = ((right_cbp >> 1) | block_cbp) & 5; // FIXME check                                               // 0.0
/*68  */             if (idx == 5) {                                                                                        // 0.0
/*70  */                 v->vc1dsp.vc1_h_loop_filter8(dst, linesize, v->pq);                                                // 0.0
/*72  */             } else if (idx) {                                                                                      // 0.0
/*74  */                 if (idx == 1)                                                                                      // 0.0
/*76  */                     v->vc1dsp.vc1_h_loop_filter4(dst + 4 * linesize, linesize, v->pq);                             // 0.0
/*78  */                 else                                                                                               // 0.0
/*80  */                     v->vc1dsp.vc1_h_loop_filter4(dst,                linesize, v->pq);                             // 0.0
/*82  */             }                                                                                                      // 0.0
/*84  */         }                                                                                                          // 0.0
/*86  */     }                                                                                                              // 0.0
/*90  */     dst -= 4;                                                                                                      // 0.0
/*92  */     ttblk = (v->ttblk[s->mb_x - s->mb_stride - 1] >> (block_num * 4)) & 0xf;                                       // 0.0
/*94  */     if (ttblk == TT_4X4 || ttblk == TT_4X8) {                                                                      // 0.0
/*96  */         idx = (block_cbp | (block_cbp >> 1)) & 5;                                                                  // 0.0
/*98  */         if (idx == 5) {                                                                                            // 0.0
/*100 */             v->vc1dsp.vc1_h_loop_filter8(dst, linesize, v->pq);                                                    // 0.0
/*102 */         } else if (idx) {                                                                                          // 0.0
/*104 */             if (idx == 1)                                                                                          // 0.0
/*106 */                 v->vc1dsp.vc1_h_loop_filter4(dst + linesize * 4, linesize, v->pq);                                 // 0.0
/*108 */             else                                                                                                   // 0.0
/*110 */                 v->vc1dsp.vc1_h_loop_filter4(dst,                linesize, v->pq);                                 // 0.0
/*112 */         }                                                                                                          // 0.0
/*114 */     }                                                                                                              // 0.0
/*116 */ }                                                                                                                  // 0.0

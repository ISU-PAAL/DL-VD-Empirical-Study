// commit message FFmpeg@9b6aafba6c (target=1, prob=0.41022977, correct=False): mpegvideo: fix invalid memory access for small video dimensions
/*0   */ static av_always_inline void mpeg_motion_lowres(MpegEncContext *s,                                  // (8) 0.04297
/*2   */                                                 uint8_t *dest_y,                                    // (4) 0.1094
/*4   */                                                 uint8_t *dest_cb,                                   // (2) 0.1094
/*6   */                                                 uint8_t *dest_cr,                                   // (3) 0.1094
/*8   */                                                 int field_based,                                    // (5) 0.1016
/*10  */                                                 int bottom_field,                                   // (7) 0.1016
/*12  */                                                 int field_select,                                   // (6) 0.1016
/*14  */                                                 uint8_t **ref_picture,                              // (1) 0.1094
/*16  */                                                 h264_chroma_mc_func *pix_op,                        // (0) 0.1211
/*18  */                                                 int motion_x, int motion_y,                         // 0.0
/*20  */                                                 int h, int mb_y)                                    // 0.0
/*22  */ {                                                                                                   // 0.0
/*24  */     uint8_t *ptr_y, *ptr_cb, *ptr_cr;                                                               // 0.0
/*26  */     int mx, my, src_x, src_y, uvsrc_x, uvsrc_y, uvlinesize, linesize, sx, sy,                       // 0.0
/*28  */         uvsx, uvsy;                                                                                 // 0.0
/*30  */     const int lowres     = s->avctx->lowres;                                                        // 0.0
/*32  */     const int op_index   = FFMIN(lowres, 2);                                                        // 0.0
/*34  */     const int block_s    = 8>>lowres;                                                               // 0.0
/*36  */     const int s_mask     = (2 << lowres) - 1;                                                       // 0.0
/*38  */     const int h_edge_pos = s->h_edge_pos >> lowres;                                                 // 0.0
/*40  */     const int v_edge_pos = s->v_edge_pos >> lowres;                                                 // 0.0
/*42  */     linesize   = s->current_picture.f.linesize[0] << field_based;                                   // 0.0
/*44  */     uvlinesize = s->current_picture.f.linesize[1] << field_based;                                   // 0.0
/*48  */     // FIXME obviously not perfect but qpel will not work in lowres anyway                          // 0.0
/*50  */     if (s->quarter_sample) {                                                                        // 0.0
/*52  */         motion_x /= 2;                                                                              // 0.0
/*54  */         motion_y /= 2;                                                                              // 0.0
/*56  */     }                                                                                               // 0.0
/*60  */     if (field_based) {                                                                              // 0.0
/*62  */         motion_y += (bottom_field - field_select) * (1 << lowres - 1);                              // 0.0
/*64  */     }                                                                                               // 0.0
/*68  */     sx = motion_x & s_mask;                                                                         // 0.0
/*70  */     sy = motion_y & s_mask;                                                                         // 0.0
/*72  */     src_x = s->mb_x * 2 * block_s + (motion_x >> lowres + 1);                                       // 0.0
/*74  */     src_y = (mb_y * 2 * block_s >> field_based) + (motion_y >> lowres + 1);                         // 0.0
/*78  */     if (s->out_format == FMT_H263) {                                                                // 0.0
/*80  */         uvsx    = ((motion_x >> 1) & s_mask) | (sx & 1);                                            // 0.0
/*82  */         uvsy    = ((motion_y >> 1) & s_mask) | (sy & 1);                                            // 0.0
/*84  */         uvsrc_x = src_x >> 1;                                                                       // 0.0
/*86  */         uvsrc_y = src_y >> 1;                                                                       // 0.0
/*88  */     } else if (s->out_format == FMT_H261) {                                                         // 0.0
/*90  */         // even chroma mv's are full pel in H261                                                    // 0.0
/*92  */         mx      = motion_x / 4;                                                                     // 0.0
/*94  */         my      = motion_y / 4;                                                                     // 0.0
/*96  */         uvsx    = (2 * mx) & s_mask;                                                                // 0.0
/*98  */         uvsy    = (2 * my) & s_mask;                                                                // 0.0
/*100 */         uvsrc_x = s->mb_x * block_s + (mx >> lowres);                                               // 0.0
/*102 */         uvsrc_y =    mb_y * block_s + (my >> lowres);                                               // 0.0
/*104 */     } else {                                                                                        // 0.0
/*106 */         mx      = motion_x / 2;                                                                     // 0.0
/*108 */         my      = motion_y / 2;                                                                     // 0.0
/*110 */         uvsx    = mx & s_mask;                                                                      // 0.0
/*112 */         uvsy    = my & s_mask;                                                                      // 0.0
/*114 */         uvsrc_x = s->mb_x * block_s                 + (mx >> lowres + 1);                           // 0.0
/*116 */         uvsrc_y =   (mb_y * block_s >> field_based) + (my >> lowres + 1);                           // 0.0
/*118 */     }                                                                                               // 0.0
/*122 */     ptr_y  = ref_picture[0] + src_y   * linesize   + src_x;                                         // 0.0
/*124 */     ptr_cb = ref_picture[1] + uvsrc_y * uvlinesize + uvsrc_x;                                       // 0.0
/*126 */     ptr_cr = ref_picture[2] + uvsrc_y * uvlinesize + uvsrc_x;                                       // 0.0
/*130 */     if ((unsigned) src_x >  h_edge_pos - (!!sx) - 2 * block_s ||                                    // 0.0
/*132 */         (unsigned) src_y > (v_edge_pos >> field_based) - (!!sy) - h) {                              // 0.0
/*134 */         s->dsp.emulated_edge_mc(s->edge_emu_buffer, ptr_y,                                          // 0.0
/*136 */                                 s->linesize, 17, 17 + field_based,                                  // 0.0
/*138 */                                 src_x, src_y << field_based, h_edge_pos,                            // 0.0
/*140 */                                 v_edge_pos);                                                        // 0.0
/*142 */         ptr_y = s->edge_emu_buffer;                                                                 // 0.0
/*144 */         if (!CONFIG_GRAY || !(s->flags & CODEC_FLAG_GRAY)) {                                        // 0.0
/*146 */             uint8_t *uvbuf = s->edge_emu_buffer + 18 * s->linesize;                                 // 0.0
/*148 */             s->dsp.emulated_edge_mc(uvbuf , ptr_cb, s->uvlinesize, 9,                               // 0.0
/*150 */                                     9 + field_based,                                                // 0.0
/*152 */                                     uvsrc_x, uvsrc_y << field_based,                                // 0.0
/*154 */                                     h_edge_pos >> 1, v_edge_pos >> 1);                              // 0.0
/*156 */             s->dsp.emulated_edge_mc(uvbuf + 16, ptr_cr, s->uvlinesize, 9,                           // 0.0
/*158 */                                     9 + field_based,                                                // 0.0
/*160 */                                     uvsrc_x, uvsrc_y << field_based,                                // 0.0
/*162 */                                     h_edge_pos >> 1, v_edge_pos >> 1);                              // 0.0
/*164 */             ptr_cb = uvbuf;                                                                         // 0.0
/*166 */             ptr_cr = uvbuf + 16;                                                                    // 0.0
/*168 */         }                                                                                           // 0.0
/*170 */     }                                                                                               // 0.0
/*174 */     // FIXME use this for field pix too instead of the obnoxious hack which changes picture.f.data  // 0.0
/*176 */     if (bottom_field) {                                                                             // 0.0
/*178 */         dest_y  += s->linesize;                                                                     // 0.0
/*180 */         dest_cb += s->uvlinesize;                                                                   // 0.0
/*182 */         dest_cr += s->uvlinesize;                                                                   // 0.0
/*184 */     }                                                                                               // 0.0
/*188 */     if (field_select) {                                                                             // 0.0
/*190 */         ptr_y   += s->linesize;                                                                     // 0.0
/*192 */         ptr_cb  += s->uvlinesize;                                                                   // 0.0
/*194 */         ptr_cr  += s->uvlinesize;                                                                   // 0.0
/*196 */     }                                                                                               // 0.0
/*200 */     sx = (sx << 2) >> lowres;                                                                       // 0.0
/*202 */     sy = (sy << 2) >> lowres;                                                                       // 0.0
/*204 */     pix_op[lowres - 1](dest_y, ptr_y, linesize, h, sx, sy);                                         // 0.0
/*208 */     if (!CONFIG_GRAY || !(s->flags & CODEC_FLAG_GRAY)) {                                            // 0.0
/*210 */         uvsx = (uvsx << 2) >> lowres;                                                               // 0.0
/*212 */         uvsy = (uvsy << 2) >> lowres;                                                               // 0.0
/*214 */         pix_op[op_index](dest_cb, ptr_cb, uvlinesize, h >> s->chroma_y_shift,                       // 0.0
/*216 */                          uvsx, uvsy);                                                               // 0.0
/*218 */         pix_op[op_index](dest_cr, ptr_cr, uvlinesize, h >> s->chroma_y_shift,                       // 0.0
/*220 */                          uvsx, uvsy);                                                               // 0.0
/*222 */     }                                                                                               // 0.0
/*224 */     // FIXME h261 lowres loop filter                                                                // 0.0
/*226 */ }                                                                                                   // 0.0

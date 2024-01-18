// commit message FFmpeg@c341f734e5 (target=1, prob=0.8069667, correct=True): Convert multiplier for MV from int to ptrdiff_t.
/*0   */ void ff_mspel_motion(MpegEncContext *s,                                                               // (14) 0.0293
/*2   */                                uint8_t *dest_y, uint8_t *dest_cb, uint8_t *dest_cr,                   // (0) 0.1113
/*4   */                                uint8_t **ref_picture, op_pixels_func (*pix_op)[4],                    // (1) 0.1035
/*6   */                                int motion_x, int motion_y, int h)                                     // (2) 0.08398
/*8   */ {                                                                                                     // (21) 0.001953
/*10  */     Wmv2Context * const w= (Wmv2Context*)s;                                                           // (9) 0.04102
/*12  */     uint8_t *ptr;                                                                                     // (19) 0.01953
/*14  */     int dxy, offset, mx, my, src_x, src_y, v_edge_pos, linesize, uvlinesize;                          // (3) 0.07031
/*16  */     int emu=0;                                                                                        // (20) 0.01758
/*20  */     dxy = ((motion_y & 1) << 1) | (motion_x & 1);                                                     // (4) 0.04687
/*22  */     dxy = 2*dxy + w->hshift;                                                                          // (13) 0.03125
/*24  */     src_x = s->mb_x * 16 + (motion_x >> 1);                                                           // (6) 0.04297
/*26  */     src_y = s->mb_y * 16 + (motion_y >> 1);                                                           // (7) 0.04297
/*30  */     /* WARNING: do no forget half pels */                                                             // (17) 0.02539
/*32  */     v_edge_pos = s->v_edge_pos;                                                                       // (12) 0.0332
/*34  */     src_x = av_clip(src_x, -16, s->width);                                                            // (8) 0.04297
/*36  */     src_y = av_clip(src_y, -16, s->height);                                                           // (5) 0.04297
/*40  */     if(src_x<=-16 || src_x >= s->width)                                                               // (11) 0.03906
/*42  */         dxy &= ~3;                                                                                    // (15) 0.02734
/*44  */     if(src_y<=-16 || src_y >= s->height)                                                              // (10) 0.03906
/*46  */         dxy &= ~4;                                                                                    // (16) 0.02734
/*50  */     linesize   = s->linesize;                                                                         // (18) 0.02539
/*52  */     uvlinesize = s->uvlinesize;                                                                       // 0.0
/*54  */     ptr = ref_picture[0] + (src_y * linesize) + src_x;                                                // 0.0
/*58  */         if(src_x<1 || src_y<1 || src_x + 17  >= s->h_edge_pos                                         // 0.0
/*60  */                               || src_y + h+1 >= v_edge_pos){                                          // 0.0
/*62  */             s->vdsp.emulated_edge_mc(s->edge_emu_buffer, ptr - 1 - s->linesize, s->linesize, 19, 19,  // 0.0
/*64  */                              src_x-1, src_y-1, s->h_edge_pos, s->v_edge_pos);                         // 0.0
/*66  */             ptr= s->edge_emu_buffer + 1 + s->linesize;                                                // 0.0
/*68  */             emu=1;                                                                                    // 0.0
/*70  */         }                                                                                             // 0.0
/*74  */     s->dsp.put_mspel_pixels_tab[dxy](dest_y             , ptr             , linesize);                // 0.0
/*76  */     s->dsp.put_mspel_pixels_tab[dxy](dest_y+8           , ptr+8           , linesize);                // 0.0
/*78  */     s->dsp.put_mspel_pixels_tab[dxy](dest_y  +8*linesize, ptr  +8*linesize, linesize);                // 0.0
/*80  */     s->dsp.put_mspel_pixels_tab[dxy](dest_y+8+8*linesize, ptr+8+8*linesize, linesize);                // 0.0
/*84  */     if(s->flags&CODEC_FLAG_GRAY) return;                                                              // 0.0
/*88  */     if (s->out_format == FMT_H263) {                                                                  // 0.0
/*90  */         dxy = 0;                                                                                      // 0.0
/*92  */         if ((motion_x & 3) != 0)                                                                      // 0.0
/*94  */             dxy |= 1;                                                                                 // 0.0
/*96  */         if ((motion_y & 3) != 0)                                                                      // 0.0
/*98  */             dxy |= 2;                                                                                 // 0.0
/*100 */         mx = motion_x >> 2;                                                                           // 0.0
/*102 */         my = motion_y >> 2;                                                                           // 0.0
/*104 */     } else {                                                                                          // 0.0
/*106 */         mx = motion_x / 2;                                                                            // 0.0
/*108 */         my = motion_y / 2;                                                                            // 0.0
/*110 */         dxy = ((my & 1) << 1) | (mx & 1);                                                             // 0.0
/*112 */         mx >>= 1;                                                                                     // 0.0
/*114 */         my >>= 1;                                                                                     // 0.0
/*116 */     }                                                                                                 // 0.0
/*120 */     src_x = s->mb_x * 8 + mx;                                                                         // 0.0
/*122 */     src_y = s->mb_y * 8 + my;                                                                         // 0.0
/*124 */     src_x = av_clip(src_x, -8, s->width >> 1);                                                        // 0.0
/*126 */     if (src_x == (s->width >> 1))                                                                     // 0.0
/*128 */         dxy &= ~1;                                                                                    // 0.0
/*130 */     src_y = av_clip(src_y, -8, s->height >> 1);                                                       // 0.0
/*132 */     if (src_y == (s->height >> 1))                                                                    // 0.0
/*134 */         dxy &= ~2;                                                                                    // 0.0
/*136 */     offset = (src_y * uvlinesize) + src_x;                                                            // 0.0
/*138 */     ptr = ref_picture[1] + offset;                                                                    // 0.0
/*140 */     if(emu){                                                                                          // 0.0
/*142 */         s->vdsp.emulated_edge_mc(s->edge_emu_buffer, ptr, s->uvlinesize, 9, 9,                        // 0.0
/*144 */                          src_x, src_y, s->h_edge_pos>>1, s->v_edge_pos>>1);                           // 0.0
/*146 */         ptr= s->edge_emu_buffer;                                                                      // 0.0
/*148 */     }                                                                                                 // 0.0
/*150 */     pix_op[1][dxy](dest_cb, ptr, uvlinesize, h >> 1);                                                 // 0.0
/*154 */     ptr = ref_picture[2] + offset;                                                                    // 0.0
/*156 */     if(emu){                                                                                          // 0.0
/*158 */         s->vdsp.emulated_edge_mc(s->edge_emu_buffer, ptr, s->uvlinesize, 9, 9,                        // 0.0
/*160 */                          src_x, src_y, s->h_edge_pos>>1, s->v_edge_pos>>1);                           // 0.0
/*162 */         ptr= s->edge_emu_buffer;                                                                      // 0.0
/*164 */     }                                                                                                 // 0.0
/*166 */     pix_op[1][dxy](dest_cr, ptr, uvlinesize, h >> 1);                                                 // 0.0
/*168 */ }                                                                                                     // 0.0

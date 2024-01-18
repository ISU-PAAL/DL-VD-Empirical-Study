// commit message FFmpeg@aacf6b3a2f (target=1, prob=0.66108054, correct=True): rv34: fix invalid memory access for small video dimensions
/*0   */ static inline void rv34_mc(RV34DecContext *r, const int block_type,                                               // (10) 0.04492
/*2   */                           const int xoff, const int yoff, int mv_off,                                             // (3) 0.08008
/*4   */                           const int width, const int height, int dir,                                             // (7) 0.07031
/*6   */                           const int thirdpel, int weighted,                                                       // (8) 0.06445
/*8   */                           qpel_mc_func (*qpel_mc)[16],                                                            // (5) 0.07617
/*10  */                           h264_chroma_mc_func (*chroma_mc))                                                       // (4) 0.07813
/*12  */ {                                                                                                                 // (15) 0.001953
/*14  */     MpegEncContext *s = &r->s;                                                                                    // (12) 0.0293
/*16  */     uint8_t *Y, *U, *V, *srcY, *srcU, *srcV;                                                                      // (9) 0.05469
/*18  */     int dxy, mx, my, umx, umy, lx, ly, uvmx, uvmy, src_x, src_y, uvsrc_x, uvsrc_y;                                // (0) 0.09961
/*20  */     int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride + mv_off;                                               // (6) 0.07422
/*22  */     int is16x16 = 1;                                                                                              // (13) 0.02148
/*26  */     if(thirdpel){                                                                                                 // (14) 0.01563
/*28  */         int chroma_mx, chroma_my;                                                                                 // (11) 0.03516
/*30  */         mx = (s->current_picture_ptr->f.motion_val[dir][mv_pos][0] + (3 << 24)) / 3 - (1 << 24);                  // (1) 0.09375
/*32  */         my = (s->current_picture_ptr->f.motion_val[dir][mv_pos][1] + (3 << 24)) / 3 - (1 << 24);                  // (2) 0.0918
/*34  */         lx = (s->current_picture_ptr->f.motion_val[dir][mv_pos][0] + (3 << 24)) % 3;                              // 0.0
/*36  */         ly = (s->current_picture_ptr->f.motion_val[dir][mv_pos][1] + (3 << 24)) % 3;                              // 0.0
/*38  */         chroma_mx = s->current_picture_ptr->f.motion_val[dir][mv_pos][0] / 2;                                     // 0.0
/*40  */         chroma_my = s->current_picture_ptr->f.motion_val[dir][mv_pos][1] / 2;                                     // 0.0
/*42  */         umx = (chroma_mx + (3 << 24)) / 3 - (1 << 24);                                                            // 0.0
/*44  */         umy = (chroma_my + (3 << 24)) / 3 - (1 << 24);                                                            // 0.0
/*46  */         uvmx = chroma_coeffs[(chroma_mx + (3 << 24)) % 3];                                                        // 0.0
/*48  */         uvmy = chroma_coeffs[(chroma_my + (3 << 24)) % 3];                                                        // 0.0
/*50  */     }else{                                                                                                        // 0.0
/*52  */         int cx, cy;                                                                                               // 0.0
/*54  */         mx = s->current_picture_ptr->f.motion_val[dir][mv_pos][0] >> 2;                                           // 0.0
/*56  */         my = s->current_picture_ptr->f.motion_val[dir][mv_pos][1] >> 2;                                           // 0.0
/*58  */         lx = s->current_picture_ptr->f.motion_val[dir][mv_pos][0] & 3;                                            // 0.0
/*60  */         ly = s->current_picture_ptr->f.motion_val[dir][mv_pos][1] & 3;                                            // 0.0
/*62  */         cx = s->current_picture_ptr->f.motion_val[dir][mv_pos][0] / 2;                                            // 0.0
/*64  */         cy = s->current_picture_ptr->f.motion_val[dir][mv_pos][1] / 2;                                            // 0.0
/*66  */         umx = cx >> 2;                                                                                            // 0.0
/*68  */         umy = cy >> 2;                                                                                            // 0.0
/*70  */         uvmx = (cx & 3) << 1;                                                                                     // 0.0
/*72  */         uvmy = (cy & 3) << 1;                                                                                     // 0.0
/*74  */         //due to some flaw RV40 uses the same MC compensation routine for H2V2 and H3V3                           // 0.0
/*76  */         if(uvmx == 6 && uvmy == 6)                                                                                // 0.0
/*78  */             uvmx = uvmy = 4;                                                                                      // 0.0
/*80  */     }                                                                                                             // 0.0
/*82  */     dxy = ly*4 + lx;                                                                                              // 0.0
/*84  */     srcY = dir ? s->next_picture_ptr->f.data[0] : s->last_picture_ptr->f.data[0];                                 // 0.0
/*86  */     srcU = dir ? s->next_picture_ptr->f.data[1] : s->last_picture_ptr->f.data[1];                                 // 0.0
/*88  */     srcV = dir ? s->next_picture_ptr->f.data[2] : s->last_picture_ptr->f.data[2];                                 // 0.0
/*90  */     src_x = s->mb_x * 16 + xoff + mx;                                                                             // 0.0
/*92  */     src_y = s->mb_y * 16 + yoff + my;                                                                             // 0.0
/*94  */     uvsrc_x = s->mb_x * 8 + (xoff >> 1) + umx;                                                                    // 0.0
/*96  */     uvsrc_y = s->mb_y * 8 + (yoff >> 1) + umy;                                                                    // 0.0
/*98  */     srcY += src_y * s->linesize + src_x;                                                                          // 0.0
/*100 */     srcU += uvsrc_y * s->uvlinesize + uvsrc_x;                                                                    // 0.0
/*102 */     srcV += uvsrc_y * s->uvlinesize + uvsrc_x;                                                                    // 0.0
/*104 */     if(   (unsigned)(src_x - !!lx*2) > s->h_edge_pos - !!lx*2 - (width <<3) - 4                                   // 0.0
/*106 */        || (unsigned)(src_y - !!ly*2) > s->v_edge_pos - !!ly*2 - (height<<3) - 4){                                 // 0.0
/*108 */         uint8_t *uvbuf = s->edge_emu_buffer + 22 * s->linesize;                                                   // 0.0
/*112 */         srcY -= 2 + 2*s->linesize;                                                                                // 0.0
/*114 */         s->dsp.emulated_edge_mc(s->edge_emu_buffer, srcY, s->linesize, (width<<3)+6, (height<<3)+6,               // 0.0
/*116 */                             src_x - 2, src_y - 2, s->h_edge_pos, s->v_edge_pos);                                  // 0.0
/*118 */         srcY = s->edge_emu_buffer + 2 + 2*s->linesize;                                                            // 0.0
/*120 */         s->dsp.emulated_edge_mc(uvbuf     , srcU, s->uvlinesize, (width<<2)+1, (height<<2)+1,                     // 0.0
/*122 */                             uvsrc_x, uvsrc_y, s->h_edge_pos >> 1, s->v_edge_pos >> 1);                            // 0.0
/*124 */         s->dsp.emulated_edge_mc(uvbuf + 16, srcV, s->uvlinesize, (width<<2)+1, (height<<2)+1,                     // 0.0
/*126 */                             uvsrc_x, uvsrc_y, s->h_edge_pos >> 1, s->v_edge_pos >> 1);                            // 0.0
/*128 */         srcU = uvbuf;                                                                                             // 0.0
/*130 */         srcV = uvbuf + 16;                                                                                        // 0.0
/*132 */     }                                                                                                             // 0.0
/*134 */     if(!weighted){                                                                                                // 0.0
/*136 */         Y = s->dest[0] + xoff      + yoff     *s->linesize;                                                       // 0.0
/*138 */         U = s->dest[1] + (xoff>>1) + (yoff>>1)*s->uvlinesize;                                                     // 0.0
/*140 */         V = s->dest[2] + (xoff>>1) + (yoff>>1)*s->uvlinesize;                                                     // 0.0
/*142 */     }else{                                                                                                        // 0.0
/*144 */         Y = r->tmp_b_block_y [dir]     +  xoff     +  yoff    *s->linesize;                                       // 0.0
/*146 */         U = r->tmp_b_block_uv[dir*2]   + (xoff>>1) + (yoff>>1)*s->uvlinesize;                                     // 0.0
/*148 */         V = r->tmp_b_block_uv[dir*2+1] + (xoff>>1) + (yoff>>1)*s->uvlinesize;                                     // 0.0
/*150 */     }                                                                                                             // 0.0
/*154 */     if(block_type == RV34_MB_P_16x8){                                                                             // 0.0
/*156 */         qpel_mc[1][dxy](Y, srcY, s->linesize);                                                                    // 0.0
/*158 */         Y    += 8;                                                                                                // 0.0
/*160 */         srcY += 8;                                                                                                // 0.0
/*162 */     }else if(block_type == RV34_MB_P_8x16){                                                                       // 0.0
/*164 */         qpel_mc[1][dxy](Y, srcY, s->linesize);                                                                    // 0.0
/*166 */         Y    += 8 * s->linesize;                                                                                  // 0.0
/*168 */         srcY += 8 * s->linesize;                                                                                  // 0.0
/*170 */     }                                                                                                             // 0.0
/*172 */     is16x16 = (block_type != RV34_MB_P_8x8) && (block_type != RV34_MB_P_16x8) && (block_type != RV34_MB_P_8x16);  // 0.0
/*174 */     qpel_mc[!is16x16][dxy](Y, srcY, s->linesize);                                                                 // 0.0
/*176 */     chroma_mc[2-width]   (U, srcU, s->uvlinesize, height*4, uvmx, uvmy);                                          // 0.0
/*178 */     chroma_mc[2-width]   (V, srcV, s->uvlinesize, height*4, uvmx, uvmy);                                          // 0.0
/*180 */ }                                                                                                                 // 0.0

// commit message FFmpeg@c341f734e5 (target=1, prob=0.48202702, correct=False): Convert multiplier for MV from int to ptrdiff_t.
/*0   */ void mpeg_motion_internal(MpegEncContext *s,                                                                       // (14) 0.0293
/*2   */                  uint8_t *dest_y, uint8_t *dest_cb, uint8_t *dest_cr,                                              // (0) 0.08398
/*4   */                  int field_based, int bottom_field, int field_select,                                              // (4) 0.06055
/*6   */                  uint8_t **ref_picture, op_pixels_func (*pix_op)[4],                                               // (2) 0.07617
/*8   */                  int motion_x, int motion_y, int h, int is_mpeg12, int mb_y)                                       // (1) 0.08008
/*10  */ {                                                                                                                  // (22) 0.001953
/*12  */     uint8_t *ptr_y, *ptr_cb, *ptr_cr;                                                                              // (11) 0.04297
/*14  */     int dxy, uvdxy, mx, my, src_x, src_y,                                                                          // (9) 0.04688
/*16  */         uvsrc_x, uvsrc_y, v_edge_pos;                                                                              // (8) 0.04883
/*18  */     emuedge_linesize_type uvlinesize, linesize;                                                                    // (13) 0.03711
/*22  */ #if 0                                                                                                              // (18) 0.005859
/*24  */ if(s->quarter_sample)                                                                                              // (17) 0.01563
/*26  */ {                                                                                                                  // (20) 0.001953
/*28  */     motion_x>>=1;                                                                                                  // (15) 0.01953
/*30  */     motion_y>>=1;                                                                                                  // (16) 0.01953
/*32  */ }                                                                                                                  // (21) 0.001953
/*34  */ #endif                                                                                                             // (19) 0.003906
/*38  */     v_edge_pos = s->v_edge_pos >> field_based;                                                                     // (12) 0.04102
/*40  */     linesize   = s->current_picture.f.linesize[0] << field_based;                                                  // (6) 0.05078
/*42  */     uvlinesize = s->current_picture.f.linesize[1] << field_based;                                                  // (7) 0.05078
/*46  */     dxy = ((motion_y & 1) << 1) | (motion_x & 1);                                                                  // (10) 0.04688
/*48  */     src_x = s->mb_x* 16               + (motion_x >> 1);                                                           // (3) 0.07031
/*50  */     src_y =(   mb_y<<(4-field_based)) + (motion_y >> 1);                                                           // (5) 0.05859
/*54  */     if (!is_mpeg12 && s->out_format == FMT_H263) {                                                                 // 0.0
/*56  */         if((s->workaround_bugs & FF_BUG_HPEL_CHROMA) && field_based){                                              // 0.0
/*58  */             mx = (motion_x>>1)|(motion_x&1);                                                                       // 0.0
/*60  */             my = motion_y >>1;                                                                                     // 0.0
/*62  */             uvdxy = ((my & 1) << 1) | (mx & 1);                                                                    // 0.0
/*64  */             uvsrc_x = s->mb_x* 8               + (mx >> 1);                                                        // 0.0
/*66  */             uvsrc_y =(   mb_y<<(3-field_based))+ (my >> 1);                                                        // 0.0
/*68  */         }else{                                                                                                     // 0.0
/*70  */             uvdxy = dxy | (motion_y & 2) | ((motion_x & 2) >> 1);                                                  // 0.0
/*72  */             uvsrc_x = src_x>>1;                                                                                    // 0.0
/*74  */             uvsrc_y = src_y>>1;                                                                                    // 0.0
/*76  */         }                                                                                                          // 0.0
/*78  */     }else if(!is_mpeg12 && s->out_format == FMT_H261){//even chroma mv's are full pel in H261                      // 0.0
/*80  */         mx = motion_x / 4;                                                                                         // 0.0
/*82  */         my = motion_y / 4;                                                                                         // 0.0
/*84  */         uvdxy = 0;                                                                                                 // 0.0
/*86  */         uvsrc_x = s->mb_x*8 + mx;                                                                                  // 0.0
/*88  */         uvsrc_y =    mb_y*8 + my;                                                                                  // 0.0
/*90  */     } else {                                                                                                       // 0.0
/*92  */         if(s->chroma_y_shift){                                                                                     // 0.0
/*94  */             mx = motion_x / 2;                                                                                     // 0.0
/*96  */             my = motion_y / 2;                                                                                     // 0.0
/*98  */             uvdxy = ((my & 1) << 1) | (mx & 1);                                                                    // 0.0
/*100 */             uvsrc_x = s->mb_x* 8               + (mx >> 1);                                                        // 0.0
/*102 */             uvsrc_y =(   mb_y<<(3-field_based))+ (my >> 1);                                                        // 0.0
/*104 */         } else {                                                                                                   // 0.0
/*106 */             if(s->chroma_x_shift){                                                                                 // 0.0
/*108 */             //Chroma422                                                                                            // 0.0
/*110 */                 mx = motion_x / 2;                                                                                 // 0.0
/*112 */                 uvdxy = ((motion_y & 1) << 1) | (mx & 1);                                                          // 0.0
/*114 */                 uvsrc_x = s->mb_x* 8           + (mx >> 1);                                                        // 0.0
/*116 */                 uvsrc_y = src_y;                                                                                   // 0.0
/*118 */             } else {                                                                                               // 0.0
/*120 */             //Chroma444                                                                                            // 0.0
/*122 */                 uvdxy = dxy;                                                                                       // 0.0
/*124 */                 uvsrc_x = src_x;                                                                                   // 0.0
/*126 */                 uvsrc_y = src_y;                                                                                   // 0.0
/*128 */             }                                                                                                      // 0.0
/*130 */         }                                                                                                          // 0.0
/*132 */     }                                                                                                              // 0.0
/*136 */     ptr_y  = ref_picture[0] + src_y * linesize + src_x;                                                            // 0.0
/*138 */     ptr_cb = ref_picture[1] + uvsrc_y * uvlinesize + uvsrc_x;                                                      // 0.0
/*140 */     ptr_cr = ref_picture[2] + uvsrc_y * uvlinesize + uvsrc_x;                                                      // 0.0
/*144 */     if(   (unsigned)src_x > FFMAX(s->h_edge_pos - (motion_x&1) - 16, 0)                                            // 0.0
/*146 */        || (unsigned)src_y > FFMAX(   v_edge_pos - (motion_y&1) - h , 0)){                                          // 0.0
/*148 */             if(is_mpeg12 || s->codec_id == AV_CODEC_ID_MPEG2VIDEO ||                                               // 0.0
/*150 */                s->codec_id == AV_CODEC_ID_MPEG1VIDEO){                                                             // 0.0
/*152 */                 av_log(s->avctx,AV_LOG_DEBUG,                                                                      // 0.0
/*154 */                         "MPEG motion vector out of boundary (%d %d)\n", src_x, src_y);                             // 0.0
/*156 */                 return;                                                                                            // 0.0
/*158 */             }                                                                                                      // 0.0
/*160 */             s->vdsp.emulated_edge_mc(s->edge_emu_buffer, ptr_y, s->linesize,                                       // 0.0
/*162 */                                 17, 17+field_based,                                                                // 0.0
/*164 */                                 src_x, src_y<<field_based,                                                         // 0.0
/*166 */                                 s->h_edge_pos, s->v_edge_pos);                                                     // 0.0
/*168 */             ptr_y = s->edge_emu_buffer;                                                                            // 0.0
/*170 */             if(!CONFIG_GRAY || !(s->flags&CODEC_FLAG_GRAY)){                                                       // 0.0
/*172 */                 uint8_t *uvbuf= s->edge_emu_buffer+18*s->linesize;                                                 // 0.0
/*174 */                 s->vdsp.emulated_edge_mc(uvbuf ,                                                                   // 0.0
/*176 */                                     ptr_cb, s->uvlinesize,                                                         // 0.0
/*178 */                                     9, 9+field_based,                                                              // 0.0
/*180 */                                     uvsrc_x, uvsrc_y<<field_based,                                                 // 0.0
/*182 */                                     s->h_edge_pos>>1, s->v_edge_pos>>1);                                           // 0.0
/*184 */                 s->vdsp.emulated_edge_mc(uvbuf+16,                                                                 // 0.0
/*186 */                                     ptr_cr, s->uvlinesize,                                                         // 0.0
/*188 */                                     9, 9+field_based,                                                              // 0.0
/*190 */                                     uvsrc_x, uvsrc_y<<field_based,                                                 // 0.0
/*192 */                                     s->h_edge_pos>>1, s->v_edge_pos>>1);                                           // 0.0
/*194 */                 ptr_cb= uvbuf;                                                                                     // 0.0
/*196 */                 ptr_cr= uvbuf+16;                                                                                  // 0.0
/*198 */             }                                                                                                      // 0.0
/*200 */     }                                                                                                              // 0.0
/*204 */     if(bottom_field){ //FIXME use this for field pix too instead of the obnoxious hack which changes picture.data  // 0.0
/*206 */         dest_y += s->linesize;                                                                                     // 0.0
/*208 */         dest_cb+= s->uvlinesize;                                                                                   // 0.0
/*210 */         dest_cr+= s->uvlinesize;                                                                                   // 0.0
/*212 */     }                                                                                                              // 0.0
/*216 */     if(field_select){                                                                                              // 0.0
/*218 */         ptr_y += s->linesize;                                                                                      // 0.0
/*220 */         ptr_cb+= s->uvlinesize;                                                                                    // 0.0
/*222 */         ptr_cr+= s->uvlinesize;                                                                                    // 0.0
/*224 */     }                                                                                                              // 0.0
/*228 */     pix_op[0][dxy](dest_y, ptr_y, linesize, h);                                                                    // 0.0
/*232 */     if(!CONFIG_GRAY || !(s->flags&CODEC_FLAG_GRAY)){                                                               // 0.0
/*234 */         pix_op[s->chroma_x_shift][uvdxy]                                                                           // 0.0
/*236 */                 (dest_cb, ptr_cb, uvlinesize, h >> s->chroma_y_shift);                                             // 0.0
/*238 */         pix_op[s->chroma_x_shift][uvdxy]                                                                           // 0.0
/*240 */                 (dest_cr, ptr_cr, uvlinesize, h >> s->chroma_y_shift);                                             // 0.0
/*242 */     }                                                                                                              // 0.0
/*244 */     if(!is_mpeg12 && (CONFIG_H261_ENCODER || CONFIG_H261_DECODER) &&                                               // 0.0
/*246 */          s->out_format == FMT_H261){                                                                               // 0.0
/*248 */         ff_h261_loop_filter(s);                                                                                    // 0.0
/*250 */     }                                                                                                              // 0.0
/*252 */ }                                                                                                                  // 0.0

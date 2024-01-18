// commit message FFmpeg@f6774f905f (target=1, prob=0.62966776, correct=True): mpegvideo: operate with pointers to AVFrames instead of whole structs
/*0   */ static void vc1_mc_1mv(VC1Context *v, int dir)                                                                     // (8) 0.04102
/*2   */ {                                                                                                                  // (24) 0.001953
/*4   */     MpegEncContext *s = &v->s;                                                                                     // (16) 0.0293
/*6   */     H264ChromaContext *h264chroma = &v->h264chroma;                                                                // (5) 0.04297
/*8   */     uint8_t *srcY, *srcU, *srcV;                                                                                   // (13) 0.03711
/*10  */     int dxy, mx, my, uvmx, uvmy, src_x, src_y, uvsrc_x, uvsrc_y;                                                   // (2) 0.07812
/*12  */     int v_edge_pos = s->v_edge_pos >> v->field_mode;                                                               // (4) 0.04687
/*14  */     int i;                                                                                                         // (22) 0.01172
/*16  */     uint8_t (*luty)[256], (*lutuv)[256];                                                                           // (11) 0.03906
/*18  */     int use_ic;                                                                                                    // (20) 0.01563
/*22  */     if ((!v->field_mode ||                                                                                         // (18) 0.02344
/*24  */          (v->ref_field_type[dir] == 1 && v->cur_field_type == 1)) &&                                               // (3) 0.06445
/*26  */         !v->s.last_picture.f.data[0])                                                                              // (7) 0.04297
/*28  */         return;                                                                                                    // (19) 0.01758
/*32  */     mx = s->mv[dir][0][0];                                                                                         // (14) 0.0332
/*34  */     my = s->mv[dir][0][1];                                                                                         // (15) 0.03125
/*38  */     // store motion vectors for further use in B frames                                                            // (17) 0.02539
/*40  */     if (s->pict_type == AV_PICTURE_TYPE_P) {                                                                       // (6) 0.04297
/*42  */         for (i = 0; i < 4; i++) {                                                                                  // (12) 0.03906
/*44  */             s->current_picture.motion_val[1][s->block_index[i] + v->blocks_off][0] = mx;                           // (0) 0.08594
/*46  */             s->current_picture.motion_val[1][s->block_index[i] + v->blocks_off][1] = my;                           // (1) 0.08398
/*48  */         }                                                                                                          // (21) 0.01562
/*50  */     }                                                                                                              // (23) 0.007812
/*54  */     uvmx = (mx + ((mx & 3) == 3)) >> 1;                                                                            // (9) 0.04102
/*56  */     uvmy = (my + ((my & 3) == 3)) >> 1;                                                                            // (10) 0.04102
/*58  */     v->luma_mv[s->mb_x][0] = uvmx;                                                                                 // 0.0
/*60  */     v->luma_mv[s->mb_x][1] = uvmy;                                                                                 // 0.0
/*64  */     if (v->field_mode &&                                                                                           // 0.0
/*66  */         v->cur_field_type != v->ref_field_type[dir]) {                                                             // 0.0
/*68  */         my   = my   - 2 + 4 * v->cur_field_type;                                                                   // 0.0
/*70  */         uvmy = uvmy - 2 + 4 * v->cur_field_type;                                                                   // 0.0
/*72  */     }                                                                                                              // 0.0
/*76  */     // fastuvmc shall be ignored for interlaced frame picture                                                      // 0.0
/*78  */     if (v->fastuvmc && (v->fcm != ILACE_FRAME)) {                                                                  // 0.0
/*80  */         uvmx = uvmx + ((uvmx < 0) ? (uvmx & 1) : -(uvmx & 1));                                                     // 0.0
/*82  */         uvmy = uvmy + ((uvmy < 0) ? (uvmy & 1) : -(uvmy & 1));                                                     // 0.0
/*84  */     }                                                                                                              // 0.0
/*86  */     if (!dir) {                                                                                                    // 0.0
/*88  */         if (v->field_mode && (v->cur_field_type != v->ref_field_type[dir]) && v->second_field) {                   // 0.0
/*90  */             srcY = s->current_picture.f.data[0];                                                                   // 0.0
/*92  */             srcU = s->current_picture.f.data[1];                                                                   // 0.0
/*94  */             srcV = s->current_picture.f.data[2];                                                                   // 0.0
/*96  */             luty  = v->curr_luty;                                                                                  // 0.0
/*98  */             lutuv = v->curr_lutuv;                                                                                 // 0.0
/*100 */             use_ic = v->curr_use_ic;                                                                               // 0.0
/*102 */         } else {                                                                                                   // 0.0
/*104 */             srcY = s->last_picture.f.data[0];                                                                      // 0.0
/*106 */             srcU = s->last_picture.f.data[1];                                                                      // 0.0
/*108 */             srcV = s->last_picture.f.data[2];                                                                      // 0.0
/*110 */             luty  = v->last_luty;                                                                                  // 0.0
/*112 */             lutuv = v->last_lutuv;                                                                                 // 0.0
/*114 */             use_ic = v->last_use_ic;                                                                               // 0.0
/*116 */         }                                                                                                          // 0.0
/*118 */     } else {                                                                                                       // 0.0
/*120 */         srcY = s->next_picture.f.data[0];                                                                          // 0.0
/*122 */         srcU = s->next_picture.f.data[1];                                                                          // 0.0
/*124 */         srcV = s->next_picture.f.data[2];                                                                          // 0.0
/*126 */         luty  = v->next_luty;                                                                                      // 0.0
/*128 */         lutuv = v->next_lutuv;                                                                                     // 0.0
/*130 */         use_ic = v->next_use_ic;                                                                                   // 0.0
/*132 */     }                                                                                                              // 0.0
/*136 */     if (!srcY || !srcU) {                                                                                          // 0.0
/*138 */         av_log(v->s.avctx, AV_LOG_ERROR, "Referenced frame missing.\n");                                           // 0.0
/*140 */         return;                                                                                                    // 0.0
/*142 */     }                                                                                                              // 0.0
/*146 */     src_x   = s->mb_x * 16 + (mx   >> 2);                                                                          // 0.0
/*148 */     src_y   = s->mb_y * 16 + (my   >> 2);                                                                          // 0.0
/*150 */     uvsrc_x = s->mb_x *  8 + (uvmx >> 2);                                                                          // 0.0
/*152 */     uvsrc_y = s->mb_y *  8 + (uvmy >> 2);                                                                          // 0.0
/*156 */     if (v->profile != PROFILE_ADVANCED) {                                                                          // 0.0
/*158 */         src_x   = av_clip(  src_x, -16, s->mb_width  * 16);                                                        // 0.0
/*160 */         src_y   = av_clip(  src_y, -16, s->mb_height * 16);                                                        // 0.0
/*162 */         uvsrc_x = av_clip(uvsrc_x,  -8, s->mb_width  *  8);                                                        // 0.0
/*164 */         uvsrc_y = av_clip(uvsrc_y,  -8, s->mb_height *  8);                                                        // 0.0
/*166 */     } else {                                                                                                       // 0.0
/*168 */         src_x   = av_clip(  src_x, -17, s->avctx->coded_width);                                                    // 0.0
/*170 */         src_y   = av_clip(  src_y, -18, s->avctx->coded_height + 1);                                               // 0.0
/*172 */         uvsrc_x = av_clip(uvsrc_x,  -8, s->avctx->coded_width  >> 1);                                              // 0.0
/*174 */         uvsrc_y = av_clip(uvsrc_y,  -8, s->avctx->coded_height >> 1);                                              // 0.0
/*176 */     }                                                                                                              // 0.0
/*180 */     srcY += src_y   * s->linesize   + src_x;                                                                       // 0.0
/*182 */     srcU += uvsrc_y * s->uvlinesize + uvsrc_x;                                                                     // 0.0
/*184 */     srcV += uvsrc_y * s->uvlinesize + uvsrc_x;                                                                     // 0.0
/*188 */     if (v->field_mode && v->ref_field_type[dir]) {                                                                 // 0.0
/*190 */         srcY += s->current_picture_ptr->f.linesize[0];                                                             // 0.0
/*192 */         srcU += s->current_picture_ptr->f.linesize[1];                                                             // 0.0
/*194 */         srcV += s->current_picture_ptr->f.linesize[2];                                                             // 0.0
/*196 */     }                                                                                                              // 0.0
/*200 */     /* for grayscale we should not try to read from unknown area */                                                // 0.0
/*202 */     if (s->flags & CODEC_FLAG_GRAY) {                                                                              // 0.0
/*204 */         srcU = s->edge_emu_buffer + 18 * s->linesize;                                                              // 0.0
/*206 */         srcV = s->edge_emu_buffer + 18 * s->linesize;                                                              // 0.0
/*208 */     }                                                                                                              // 0.0
/*212 */     if (v->rangeredfrm || use_ic                                                                                   // 0.0
/*214 */         || s->h_edge_pos < 22 || v_edge_pos < 22                                                                   // 0.0
/*216 */         || (unsigned)(src_x - s->mspel) > s->h_edge_pos - (mx&3) - 16 - s->mspel * 3                               // 0.0
/*218 */         || (unsigned)(src_y - 1)        > v_edge_pos    - (my&3) - 16 - 3) {                                       // 0.0
/*220 */         uint8_t *uvbuf = s->edge_emu_buffer + 19 * s->linesize;                                                    // 0.0
/*224 */         srcY -= s->mspel * (1 + s->linesize);                                                                      // 0.0
/*226 */         s->vdsp.emulated_edge_mc(s->edge_emu_buffer, srcY,                                                         // 0.0
/*228 */                                  s->linesize, s->linesize,                                                         // 0.0
/*230 */                                  17 + s->mspel * 2, 17 + s->mspel * 2,                                             // 0.0
/*232 */                                  src_x - s->mspel, src_y - s->mspel,                                               // 0.0
/*234 */                                  s->h_edge_pos, v_edge_pos);                                                       // 0.0
/*236 */         srcY = s->edge_emu_buffer;                                                                                 // 0.0
/*238 */         s->vdsp.emulated_edge_mc(uvbuf, srcU,                                                                      // 0.0
/*240 */                                  s->uvlinesize, s->uvlinesize,                                                     // 0.0
/*242 */                                  8 + 1, 8 + 1,                                                                     // 0.0
/*244 */                                  uvsrc_x, uvsrc_y, s->h_edge_pos >> 1, v_edge_pos >> 1);                           // 0.0
/*246 */         s->vdsp.emulated_edge_mc(uvbuf + 16, srcV,                                                                 // 0.0
/*248 */                                  s->uvlinesize, s->uvlinesize,                                                     // 0.0
/*250 */                                  8 + 1, 8 + 1,                                                                     // 0.0
/*252 */                                  uvsrc_x, uvsrc_y, s->h_edge_pos >> 1, v_edge_pos >> 1);                           // 0.0
/*254 */         srcU = uvbuf;                                                                                              // 0.0
/*256 */         srcV = uvbuf + 16;                                                                                         // 0.0
/*258 */         /* if we deal with range reduction we need to scale source blocks */                                       // 0.0
/*260 */         if (v->rangeredfrm) {                                                                                      // 0.0
/*262 */             int i, j;                                                                                              // 0.0
/*264 */             uint8_t *src, *src2;                                                                                   // 0.0
/*268 */             src = srcY;                                                                                            // 0.0
/*270 */             for (j = 0; j < 17 + s->mspel * 2; j++) {                                                              // 0.0
/*272 */                 for (i = 0; i < 17 + s->mspel * 2; i++)                                                            // 0.0
/*274 */                     src[i] = ((src[i] - 128) >> 1) + 128;                                                          // 0.0
/*276 */                 src += s->linesize;                                                                                // 0.0
/*278 */             }                                                                                                      // 0.0
/*280 */             src  = srcU;                                                                                           // 0.0
/*282 */             src2 = srcV;                                                                                           // 0.0
/*284 */             for (j = 0; j < 9; j++) {                                                                              // 0.0
/*286 */                 for (i = 0; i < 9; i++) {                                                                          // 0.0
/*288 */                     src[i]  = ((src[i]  - 128) >> 1) + 128;                                                        // 0.0
/*290 */                     src2[i] = ((src2[i] - 128) >> 1) + 128;                                                        // 0.0
/*292 */                 }                                                                                                  // 0.0
/*294 */                 src  += s->uvlinesize;                                                                             // 0.0
/*296 */                 src2 += s->uvlinesize;                                                                             // 0.0
/*298 */             }                                                                                                      // 0.0
/*300 */         }                                                                                                          // 0.0
/*302 */         /* if we deal with intensity compensation we need to scale source blocks */                                // 0.0
/*304 */         if (use_ic) {                                                                                              // 0.0
/*306 */             int i, j;                                                                                              // 0.0
/*308 */             uint8_t *src, *src2;                                                                                   // 0.0
/*312 */             src = srcY;                                                                                            // 0.0
/*314 */             for (j = 0; j < 17 + s->mspel * 2; j++) {                                                              // 0.0
/*316 */                 int f = v->field_mode ? v->ref_field_type[dir] : ((j + src_y - s->mspel) & 1) ;                    // 0.0
/*318 */                 for (i = 0; i < 17 + s->mspel * 2; i++)                                                            // 0.0
/*320 */                     src[i] = luty[f][src[i]];                                                                      // 0.0
/*322 */                 src += s->linesize;                                                                                // 0.0
/*324 */             }                                                                                                      // 0.0
/*326 */             src  = srcU;                                                                                           // 0.0
/*328 */             src2 = srcV;                                                                                           // 0.0
/*330 */             for (j = 0; j < 9; j++) {                                                                              // 0.0
/*332 */                 int f = v->field_mode ? v->ref_field_type[dir] : ((j + uvsrc_y) & 1);                              // 0.0
/*334 */                 for (i = 0; i < 9; i++) {                                                                          // 0.0
/*336 */                     src[i]  = lutuv[f][src[i]];                                                                    // 0.0
/*338 */                     src2[i] = lutuv[f][src2[i]];                                                                   // 0.0
/*340 */                 }                                                                                                  // 0.0
/*342 */                 src  += s->uvlinesize;                                                                             // 0.0
/*344 */                 src2 += s->uvlinesize;                                                                             // 0.0
/*346 */             }                                                                                                      // 0.0
/*348 */         }                                                                                                          // 0.0
/*350 */         srcY += s->mspel * (1 + s->linesize);                                                                      // 0.0
/*352 */     }                                                                                                              // 0.0
/*356 */     if (s->mspel) {                                                                                                // 0.0
/*358 */         dxy = ((my & 3) << 2) | (mx & 3);                                                                          // 0.0
/*360 */         v->vc1dsp.put_vc1_mspel_pixels_tab[dxy](s->dest[0]    , srcY    , s->linesize, v->rnd);                    // 0.0
/*362 */         v->vc1dsp.put_vc1_mspel_pixels_tab[dxy](s->dest[0] + 8, srcY + 8, s->linesize, v->rnd);                    // 0.0
/*364 */         srcY += s->linesize * 8;                                                                                   // 0.0
/*366 */         v->vc1dsp.put_vc1_mspel_pixels_tab[dxy](s->dest[0] + 8 * s->linesize    , srcY    , s->linesize, v->rnd);  // 0.0
/*368 */         v->vc1dsp.put_vc1_mspel_pixels_tab[dxy](s->dest[0] + 8 * s->linesize + 8, srcY + 8, s->linesize, v->rnd);  // 0.0
/*370 */     } else { // hpel mc - always used for luma                                                                     // 0.0
/*372 */         dxy = (my & 2) | ((mx & 2) >> 1);                                                                          // 0.0
/*374 */         if (!v->rnd)                                                                                               // 0.0
/*376 */             s->hdsp.put_pixels_tab[0][dxy](s->dest[0], srcY, s->linesize, 16);                                     // 0.0
/*378 */         else                                                                                                       // 0.0
/*380 */             s->hdsp.put_no_rnd_pixels_tab[0][dxy](s->dest[0], srcY, s->linesize, 16);                              // 0.0
/*382 */     }                                                                                                              // 0.0
/*386 */     if (s->flags & CODEC_FLAG_GRAY) return;                                                                        // 0.0
/*388 */     /* Chroma MC always uses qpel bilinear */                                                                      // 0.0
/*390 */     uvmx = (uvmx & 3) << 1;                                                                                        // 0.0
/*392 */     uvmy = (uvmy & 3) << 1;                                                                                        // 0.0
/*394 */     if (!v->rnd) {                                                                                                 // 0.0
/*396 */         h264chroma->put_h264_chroma_pixels_tab[0](s->dest[1], srcU, s->uvlinesize, 8, uvmx, uvmy);                 // 0.0
/*398 */         h264chroma->put_h264_chroma_pixels_tab[0](s->dest[2], srcV, s->uvlinesize, 8, uvmx, uvmy);                 // 0.0
/*400 */     } else {                                                                                                       // 0.0
/*402 */         v->vc1dsp.put_no_rnd_vc1_chroma_pixels_tab[0](s->dest[1], srcU, s->uvlinesize, 8, uvmx, uvmy);             // 0.0
/*404 */         v->vc1dsp.put_no_rnd_vc1_chroma_pixels_tab[0](s->dest[2], srcV, s->uvlinesize, 8, uvmx, uvmy);             // 0.0
/*406 */     }                                                                                                              // 0.0
/*408 */ }                                                                                                                  // 0.0

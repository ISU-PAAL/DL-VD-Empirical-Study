// commit message FFmpeg@ccce723c6d (target=0, prob=0.7883904, correct=False): vc1dec: check first field slices, fix out of array read.
/*0   */ static int vc1_decode_frame(AVCodecContext *avctx, void *data,                                                               // (6) 0.04492
/*2   */                             int *data_size, AVPacket *avpkt)                                                                 // (0) 0.08008
/*4   */ {                                                                                                                            // (26) 0.001953
/*6   */     const uint8_t *buf = avpkt->data;                                                                                        // (11) 0.0332
/*8   */     int buf_size = avpkt->size, n_slices = 0, i;                                                                             // (4) 0.04687
/*10  */     VC1Context *v = avctx->priv_data;                                                                                        // (12) 0.03125
/*12  */     MpegEncContext *s = &v->s;                                                                                               // (13) 0.0293
/*14  */     AVFrame *pict = data;                                                                                                    // (22) 0.01953
/*16  */     uint8_t *buf2 = NULL;                                                                                                    // (20) 0.02539
/*18  */     const uint8_t *buf_start = buf, *buf_start_second_field = NULL;                                                          // (2) 0.05078
/*20  */     int mb_height, n_slices1=-1;                                                                                             // (10) 0.03516
/*22  */     struct {                                                                                                                 // (25) 0.009766
/*24  */         uint8_t *buf;                                                                                                        // (16) 0.02734
/*26  */         GetBitContext gb;                                                                                                    // (18) 0.02539
/*28  */         int mby_start;                                                                                                       // (19) 0.02539
/*30  */     } *slices = NULL, *tmp;                                                                                                  // (15) 0.02734
/*34  */     v->second_field = 0;                                                                                                     // (21) 0.02148
/*38  */     if(s->flags & CODEC_FLAG_LOW_DELAY)                                                                                      // (7) 0.04297
/*40  */         s->low_delay = 1;                                                                                                    // (14) 0.0293
/*44  */     /* no supplementary picture */                                                                                           // (23) 0.01562
/*46  */     if (buf_size == 0 || (buf_size == 4 && AV_RB32(buf) == VC1_CODE_ENDOFSEQ)) {                                             // (1) 0.07422
/*48  */         /* special case for last picture */                                                                                  // (17) 0.02734
/*50  */         if (s->low_delay == 0 && s->next_picture_ptr) {                                                                      // (3) 0.05078
/*52  */             *pict = s->next_picture_ptr->f;                                                                                  // (5) 0.04687
/*54  */             s->next_picture_ptr = NULL;                                                                                      // (9) 0.04102
/*58  */             *data_size = sizeof(AVFrame);                                                                                    // (8) 0.04102
/*60  */         }                                                                                                                    // (24) 0.01562
/*64  */         return buf_size;                                                                                                     // 0.0
/*66  */     }                                                                                                                        // 0.0
/*70  */     if (s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU) {                                                             // 0.0
/*72  */         if (v->profile < PROFILE_ADVANCED)                                                                                   // 0.0
/*74  */             avctx->pix_fmt = AV_PIX_FMT_VDPAU_WMV3;                                                                          // 0.0
/*76  */         else                                                                                                                 // 0.0
/*78  */             avctx->pix_fmt = AV_PIX_FMT_VDPAU_VC1;                                                                           // 0.0
/*80  */     }                                                                                                                        // 0.0
/*84  */     //for advanced profile we may need to parse and unescape data                                                            // 0.0
/*86  */     if (avctx->codec_id == AV_CODEC_ID_VC1 || avctx->codec_id == AV_CODEC_ID_VC1IMAGE) {                                     // 0.0
/*88  */         int buf_size2 = 0;                                                                                                   // 0.0
/*90  */         buf2 = av_mallocz(buf_size + FF_INPUT_BUFFER_PADDING_SIZE);                                                          // 0.0
/*94  */         if (IS_MARKER(AV_RB32(buf))) { /* frame starts with marker and needs to be parsed */                                 // 0.0
/*96  */             const uint8_t *start, *end, *next;                                                                               // 0.0
/*98  */             int size;                                                                                                        // 0.0
/*102 */             next = buf;                                                                                                      // 0.0
/*104 */             for (start = buf, end = buf + buf_size; next < end; start = next) {                                              // 0.0
/*106 */                 next = find_next_marker(start + 4, end);                                                                     // 0.0
/*108 */                 size = next - start - 4;                                                                                     // 0.0
/*110 */                 if (size <= 0) continue;                                                                                     // 0.0
/*112 */                 switch (AV_RB32(start)) {                                                                                    // 0.0
/*114 */                 case VC1_CODE_FRAME:                                                                                         // 0.0
/*116 */                     if (avctx->hwaccel ||                                                                                    // 0.0
/*118 */                         s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU)                                               // 0.0
/*120 */                         buf_start = start;                                                                                   // 0.0
/*122 */                     buf_size2 = vc1_unescape_buffer(start + 4, size, buf2);                                                  // 0.0
/*124 */                     break;                                                                                                   // 0.0
/*126 */                 case VC1_CODE_FIELD: {                                                                                       // 0.0
/*128 */                     int buf_size3;                                                                                           // 0.0
/*130 */                     if (avctx->hwaccel ||                                                                                    // 0.0
/*132 */                         s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU)                                               // 0.0
/*134 */                         buf_start_second_field = start;                                                                      // 0.0
/*136 */                     tmp = av_realloc(slices, sizeof(*slices) * (n_slices+1));                                                // 0.0
/*138 */                     if (!tmp)                                                                                                // 0.0
/*140 */                         goto err;                                                                                            // 0.0
/*142 */                     slices = tmp;                                                                                            // 0.0
/*144 */                     slices[n_slices].buf = av_mallocz(buf_size + FF_INPUT_BUFFER_PADDING_SIZE);                              // 0.0
/*146 */                     if (!slices[n_slices].buf)                                                                               // 0.0
/*148 */                         goto err;                                                                                            // 0.0
/*150 */                     buf_size3 = vc1_unescape_buffer(start + 4, size,                                                         // 0.0
/*152 */                                                     slices[n_slices].buf);                                                   // 0.0
/*154 */                     init_get_bits(&slices[n_slices].gb, slices[n_slices].buf,                                                // 0.0
/*156 */                                   buf_size3 << 3);                                                                           // 0.0
/*158 */                     /* assuming that the field marker is at the exact middle,                                                // 0.0
/*160 */                        hope it's correct */                                                                                  // 0.0
/*162 */                     slices[n_slices].mby_start = s->mb_height >> 1;                                                          // 0.0
/*164 */                     n_slices1 = n_slices - 1; // index of the last slice of the first field                                  // 0.0
/*166 */                     n_slices++;                                                                                              // 0.0
/*168 */                     break;                                                                                                   // 0.0
/*170 */                 }                                                                                                            // 0.0
/*172 */                 case VC1_CODE_ENTRYPOINT: /* it should be before frame data */                                               // 0.0
/*174 */                     buf_size2 = vc1_unescape_buffer(start + 4, size, buf2);                                                  // 0.0
/*176 */                     init_get_bits(&s->gb, buf2, buf_size2 * 8);                                                              // 0.0
/*178 */                     ff_vc1_decode_entry_point(avctx, v, &s->gb);                                                             // 0.0
/*180 */                     break;                                                                                                   // 0.0
/*182 */                 case VC1_CODE_SLICE: {                                                                                       // 0.0
/*184 */                     int buf_size3;                                                                                           // 0.0
/*186 */                     tmp = av_realloc(slices, sizeof(*slices) * (n_slices+1));                                                // 0.0
/*188 */                     if (!tmp)                                                                                                // 0.0
/*190 */                         goto err;                                                                                            // 0.0
/*192 */                     slices = tmp;                                                                                            // 0.0
/*194 */                     slices[n_slices].buf = av_mallocz(buf_size + FF_INPUT_BUFFER_PADDING_SIZE);                              // 0.0
/*196 */                     if (!slices[n_slices].buf)                                                                               // 0.0
/*198 */                         goto err;                                                                                            // 0.0
/*200 */                     buf_size3 = vc1_unescape_buffer(start + 4, size,                                                         // 0.0
/*202 */                                                     slices[n_slices].buf);                                                   // 0.0
/*204 */                     init_get_bits(&slices[n_slices].gb, slices[n_slices].buf,                                                // 0.0
/*206 */                                   buf_size3 << 3);                                                                           // 0.0
/*208 */                     slices[n_slices].mby_start = get_bits(&slices[n_slices].gb, 9);                                          // 0.0
/*210 */                     n_slices++;                                                                                              // 0.0
/*212 */                     break;                                                                                                   // 0.0
/*214 */                 }                                                                                                            // 0.0
/*216 */                 }                                                                                                            // 0.0
/*218 */             }                                                                                                                // 0.0
/*220 */         } else if (v->interlace && ((buf[0] & 0xC0) == 0xC0)) { /* WVC1 interlaced stores both fields divided by marker */   // 0.0
/*222 */             const uint8_t *divider;                                                                                          // 0.0
/*224 */             int buf_size3;                                                                                                   // 0.0
/*228 */             divider = find_next_marker(buf, buf + buf_size);                                                                 // 0.0
/*230 */             if ((divider == (buf + buf_size)) || AV_RB32(divider) != VC1_CODE_FIELD) {                                       // 0.0
/*232 */                 av_log(avctx, AV_LOG_ERROR, "Error in WVC1 interlaced frame\n");                                             // 0.0
/*234 */                 goto err;                                                                                                    // 0.0
/*236 */             } else { // found field marker, unescape second field                                                            // 0.0
/*238 */                 if (avctx->hwaccel ||                                                                                        // 0.0
/*240 */                     s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU)                                                   // 0.0
/*242 */                     buf_start_second_field = divider;                                                                        // 0.0
/*244 */                 tmp = av_realloc(slices, sizeof(*slices) * (n_slices+1));                                                    // 0.0
/*246 */                 if (!tmp)                                                                                                    // 0.0
/*248 */                     goto err;                                                                                                // 0.0
/*250 */                 slices = tmp;                                                                                                // 0.0
/*252 */                 slices[n_slices].buf = av_mallocz(buf_size + FF_INPUT_BUFFER_PADDING_SIZE);                                  // 0.0
/*254 */                 if (!slices[n_slices].buf)                                                                                   // 0.0
/*256 */                     goto err;                                                                                                // 0.0
/*258 */                 buf_size3 = vc1_unescape_buffer(divider + 4, buf + buf_size - divider - 4, slices[n_slices].buf);            // 0.0
/*260 */                 init_get_bits(&slices[n_slices].gb, slices[n_slices].buf,                                                    // 0.0
/*262 */                               buf_size3 << 3);                                                                               // 0.0
/*264 */                 slices[n_slices].mby_start = s->mb_height >> 1;                                                              // 0.0
/*266 */                 n_slices1 = n_slices - 1;                                                                                    // 0.0
/*268 */                 n_slices++;                                                                                                  // 0.0
/*270 */             }                                                                                                                // 0.0
/*272 */             buf_size2 = vc1_unescape_buffer(buf, divider - buf, buf2);                                                       // 0.0
/*274 */         } else {                                                                                                             // 0.0
/*276 */             buf_size2 = vc1_unescape_buffer(buf, buf_size, buf2);                                                            // 0.0
/*278 */         }                                                                                                                    // 0.0
/*280 */         init_get_bits(&s->gb, buf2, buf_size2*8);                                                                            // 0.0
/*282 */     } else                                                                                                                   // 0.0
/*284 */         init_get_bits(&s->gb, buf, buf_size*8);                                                                              // 0.0
/*288 */     if (v->res_sprite) {                                                                                                     // 0.0
/*290 */         v->new_sprite  = !get_bits1(&s->gb);                                                                                 // 0.0
/*292 */         v->two_sprites =  get_bits1(&s->gb);                                                                                 // 0.0
/*294 */         /* res_sprite means a Windows Media Image stream, AV_CODEC_ID_*IMAGE means                                           // 0.0
/*296 */            we're using the sprite compositor. These are intentionally kept separate                                          // 0.0
/*298 */            so you can get the raw sprites by using the wmv3 decoder for WMVP or                                              // 0.0
/*300 */            the vc1 one for WVP2 */                                                                                           // 0.0
/*302 */         if (avctx->codec_id == AV_CODEC_ID_WMV3IMAGE || avctx->codec_id == AV_CODEC_ID_VC1IMAGE) {                           // 0.0
/*304 */             if (v->new_sprite) {                                                                                             // 0.0
/*306 */                 // switch AVCodecContext parameters to those of the sprites                                                  // 0.0
/*308 */                 avctx->width  = avctx->coded_width  = v->sprite_width;                                                       // 0.0
/*310 */                 avctx->height = avctx->coded_height = v->sprite_height;                                                      // 0.0
/*312 */             } else {                                                                                                         // 0.0
/*314 */                 goto image;                                                                                                  // 0.0
/*316 */             }                                                                                                                // 0.0
/*318 */         }                                                                                                                    // 0.0
/*320 */     }                                                                                                                        // 0.0
/*324 */     if (s->context_initialized &&                                                                                            // 0.0
/*326 */         (s->width  != avctx->coded_width ||                                                                                  // 0.0
/*328 */          s->height != avctx->coded_height)) {                                                                                // 0.0
/*330 */         ff_vc1_decode_end(avctx);                                                                                            // 0.0
/*332 */     }                                                                                                                        // 0.0
/*336 */     if (!s->context_initialized) {                                                                                           // 0.0
/*338 */         if (ff_msmpeg4_decode_init(avctx) < 0 || ff_vc1_decode_init_alloc_tables(v) < 0)                                     // 0.0
/*340 */             goto err;                                                                                                        // 0.0
/*344 */         s->low_delay = !avctx->has_b_frames || v->res_sprite;                                                                // 0.0
/*348 */         if (v->profile == PROFILE_ADVANCED) {                                                                                // 0.0
/*350 */             s->h_edge_pos = avctx->coded_width;                                                                              // 0.0
/*352 */             s->v_edge_pos = avctx->coded_height;                                                                             // 0.0
/*354 */         }                                                                                                                    // 0.0
/*356 */     }                                                                                                                        // 0.0
/*360 */     /* We need to set current_picture_ptr before reading the header,                                                         // 0.0
/*362 */      * otherwise we cannot store anything in there. */                                                                       // 0.0
/*364 */     if (s->current_picture_ptr == NULL || s->current_picture_ptr->f.data[0]) {                                               // 0.0
/*366 */         int i = ff_find_unused_picture(s, 0);                                                                                // 0.0
/*368 */         if (i < 0)                                                                                                           // 0.0
/*370 */             goto err;                                                                                                        // 0.0
/*372 */         s->current_picture_ptr = &s->picture[i];                                                                             // 0.0
/*374 */     }                                                                                                                        // 0.0
/*378 */     // do parse frame header                                                                                                 // 0.0
/*380 */     v->pic_header_flag = 0;                                                                                                  // 0.0
/*382 */     if (v->profile < PROFILE_ADVANCED) {                                                                                     // 0.0
/*384 */         if (ff_vc1_parse_frame_header(v, &s->gb) < 0) {                                                                      // 0.0
/*386 */             goto err;                                                                                                        // 0.0
/*388 */         }                                                                                                                    // 0.0
/*390 */     } else {                                                                                                                 // 0.0
/*392 */         if (ff_vc1_parse_frame_header_adv(v, &s->gb) < 0) {                                                                  // 0.0
/*394 */             goto err;                                                                                                        // 0.0
/*396 */         }                                                                                                                    // 0.0
/*398 */     }                                                                                                                        // 0.0
/*402 */     if (avctx->debug & FF_DEBUG_PICT_INFO)                                                                                   // 0.0
/*404 */         av_log(v->s.avctx, AV_LOG_DEBUG, "pict_type: %c\n", av_get_picture_type_char(s->pict_type));                         // 0.0
/*408 */     if ((avctx->codec_id == AV_CODEC_ID_WMV3IMAGE || avctx->codec_id == AV_CODEC_ID_VC1IMAGE)                                // 0.0
/*410 */         && s->pict_type != AV_PICTURE_TYPE_I) {                                                                              // 0.0
/*412 */         av_log(v->s.avctx, AV_LOG_ERROR, "Sprite decoder: expected I-frame\n");                                              // 0.0
/*414 */         goto err;                                                                                                            // 0.0
/*416 */     }                                                                                                                        // 0.0
/*420 */     if ((s->mb_height >> v->field_mode) == 0) {                                                                              // 0.0
/*422 */         av_log(v->s.avctx, AV_LOG_ERROR, "image too short\n");                                                               // 0.0
/*424 */         goto err;                                                                                                            // 0.0
/*426 */     }                                                                                                                        // 0.0
/*430 */     // process pulldown flags                                                                                                // 0.0
/*432 */     s->current_picture_ptr->f.repeat_pict = 0;                                                                               // 0.0
/*434 */     // Pulldown flags are only valid when 'broadcast' has been set.                                                          // 0.0
/*436 */     // So ticks_per_frame will be 2                                                                                          // 0.0
/*438 */     if (v->rff) {                                                                                                            // 0.0
/*440 */         // repeat field                                                                                                      // 0.0
/*442 */         s->current_picture_ptr->f.repeat_pict = 1;                                                                           // 0.0
/*444 */     } else if (v->rptfrm) {                                                                                                  // 0.0
/*446 */         // repeat frames                                                                                                     // 0.0
/*448 */         s->current_picture_ptr->f.repeat_pict = v->rptfrm * 2;                                                               // 0.0
/*450 */     }                                                                                                                        // 0.0
/*454 */     // for skipping the frame                                                                                                // 0.0
/*456 */     s->current_picture.f.pict_type = s->pict_type;                                                                           // 0.0
/*458 */     s->current_picture.f.key_frame = s->pict_type == AV_PICTURE_TYPE_I;                                                      // 0.0
/*462 */     /* skip B-frames if we don't have reference frames */                                                                    // 0.0
/*464 */     if (s->last_picture_ptr == NULL && (s->pict_type == AV_PICTURE_TYPE_B || s->dropable)) {                                 // 0.0
/*466 */         goto err;                                                                                                            // 0.0
/*468 */     }                                                                                                                        // 0.0
/*470 */     if ((avctx->skip_frame >= AVDISCARD_NONREF && s->pict_type == AV_PICTURE_TYPE_B) ||                                      // 0.0
/*472 */         (avctx->skip_frame >= AVDISCARD_NONKEY && s->pict_type != AV_PICTURE_TYPE_I) ||                                      // 0.0
/*474 */          avctx->skip_frame >= AVDISCARD_ALL) {                                                                               // 0.0
/*476 */         goto end;                                                                                                            // 0.0
/*478 */     }                                                                                                                        // 0.0
/*482 */     if (s->next_p_frame_damaged) {                                                                                           // 0.0
/*484 */         if (s->pict_type == AV_PICTURE_TYPE_B)                                                                               // 0.0
/*486 */             goto end;                                                                                                        // 0.0
/*488 */         else                                                                                                                 // 0.0
/*490 */             s->next_p_frame_damaged = 0;                                                                                     // 0.0
/*492 */     }                                                                                                                        // 0.0
/*496 */     if (ff_MPV_frame_start(s, avctx) < 0) {                                                                                  // 0.0
/*498 */         goto err;                                                                                                            // 0.0
/*500 */     }                                                                                                                        // 0.0
/*504 */     v->s.current_picture_ptr->f.interlaced_frame = (v->fcm != PROGRESSIVE);                                                  // 0.0
/*506 */     v->s.current_picture_ptr->f.top_field_first  = v->tff;                                                                   // 0.0
/*510 */     s->me.qpel_put = s->dsp.put_qpel_pixels_tab;                                                                             // 0.0
/*512 */     s->me.qpel_avg = s->dsp.avg_qpel_pixels_tab;                                                                             // 0.0
/*516 */     if ((CONFIG_VC1_VDPAU_DECODER)                                                                                           // 0.0
/*518 */         &&s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU)                                                             // 0.0
/*520 */         ff_vdpau_vc1_decode_picture(s, buf_start, (buf + buf_size) - buf_start);                                             // 0.0
/*522 */     else if (avctx->hwaccel) {                                                                                               // 0.0
/*524 */         if (v->field_mode && buf_start_second_field) {                                                                       // 0.0
/*526 */             // decode first field                                                                                            // 0.0
/*528 */             s->picture_structure = PICT_BOTTOM_FIELD - v->tff;                                                               // 0.0
/*530 */             if (avctx->hwaccel->start_frame(avctx, buf_start, buf_start_second_field - buf_start) < 0)                       // 0.0
/*532 */                 goto err;                                                                                                    // 0.0
/*534 */             if (avctx->hwaccel->decode_slice(avctx, buf_start, buf_start_second_field - buf_start) < 0)                      // 0.0
/*536 */                 goto err;                                                                                                    // 0.0
/*538 */             if (avctx->hwaccel->end_frame(avctx) < 0)                                                                        // 0.0
/*540 */                 goto err;                                                                                                    // 0.0
/*544 */             // decode second field                                                                                           // 0.0
/*546 */             s->gb = slices[n_slices1 + 1].gb;                                                                                // 0.0
/*548 */             s->picture_structure = PICT_TOP_FIELD + v->tff;                                                                  // 0.0
/*550 */             v->second_field = 1;                                                                                             // 0.0
/*552 */             v->pic_header_flag = 0;                                                                                          // 0.0
/*554 */             if (ff_vc1_parse_frame_header_adv(v, &s->gb) < 0) {                                                              // 0.0
/*556 */                 av_log(avctx, AV_LOG_ERROR, "parsing header for second field failed");                                       // 0.0
/*558 */                 goto err;                                                                                                    // 0.0
/*560 */             }                                                                                                                // 0.0
/*562 */             v->s.current_picture_ptr->f.pict_type = v->s.pict_type;                                                          // 0.0
/*566 */             if (avctx->hwaccel->start_frame(avctx, buf_start_second_field, (buf + buf_size) - buf_start_second_field) < 0)   // 0.0
/*568 */                 goto err;                                                                                                    // 0.0
/*570 */             if (avctx->hwaccel->decode_slice(avctx, buf_start_second_field, (buf + buf_size) - buf_start_second_field) < 0)  // 0.0
/*572 */                 goto err;                                                                                                    // 0.0
/*574 */             if (avctx->hwaccel->end_frame(avctx) < 0)                                                                        // 0.0
/*576 */                 goto err;                                                                                                    // 0.0
/*578 */         } else {                                                                                                             // 0.0
/*580 */             s->picture_structure = PICT_FRAME;                                                                               // 0.0
/*582 */             if (avctx->hwaccel->start_frame(avctx, buf_start, (buf + buf_size) - buf_start) < 0)                             // 0.0
/*584 */                 goto err;                                                                                                    // 0.0
/*586 */             if (avctx->hwaccel->decode_slice(avctx, buf_start, (buf + buf_size) - buf_start) < 0)                            // 0.0
/*588 */                 goto err;                                                                                                    // 0.0
/*590 */             if (avctx->hwaccel->end_frame(avctx) < 0)                                                                        // 0.0
/*592 */                 goto err;                                                                                                    // 0.0
/*594 */         }                                                                                                                    // 0.0
/*596 */     } else {                                                                                                                 // 0.0
/*598 */         if (v->fcm == ILACE_FRAME && s->pict_type == AV_PICTURE_TYPE_B)                                                      // 0.0
/*600 */             goto err; // This codepath is still incomplete thus it is disabled                                               // 0.0
/*604 */         ff_er_frame_start(s);                                                                                                // 0.0
/*608 */         v->bits = buf_size * 8;                                                                                              // 0.0
/*610 */         v->end_mb_x = s->mb_width;                                                                                           // 0.0
/*612 */         if (v->field_mode) {                                                                                                 // 0.0
/*614 */             uint8_t *tmp[2];                                                                                                 // 0.0
/*616 */             s->current_picture.f.linesize[0] <<= 1;                                                                          // 0.0
/*618 */             s->current_picture.f.linesize[1] <<= 1;                                                                          // 0.0
/*620 */             s->current_picture.f.linesize[2] <<= 1;                                                                          // 0.0
/*622 */             s->linesize                      <<= 1;                                                                          // 0.0
/*624 */             s->uvlinesize                    <<= 1;                                                                          // 0.0
/*626 */             tmp[0]          = v->mv_f_last[0];                                                                               // 0.0
/*628 */             tmp[1]          = v->mv_f_last[1];                                                                               // 0.0
/*630 */             v->mv_f_last[0] = v->mv_f_next[0];                                                                               // 0.0
/*632 */             v->mv_f_last[1] = v->mv_f_next[1];                                                                               // 0.0
/*634 */             v->mv_f_next[0] = v->mv_f[0];                                                                                    // 0.0
/*636 */             v->mv_f_next[1] = v->mv_f[1];                                                                                    // 0.0
/*638 */             v->mv_f[0] = tmp[0];                                                                                             // 0.0
/*640 */             v->mv_f[1] = tmp[1];                                                                                             // 0.0
/*642 */         }                                                                                                                    // 0.0
/*644 */         mb_height = s->mb_height >> v->field_mode;                                                                           // 0.0
/*646 */         for (i = 0; i <= n_slices; i++) {                                                                                    // 0.0
/*648 */             if (i > 0 &&  slices[i - 1].mby_start >= mb_height) {                                                            // 0.0
/*650 */                 if (v->field_mode <= 0) {                                                                                    // 0.0
/*652 */                     av_log(v->s.avctx, AV_LOG_ERROR, "Slice %d starts beyond "                                               // 0.0
/*654 */                            "picture boundary (%d >= %d)\n", i,                                                               // 0.0
/*656 */                            slices[i - 1].mby_start, mb_height);                                                              // 0.0
/*658 */                     continue;                                                                                                // 0.0
/*660 */                 }                                                                                                            // 0.0
/*662 */                 v->second_field = 1;                                                                                         // 0.0
/*664 */                 v->blocks_off   = s->mb_width  * s->mb_height << 1;                                                          // 0.0
/*666 */                 v->mb_off       = s->mb_stride * s->mb_height >> 1;                                                          // 0.0
/*668 */             } else {                                                                                                         // 0.0
/*670 */                 v->second_field = 0;                                                                                         // 0.0
/*672 */                 v->blocks_off   = 0;                                                                                         // 0.0
/*674 */                 v->mb_off       = 0;                                                                                         // 0.0
/*676 */             }                                                                                                                // 0.0
/*678 */             if (i) {                                                                                                         // 0.0
/*680 */                 v->pic_header_flag = 0;                                                                                      // 0.0
/*682 */                 if (v->field_mode && i == n_slices1 + 2) {                                                                   // 0.0
/*684 */                     if (ff_vc1_parse_frame_header_adv(v, &s->gb) < 0) {                                                      // 0.0
/*686 */                         av_log(v->s.avctx, AV_LOG_ERROR, "Field header damaged\n");                                          // 0.0
/*688 */                         continue;                                                                                            // 0.0
/*690 */                     }                                                                                                        // 0.0
/*692 */                 } else if (get_bits1(&s->gb)) {                                                                              // 0.0
/*694 */                     v->pic_header_flag = 1;                                                                                  // 0.0
/*696 */                     if (ff_vc1_parse_frame_header_adv(v, &s->gb) < 0) {                                                      // 0.0
/*698 */                         av_log(v->s.avctx, AV_LOG_ERROR, "Slice header damaged\n");                                          // 0.0
/*700 */                         continue;                                                                                            // 0.0
/*702 */                     }                                                                                                        // 0.0
/*704 */                 }                                                                                                            // 0.0
/*706 */             }                                                                                                                // 0.0
/*708 */             s->start_mb_y = (i == 0) ? 0 : FFMAX(0, slices[i-1].mby_start % mb_height);                                      // 0.0
/*710 */             if (!v->field_mode || v->second_field)                                                                           // 0.0
/*712 */                 s->end_mb_y = (i == n_slices     ) ? mb_height : FFMIN(mb_height, slices[i].mby_start % mb_height);          // 0.0
/*714 */             else                                                                                                             // 0.0
/*716 */                 s->end_mb_y = (i <= n_slices1 + 1) ? mb_height : FFMIN(mb_height, slices[i].mby_start % mb_height);          // 0.0
/*718 */             if (s->end_mb_y <= s->start_mb_y) {                                                                              // 0.0
/*720 */                 av_log(v->s.avctx, AV_LOG_ERROR, "end mb y %d %d invalid\n", s->end_mb_y, s->start_mb_y);                    // 0.0
/*722 */                 continue;                                                                                                    // 0.0
/*724 */             }                                                                                                                // 0.0
/*726 */             ff_vc1_decode_blocks(v);                                                                                         // 0.0
/*728 */             if (i != n_slices)                                                                                               // 0.0
/*730 */                 s->gb = slices[i].gb;                                                                                        // 0.0
/*732 */         }                                                                                                                    // 0.0
/*734 */         if (v->field_mode) {                                                                                                 // 0.0
/*736 */             v->second_field = 0;                                                                                             // 0.0
/*738 */             if (s->pict_type == AV_PICTURE_TYPE_B) {                                                                         // 0.0
/*740 */                 memcpy(v->mv_f_base, v->mv_f_next_base,                                                                      // 0.0
/*742 */                        2 * (s->b8_stride * (s->mb_height * 2 + 1) + s->mb_stride * (s->mb_height + 1) * 2));                 // 0.0
/*744 */             }                                                                                                                // 0.0
/*746 */             s->current_picture.f.linesize[0] >>= 1;                                                                          // 0.0
/*748 */             s->current_picture.f.linesize[1] >>= 1;                                                                          // 0.0
/*750 */             s->current_picture.f.linesize[2] >>= 1;                                                                          // 0.0
/*752 */             s->linesize                      >>= 1;                                                                          // 0.0
/*754 */             s->uvlinesize                    >>= 1;                                                                          // 0.0
/*756 */         }                                                                                                                    // 0.0
/*758 */         av_dlog(s->avctx, "Consumed %i/%i bits\n",                                                                           // 0.0
/*760 */                 get_bits_count(&s->gb), s->gb.size_in_bits);                                                                 // 0.0
/*762 */ //  if (get_bits_count(&s->gb) > buf_size * 8)                                                                               // 0.0
/*764 */ //      return -1;                                                                                                           // 0.0
/*766 */         if(s->error_occurred && s->pict_type == AV_PICTURE_TYPE_B)                                                           // 0.0
/*768 */             goto err;                                                                                                        // 0.0
/*770 */         if(!v->field_mode)                                                                                                   // 0.0
/*772 */             ff_er_frame_end(s);                                                                                              // 0.0
/*774 */     }                                                                                                                        // 0.0
/*778 */     ff_MPV_frame_end(s);                                                                                                     // 0.0
/*782 */     if (avctx->codec_id == AV_CODEC_ID_WMV3IMAGE || avctx->codec_id == AV_CODEC_ID_VC1IMAGE) {                               // 0.0
/*784 */ image:                                                                                                                       // 0.0
/*786 */         avctx->width  = avctx->coded_width  = v->output_width;                                                               // 0.0
/*788 */         avctx->height = avctx->coded_height = v->output_height;                                                              // 0.0
/*790 */         if (avctx->skip_frame >= AVDISCARD_NONREF)                                                                           // 0.0
/*792 */             goto end;                                                                                                        // 0.0
/*794 */ #if CONFIG_WMV3IMAGE_DECODER || CONFIG_VC1IMAGE_DECODER                                                                      // 0.0
/*796 */         if (vc1_decode_sprites(v, &s->gb))                                                                                   // 0.0
/*798 */             goto err;                                                                                                        // 0.0
/*800 */ #endif                                                                                                                       // 0.0
/*802 */         *pict      = v->sprite_output_frame;                                                                                 // 0.0
/*804 */         *data_size = sizeof(AVFrame);                                                                                        // 0.0
/*806 */     } else {                                                                                                                 // 0.0
/*808 */         if (s->pict_type == AV_PICTURE_TYPE_B || s->low_delay) {                                                             // 0.0
/*810 */             *pict = s->current_picture_ptr->f;                                                                               // 0.0
/*812 */         } else if (s->last_picture_ptr != NULL) {                                                                            // 0.0
/*814 */             *pict = s->last_picture_ptr->f;                                                                                  // 0.0
/*816 */         }                                                                                                                    // 0.0
/*818 */         if (s->last_picture_ptr || s->low_delay) {                                                                           // 0.0
/*820 */             *data_size = sizeof(AVFrame);                                                                                    // 0.0
/*822 */             ff_print_debug_info(s, pict);                                                                                    // 0.0
/*824 */         }                                                                                                                    // 0.0
/*826 */     }                                                                                                                        // 0.0
/*830 */ end:                                                                                                                         // 0.0
/*832 */     av_free(buf2);                                                                                                           // 0.0
/*834 */     for (i = 0; i < n_slices; i++)                                                                                           // 0.0
/*836 */         av_free(slices[i].buf);                                                                                              // 0.0
/*838 */     av_free(slices);                                                                                                         // 0.0
/*840 */     return buf_size;                                                                                                         // 0.0
/*844 */ err:                                                                                                                         // 0.0
/*846 */     av_free(buf2);                                                                                                           // 0.0
/*848 */     for (i = 0; i < n_slices; i++)                                                                                           // 0.0
/*850 */         av_free(slices[i].buf);                                                                                              // 0.0
/*852 */     av_free(slices);                                                                                                         // 0.0
/*854 */     return -1;                                                                                                               // 0.0
/*856 */ }                                                                                                                            // 0.0

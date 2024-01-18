// commit message FFmpeg@42361bdf51 (target=0, prob=0.53652495, correct=False): avcodec/mpegvideo: fix buffer clear code so it should work with negative linesizes
/*0   */ int ff_MPV_frame_start(MpegEncContext *s, AVCodecContext *avctx)                                              // (9) 0.04883
/*2   */ {                                                                                                             // (24) 0.001953
/*4   */     int i, ret;                                                                                               // (19) 0.01562
/*6   */     Picture *pic;                                                                                             // (21) 0.01367
/*8   */     s->mb_skipped = 0;                                                                                        // (16) 0.02344
/*12  */     if (!ff_thread_can_start_frame(avctx)) {                                                                  // (14) 0.03711
/*14  */         av_log(avctx, AV_LOG_ERROR, "Attempt to start a frame outside SETUP state\n");                        // (0) 0.06445
/*16  */         return -1;                                                                                            // (17) 0.02148
/*18  */     }                                                                                                         // (22) 0.007812
/*22  */     /* mark & release old frames */                                                                           // (18) 0.01953
/*24  */     if (s->pict_type != AV_PICTURE_TYPE_B && s->last_picture_ptr &&                                           // (4) 0.05664
/*26  */         s->last_picture_ptr != s->next_picture_ptr &&                                                         // (12) 0.04492
/*28  */         s->last_picture_ptr->f.buf[0]) {                                                                      // (13) 0.04297
/*30  */         ff_mpeg_unref_picture(s, s->last_picture_ptr);                                                        // (8) 0.05078
/*32  */     }                                                                                                         // (23) 0.007812
/*36  */     /* release forgotten pictures */                                                                          // (20) 0.01562
/*38  */     /* if (mpeg124/h263) */                                                                                   // (15) 0.02539
/*40  */     for (i = 0; i < MAX_PICTURE_COUNT; i++) {                                                                 // (11) 0.04492
/*42  */         if (&s->picture[i] != s->last_picture_ptr &&                                                          // (10) 0.04687
/*44  */             &s->picture[i] != s->next_picture_ptr &&                                                          // (7) 0.05273
/*46  */             s->picture[i].reference && !s->picture[i].needs_realloc) {                                        // (1) 0.0625
/*48  */             if (!(avctx->active_thread_type & FF_THREAD_FRAME))                                               // (2) 0.06055
/*50  */                 av_log(avctx, AV_LOG_ERROR,                                                                   // (6) 0.05469
/*52  */                        "releasing zombie picture\n");                                                         // (3) 0.05859
/*54  */             ff_mpeg_unref_picture(s, &s->picture[i]);                                                         // (5) 0.05664
/*56  */         }                                                                                                     // 0.0
/*58  */     }                                                                                                         // 0.0
/*62  */     ff_mpeg_unref_picture(s, &s->current_picture);                                                            // 0.0
/*66  */     release_unused_pictures(s);                                                                               // 0.0
/*70  */     if (s->current_picture_ptr &&                                                                             // 0.0
/*72  */         s->current_picture_ptr->f.buf[0] == NULL) {                                                           // 0.0
/*74  */         // we already have a unused image                                                                     // 0.0
/*76  */         // (maybe it was set before reading the header)                                                       // 0.0
/*78  */         pic = s->current_picture_ptr;                                                                         // 0.0
/*80  */     } else {                                                                                                  // 0.0
/*82  */         i   = ff_find_unused_picture(s, 0);                                                                   // 0.0
/*84  */         if (i < 0) {                                                                                          // 0.0
/*86  */             av_log(s->avctx, AV_LOG_ERROR, "no frame buffer available\n");                                    // 0.0
/*88  */             return i;                                                                                         // 0.0
/*90  */         }                                                                                                     // 0.0
/*92  */         pic = &s->picture[i];                                                                                 // 0.0
/*94  */     }                                                                                                         // 0.0
/*98  */     pic->reference = 0;                                                                                       // 0.0
/*100 */     if (!s->droppable) {                                                                                      // 0.0
/*102 */         if (s->pict_type != AV_PICTURE_TYPE_B)                                                                // 0.0
/*104 */             pic->reference = 3;                                                                               // 0.0
/*106 */     }                                                                                                         // 0.0
/*110 */     pic->f.coded_picture_number = s->coded_picture_number++;                                                  // 0.0
/*114 */     if (ff_alloc_picture(s, pic, 0) < 0)                                                                      // 0.0
/*116 */         return -1;                                                                                            // 0.0
/*120 */     s->current_picture_ptr = pic;                                                                             // 0.0
/*122 */     // FIXME use only the vars from current_pic                                                               // 0.0
/*124 */     s->current_picture_ptr->f.top_field_first = s->top_field_first;                                           // 0.0
/*126 */     if (s->codec_id == AV_CODEC_ID_MPEG1VIDEO ||                                                              // 0.0
/*128 */         s->codec_id == AV_CODEC_ID_MPEG2VIDEO) {                                                              // 0.0
/*130 */         if (s->picture_structure != PICT_FRAME)                                                               // 0.0
/*132 */             s->current_picture_ptr->f.top_field_first =                                                       // 0.0
/*134 */                 (s->picture_structure == PICT_TOP_FIELD) == s->first_field;                                   // 0.0
/*136 */     }                                                                                                         // 0.0
/*138 */     s->current_picture_ptr->f.interlaced_frame = !s->progressive_frame &&                                     // 0.0
/*140 */                                                  !s->progressive_sequence;                                    // 0.0
/*142 */     s->current_picture_ptr->field_picture      =  s->picture_structure != PICT_FRAME;                         // 0.0
/*146 */     s->current_picture_ptr->f.pict_type = s->pict_type;                                                       // 0.0
/*148 */     // if (s->flags && CODEC_FLAG_QSCALE)                                                                     // 0.0
/*150 */     //     s->current_picture_ptr->quality = s->new_picture_ptr->quality;                                     // 0.0
/*152 */     s->current_picture_ptr->f.key_frame = s->pict_type == AV_PICTURE_TYPE_I;                                  // 0.0
/*156 */     if ((ret = ff_mpeg_ref_picture(s, &s->current_picture,                                                    // 0.0
/*158 */                                    s->current_picture_ptr)) < 0)                                              // 0.0
/*160 */         return ret;                                                                                           // 0.0
/*164 */     if (s->pict_type != AV_PICTURE_TYPE_B) {                                                                  // 0.0
/*166 */         s->last_picture_ptr = s->next_picture_ptr;                                                            // 0.0
/*168 */         if (!s->droppable)                                                                                    // 0.0
/*170 */             s->next_picture_ptr = s->current_picture_ptr;                                                     // 0.0
/*172 */     }                                                                                                         // 0.0
/*174 */     av_dlog(s->avctx, "L%p N%p C%p L%p N%p C%p type:%d drop:%d\n",                                            // 0.0
/*176 */             s->last_picture_ptr, s->next_picture_ptr,s->current_picture_ptr,                                  // 0.0
/*178 */             s->last_picture_ptr    ? s->last_picture_ptr->f.data[0]    : NULL,                                // 0.0
/*180 */             s->next_picture_ptr    ? s->next_picture_ptr->f.data[0]    : NULL,                                // 0.0
/*182 */             s->current_picture_ptr ? s->current_picture_ptr->f.data[0] : NULL,                                // 0.0
/*184 */             s->pict_type, s->droppable);                                                                      // 0.0
/*188 */     if ((s->last_picture_ptr == NULL ||                                                                       // 0.0
/*190 */          s->last_picture_ptr->f.buf[0] == NULL) &&                                                            // 0.0
/*192 */         (s->pict_type != AV_PICTURE_TYPE_I ||                                                                 // 0.0
/*194 */          s->picture_structure != PICT_FRAME)) {                                                               // 0.0
/*196 */         int h_chroma_shift, v_chroma_shift;                                                                   // 0.0
/*198 */         av_pix_fmt_get_chroma_sub_sample(s->avctx->pix_fmt,                                                   // 0.0
/*200 */                                          &h_chroma_shift, &v_chroma_shift);                                   // 0.0
/*202 */         if (s->pict_type == AV_PICTURE_TYPE_B && s->next_picture_ptr && s->next_picture_ptr->f.buf[0])        // 0.0
/*204 */             av_log(avctx, AV_LOG_DEBUG,                                                                       // 0.0
/*206 */                    "allocating dummy last picture for B frame\n");                                            // 0.0
/*208 */         else if (s->pict_type != AV_PICTURE_TYPE_I)                                                           // 0.0
/*210 */             av_log(avctx, AV_LOG_ERROR,                                                                       // 0.0
/*212 */                    "warning: first frame is no keyframe\n");                                                  // 0.0
/*214 */         else if (s->picture_structure != PICT_FRAME)                                                          // 0.0
/*216 */             av_log(avctx, AV_LOG_DEBUG,                                                                       // 0.0
/*218 */                    "allocate dummy last picture for field based first keyframe\n");                           // 0.0
/*222 */         /* Allocate a dummy frame */                                                                          // 0.0
/*224 */         i = ff_find_unused_picture(s, 0);                                                                     // 0.0
/*226 */         if (i < 0) {                                                                                          // 0.0
/*228 */             av_log(s->avctx, AV_LOG_ERROR, "no frame buffer available\n");                                    // 0.0
/*230 */             return i;                                                                                         // 0.0
/*232 */         }                                                                                                     // 0.0
/*234 */         s->last_picture_ptr = &s->picture[i];                                                                 // 0.0
/*238 */         s->last_picture_ptr->reference   = 3;                                                                 // 0.0
/*240 */         s->last_picture_ptr->f.key_frame = 0;                                                                 // 0.0
/*242 */         s->last_picture_ptr->f.pict_type = AV_PICTURE_TYPE_P;                                                 // 0.0
/*246 */         if (ff_alloc_picture(s, s->last_picture_ptr, 0) < 0) {                                                // 0.0
/*248 */             s->last_picture_ptr = NULL;                                                                       // 0.0
/*250 */             return -1;                                                                                        // 0.0
/*252 */         }                                                                                                     // 0.0
/*256 */         memset(s->last_picture_ptr->f.data[0], 0x80,                                                          // 0.0
/*258 */                avctx->height * s->last_picture_ptr->f.linesize[0]);                                           // 0.0
/*260 */         memset(s->last_picture_ptr->f.data[1], 0x80,                                                          // 0.0
/*262 */                (avctx->height >> v_chroma_shift) *                                                            // 0.0
/*264 */                s->last_picture_ptr->f.linesize[1]);                                                           // 0.0
/*266 */         memset(s->last_picture_ptr->f.data[2], 0x80,                                                          // 0.0
/*268 */                (avctx->height >> v_chroma_shift) *                                                            // 0.0
/*270 */                s->last_picture_ptr->f.linesize[2]);                                                           // 0.0
/*274 */         if(s->codec_id == AV_CODEC_ID_FLV1 || s->codec_id == AV_CODEC_ID_H263){                               // 0.0
/*276 */             for(i=0; i<avctx->height; i++)                                                                    // 0.0
/*278 */             memset(s->last_picture_ptr->f.data[0] + s->last_picture_ptr->f.linesize[0]*i, 16, avctx->width);  // 0.0
/*280 */         }                                                                                                     // 0.0
/*284 */         ff_thread_report_progress(&s->last_picture_ptr->tf, INT_MAX, 0);                                      // 0.0
/*286 */         ff_thread_report_progress(&s->last_picture_ptr->tf, INT_MAX, 1);                                      // 0.0
/*288 */     }                                                                                                         // 0.0
/*290 */     if ((s->next_picture_ptr == NULL ||                                                                       // 0.0
/*292 */          s->next_picture_ptr->f.buf[0] == NULL) &&                                                            // 0.0
/*294 */         s->pict_type == AV_PICTURE_TYPE_B) {                                                                  // 0.0
/*296 */         /* Allocate a dummy frame */                                                                          // 0.0
/*298 */         i = ff_find_unused_picture(s, 0);                                                                     // 0.0
/*300 */         if (i < 0) {                                                                                          // 0.0
/*302 */             av_log(s->avctx, AV_LOG_ERROR, "no frame buffer available\n");                                    // 0.0
/*304 */             return i;                                                                                         // 0.0
/*306 */         }                                                                                                     // 0.0
/*308 */         s->next_picture_ptr = &s->picture[i];                                                                 // 0.0
/*312 */         s->next_picture_ptr->reference   = 3;                                                                 // 0.0
/*314 */         s->next_picture_ptr->f.key_frame = 0;                                                                 // 0.0
/*316 */         s->next_picture_ptr->f.pict_type = AV_PICTURE_TYPE_P;                                                 // 0.0
/*320 */         if (ff_alloc_picture(s, s->next_picture_ptr, 0) < 0) {                                                // 0.0
/*322 */             s->next_picture_ptr = NULL;                                                                       // 0.0
/*324 */             return -1;                                                                                        // 0.0
/*326 */         }                                                                                                     // 0.0
/*328 */         ff_thread_report_progress(&s->next_picture_ptr->tf, INT_MAX, 0);                                      // 0.0
/*330 */         ff_thread_report_progress(&s->next_picture_ptr->tf, INT_MAX, 1);                                      // 0.0
/*332 */     }                                                                                                         // 0.0
/*336 */ #if 0 // BUFREF-FIXME                                                                                         // 0.0
/*338 */     memset(s->last_picture.f.data, 0, sizeof(s->last_picture.f.data));                                        // 0.0
/*340 */     memset(s->next_picture.f.data, 0, sizeof(s->next_picture.f.data));                                        // 0.0
/*342 */ #endif                                                                                                        // 0.0
/*344 */     if (s->last_picture_ptr) {                                                                                // 0.0
/*346 */         ff_mpeg_unref_picture(s, &s->last_picture);                                                           // 0.0
/*348 */         if (s->last_picture_ptr->f.buf[0] &&                                                                  // 0.0
/*350 */             (ret = ff_mpeg_ref_picture(s, &s->last_picture,                                                   // 0.0
/*352 */                                        s->last_picture_ptr)) < 0)                                             // 0.0
/*354 */             return ret;                                                                                       // 0.0
/*356 */     }                                                                                                         // 0.0
/*358 */     if (s->next_picture_ptr) {                                                                                // 0.0
/*360 */         ff_mpeg_unref_picture(s, &s->next_picture);                                                           // 0.0
/*362 */         if (s->next_picture_ptr->f.buf[0] &&                                                                  // 0.0
/*364 */             (ret = ff_mpeg_ref_picture(s, &s->next_picture,                                                   // 0.0
/*366 */                                        s->next_picture_ptr)) < 0)                                             // 0.0
/*368 */             return ret;                                                                                       // 0.0
/*370 */     }                                                                                                         // 0.0
/*374 */     av_assert0(s->pict_type == AV_PICTURE_TYPE_I || (s->last_picture_ptr &&                                   // 0.0
/*376 */                                                  s->last_picture_ptr->f.buf[0]));                             // 0.0
/*380 */     if (s->picture_structure!= PICT_FRAME) {                                                                  // 0.0
/*382 */         int i;                                                                                                // 0.0
/*384 */         for (i = 0; i < 4; i++) {                                                                             // 0.0
/*386 */             if (s->picture_structure == PICT_BOTTOM_FIELD) {                                                  // 0.0
/*388 */                 s->current_picture.f.data[i] +=                                                               // 0.0
/*390 */                     s->current_picture.f.linesize[i];                                                         // 0.0
/*392 */             }                                                                                                 // 0.0
/*394 */             s->current_picture.f.linesize[i] *= 2;                                                            // 0.0
/*396 */             s->last_picture.f.linesize[i]    *= 2;                                                            // 0.0
/*398 */             s->next_picture.f.linesize[i]    *= 2;                                                            // 0.0
/*400 */         }                                                                                                     // 0.0
/*402 */     }                                                                                                         // 0.0
/*406 */     s->err_recognition = avctx->err_recognition;                                                              // 0.0
/*410 */     /* set dequantizer, we can't do it during init as                                                         // 0.0
/*412 */      * it might change for mpeg4 and we can't do it in the header                                             // 0.0
/*414 */      * decode as init is not called for mpeg4 there yet */                                                    // 0.0
/*416 */     if (s->mpeg_quant || s->codec_id == AV_CODEC_ID_MPEG2VIDEO) {                                             // 0.0
/*418 */         s->dct_unquantize_intra = s->dct_unquantize_mpeg2_intra;                                              // 0.0
/*420 */         s->dct_unquantize_inter = s->dct_unquantize_mpeg2_inter;                                              // 0.0
/*422 */     } else if (s->out_format == FMT_H263 || s->out_format == FMT_H261) {                                      // 0.0
/*424 */         s->dct_unquantize_intra = s->dct_unquantize_h263_intra;                                               // 0.0
/*426 */         s->dct_unquantize_inter = s->dct_unquantize_h263_inter;                                               // 0.0
/*428 */     } else {                                                                                                  // 0.0
/*430 */         s->dct_unquantize_intra = s->dct_unquantize_mpeg1_intra;                                              // 0.0
/*432 */         s->dct_unquantize_inter = s->dct_unquantize_mpeg1_inter;                                              // 0.0
/*434 */     }                                                                                                         // 0.0
/*438 */     return 0;                                                                                                 // 0.0
/*440 */ }                                                                                                             // 0.0

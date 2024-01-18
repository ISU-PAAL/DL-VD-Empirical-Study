// commit message FFmpeg@d7b2bb5391 (target=0, prob=0.4204443, correct=True): h264_sei: Check actual presence of picture timing SEI message
/*0   */ static inline int parse_nal_units(AVCodecParserContext *s,                                            // (7) 0.03516
/*2   */                                   AVCodecContext *avctx,                                              // (1) 0.08008
/*4   */                                   const uint8_t *buf, int buf_size)                                   // (0) 0.08984
/*6   */ {                                                                                                     // (28) 0.001953
/*8   */     H264ParseContext *p = s->priv_data;                                                               // (10) 0.0332
/*10  */     const uint8_t *buf_end = buf + buf_size;                                                          // (5) 0.03711
/*14  */     H2645NAL nal = { NULL };                                                                          // (17) 0.02734
/*18  */     unsigned int pps_id;                                                                              // (20) 0.01953
/*20  */     unsigned int slice_type;                                                                          // (24) 0.01758
/*22  */     int state = -1, got_reset = 0;                                                                    // (13) 0.0293
/*24  */     int field_poc[2];                                                                                 // (19) 0.02148
/*26  */     int ret;                                                                                          // (27) 0.01172
/*30  */     /* set some sane default values */                                                                // (21) 0.01953
/*32  */     s->pict_type         = AV_PICTURE_TYPE_I;                                                         // (3) 0.05273
/*34  */     s->key_frame         = 0;                                                                         // (6) 0.03711
/*36  */     s->picture_structure = AV_PICTURE_STRUCTURE_UNKNOWN;                                              // (4) 0.04297
/*40  */     ff_h264_sei_uninit(&p->sei);                                                                      // (8) 0.0332
/*44  */     if (!buf_size)                                                                                    // (25) 0.01758
/*46  */         return 0;                                                                                     // (22) 0.01953
/*50  */     for (;;) {                                                                                        // (26) 0.01562
/*52  */         const SPS *sps;                                                                               // (15) 0.02734
/*54  */         int src_length, consumed;                                                                     // (16) 0.02734
/*56  */         buf = avpriv_find_start_code(buf, buf_end, &state);                                           // (2) 0.05273
/*58  */         if (buf >= buf_end)                                                                           // (14) 0.0293
/*60  */             break;                                                                                    // (18) 0.02539
/*62  */         --buf;                                                                                        // (23) 0.01953
/*64  */         src_length = buf_end - buf;                                                                   // (11) 0.0332
/*66  */         switch (state & 0x1f) {                                                                       // (12) 0.0332
/*68  */         case H264_NAL_SLICE:                                                                          // (9) 0.0332
/*70  */         case H264_NAL_IDR_SLICE:                                                                      // 0.0
/*72  */             // Do not walk the whole buffer just to decode slice header                               // 0.0
/*74  */             if ((state & 0x1f) == H264_NAL_IDR_SLICE || ((state >> 5) & 0x3) == 0) {                  // 0.0
/*76  */                 /* IDR or disposable slice                                                            // 0.0
/*78  */                  * No need to decode many bytes because MMCOs shall not be present. */                // 0.0
/*80  */                 if (src_length > 60)                                                                  // 0.0
/*82  */                     src_length = 60;                                                                  // 0.0
/*84  */             } else {                                                                                  // 0.0
/*86  */                 /* To decode up to MMCOs */                                                           // 0.0
/*88  */                 if (src_length > 1000)                                                                // 0.0
/*90  */                     src_length = 1000;                                                                // 0.0
/*92  */             }                                                                                         // 0.0
/*94  */             break;                                                                                    // 0.0
/*96  */         }                                                                                             // 0.0
/*100 */         consumed = ff_h2645_extract_rbsp(buf, src_length, &nal);                                      // 0.0
/*102 */         if (consumed < 0)                                                                             // 0.0
/*104 */             break;                                                                                    // 0.0
/*108 */         ret = init_get_bits(&nal.gb, nal.data, nal.size * 8);                                         // 0.0
/*110 */         if (ret < 0)                                                                                  // 0.0
/*112 */             goto fail;                                                                                // 0.0
/*114 */         get_bits1(&nal.gb);                                                                           // 0.0
/*116 */         nal.ref_idc = get_bits(&nal.gb, 2);                                                           // 0.0
/*118 */         nal.type    = get_bits(&nal.gb, 5);                                                           // 0.0
/*122 */         switch (nal.type) {                                                                           // 0.0
/*124 */         case H264_NAL_SPS:                                                                            // 0.0
/*126 */             ff_h264_decode_seq_parameter_set(&nal.gb, avctx, &p->ps);                                 // 0.0
/*128 */             break;                                                                                    // 0.0
/*130 */         case H264_NAL_PPS:                                                                            // 0.0
/*132 */             ff_h264_decode_picture_parameter_set(&nal.gb, avctx, &p->ps,                              // 0.0
/*134 */                                                  nal.size_bits);                                      // 0.0
/*136 */             break;                                                                                    // 0.0
/*138 */         case H264_NAL_SEI:                                                                            // 0.0
/*140 */             ff_h264_sei_decode(&p->sei, &nal.gb, &p->ps, avctx);                                      // 0.0
/*142 */             break;                                                                                    // 0.0
/*144 */         case H264_NAL_IDR_SLICE:                                                                      // 0.0
/*146 */             s->key_frame = 1;                                                                         // 0.0
/*150 */             p->poc.prev_frame_num        = 0;                                                         // 0.0
/*152 */             p->poc.prev_frame_num_offset = 0;                                                         // 0.0
/*154 */             p->poc.prev_poc_msb          =                                                            // 0.0
/*156 */             p->poc.prev_poc_lsb          = 0;                                                         // 0.0
/*158 */         /* fall through */                                                                            // 0.0
/*160 */         case H264_NAL_SLICE:                                                                          // 0.0
/*162 */             get_ue_golomb(&nal.gb);  // skip first_mb_in_slice                                        // 0.0
/*164 */             slice_type   = get_ue_golomb_31(&nal.gb);                                                 // 0.0
/*166 */             s->pict_type = ff_h264_golomb_to_pict_type[slice_type % 5];                               // 0.0
/*168 */             if (p->sei.recovery_point.recovery_frame_cnt >= 0) {                                      // 0.0
/*170 */                 /* key frame, since recovery_frame_cnt is set */                                      // 0.0
/*172 */                 s->key_frame = 1;                                                                     // 0.0
/*174 */             }                                                                                         // 0.0
/*176 */             pps_id = get_ue_golomb(&nal.gb);                                                          // 0.0
/*178 */             if (pps_id >= MAX_PPS_COUNT) {                                                            // 0.0
/*180 */                 av_log(avctx, AV_LOG_ERROR,                                                           // 0.0
/*182 */                        "pps_id %u out of range\n", pps_id);                                           // 0.0
/*184 */                 goto fail;                                                                            // 0.0
/*186 */             }                                                                                         // 0.0
/*188 */             if (!p->ps.pps_list[pps_id]) {                                                            // 0.0
/*190 */                 av_log(avctx, AV_LOG_ERROR,                                                           // 0.0
/*192 */                        "non-existing PPS %u referenced\n", pps_id);                                   // 0.0
/*194 */                 goto fail;                                                                            // 0.0
/*196 */             }                                                                                         // 0.0
/*198 */             p->ps.pps = (const PPS*)p->ps.pps_list[pps_id]->data;                                     // 0.0
/*200 */             if (!p->ps.sps_list[p->ps.pps->sps_id]) {                                                 // 0.0
/*202 */                 av_log(avctx, AV_LOG_ERROR,                                                           // 0.0
/*204 */                        "non-existing SPS %u referenced\n", p->ps.pps->sps_id);                        // 0.0
/*206 */                 goto fail;                                                                            // 0.0
/*208 */             }                                                                                         // 0.0
/*210 */             p->ps.sps = (SPS*)p->ps.sps_list[p->ps.pps->sps_id]->data;                                // 0.0
/*214 */             sps = p->ps.sps;                                                                          // 0.0
/*218 */             p->poc.frame_num = get_bits(&nal.gb, sps->log2_max_frame_num);                            // 0.0
/*222 */             s->coded_width  = 16 * sps->mb_width;                                                     // 0.0
/*224 */             s->coded_height = 16 * sps->mb_height;                                                    // 0.0
/*226 */             s->width        = s->coded_width  - (sps->crop_right + sps->crop_left);                   // 0.0
/*228 */             s->height       = s->coded_height - (sps->crop_top   + sps->crop_bottom);                 // 0.0
/*230 */             if (s->width <= 0 || s->height <= 0) {                                                    // 0.0
/*232 */                 s->width  = s->coded_width;                                                           // 0.0
/*234 */                 s->height = s->coded_height;                                                          // 0.0
/*236 */             }                                                                                         // 0.0
/*240 */             switch (sps->bit_depth_luma) {                                                            // 0.0
/*242 */             case 9:                                                                                   // 0.0
/*244 */                 if (sps->chroma_format_idc == 3)      s->format = AV_PIX_FMT_YUV444P9;                // 0.0
/*246 */                 else if (sps->chroma_format_idc == 2) s->format = AV_PIX_FMT_YUV422P9;                // 0.0
/*248 */                 else                                  s->format = AV_PIX_FMT_YUV420P9;                // 0.0
/*250 */                 break;                                                                                // 0.0
/*252 */             case 10:                                                                                  // 0.0
/*254 */                 if (sps->chroma_format_idc == 3)      s->format = AV_PIX_FMT_YUV444P10;               // 0.0
/*256 */                 else if (sps->chroma_format_idc == 2) s->format = AV_PIX_FMT_YUV422P10;               // 0.0
/*258 */                 else                                  s->format = AV_PIX_FMT_YUV420P10;               // 0.0
/*260 */                 break;                                                                                // 0.0
/*262 */             case 8:                                                                                   // 0.0
/*264 */                 if (sps->chroma_format_idc == 3)      s->format = AV_PIX_FMT_YUV444P;                 // 0.0
/*266 */                 else if (sps->chroma_format_idc == 2) s->format = AV_PIX_FMT_YUV422P;                 // 0.0
/*268 */                 else                                  s->format = AV_PIX_FMT_YUV420P;                 // 0.0
/*270 */                 break;                                                                                // 0.0
/*272 */             default:                                                                                  // 0.0
/*274 */                 s->format = AV_PIX_FMT_NONE;                                                          // 0.0
/*276 */             }                                                                                         // 0.0
/*280 */             avctx->profile = ff_h264_get_profile(sps);                                                // 0.0
/*282 */             avctx->level   = sps->level_idc;                                                          // 0.0
/*286 */             if (sps->frame_mbs_only_flag) {                                                           // 0.0
/*288 */                 p->picture_structure = PICT_FRAME;                                                    // 0.0
/*290 */             } else {                                                                                  // 0.0
/*292 */                 if (get_bits1(&nal.gb)) { // field_pic_flag                                           // 0.0
/*294 */                     p->picture_structure = PICT_TOP_FIELD + get_bits1(&nal.gb); // bottom_field_flag  // 0.0
/*296 */                 } else {                                                                              // 0.0
/*298 */                     p->picture_structure = PICT_FRAME;                                                // 0.0
/*300 */                 }                                                                                     // 0.0
/*302 */             }                                                                                         // 0.0
/*306 */             if (nal.type == H264_NAL_IDR_SLICE)                                                       // 0.0
/*308 */                 get_ue_golomb(&nal.gb); /* idr_pic_id */                                              // 0.0
/*310 */             if (sps->poc_type == 0) {                                                                 // 0.0
/*312 */                 p->poc.poc_lsb = get_bits(&nal.gb, sps->log2_max_poc_lsb);                            // 0.0
/*316 */                 if (p->ps.pps->pic_order_present == 1 &&                                              // 0.0
/*318 */                     p->picture_structure == PICT_FRAME)                                               // 0.0
/*320 */                     p->poc.delta_poc_bottom = get_se_golomb(&nal.gb);                                 // 0.0
/*322 */             }                                                                                         // 0.0
/*326 */             if (sps->poc_type == 1 &&                                                                 // 0.0
/*328 */                 !sps->delta_pic_order_always_zero_flag) {                                             // 0.0
/*330 */                 p->poc.delta_poc[0] = get_se_golomb(&nal.gb);                                         // 0.0
/*334 */                 if (p->ps.pps->pic_order_present == 1 &&                                              // 0.0
/*336 */                     p->picture_structure == PICT_FRAME)                                               // 0.0
/*338 */                     p->poc.delta_poc[1] = get_se_golomb(&nal.gb);                                     // 0.0
/*340 */             }                                                                                         // 0.0
/*344 */             /* Decode POC of this picture.                                                            // 0.0
/*346 */              * The prev_ values needed for decoding POC of the next picture are not set here. */      // 0.0
/*348 */             field_poc[0] = field_poc[1] = INT_MAX;                                                    // 0.0
/*350 */             ff_h264_init_poc(field_poc, &s->output_picture_number, sps,                               // 0.0
/*352 */                              &p->poc, p->picture_structure, nal.ref_idc);                             // 0.0
/*356 */             /* Continue parsing to check if MMCO_RESET is present.                                    // 0.0
/*358 */              * FIXME: MMCO_RESET could appear in non-first slice.                                     // 0.0
/*360 */              *        Maybe, we should parse all undisposable non-IDR slice of this                   // 0.0
/*362 */              *        picture until encountering MMCO_RESET in a slice of it. */                      // 0.0
/*364 */             if (nal.ref_idc && nal.type != H264_NAL_IDR_SLICE) {                                      // 0.0
/*366 */                 got_reset = scan_mmco_reset(s, &nal.gb, avctx);                                       // 0.0
/*368 */                 if (got_reset < 0)                                                                    // 0.0
/*370 */                     goto fail;                                                                        // 0.0
/*372 */             }                                                                                         // 0.0
/*376 */             /* Set up the prev_ values for decoding POC of the next picture. */                       // 0.0
/*378 */             p->poc.prev_frame_num        = got_reset ? 0 : p->poc.frame_num;                          // 0.0
/*380 */             p->poc.prev_frame_num_offset = got_reset ? 0 : p->poc.frame_num_offset;                   // 0.0
/*382 */             if (nal.ref_idc != 0) {                                                                   // 0.0
/*384 */                 if (!got_reset) {                                                                     // 0.0
/*386 */                     p->poc.prev_poc_msb = p->poc.poc_msb;                                             // 0.0
/*388 */                     p->poc.prev_poc_lsb = p->poc.poc_lsb;                                             // 0.0
/*390 */                 } else {                                                                              // 0.0
/*392 */                     p->poc.prev_poc_msb = 0;                                                          // 0.0
/*394 */                     p->poc.prev_poc_lsb =                                                             // 0.0
/*396 */                         p->picture_structure == PICT_BOTTOM_FIELD ? 0 : field_poc[0];                 // 0.0
/*398 */                 }                                                                                     // 0.0
/*400 */             }                                                                                         // 0.0
/*404 */             if (sps->pic_struct_present_flag) {                                                       // 0.0
/*406 */                 switch (p->sei.picture_timing.pic_struct) {                                           // 0.0
/*408 */                 case SEI_PIC_STRUCT_TOP_FIELD:                                                        // 0.0
/*410 */                 case SEI_PIC_STRUCT_BOTTOM_FIELD:                                                     // 0.0
/*412 */                     s->repeat_pict = 0;                                                               // 0.0
/*414 */                     break;                                                                            // 0.0
/*416 */                 case SEI_PIC_STRUCT_FRAME:                                                            // 0.0
/*418 */                 case SEI_PIC_STRUCT_TOP_BOTTOM:                                                       // 0.0
/*420 */                 case SEI_PIC_STRUCT_BOTTOM_TOP:                                                       // 0.0
/*422 */                     s->repeat_pict = 1;                                                               // 0.0
/*424 */                     break;                                                                            // 0.0
/*426 */                 case SEI_PIC_STRUCT_TOP_BOTTOM_TOP:                                                   // 0.0
/*428 */                 case SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM:                                                // 0.0
/*430 */                     s->repeat_pict = 2;                                                               // 0.0
/*432 */                     break;                                                                            // 0.0
/*434 */                 case SEI_PIC_STRUCT_FRAME_DOUBLING:                                                   // 0.0
/*436 */                     s->repeat_pict = 3;                                                               // 0.0
/*438 */                     break;                                                                            // 0.0
/*440 */                 case SEI_PIC_STRUCT_FRAME_TRIPLING:                                                   // 0.0
/*442 */                     s->repeat_pict = 5;                                                               // 0.0
/*444 */                     break;                                                                            // 0.0
/*446 */                 default:                                                                              // 0.0
/*448 */                     s->repeat_pict = p->picture_structure == PICT_FRAME ? 1 : 0;                      // 0.0
/*450 */                     break;                                                                            // 0.0
/*452 */                 }                                                                                     // 0.0
/*454 */             } else {                                                                                  // 0.0
/*456 */                 s->repeat_pict = p->picture_structure == PICT_FRAME ? 1 : 0;                          // 0.0
/*458 */             }                                                                                         // 0.0
/*462 */             if (p->picture_structure == PICT_FRAME) {                                                 // 0.0
/*464 */                 s->picture_structure = AV_PICTURE_STRUCTURE_FRAME;                                    // 0.0
/*466 */                 if (sps->pic_struct_present_flag) {                                                   // 0.0
/*468 */                     switch (p->sei.picture_timing.pic_struct) {                                       // 0.0
/*470 */                     case SEI_PIC_STRUCT_TOP_BOTTOM:                                                   // 0.0
/*472 */                     case SEI_PIC_STRUCT_TOP_BOTTOM_TOP:                                               // 0.0
/*474 */                         s->field_order = AV_FIELD_TT;                                                 // 0.0
/*476 */                         break;                                                                        // 0.0
/*478 */                     case SEI_PIC_STRUCT_BOTTOM_TOP:                                                   // 0.0
/*480 */                     case SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM:                                            // 0.0
/*482 */                         s->field_order = AV_FIELD_BB;                                                 // 0.0
/*484 */                         break;                                                                        // 0.0
/*486 */                     default:                                                                          // 0.0
/*488 */                         s->field_order = AV_FIELD_PROGRESSIVE;                                        // 0.0
/*490 */                         break;                                                                        // 0.0
/*492 */                     }                                                                                 // 0.0
/*494 */                 } else {                                                                              // 0.0
/*496 */                     if (field_poc[0] < field_poc[1])                                                  // 0.0
/*498 */                         s->field_order = AV_FIELD_TT;                                                 // 0.0
/*500 */                     else if (field_poc[0] > field_poc[1])                                             // 0.0
/*502 */                         s->field_order = AV_FIELD_BB;                                                 // 0.0
/*504 */                     else                                                                              // 0.0
/*506 */                         s->field_order = AV_FIELD_PROGRESSIVE;                                        // 0.0
/*508 */                 }                                                                                     // 0.0
/*510 */             } else {                                                                                  // 0.0
/*512 */                 if (p->picture_structure == PICT_TOP_FIELD)                                           // 0.0
/*514 */                     s->picture_structure = AV_PICTURE_STRUCTURE_TOP_FIELD;                            // 0.0
/*516 */                 else                                                                                  // 0.0
/*518 */                     s->picture_structure = AV_PICTURE_STRUCTURE_BOTTOM_FIELD;                         // 0.0
/*520 */                 s->field_order = AV_FIELD_UNKNOWN;                                                    // 0.0
/*522 */             }                                                                                         // 0.0
/*526 */             av_freep(&nal.rbsp_buffer);                                                               // 0.0
/*528 */             return 0; /* no need to evaluate the rest */                                              // 0.0
/*530 */         }                                                                                             // 0.0
/*532 */         buf += consumed;                                                                              // 0.0
/*534 */     }                                                                                                 // 0.0
/*536 */     /* didn't find a picture! */                                                                      // 0.0
/*538 */     av_log(avctx, AV_LOG_ERROR, "missing picture in access unit\n");                                  // 0.0
/*540 */ fail:                                                                                                 // 0.0
/*542 */     av_freep(&nal.rbsp_buffer);                                                                       // 0.0
/*544 */     return -1;                                                                                        // 0.0
/*546 */ }                                                                                                     // 0.0

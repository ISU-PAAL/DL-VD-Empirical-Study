// commit message FFmpeg@a4c7a5ea27 (target=0, prob=0.48211938, correct=True): Call ff_fetch_timestamp() for mpeg1/2 when a picture start code is found instead of calling it at the end of a frame with a large negative offset. This significantly reduces the maximal distance in container packets between the point where the first byte of the "access unit" was stored and where we call ff_fetch_timestamp() thus reducing the constraints on our parser. Also change the parser from next_frame_offset to cur, this is needed because now the reference is from container packet start instead of frame start. (i previously misinterpreted this as bug)
/*0   */ static void mpegvideo_extract_headers(AVCodecParserContext *s,                                        // (4) 0.007118
/*2   */                                       AVCodecContext *avctx,                                          // (3) 0.00913
/*4   */                                       const uint8_t *buf, int buf_size)                               // (2) 0.009256
/*6   */ {                                                                                                     // (23) 0.000308
/*8   */     ParseContext1 *pc = s->priv_data;                                                                 // (12) 0.003834
/*10  */     const uint8_t *buf_end;                                                                           // (19) 0.002943
/*12  */     const uint8_t *buf_start= buf;                                                                    // (15) 0.003369
/*14  */     uint32_t start_code;                                                                              // (22) 0.00214
/*16  */     int frame_rate_index, ext_type, bytes_left;                                                       // (14) 0.003547
/*18  */     int frame_rate_ext_n, frame_rate_ext_d;                                                           // (11) 0.00418
/*20  */     int picture_structure, top_field_first, repeat_first_field, progressive_frame;                    // (8) 0.005581
/*22  */     int horiz_size_ext, vert_size_ext, bit_rate_ext;                                                  // (0) 0.2133
/*24  */ //FIXME replace the crap with get_bits()                                                              // (1) 0.1543
/*26  */     s->repeat_pict = 0;                                                                               // (9) 0.004886
/*28  */     buf_end = buf + buf_size;                                                                         // (17) 0.003048
/*30  */     while (buf < buf_end) {                                                                           // (18) 0.003029
/*32  */         start_code= -1;                                                                               // (21) 0.002666
/*34  */         buf= ff_find_start_code(buf, buf_end, &start_code);                                           // (7) 0.005584
/*36  */         bytes_left = buf_end - buf;                                                                   // (16) 0.003139
/*38  */         switch(start_code) {                                                                          // (20) 0.002835
/*40  */         case PICTURE_START_CODE:                                                                      // (10) 0.004419
/*42  */             ff_fetch_timestamp(s, buf-buf_start-4, 1);                                                // (5) 0.006239
/*46  */             if (bytes_left >= 2) {                                                                    // (13) 0.003654
/*48  */                 s->pict_type = (buf[1] >> 3) & 7;                                                     // (6) 0.006039
/*50  */             }                                                                                         // 0.0
/*52  */             break;                                                                                    // 0.0
/*54  */         case SEQ_START_CODE:                                                                          // 0.0
/*56  */             if (bytes_left >= 7) {                                                                    // 0.0
/*58  */                 pc->width  = (buf[0] << 4) | (buf[1] >> 4);                                           // 0.0
/*60  */                 pc->height = ((buf[1] & 0x0f) << 8) | buf[2];                                         // 0.0
/*62  */                 avcodec_set_dimensions(avctx, pc->width, pc->height);                                 // 0.0
/*64  */                 frame_rate_index = buf[3] & 0xf;                                                      // 0.0
/*66  */                 pc->frame_rate.den = avctx->time_base.den = ff_frame_rate_tab[frame_rate_index].num;  // 0.0
/*68  */                 pc->frame_rate.num = avctx->time_base.num = ff_frame_rate_tab[frame_rate_index].den;  // 0.0
/*70  */                 avctx->bit_rate = ((buf[4]<<10) | (buf[5]<<2) | (buf[6]>>6))*400;                     // 0.0
/*72  */                 avctx->codec_id = CODEC_ID_MPEG1VIDEO;                                                // 0.0
/*74  */                 avctx->sub_id = 1;                                                                    // 0.0
/*76  */             }                                                                                         // 0.0
/*78  */             break;                                                                                    // 0.0
/*80  */         case EXT_START_CODE:                                                                          // 0.0
/*82  */             if (bytes_left >= 1) {                                                                    // 0.0
/*84  */                 ext_type = (buf[0] >> 4);                                                             // 0.0
/*86  */                 switch(ext_type) {                                                                    // 0.0
/*88  */                 case 0x1: /* sequence extension */                                                    // 0.0
/*90  */                     if (bytes_left >= 6) {                                                            // 0.0
/*92  */                         horiz_size_ext = ((buf[1] & 1) << 1) | (buf[2] >> 7);                         // 0.0
/*94  */                         vert_size_ext = (buf[2] >> 5) & 3;                                            // 0.0
/*96  */                         bit_rate_ext = ((buf[2] & 0x1F)<<7) | (buf[3]>>1);                            // 0.0
/*98  */                         frame_rate_ext_n = (buf[5] >> 5) & 3;                                         // 0.0
/*100 */                         frame_rate_ext_d = (buf[5] & 0x1f);                                           // 0.0
/*102 */                         pc->progressive_sequence = buf[1] & (1 << 3);                                 // 0.0
/*104 */                         avctx->has_b_frames= !(buf[5] >> 7);                                          // 0.0
/*108 */                         pc->width  |=(horiz_size_ext << 12);                                          // 0.0
/*110 */                         pc->height |=( vert_size_ext << 12);                                          // 0.0
/*112 */                         avctx->bit_rate += (bit_rate_ext << 18) * 400;                                // 0.0
/*114 */                         avcodec_set_dimensions(avctx, pc->width, pc->height);                         // 0.0
/*116 */                         avctx->time_base.den = pc->frame_rate.den * (frame_rate_ext_n + 1) * 2;       // 0.0
/*118 */                         avctx->time_base.num = pc->frame_rate.num * (frame_rate_ext_d + 1);           // 0.0
/*120 */                         avctx->codec_id = CODEC_ID_MPEG2VIDEO;                                        // 0.0
/*122 */                         avctx->sub_id = 2; /* forces MPEG2 */                                         // 0.0
/*124 */                     }                                                                                 // 0.0
/*126 */                     break;                                                                            // 0.0
/*128 */                 case 0x8: /* picture coding extension */                                              // 0.0
/*130 */                     if (bytes_left >= 5) {                                                            // 0.0
/*132 */                         picture_structure = buf[2]&3;                                                 // 0.0
/*134 */                         top_field_first = buf[3] & (1 << 7);                                          // 0.0
/*136 */                         repeat_first_field = buf[3] & (1 << 1);                                       // 0.0
/*138 */                         progressive_frame = buf[4] & (1 << 7);                                        // 0.0
/*142 */                         /* check if we must repeat the frame */                                       // 0.0
/*144 */                         s->repeat_pict = 1;                                                           // 0.0
/*146 */                         if (repeat_first_field) {                                                     // 0.0
/*148 */                             if (pc->progressive_sequence) {                                           // 0.0
/*150 */                                 if (top_field_first)                                                  // 0.0
/*152 */                                     s->repeat_pict = 5;                                               // 0.0
/*154 */                                 else                                                                  // 0.0
/*156 */                                     s->repeat_pict = 3;                                               // 0.0
/*158 */                             } else if (progressive_frame) {                                           // 0.0
/*160 */                                 s->repeat_pict = 2;                                                   // 0.0
/*162 */                             }                                                                         // 0.0
/*164 */                         }                                                                             // 0.0
/*166 */                     }                                                                                 // 0.0
/*168 */                     break;                                                                            // 0.0
/*170 */                 }                                                                                     // 0.0
/*172 */             }                                                                                         // 0.0
/*174 */             break;                                                                                    // 0.0
/*176 */         case -1:                                                                                      // 0.0
/*178 */             goto the_end;                                                                             // 0.0
/*180 */         default:                                                                                      // 0.0
/*182 */             /* we stop parsing when we encounter a slice. It ensures                                  // 0.0
/*184 */                that this function takes a negligible amount of time */                                // 0.0
/*186 */             if (start_code >= SLICE_MIN_START_CODE &&                                                 // 0.0
/*188 */                 start_code <= SLICE_MAX_START_CODE)                                                   // 0.0
/*190 */                 goto the_end;                                                                         // 0.0
/*192 */             break;                                                                                    // 0.0
/*194 */         }                                                                                             // 0.0
/*196 */     }                                                                                                 // 0.0
/*198 */  the_end: ;                                                                                           // 0.0
/*200 */ }                                                                                                     // 0.0

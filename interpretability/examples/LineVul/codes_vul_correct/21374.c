// commit message FFmpeg@d59591fb02 (target=1, prob=0.99929166, correct=True): In mpeg1/2 timestamps are associated with the access unit which contains the first picture startcode that commences in the PES packet, instead of the first access unit that commences in the PES packet. Fix the parser to handle that properly. This was a very long standing bug ... The change to the seek regressions is because the mpeg ts muxer stores too many invalid and randomized timestamps which overflow the 4 entry buffer we use in the parser.
/*0   */ static void mpegvideo_extract_headers(AVCodecParserContext *s,                                        // (2) 0.03666
/*2   */                                       AVCodecContext *avctx,                                          // (6) 0.008822
/*4   */                                       const uint8_t *buf, int buf_size)                               // (9) 0.004885
/*6   */ {                                                                                                     // (21) 0.001156
/*8   */     ParseContext1 *pc = s->priv_data;                                                                 // (3) 0.02293
/*10  */     const uint8_t *buf_end;                                                                           // (7) 0.007073
/*13  */     uint32_t start_code;                                                                              // (19) 0.001382
/*15  */     int frame_rate_index, ext_type, bytes_left;                                                       // (16) 0.002209
/*17  */     int frame_rate_ext_n, frame_rate_ext_d;                                                           // (15) 0.002328
/*19  */     int picture_structure, top_field_first, repeat_first_field, progressive_frame;                    // (8) 0.006426
/*21  */     int horiz_size_ext, vert_size_ext, bit_rate_ext;                                                  // (1) 0.0435
/*23  */ //FIXME replace the crap with get_bits()                                                              // (0) 0.4575
/*25  */     s->repeat_pict = 0;                                                                               // (4) 0.01579
/*27  */     buf_end = buf + buf_size;                                                                         // (11) 0.003729
/*29  */     while (buf < buf_end) {                                                                           // (5) 0.01549
/*31  */         start_code= -1;                                                                               // (17) 0.001629
/*33  */         buf= ff_find_start_code(buf, buf_end, &start_code);                                           // (14) 0.003069
/*35  */         bytes_left = buf_end - buf;                                                                   // (22) 0.001028
/*37  */         switch(start_code) {                                                                          // (18) 0.00147
/*39  */         case PICTURE_START_CODE:                                                                      // (13) 0.003108
/*41  */             ff_fetch_timestamp(s, buf-buf_start-4, 1);                                                // (10) 0.004356
/*45  */             if (bytes_left >= 2) {                                                                    // (20) 0.001174
/*47  */                 s->pict_type = (buf[1] >> 3) & 7;                                                     // (12) 0.003716
/*49  */             }                                                                                         // (23) 0.0008692
/*51  */             break;                                                                                    // 0.0
/*53  */         case SEQ_START_CODE:                                                                          // 0.0
/*55  */             if (bytes_left >= 7) {                                                                    // 0.0
/*57  */                 pc->width  = (buf[0] << 4) | (buf[1] >> 4);                                           // 0.0
/*59  */                 pc->height = ((buf[1] & 0x0f) << 8) | buf[2];                                         // 0.0
/*61  */                 avcodec_set_dimensions(avctx, pc->width, pc->height);                                 // 0.0
/*63  */                 frame_rate_index = buf[3] & 0xf;                                                      // 0.0
/*65  */                 pc->frame_rate.den = avctx->time_base.den = ff_frame_rate_tab[frame_rate_index].num;  // 0.0
/*67  */                 pc->frame_rate.num = avctx->time_base.num = ff_frame_rate_tab[frame_rate_index].den;  // 0.0
/*69  */                 avctx->bit_rate = ((buf[4]<<10) | (buf[5]<<2) | (buf[6]>>6))*400;                     // 0.0
/*71  */                 avctx->codec_id = CODEC_ID_MPEG1VIDEO;                                                // 0.0
/*73  */                 avctx->sub_id = 1;                                                                    // 0.0
/*75  */             }                                                                                         // 0.0
/*77  */             break;                                                                                    // 0.0
/*79  */         case EXT_START_CODE:                                                                          // 0.0
/*81  */             if (bytes_left >= 1) {                                                                    // 0.0
/*83  */                 ext_type = (buf[0] >> 4);                                                             // 0.0
/*85  */                 switch(ext_type) {                                                                    // 0.0
/*87  */                 case 0x1: /* sequence extension */                                                    // 0.0
/*89  */                     if (bytes_left >= 6) {                                                            // 0.0
/*91  */                         horiz_size_ext = ((buf[1] & 1) << 1) | (buf[2] >> 7);                         // 0.0
/*93  */                         vert_size_ext = (buf[2] >> 5) & 3;                                            // 0.0
/*95  */                         bit_rate_ext = ((buf[2] & 0x1F)<<7) | (buf[3]>>1);                            // 0.0
/*97  */                         frame_rate_ext_n = (buf[5] >> 5) & 3;                                         // 0.0
/*99  */                         frame_rate_ext_d = (buf[5] & 0x1f);                                           // 0.0
/*101 */                         pc->progressive_sequence = buf[1] & (1 << 3);                                 // 0.0
/*103 */                         avctx->has_b_frames= !(buf[5] >> 7);                                          // 0.0
/*107 */                         pc->width  |=(horiz_size_ext << 12);                                          // 0.0
/*109 */                         pc->height |=( vert_size_ext << 12);                                          // 0.0
/*111 */                         avctx->bit_rate += (bit_rate_ext << 18) * 400;                                // 0.0
/*113 */                         avcodec_set_dimensions(avctx, pc->width, pc->height);                         // 0.0
/*115 */                         avctx->time_base.den = pc->frame_rate.den * (frame_rate_ext_n + 1);           // 0.0
/*117 */                         avctx->time_base.num = pc->frame_rate.num * (frame_rate_ext_d + 1);           // 0.0
/*119 */                         avctx->codec_id = CODEC_ID_MPEG2VIDEO;                                        // 0.0
/*121 */                         avctx->sub_id = 2; /* forces MPEG2 */                                         // 0.0
/*123 */                     }                                                                                 // 0.0
/*125 */                     break;                                                                            // 0.0
/*127 */                 case 0x8: /* picture coding extension */                                              // 0.0
/*129 */                     if (bytes_left >= 5) {                                                            // 0.0
/*131 */                         picture_structure = buf[2]&3;                                                 // 0.0
/*133 */                         top_field_first = buf[3] & (1 << 7);                                          // 0.0
/*135 */                         repeat_first_field = buf[3] & (1 << 1);                                       // 0.0
/*137 */                         progressive_frame = buf[4] & (1 << 7);                                        // 0.0
/*141 */                         /* check if we must repeat the frame */                                       // 0.0
/*143 */                         if (repeat_first_field) {                                                     // 0.0
/*145 */                             if (pc->progressive_sequence) {                                           // 0.0
/*147 */                                 if (top_field_first)                                                  // 0.0
/*149 */                                     s->repeat_pict = 4;                                               // 0.0
/*151 */                                 else                                                                  // 0.0
/*153 */                                     s->repeat_pict = 2;                                               // 0.0
/*155 */                             } else if (progressive_frame) {                                           // 0.0
/*157 */                                 s->repeat_pict = 1;                                                   // 0.0
/*159 */                             }                                                                         // 0.0
/*161 */                         }                                                                             // 0.0
/*163 */                     }                                                                                 // 0.0
/*165 */                     break;                                                                            // 0.0
/*167 */                 }                                                                                     // 0.0
/*169 */             }                                                                                         // 0.0
/*171 */             break;                                                                                    // 0.0
/*173 */         case -1:                                                                                      // 0.0
/*175 */             goto the_end;                                                                             // 0.0
/*177 */         default:                                                                                      // 0.0
/*179 */             /* we stop parsing when we encounter a slice. It ensures                                  // 0.0
/*181 */                that this function takes a negligible amount of time */                                // 0.0
/*183 */             if (start_code >= SLICE_MIN_START_CODE &&                                                 // 0.0
/*185 */                 start_code <= SLICE_MAX_START_CODE)                                                   // 0.0
/*187 */                 goto the_end;                                                                         // 0.0
/*189 */             break;                                                                                    // 0.0
/*191 */         }                                                                                             // 0.0
/*193 */     }                                                                                                 // 0.0
/*195 */  the_end: ;                                                                                           // 0.0
/*197 */ }                                                                                                     // 0.0

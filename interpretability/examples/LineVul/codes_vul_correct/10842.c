// commit message FFmpeg@1178868683 (target=1, prob=0.7006504, correct=True): exr: fix overflow check in lineoffset processing
/*0   */ static int decode_frame(AVCodecContext *avctx,                                                                                        // (12) 0.02923
/*2   */                         void *data,                                                                                                   // (2) 0.0519
/*4   */                         int *got_frame,                                                                                               // (1) 0.056
/*6   */                         AVPacket *avpkt)                                                                                              // (0) 0.05983
/*8   */ {                                                                                                                                     // (30) 0.002097
/*10  */     const uint8_t *buf      = avpkt->data;                                                                                            // (4) 0.04239
/*12  */     unsigned int   buf_size = avpkt->size;                                                                                            // (7) 0.03282
/*14  */     const uint8_t *buf_end  = buf + buf_size;                                                                                         // (5) 0.03854
/*18  */     const AVPixFmtDescriptor *desc;                                                                                                   // (13) 0.02898
/*20  */     EXRContext *const s = avctx->priv_data;                                                                                           // (6) 0.03288
/*22  */     AVFrame *picture  = data;                                                                                                         // (22) 0.02146
/*24  */     AVFrame *const p = &s->picture;                                                                                                   // (14) 0.02724
/*26  */     uint8_t *ptr;                                                                                                                     // (25) 0.01991
/*30  */     int i, x, y, stride, magic_number, version, flags, ret;                                                                           // (3) 0.04958
/*32  */     int w = 0;                                                                                                                        // (28) 0.01553
/*34  */     int h = 0;                                                                                                                        // (29) 0.01543
/*36  */     unsigned int xmin   = ~0;                                                                                                         // (17) 0.02501
/*38  */     unsigned int xmax   = ~0;                                                                                                         // (16) 0.02501
/*40  */     unsigned int ymin   = ~0;                                                                                                         // (19) 0.02499
/*42  */     unsigned int ymax   = ~0;                                                                                                         // (18) 0.02499
/*44  */     unsigned int xdelta = ~0;                                                                                                         // (21) 0.02311
/*48  */     int out_line_size;                                                                                                                // (27) 0.01927
/*50  */     int bxmin, axmax;                                                                                                                 // (24) 0.02121
/*52  */     int scan_lines_per_block;                                                                                                         // (20) 0.02333
/*54  */     unsigned long scan_line_size;                                                                                                     // (23) 0.02133
/*56  */     unsigned long uncompressed_size;                                                                                                  // (26) 0.0194
/*60  */     unsigned int current_channel_offset = 0;                                                                                          // (15) 0.02566
/*64  */     s->channel_offsets[0] = -1;                                                                                                       // (8) 0.0308
/*66  */     s->channel_offsets[1] = -1;                                                                                                       // (10) 0.03077
/*68  */     s->channel_offsets[2] = -1;                                                                                                       // (11) 0.03076
/*70  */     s->channel_offsets[3] = -1;                                                                                                       // (9) 0.03078
/*72  */     s->bits_per_color_id = -1;                                                                                                        // 0.0
/*74  */     s->compr = -1;                                                                                                                    // 0.0
/*78  */     if (buf_size < 10) {                                                                                                              // 0.0
/*80  */         av_log(avctx, AV_LOG_ERROR, "Too short header to parse\n");                                                                   // 0.0
/*82  */         return AVERROR_INVALIDDATA;                                                                                                   // 0.0
/*84  */     }                                                                                                                                 // 0.0
/*88  */     magic_number = bytestream_get_le32(&buf);                                                                                         // 0.0
/*90  */     if (magic_number != 20000630) { // As per documentation of OpenEXR it's supposed to be int 20000630 little-endian                 // 0.0
/*92  */         av_log(avctx, AV_LOG_ERROR, "Wrong magic number %d\n", magic_number);                                                         // 0.0
/*94  */         return AVERROR_INVALIDDATA;                                                                                                   // 0.0
/*96  */     }                                                                                                                                 // 0.0
/*100 */     version = bytestream_get_byte(&buf);                                                                                              // 0.0
/*102 */     if (version != 2) {                                                                                                               // 0.0
/*104 */         av_log(avctx, AV_LOG_ERROR, "Unsupported version %d\n", version);                                                             // 0.0
/*106 */         return AVERROR_PATCHWELCOME;                                                                                                  // 0.0
/*108 */     }                                                                                                                                 // 0.0
/*112 */     flags = bytestream_get_le24(&buf);                                                                                                // 0.0
/*114 */     if (flags & 0x2) {                                                                                                                // 0.0
/*116 */         av_log(avctx, AV_LOG_ERROR, "Tile based images are not supported\n");                                                         // 0.0
/*118 */         return AVERROR_PATCHWELCOME;                                                                                                  // 0.0
/*120 */     }                                                                                                                                 // 0.0
/*124 */     // Parse the header                                                                                                               // 0.0
/*126 */     while (buf < buf_end && buf[0]) {                                                                                                 // 0.0
/*128 */         unsigned int variable_buffer_data_size;                                                                                       // 0.0
/*130 */         // Process the channel list                                                                                                   // 0.0
/*132 */         if (check_header_variable(avctx, &buf, buf_end, "channels", "chlist", 38, &variable_buffer_data_size) >= 0) {                 // 0.0
/*134 */             const uint8_t *channel_list_end;                                                                                          // 0.0
/*136 */             if (!variable_buffer_data_size)                                                                                           // 0.0
/*138 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*142 */             channel_list_end = buf + variable_buffer_data_size;                                                                       // 0.0
/*144 */             while (channel_list_end - buf >= 19) {                                                                                    // 0.0
/*146 */                 int current_bits_per_color_id = -1;                                                                                   // 0.0
/*148 */                 int channel_index = -1;                                                                                               // 0.0
/*152 */                 if (!strcmp(buf, "R"))                                                                                                // 0.0
/*154 */                     channel_index = 0;                                                                                                // 0.0
/*156 */                 else if (!strcmp(buf, "G"))                                                                                           // 0.0
/*158 */                     channel_index = 1;                                                                                                // 0.0
/*160 */                 else if (!strcmp(buf, "B"))                                                                                           // 0.0
/*162 */                     channel_index = 2;                                                                                                // 0.0
/*164 */                 else if (!strcmp(buf, "A"))                                                                                           // 0.0
/*166 */                     channel_index = 3;                                                                                                // 0.0
/*168 */                 else                                                                                                                  // 0.0
/*170 */                     av_log(avctx, AV_LOG_WARNING, "Unsupported channel %.256s\n", buf);                                               // 0.0
/*174 */                 while (bytestream_get_byte(&buf) && buf < channel_list_end)                                                           // 0.0
/*176 */                     continue; /* skip */                                                                                              // 0.0
/*180 */                 if (channel_list_end - * &buf < 4) {                                                                                  // 0.0
/*182 */                     av_log(avctx, AV_LOG_ERROR, "Incomplete header\n");                                                               // 0.0
/*184 */                     return AVERROR_INVALIDDATA;                                                                                       // 0.0
/*186 */                 }                                                                                                                     // 0.0
/*190 */                 current_bits_per_color_id = bytestream_get_le32(&buf);                                                                // 0.0
/*192 */                 if (current_bits_per_color_id > 2) {                                                                                  // 0.0
/*194 */                     av_log(avctx, AV_LOG_ERROR, "Unknown color format\n");                                                            // 0.0
/*196 */                     return AVERROR_INVALIDDATA;                                                                                       // 0.0
/*198 */                 }                                                                                                                     // 0.0
/*202 */                 if (channel_index >= 0) {                                                                                             // 0.0
/*204 */                     if (s->bits_per_color_id != -1 && s->bits_per_color_id != current_bits_per_color_id) {                            // 0.0
/*206 */                         av_log(avctx, AV_LOG_ERROR, "RGB channels not of the same depth\n");                                          // 0.0
/*208 */                         return AVERROR_INVALIDDATA;                                                                                   // 0.0
/*210 */                     }                                                                                                                 // 0.0
/*212 */                     s->bits_per_color_id  = current_bits_per_color_id;                                                                // 0.0
/*214 */                     s->channel_offsets[channel_index] = current_channel_offset;                                                       // 0.0
/*216 */                 }                                                                                                                     // 0.0
/*220 */                 current_channel_offset += 1 << current_bits_per_color_id;                                                             // 0.0
/*222 */                 buf += 12;                                                                                                            // 0.0
/*224 */             }                                                                                                                         // 0.0
/*228 */             /* Check if all channels are set with an offset or if the channels                                                        // 0.0
/*230 */              * are causing an overflow  */                                                                                            // 0.0
/*234 */             if (FFMIN3(s->channel_offsets[0],                                                                                         // 0.0
/*236 */                        s->channel_offsets[1],                                                                                         // 0.0
/*238 */                        s->channel_offsets[2]) < 0) {                                                                                  // 0.0
/*240 */                 if (s->channel_offsets[0] < 0)                                                                                        // 0.0
/*242 */                     av_log(avctx, AV_LOG_ERROR, "Missing red channel\n");                                                             // 0.0
/*244 */                 if (s->channel_offsets[1] < 0)                                                                                        // 0.0
/*246 */                     av_log(avctx, AV_LOG_ERROR, "Missing green channel\n");                                                           // 0.0
/*248 */                 if (s->channel_offsets[2] < 0)                                                                                        // 0.0
/*250 */                     av_log(avctx, AV_LOG_ERROR, "Missing blue channel\n");                                                            // 0.0
/*252 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*254 */             }                                                                                                                         // 0.0
/*258 */             buf = channel_list_end;                                                                                                   // 0.0
/*260 */             continue;                                                                                                                 // 0.0
/*262 */         } else if (check_header_variable(avctx, &buf, buf_end, "dataWindow", "box2i", 31, &variable_buffer_data_size) >= 0) {         // 0.0
/*264 */             if (!variable_buffer_data_size)                                                                                           // 0.0
/*266 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*270 */             xmin = AV_RL32(buf);                                                                                                      // 0.0
/*272 */             ymin = AV_RL32(buf + 4);                                                                                                  // 0.0
/*274 */             xmax = AV_RL32(buf + 8);                                                                                                  // 0.0
/*276 */             ymax = AV_RL32(buf + 12);                                                                                                 // 0.0
/*278 */             xdelta = (xmax-xmin) + 1;                                                                                                 // 0.0
/*282 */             buf += variable_buffer_data_size;                                                                                         // 0.0
/*284 */             continue;                                                                                                                 // 0.0
/*286 */         } else if (check_header_variable(avctx, &buf, buf_end, "displayWindow", "box2i", 34, &variable_buffer_data_size) >= 0) {      // 0.0
/*288 */             if (!variable_buffer_data_size)                                                                                           // 0.0
/*290 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*294 */             w = AV_RL32(buf + 8) + 1;                                                                                                 // 0.0
/*296 */             h = AV_RL32(buf + 12) + 1;                                                                                                // 0.0
/*300 */             buf += variable_buffer_data_size;                                                                                         // 0.0
/*302 */             continue;                                                                                                                 // 0.0
/*304 */         } else if (check_header_variable(avctx, &buf, buf_end, "lineOrder", "lineOrder", 25, &variable_buffer_data_size) >= 0) {      // 0.0
/*306 */             if (!variable_buffer_data_size)                                                                                           // 0.0
/*308 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*312 */             if (*buf) {                                                                                                               // 0.0
/*314 */                 av_log(avctx, AV_LOG_ERROR, "Doesn't support this line order : %d\n", *buf);                                          // 0.0
/*316 */                 return AVERROR_PATCHWELCOME;                                                                                          // 0.0
/*318 */             }                                                                                                                         // 0.0
/*322 */             buf += variable_buffer_data_size;                                                                                         // 0.0
/*324 */             continue;                                                                                                                 // 0.0
/*326 */         } else if (check_header_variable(avctx, &buf, buf_end, "pixelAspectRatio", "float", 31, &variable_buffer_data_size) >= 0) {   // 0.0
/*328 */             if (!variable_buffer_data_size)                                                                                           // 0.0
/*330 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*334 */             avctx->sample_aspect_ratio = av_d2q(av_int2float(AV_RL32(buf)), 255);                                                     // 0.0
/*338 */             buf += variable_buffer_data_size;                                                                                         // 0.0
/*340 */             continue;                                                                                                                 // 0.0
/*342 */         } else if (check_header_variable(avctx, &buf, buf_end, "compression", "compression", 29, &variable_buffer_data_size) >= 0) {  // 0.0
/*344 */             if (!variable_buffer_data_size)                                                                                           // 0.0
/*346 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*350 */             if (s->compr == -1)                                                                                                       // 0.0
/*352 */                 s->compr = *buf;                                                                                                      // 0.0
/*354 */             else                                                                                                                      // 0.0
/*356 */                 av_log(avctx, AV_LOG_WARNING, "Found more than one compression attribute\n");                                         // 0.0
/*360 */             buf += variable_buffer_data_size;                                                                                         // 0.0
/*362 */             continue;                                                                                                                 // 0.0
/*364 */         }                                                                                                                             // 0.0
/*368 */         // Check if there is enough bytes for a header                                                                                // 0.0
/*370 */         if (buf_end - buf <= 9) {                                                                                                     // 0.0
/*372 */             av_log(avctx, AV_LOG_ERROR, "Incomplete header\n");                                                                       // 0.0
/*374 */             return AVERROR_INVALIDDATA;                                                                                               // 0.0
/*376 */         }                                                                                                                             // 0.0
/*380 */         // Process unknown variables                                                                                                  // 0.0
/*382 */         for (i = 0; i < 2; i++) {                                                                                                     // 0.0
/*384 */             // Skip variable name/type                                                                                                // 0.0
/*386 */             while (++buf < buf_end)                                                                                                   // 0.0
/*388 */                 if (buf[0] == 0x0)                                                                                                    // 0.0
/*390 */                     break;                                                                                                            // 0.0
/*392 */         }                                                                                                                             // 0.0
/*394 */         buf++;                                                                                                                        // 0.0
/*396 */         // Skip variable length                                                                                                       // 0.0
/*398 */         if (buf_end - buf >= 5) {                                                                                                     // 0.0
/*400 */             variable_buffer_data_size = get_header_variable_length(&buf, buf_end);                                                    // 0.0
/*402 */             if (!variable_buffer_data_size) {                                                                                         // 0.0
/*404 */                 av_log(avctx, AV_LOG_ERROR, "Incomplete header\n");                                                                   // 0.0
/*406 */                 return AVERROR_INVALIDDATA;                                                                                           // 0.0
/*408 */             }                                                                                                                         // 0.0
/*410 */             buf += variable_buffer_data_size;                                                                                         // 0.0
/*412 */         }                                                                                                                             // 0.0
/*414 */     }                                                                                                                                 // 0.0
/*418 */     if (s->compr == -1) {                                                                                                             // 0.0
/*420 */         av_log(avctx, AV_LOG_ERROR, "Missing compression attribute\n");                                                               // 0.0
/*422 */         return AVERROR_INVALIDDATA;                                                                                                   // 0.0
/*424 */     }                                                                                                                                 // 0.0
/*428 */     if (buf >= buf_end) {                                                                                                             // 0.0
/*430 */         av_log(avctx, AV_LOG_ERROR, "Incomplete frame\n");                                                                            // 0.0
/*432 */         return AVERROR_INVALIDDATA;                                                                                                   // 0.0
/*434 */     }                                                                                                                                 // 0.0
/*436 */     buf++;                                                                                                                            // 0.0
/*440 */     switch (s->bits_per_color_id) {                                                                                                   // 0.0
/*442 */     case 2: // 32-bit                                                                                                                 // 0.0
/*444 */     case 1: // 16-bit                                                                                                                 // 0.0
/*446 */         if (s->channel_offsets[3] >= 0)                                                                                               // 0.0
/*448 */             avctx->pix_fmt = AV_PIX_FMT_RGBA64;                                                                                       // 0.0
/*450 */         else                                                                                                                          // 0.0
/*452 */             avctx->pix_fmt = AV_PIX_FMT_RGB48;                                                                                        // 0.0
/*454 */         break;                                                                                                                        // 0.0
/*456 */     // 8-bit                                                                                                                          // 0.0
/*458 */     case 0:                                                                                                                           // 0.0
/*460 */         av_log_missing_feature(avctx, "8-bit OpenEXR", 1);                                                                            // 0.0
/*462 */         return AVERROR_PATCHWELCOME;                                                                                                  // 0.0
/*464 */     default:                                                                                                                          // 0.0
/*466 */         av_log(avctx, AV_LOG_ERROR, "Unknown color format : %d\n", s->bits_per_color_id);                                             // 0.0
/*468 */         return AVERROR_INVALIDDATA;                                                                                                   // 0.0
/*470 */     }                                                                                                                                 // 0.0
/*474 */     switch (s->compr) {                                                                                                               // 0.0
/*476 */     case EXR_RAW:                                                                                                                     // 0.0
/*478 */     case EXR_RLE:                                                                                                                     // 0.0
/*480 */     case EXR_ZIP1:                                                                                                                    // 0.0
/*482 */         scan_lines_per_block = 1;                                                                                                     // 0.0
/*484 */         break;                                                                                                                        // 0.0
/*486 */     case EXR_ZIP16:                                                                                                                   // 0.0
/*488 */         scan_lines_per_block = 16;                                                                                                    // 0.0
/*490 */         break;                                                                                                                        // 0.0
/*492 */     default:                                                                                                                          // 0.0
/*494 */         av_log(avctx, AV_LOG_ERROR, "Compression type %d is not supported\n", s->compr);                                              // 0.0
/*496 */         return AVERROR_PATCHWELCOME;                                                                                                  // 0.0
/*498 */     }                                                                                                                                 // 0.0
/*502 */     if (s->picture.data[0])                                                                                                           // 0.0
/*504 */         ff_thread_release_buffer(avctx, &s->picture);                                                                                 // 0.0
/*506 */     if (av_image_check_size(w, h, 0, avctx))                                                                                          // 0.0
/*508 */         return AVERROR_INVALIDDATA;                                                                                                   // 0.0
/*512 */     // Verify the xmin, xmax, ymin, ymax and xdelta before setting the actual image size                                              // 0.0
/*514 */     if (xmin > xmax || ymin > ymax || xdelta != xmax - xmin + 1 || xmax >= w || ymax >= h) {                                          // 0.0
/*516 */         av_log(avctx, AV_LOG_ERROR, "Wrong sizing or missing size information\n");                                                    // 0.0
/*518 */         return AVERROR_INVALIDDATA;                                                                                                   // 0.0
/*520 */     }                                                                                                                                 // 0.0
/*524 */     if (w != avctx->width || h != avctx->height) {                                                                                    // 0.0
/*526 */         avcodec_set_dimensions(avctx, w, h);                                                                                          // 0.0
/*528 */     }                                                                                                                                 // 0.0
/*532 */     desc = av_pix_fmt_desc_get(avctx->pix_fmt);                                                                                       // 0.0
/*534 */     bxmin = xmin * 2 * desc->nb_components;                                                                                           // 0.0
/*536 */     axmax = (avctx->width - (xmax + 1)) * 2 * desc->nb_components;                                                                    // 0.0
/*538 */     out_line_size = avctx->width * 2 * desc->nb_components;                                                                           // 0.0
/*540 */     scan_line_size = xdelta * current_channel_offset;                                                                                 // 0.0
/*542 */     uncompressed_size = scan_line_size * scan_lines_per_block;                                                                        // 0.0
/*546 */     if (s->compr != EXR_RAW) {                                                                                                        // 0.0
/*548 */         av_fast_padded_malloc(&s->uncompressed_data, &s->uncompressed_size, uncompressed_size);                                       // 0.0
/*550 */         av_fast_padded_malloc(&s->tmp, &s->tmp_size, uncompressed_size);                                                              // 0.0
/*552 */         if (!s->uncompressed_data || !s->tmp)                                                                                         // 0.0
/*554 */             return AVERROR(ENOMEM);                                                                                                   // 0.0
/*556 */     }                                                                                                                                 // 0.0
/*560 */     if ((ret = ff_thread_get_buffer(avctx, p)) < 0) {                                                                                 // 0.0
/*562 */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                                                         // 0.0
/*564 */         return ret;                                                                                                                   // 0.0
/*566 */     }                                                                                                                                 // 0.0
/*570 */     ptr    = p->data[0];                                                                                                              // 0.0
/*572 */     stride = p->linesize[0];                                                                                                          // 0.0
/*576 */     // Zero out the start if ymin is not 0                                                                                            // 0.0
/*578 */     for (y = 0; y < ymin; y++) {                                                                                                      // 0.0
/*580 */         memset(ptr, 0, out_line_size);                                                                                                // 0.0
/*582 */         ptr += stride;                                                                                                                // 0.0
/*584 */     }                                                                                                                                 // 0.0
/*588 */     // Process the actual scan line blocks                                                                                            // 0.0
/*590 */     for (y = ymin; y <= ymax; y += scan_lines_per_block) {                                                                            // 0.0
/*592 */         uint16_t *ptr_x = (uint16_t *)ptr;                                                                                            // 0.0
/*594 */         if (buf_end - buf > 8) {                                                                                                      // 0.0
/*596 */             /* Read the lineoffset from the line offset table and add 8 bytes                                                         // 0.0
/*598 */                to skip the coordinates and data size fields */                                                                        // 0.0
/*600 */             const uint64_t line_offset = bytestream_get_le64(&buf) + 8;                                                               // 0.0
/*602 */             int32_t data_size;                                                                                                        // 0.0
/*606 */             // Check if the buffer has the required bytes needed from the offset                                                      // 0.0
/*608 */             if ((line_offset > buf_size) ||                                                                                           // 0.0
/*610 */                 (s->compr == EXR_RAW && line_offset > avpkt->size - xdelta * current_channel_offset) ||                               // 0.0
/*612 */                 (s->compr != EXR_RAW && line_offset > buf_size - (data_size = AV_RL32(avpkt->data + line_offset - 4)))) {             // 0.0
/*614 */                 // Line offset is probably wrong and not inside the buffer                                                            // 0.0
/*616 */                 av_log(avctx, AV_LOG_WARNING, "Line offset for line %d is out of reach setting it to black\n", y);                    // 0.0
/*618 */                 for (i = 0; i < scan_lines_per_block && y + i <= ymax; i++, ptr += stride) {                                          // 0.0
/*620 */                     ptr_x = (uint16_t *)ptr;                                                                                          // 0.0
/*622 */                     memset(ptr_x, 0, out_line_size);                                                                                  // 0.0
/*624 */                 }                                                                                                                     // 0.0
/*626 */             } else {                                                                                                                  // 0.0
/*628 */                 const uint8_t *red_channel_buffer, *green_channel_buffer, *blue_channel_buffer, *alpha_channel_buffer = 0;            // 0.0
/*632 */                 if (scan_lines_per_block > 1)                                                                                         // 0.0
/*634 */                     uncompressed_size = scan_line_size * FFMIN(scan_lines_per_block, ymax - y + 1);                                   // 0.0
/*636 */                 if ((s->compr == EXR_ZIP1 || s->compr == EXR_ZIP16) && data_size < uncompressed_size) {                               // 0.0
/*638 */                     unsigned long dest_len = uncompressed_size;                                                                       // 0.0
/*642 */                     if (uncompress(s->tmp, &dest_len, avpkt->data + line_offset, data_size) != Z_OK ||                                // 0.0
/*644 */                         dest_len != uncompressed_size) {                                                                              // 0.0
/*646 */                         av_log(avctx, AV_LOG_ERROR, "error during zlib decompression\n");                                             // 0.0
/*648 */                         return AVERROR(EINVAL);                                                                                       // 0.0
/*650 */                     }                                                                                                                 // 0.0
/*652 */                 } else if (s->compr == EXR_RLE && data_size < uncompressed_size) {                                                    // 0.0
/*654 */                     if (rle_uncompress(avpkt->data + line_offset, data_size, s->tmp, uncompressed_size)) {                            // 0.0
/*656 */                         av_log(avctx, AV_LOG_ERROR, "error during rle decompression\n");                                              // 0.0
/*658 */                         return AVERROR(EINVAL);                                                                                       // 0.0
/*660 */                     }                                                                                                                 // 0.0
/*662 */                 }                                                                                                                     // 0.0
/*666 */                 if (s->compr != EXR_RAW && data_size < uncompressed_size) {                                                           // 0.0
/*668 */                     predictor(s->tmp, uncompressed_size);                                                                             // 0.0
/*670 */                     reorder_pixels(s->tmp, s->uncompressed_data, uncompressed_size);                                                  // 0.0
/*674 */                     red_channel_buffer   = s->uncompressed_data + xdelta * s->channel_offsets[0];                                     // 0.0
/*676 */                     green_channel_buffer = s->uncompressed_data + xdelta * s->channel_offsets[1];                                     // 0.0
/*678 */                     blue_channel_buffer  = s->uncompressed_data + xdelta * s->channel_offsets[2];                                     // 0.0
/*680 */                     if (s->channel_offsets[3] >= 0)                                                                                   // 0.0
/*682 */                         alpha_channel_buffer = s->uncompressed_data + xdelta * s->channel_offsets[3];                                 // 0.0
/*684 */                 } else {                                                                                                              // 0.0
/*686 */                     red_channel_buffer   = avpkt->data + line_offset + xdelta * s->channel_offsets[0];                                // 0.0
/*688 */                     green_channel_buffer = avpkt->data + line_offset + xdelta * s->channel_offsets[1];                                // 0.0
/*690 */                     blue_channel_buffer  = avpkt->data + line_offset + xdelta * s->channel_offsets[2];                                // 0.0
/*692 */                     if (s->channel_offsets[3] >= 0)                                                                                   // 0.0
/*694 */                         alpha_channel_buffer = avpkt->data + line_offset + xdelta * s->channel_offsets[3];                            // 0.0
/*696 */                 }                                                                                                                     // 0.0
/*700 */                 for (i = 0; i < scan_lines_per_block && y + i <= ymax; i++, ptr += stride) {                                          // 0.0
/*702 */                     const uint8_t *r, *g, *b, *a;                                                                                     // 0.0
/*706 */                     r = red_channel_buffer;                                                                                           // 0.0
/*708 */                     g = green_channel_buffer;                                                                                         // 0.0
/*710 */                     b = blue_channel_buffer;                                                                                          // 0.0
/*712 */                     if (alpha_channel_buffer)                                                                                         // 0.0
/*714 */                         a = alpha_channel_buffer;                                                                                     // 0.0
/*718 */                     ptr_x = (uint16_t *)ptr;                                                                                          // 0.0
/*722 */                     // Zero out the start if xmin is not 0                                                                            // 0.0
/*724 */                     memset(ptr_x, 0, bxmin);                                                                                          // 0.0
/*726 */                     ptr_x += xmin * desc->nb_components;                                                                              // 0.0
/*728 */                     if (s->bits_per_color_id == 2) {                                                                                  // 0.0
/*730 */                         // 32-bit                                                                                                     // 0.0
/*732 */                         for (x = 0; x < xdelta; x++) {                                                                                // 0.0
/*734 */                             *ptr_x++ = exr_flt2uint(bytestream_get_le32(&r));                                                         // 0.0
/*736 */                             *ptr_x++ = exr_flt2uint(bytestream_get_le32(&g));                                                         // 0.0
/*738 */                             *ptr_x++ = exr_flt2uint(bytestream_get_le32(&b));                                                         // 0.0
/*740 */                             if (alpha_channel_buffer)                                                                                 // 0.0
/*742 */                                 *ptr_x++ = exr_flt2uint(bytestream_get_le32(&a));                                                     // 0.0
/*744 */                         }                                                                                                             // 0.0
/*746 */                     } else {                                                                                                          // 0.0
/*748 */                         // 16-bit                                                                                                     // 0.0
/*750 */                         for (x = 0; x < xdelta; x++) {                                                                                // 0.0
/*752 */                             *ptr_x++ = exr_halflt2uint(bytestream_get_le16(&r));                                                      // 0.0
/*754 */                             *ptr_x++ = exr_halflt2uint(bytestream_get_le16(&g));                                                      // 0.0
/*756 */                             *ptr_x++ = exr_halflt2uint(bytestream_get_le16(&b));                                                      // 0.0
/*758 */                             if (alpha_channel_buffer)                                                                                 // 0.0
/*760 */                                 *ptr_x++ = exr_halflt2uint(bytestream_get_le16(&a));                                                  // 0.0
/*762 */                         }                                                                                                             // 0.0
/*764 */                     }                                                                                                                 // 0.0
/*768 */                     // Zero out the end if xmax+1 is not w                                                                            // 0.0
/*770 */                     memset(ptr_x, 0, axmax);                                                                                          // 0.0
/*774 */                     red_channel_buffer   += scan_line_size;                                                                           // 0.0
/*776 */                     green_channel_buffer += scan_line_size;                                                                           // 0.0
/*778 */                     blue_channel_buffer  += scan_line_size;                                                                           // 0.0
/*780 */                     if (alpha_channel_buffer)                                                                                         // 0.0
/*782 */                         alpha_channel_buffer += scan_line_size;                                                                       // 0.0
/*784 */                 }                                                                                                                     // 0.0
/*786 */             }                                                                                                                         // 0.0
/*788 */         }                                                                                                                             // 0.0
/*790 */     }                                                                                                                                 // 0.0
/*794 */     // Zero out the end if ymax+1 is not h                                                                                            // 0.0
/*796 */     for (y = ymax + 1; y < avctx->height; y++) {                                                                                      // 0.0
/*798 */         memset(ptr, 0, out_line_size);                                                                                                // 0.0
/*800 */         ptr += stride;                                                                                                                // 0.0
/*802 */     }                                                                                                                                 // 0.0
/*806 */     *picture   = s->picture;                                                                                                          // 0.0
/*808 */     *got_frame = 1;                                                                                                                   // 0.0
/*812 */     return buf_size;                                                                                                                  // 0.0
/*814 */ }                                                                                                                                     // 0.0

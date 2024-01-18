// commit message FFmpeg@c776531aef (target=0, prob=0.58338016, correct=False): vqavideo: change x/y loop counters to the usual pattern
/*0   */ static int vqa_decode_chunk(VqaContext *s)                                                                  // (6) 0.03323
/*2   */ {                                                                                                           // (34) 0.001955
/*4   */     unsigned int chunk_type;                                                                                // (25) 0.01758
/*6   */     unsigned int chunk_size;                                                                                // (24) 0.01758
/*8   */     int byte_skip;                                                                                          // (27) 0.01565
/*10  */     unsigned int index = 0;                                                                                 // (26) 0.01758
/*12  */     int i;                                                                                                  // (33) 0.01172
/*14  */     unsigned char r, g, b;                                                                                  // (19) 0.02148
/*16  */     int index_shift;                                                                                        // (30) 0.01563
/*18  */     int res;                                                                                                // (32) 0.01176
/*22  */     int cbf0_chunk = -1;                                                                                    // (9) 0.02734
/*24  */     int cbfz_chunk = -1;                                                                                    // (11) 0.02734
/*26  */     int cbp0_chunk = -1;                                                                                    // (14) 0.02734
/*28  */     int cbpz_chunk = -1;                                                                                    // (15) 0.02734
/*30  */     int cpl0_chunk = -1;                                                                                    // (16) 0.02734
/*32  */     int cplz_chunk = -1;                                                                                    // (17) 0.02734
/*34  */     int vptz_chunk = -1;                                                                                    // (10) 0.02734
/*38  */     int x, y;                                                                                               // (31) 0.01562
/*40  */     int lines = 0;                                                                                          // (29) 0.01563
/*42  */     int pixel_ptr;                                                                                          // (28) 0.01564
/*44  */     int vector_index = 0;                                                                                   // (21) 0.01953
/*46  */     int lobyte = 0;                                                                                         // (22) 0.01953
/*48  */     int hibyte = 0;                                                                                         // (20) 0.02148
/*50  */     int lobytes = 0;                                                                                        // (23) 0.01953
/*52  */     int hibytes = s->decode_buffer_size / 2;                                                                // (4) 0.03906
/*56  */     /* first, traverse through the frame and find the subchunks */                                          // (7) 0.0332
/*58  */     while (bytestream2_get_bytes_left(&s->gb) >= 8) {                                                       // (3) 0.04687
/*62  */         chunk_type = bytestream2_get_be32u(&s->gb);                                                         // (0) 0.05077
/*64  */         index      = bytestream2_tell(&s->gb);                                                              // (2) 0.04882
/*66  */         chunk_size = bytestream2_get_be32u(&s->gb);                                                         // (1) 0.05077
/*70  */         switch (chunk_type) {                                                                               // (8) 0.02929
/*74  */         case CBF0_TAG:                                                                                      // (13) 0.02734
/*76  */             cbf0_chunk = index;                                                                             // (5) 0.03906
/*78  */             break;                                                                                          // (18) 0.02539
/*82  */         case CBFZ_TAG:                                                                                      // (12) 0.02734
/*84  */             cbfz_chunk = index;                                                                             // 0.0
/*86  */             break;                                                                                          // 0.0
/*90  */         case CBP0_TAG:                                                                                      // 0.0
/*92  */             cbp0_chunk = index;                                                                             // 0.0
/*94  */             break;                                                                                          // 0.0
/*98  */         case CBPZ_TAG:                                                                                      // 0.0
/*100 */             cbpz_chunk = index;                                                                             // 0.0
/*102 */             break;                                                                                          // 0.0
/*106 */         case CPL0_TAG:                                                                                      // 0.0
/*108 */             cpl0_chunk = index;                                                                             // 0.0
/*110 */             break;                                                                                          // 0.0
/*114 */         case CPLZ_TAG:                                                                                      // 0.0
/*116 */             cplz_chunk = index;                                                                             // 0.0
/*118 */             break;                                                                                          // 0.0
/*122 */         case VPTZ_TAG:                                                                                      // 0.0
/*124 */             vptz_chunk = index;                                                                             // 0.0
/*126 */             break;                                                                                          // 0.0
/*130 */         default:                                                                                            // 0.0
/*132 */             av_log(s->avctx, AV_LOG_ERROR, "  VQA video: Found unknown chunk type: %c%c%c%c (%08X)\n",      // 0.0
/*134 */             (chunk_type >> 24) & 0xFF,                                                                      // 0.0
/*136 */             (chunk_type >> 16) & 0xFF,                                                                      // 0.0
/*138 */             (chunk_type >>  8) & 0xFF,                                                                      // 0.0
/*140 */             (chunk_type >>  0) & 0xFF,                                                                      // 0.0
/*142 */             chunk_type);                                                                                    // 0.0
/*144 */             break;                                                                                          // 0.0
/*146 */         }                                                                                                   // 0.0
/*150 */         byte_skip = chunk_size & 0x01;                                                                      // 0.0
/*152 */         bytestream2_skip(&s->gb, chunk_size + byte_skip);                                                   // 0.0
/*154 */     }                                                                                                       // 0.0
/*158 */     /* next, deal with the palette */                                                                       // 0.0
/*160 */     if ((cpl0_chunk != -1) && (cplz_chunk != -1)) {                                                         // 0.0
/*164 */         /* a chunk should not have both chunk types */                                                      // 0.0
/*166 */         av_log(s->avctx, AV_LOG_ERROR, "  VQA video: problem: found both CPL0 and CPLZ chunks\n");          // 0.0
/*168 */         return AVERROR_INVALIDDATA;                                                                         // 0.0
/*170 */     }                                                                                                       // 0.0
/*174 */     /* decompress the palette chunk */                                                                      // 0.0
/*176 */     if (cplz_chunk != -1) {                                                                                 // 0.0
/*180 */ /* yet to be handled */                                                                                     // 0.0
/*184 */     }                                                                                                       // 0.0
/*188 */     /* convert the RGB palette into the machine's endian format */                                          // 0.0
/*190 */     if (cpl0_chunk != -1) {                                                                                 // 0.0
/*194 */         bytestream2_seek(&s->gb, cpl0_chunk, SEEK_SET);                                                     // 0.0
/*196 */         chunk_size = bytestream2_get_be32(&s->gb);                                                          // 0.0
/*198 */         /* sanity check the palette size */                                                                 // 0.0
/*200 */         if (chunk_size / 3 > 256 || chunk_size > bytestream2_get_bytes_left(&s->gb)) {                      // 0.0
/*202 */             av_log(s->avctx, AV_LOG_ERROR, "  VQA video: problem: found a palette chunk with %d colors\n",  // 0.0
/*204 */                 chunk_size / 3);                                                                            // 0.0
/*206 */             return AVERROR_INVALIDDATA;                                                                     // 0.0
/*208 */         }                                                                                                   // 0.0
/*210 */         for (i = 0; i < chunk_size / 3; i++) {                                                              // 0.0
/*212 */             /* scale by 4 to transform 6-bit palette -> 8-bit */                                            // 0.0
/*214 */             r = bytestream2_get_byteu(&s->gb) * 4;                                                          // 0.0
/*216 */             g = bytestream2_get_byteu(&s->gb) * 4;                                                          // 0.0
/*218 */             b = bytestream2_get_byteu(&s->gb) * 4;                                                          // 0.0
/*220 */             s->palette[i] = (r << 16) | (g << 8) | (b);                                                     // 0.0
/*222 */         }                                                                                                   // 0.0
/*224 */     }                                                                                                       // 0.0
/*228 */     /* next, look for a full codebook */                                                                    // 0.0
/*230 */     if ((cbf0_chunk != -1) && (cbfz_chunk != -1)) {                                                         // 0.0
/*234 */         /* a chunk should not have both chunk types */                                                      // 0.0
/*236 */         av_log(s->avctx, AV_LOG_ERROR, "  VQA video: problem: found both CBF0 and CBFZ chunks\n");          // 0.0
/*238 */         return AVERROR_INVALIDDATA;                                                                         // 0.0
/*240 */     }                                                                                                       // 0.0
/*244 */     /* decompress the full codebook chunk */                                                                // 0.0
/*246 */     if (cbfz_chunk != -1) {                                                                                 // 0.0
/*250 */         bytestream2_seek(&s->gb, cbfz_chunk, SEEK_SET);                                                     // 0.0
/*252 */         chunk_size = bytestream2_get_be32(&s->gb);                                                          // 0.0
/*254 */         if ((res = decode_format80(&s->gb, chunk_size, s->codebook,                                         // 0.0
/*256 */                                    s->codebook_size, 0)) < 0)                                               // 0.0
/*258 */             return res;                                                                                     // 0.0
/*260 */     }                                                                                                       // 0.0
/*264 */     /* copy a full codebook */                                                                              // 0.0
/*266 */     if (cbf0_chunk != -1) {                                                                                 // 0.0
/*270 */         bytestream2_seek(&s->gb, cbf0_chunk, SEEK_SET);                                                     // 0.0
/*272 */         chunk_size = bytestream2_get_be32(&s->gb);                                                          // 0.0
/*274 */         /* sanity check the full codebook size */                                                           // 0.0
/*276 */         if (chunk_size > MAX_CODEBOOK_SIZE) {                                                               // 0.0
/*278 */             av_log(s->avctx, AV_LOG_ERROR, "  VQA video: problem: CBF0 chunk too large (0x%X bytes)\n",     // 0.0
/*280 */                 chunk_size);                                                                                // 0.0
/*282 */             return AVERROR_INVALIDDATA;                                                                     // 0.0
/*284 */         }                                                                                                   // 0.0
/*288 */         bytestream2_get_buffer(&s->gb, s->codebook, chunk_size);                                            // 0.0
/*290 */     }                                                                                                       // 0.0
/*294 */     /* decode the frame */                                                                                  // 0.0
/*296 */     if (vptz_chunk == -1) {                                                                                 // 0.0
/*300 */         /* something is wrong if there is no VPTZ chunk */                                                  // 0.0
/*302 */         av_log(s->avctx, AV_LOG_ERROR, "  VQA video: problem: no VPTZ chunk found\n");                      // 0.0
/*304 */         return AVERROR_INVALIDDATA;                                                                         // 0.0
/*306 */     }                                                                                                       // 0.0
/*310 */     bytestream2_seek(&s->gb, vptz_chunk, SEEK_SET);                                                         // 0.0
/*312 */     chunk_size = bytestream2_get_be32(&s->gb);                                                              // 0.0
/*314 */     if ((res = decode_format80(&s->gb, chunk_size,                                                          // 0.0
/*316 */                                s->decode_buffer, s->decode_buffer_size, 1)) < 0)                            // 0.0
/*318 */         return res;                                                                                         // 0.0
/*322 */     /* render the final PAL8 frame */                                                                       // 0.0
/*324 */     if (s->vector_height == 4)                                                                              // 0.0
/*326 */         index_shift = 4;                                                                                    // 0.0
/*328 */     else                                                                                                    // 0.0
/*330 */         index_shift = 3;                                                                                    // 0.0
/*332 */     for (y = 0; y < s->frame.linesize[0] * s->height;                                                       // 0.0
/*334 */         y += s->frame.linesize[0] * s->vector_height) {                                                     // 0.0
/*338 */         for (x = y; x < y + s->width; x += 4, lobytes++, hibytes++) {                                       // 0.0
/*340 */             pixel_ptr = x;                                                                                  // 0.0
/*344 */             /* get the vector index, the method for which varies according to                               // 0.0
/*346 */              * VQA file version */                                                                          // 0.0
/*348 */             switch (s->vqa_version) {                                                                       // 0.0
/*352 */             case 1:                                                                                         // 0.0
/*354 */                 lobyte = s->decode_buffer[lobytes * 2];                                                     // 0.0
/*356 */                 hibyte = s->decode_buffer[(lobytes * 2) + 1];                                               // 0.0
/*358 */                 vector_index = ((hibyte << 8) | lobyte) >> 3;                                               // 0.0
/*360 */                 vector_index <<= index_shift;                                                               // 0.0
/*362 */                 lines = s->vector_height;                                                                   // 0.0
/*364 */                 /* uniform color fill - a quick hack */                                                     // 0.0
/*366 */                 if (hibyte == 0xFF) {                                                                       // 0.0
/*368 */                     while (lines--) {                                                                       // 0.0
/*370 */                         s->frame.data[0][pixel_ptr + 0] = 255 - lobyte;                                     // 0.0
/*372 */                         s->frame.data[0][pixel_ptr + 1] = 255 - lobyte;                                     // 0.0
/*374 */                         s->frame.data[0][pixel_ptr + 2] = 255 - lobyte;                                     // 0.0
/*376 */                         s->frame.data[0][pixel_ptr + 3] = 255 - lobyte;                                     // 0.0
/*378 */                         pixel_ptr += s->frame.linesize[0];                                                  // 0.0
/*380 */                     }                                                                                       // 0.0
/*382 */                     lines=0;                                                                                // 0.0
/*384 */                 }                                                                                           // 0.0
/*386 */                 break;                                                                                      // 0.0
/*390 */             case 2:                                                                                         // 0.0
/*392 */                 lobyte = s->decode_buffer[lobytes];                                                         // 0.0
/*394 */                 hibyte = s->decode_buffer[hibytes];                                                         // 0.0
/*396 */                 vector_index = (hibyte << 8) | lobyte;                                                      // 0.0
/*398 */                 vector_index <<= index_shift;                                                               // 0.0
/*400 */                 lines = s->vector_height;                                                                   // 0.0
/*402 */                 break;                                                                                      // 0.0
/*406 */             case 3:                                                                                         // 0.0
/*408 */ /* not implemented yet */                                                                                   // 0.0
/*410 */                 lines = 0;                                                                                  // 0.0
/*412 */                 break;                                                                                      // 0.0
/*414 */             }                                                                                               // 0.0
/*418 */             while (lines--) {                                                                               // 0.0
/*420 */                 s->frame.data[0][pixel_ptr + 0] = s->codebook[vector_index++];                              // 0.0
/*422 */                 s->frame.data[0][pixel_ptr + 1] = s->codebook[vector_index++];                              // 0.0
/*424 */                 s->frame.data[0][pixel_ptr + 2] = s->codebook[vector_index++];                              // 0.0
/*426 */                 s->frame.data[0][pixel_ptr + 3] = s->codebook[vector_index++];                              // 0.0
/*428 */                 pixel_ptr += s->frame.linesize[0];                                                          // 0.0
/*430 */             }                                                                                               // 0.0
/*432 */         }                                                                                                   // 0.0
/*434 */     }                                                                                                       // 0.0
/*438 */     /* handle partial codebook */                                                                           // 0.0
/*440 */     if ((cbp0_chunk != -1) && (cbpz_chunk != -1)) {                                                         // 0.0
/*442 */         /* a chunk should not have both chunk types */                                                      // 0.0
/*444 */         av_log(s->avctx, AV_LOG_ERROR, "  VQA video: problem: found both CBP0 and CBPZ chunks\n");          // 0.0
/*446 */         return AVERROR_INVALIDDATA;                                                                         // 0.0
/*448 */     }                                                                                                       // 0.0
/*452 */     if (cbp0_chunk != -1) {                                                                                 // 0.0
/*456 */         bytestream2_seek(&s->gb, cbp0_chunk, SEEK_SET);                                                     // 0.0
/*458 */         chunk_size = bytestream2_get_be32(&s->gb);                                                          // 0.0
/*462 */         /* accumulate partial codebook */                                                                   // 0.0
/*464 */         bytestream2_get_buffer(&s->gb, &s->next_codebook_buffer[s->next_codebook_buffer_index],             // 0.0
/*466 */                                chunk_size);                                                                 // 0.0
/*468 */         s->next_codebook_buffer_index += chunk_size;                                                        // 0.0
/*472 */         s->partial_countdown--;                                                                             // 0.0
/*474 */         if (s->partial_countdown == 0) {                                                                    // 0.0
/*478 */             /* time to replace codebook */                                                                  // 0.0
/*480 */             memcpy(s->codebook, s->next_codebook_buffer,                                                    // 0.0
/*482 */                 s->next_codebook_buffer_index);                                                             // 0.0
/*486 */             /* reset accounting */                                                                          // 0.0
/*488 */             s->next_codebook_buffer_index = 0;                                                              // 0.0
/*490 */             s->partial_countdown = s->partial_count;                                                        // 0.0
/*492 */         }                                                                                                   // 0.0
/*494 */     }                                                                                                       // 0.0
/*498 */     if (cbpz_chunk != -1) {                                                                                 // 0.0
/*502 */         bytestream2_seek(&s->gb, cbpz_chunk, SEEK_SET);                                                     // 0.0
/*504 */         chunk_size = bytestream2_get_be32(&s->gb);                                                          // 0.0
/*508 */         /* accumulate partial codebook */                                                                   // 0.0
/*510 */         bytestream2_get_buffer(&s->gb, &s->next_codebook_buffer[s->next_codebook_buffer_index],             // 0.0
/*512 */                                chunk_size);                                                                 // 0.0
/*514 */         s->next_codebook_buffer_index += chunk_size;                                                        // 0.0
/*518 */         s->partial_countdown--;                                                                             // 0.0
/*520 */         if (s->partial_countdown == 0) {                                                                    // 0.0
/*522 */             GetByteContext gb;                                                                              // 0.0
/*526 */             bytestream2_init(&gb, s->next_codebook_buffer, s->next_codebook_buffer_index);                  // 0.0
/*528 */             /* decompress codebook */                                                                       // 0.0
/*530 */             if ((res = decode_format80(&gb, s->next_codebook_buffer_index,                                  // 0.0
/*532 */                                        s->codebook, s->codebook_size, 0)) < 0)                              // 0.0
/*534 */                 return res;                                                                                 // 0.0
/*538 */             /* reset accounting */                                                                          // 0.0
/*540 */             s->next_codebook_buffer_index = 0;                                                              // 0.0
/*542 */             s->partial_countdown = s->partial_count;                                                        // 0.0
/*544 */         }                                                                                                   // 0.0
/*546 */     }                                                                                                       // 0.0
/*550 */     return 0;                                                                                               // 0.0
/*552 */ }                                                                                                           // 0.0

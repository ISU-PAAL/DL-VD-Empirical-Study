// commit message FFmpeg@cb85779d45 (target=0, prob=0.5154183, correct=False): dpx: include offset in the  total_size calculation
/*0   */ static int decode_frame(AVCodecContext *avctx,                                              // (15) 0.02739
/*2   */                         void *data,                                                         // (3) 0.05267
/*4   */                         int *got_frame,                                                     // (2) 0.05658
/*6   */                         AVPacket *avpkt)                                                    // (1) 0.06048
/*8   */ {                                                                                           // (28) 0.001955
/*10  */     const uint8_t *buf = avpkt->data;                                                       // (12) 0.03317
/*12  */     int buf_size       = avpkt->size;                                                       // (8) 0.03902
/*14  */     DPXContext *const s = avctx->priv_data;                                                 // (11) 0.03317
/*16  */     AVFrame *picture  = data;                                                               // (22) 0.02147
/*18  */     AVFrame *const p = &s->picture;                                                         // (17) 0.02732
/*20  */     uint8_t *ptr[AV_NUM_DATA_POINTERS];                                                     // (9) 0.03902
/*24  */     unsigned int offset;                                                                    // (25) 0.01367
/*26  */     int magic_num, endian;                                                                  // (23) 0.02146
/*28  */     int x, y, i, ret;                                                                       // (18) 0.02392
/*30  */     int w, h, bits_per_color, descriptor, elements, packing, total_size;                    // (4) 0.0469
/*34  */     unsigned int rgbBuffer = 0;                                                             // (24) 0.01957
/*36  */     int n_datum = 0;                                                                        // (21) 0.02148
/*40  */     if (avpkt->size <= 1634) {                                                              // (14) 0.02944
/*42  */         av_log(avctx, AV_LOG_ERROR, "Packet too small for DPX header\n");                   // (0) 0.06243
/*44  */         return AVERROR_INVALIDDATA;                                                         // (13) 0.03316
/*46  */     }                                                                                       // (27) 0.007804
/*50  */     magic_num = AV_RB32(buf);                                                               // (16) 0.02732
/*52  */     buf += 4;                                                                               // (26) 0.01366
/*56  */     /* Check if the files "magic number" is "SDPX" which means it uses                      // (5) 0.04292
/*58  */      * big-endian or XPDS which is for little-endian files */                               // (6) 0.04097
/*60  */     if (magic_num == AV_RL32("SDPX")) {                                                     // (10) 0.03707
/*62  */         endian = 0;                                                                         // (20) 0.02341
/*64  */     } else if (magic_num == AV_RB32("SDPX")) {                                              // (7) 0.04097
/*66  */         endian = 1;                                                                         // (19) 0.02341
/*68  */     } else {                                                                                // 0.0
/*70  */         av_log(avctx, AV_LOG_ERROR, "DPX marker not found\n");                              // 0.0
/*72  */         return AVERROR_INVALIDDATA;                                                         // 0.0
/*74  */     }                                                                                       // 0.0
/*78  */     offset = read32(&buf, endian);                                                          // 0.0
/*80  */     if (avpkt->size <= offset) {                                                            // 0.0
/*82  */         av_log(avctx, AV_LOG_ERROR, "Invalid data start offset\n");                         // 0.0
/*84  */         return AVERROR_INVALIDDATA;                                                         // 0.0
/*86  */     }                                                                                       // 0.0
/*88  */     // Need to end in 0x304 offset from start of file                                       // 0.0
/*90  */     buf = avpkt->data + 0x304;                                                              // 0.0
/*92  */     w = read32(&buf, endian);                                                               // 0.0
/*94  */     h = read32(&buf, endian);                                                               // 0.0
/*96  */     if ((ret = av_image_check_size(w, h, 0, avctx)) < 0)                                    // 0.0
/*98  */         return ret;                                                                         // 0.0
/*102 */     if (w != avctx->width || h != avctx->height)                                            // 0.0
/*104 */         avcodec_set_dimensions(avctx, w, h);                                                // 0.0
/*108 */     // Need to end in 0x320 to read the descriptor                                          // 0.0
/*110 */     buf += 20;                                                                              // 0.0
/*112 */     descriptor = buf[0];                                                                    // 0.0
/*116 */     // Need to end in 0x323 to read the bits per color                                      // 0.0
/*118 */     buf += 3;                                                                               // 0.0
/*120 */     avctx->bits_per_raw_sample =                                                            // 0.0
/*122 */     bits_per_color = buf[0];                                                                // 0.0
/*124 */     buf++;                                                                                  // 0.0
/*126 */     packing = *((uint16_t*)buf);                                                            // 0.0
/*130 */     buf += 824;                                                                             // 0.0
/*132 */     avctx->sample_aspect_ratio.num = read32(&buf, endian);                                  // 0.0
/*134 */     avctx->sample_aspect_ratio.den = read32(&buf, endian);                                  // 0.0
/*136 */     if (avctx->sample_aspect_ratio.num > 0 && avctx->sample_aspect_ratio.den > 0)           // 0.0
/*138 */         av_reduce(&avctx->sample_aspect_ratio.num, &avctx->sample_aspect_ratio.den,         // 0.0
/*140 */                    avctx->sample_aspect_ratio.num,  avctx->sample_aspect_ratio.den,         // 0.0
/*142 */                   0x10000);                                                                 // 0.0
/*144 */     else                                                                                    // 0.0
/*146 */         avctx->sample_aspect_ratio = (AVRational){ 0, 1 };                                  // 0.0
/*150 */     switch (descriptor) {                                                                   // 0.0
/*152 */         case 51: // RGBA                                                                    // 0.0
/*154 */             elements = 4;                                                                   // 0.0
/*156 */             break;                                                                          // 0.0
/*158 */         case 50: // RGB                                                                     // 0.0
/*160 */             elements = 3;                                                                   // 0.0
/*162 */             break;                                                                          // 0.0
/*164 */         default:                                                                            // 0.0
/*166 */             av_log(avctx, AV_LOG_ERROR, "Unsupported descriptor %d\n", descriptor);         // 0.0
/*168 */             return AVERROR_INVALIDDATA;                                                     // 0.0
/*170 */     }                                                                                       // 0.0
/*174 */     switch (bits_per_color) {                                                               // 0.0
/*176 */         case 8:                                                                             // 0.0
/*178 */             if (elements == 4) {                                                            // 0.0
/*180 */                 avctx->pix_fmt = AV_PIX_FMT_RGBA;                                           // 0.0
/*182 */             } else {                                                                        // 0.0
/*184 */                 avctx->pix_fmt = AV_PIX_FMT_RGB24;                                          // 0.0
/*186 */             }                                                                               // 0.0
/*188 */             total_size = avctx->width * avctx->height * elements;                           // 0.0
/*190 */             break;                                                                          // 0.0
/*192 */         case 10:                                                                            // 0.0
/*194 */             if (!packing) {                                                                 // 0.0
/*196 */                 av_log(avctx, AV_LOG_ERROR, "Packing to 32bit required\n");                 // 0.0
/*198 */                 return -1;                                                                  // 0.0
/*200 */             }                                                                               // 0.0
/*202 */             avctx->pix_fmt = AV_PIX_FMT_GBRP10;                                             // 0.0
/*204 */             total_size = (avctx->width * avctx->height * elements + 2) / 3 * 4;             // 0.0
/*206 */             break;                                                                          // 0.0
/*208 */         case 12:                                                                            // 0.0
/*210 */             if (!packing) {                                                                 // 0.0
/*212 */                 av_log(avctx, AV_LOG_ERROR, "Packing to 16bit required\n");                 // 0.0
/*214 */                 return -1;                                                                  // 0.0
/*216 */             }                                                                               // 0.0
/*218 */             if (endian) {                                                                   // 0.0
/*220 */                 avctx->pix_fmt = AV_PIX_FMT_GBRP12BE;                                       // 0.0
/*222 */             } else {                                                                        // 0.0
/*224 */                 avctx->pix_fmt = AV_PIX_FMT_GBRP12LE;                                       // 0.0
/*226 */             }                                                                               // 0.0
/*228 */             total_size = 2 * avctx->width * avctx->height * elements;                       // 0.0
/*230 */             break;                                                                          // 0.0
/*232 */         case 16:                                                                            // 0.0
/*234 */             if (endian) {                                                                   // 0.0
/*236 */                 avctx->pix_fmt = elements == 4 ? AV_PIX_FMT_RGBA64BE : AV_PIX_FMT_RGB48BE;  // 0.0
/*238 */             } else {                                                                        // 0.0
/*240 */                 avctx->pix_fmt = elements == 4 ? AV_PIX_FMT_RGBA64LE : AV_PIX_FMT_RGB48LE;  // 0.0
/*242 */             }                                                                               // 0.0
/*244 */             total_size = 2 * avctx->width * avctx->height * elements;                       // 0.0
/*246 */             break;                                                                          // 0.0
/*248 */         default:                                                                            // 0.0
/*250 */             av_log(avctx, AV_LOG_ERROR, "Unsupported color depth : %d\n", bits_per_color);  // 0.0
/*252 */             return AVERROR_INVALIDDATA;                                                     // 0.0
/*254 */     }                                                                                       // 0.0
/*258 */     if (s->picture.data[0])                                                                 // 0.0
/*260 */         avctx->release_buffer(avctx, &s->picture);                                          // 0.0
/*262 */     if ((ret = ff_get_buffer(avctx, p)) < 0) {                                              // 0.0
/*264 */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                               // 0.0
/*266 */         return ret;                                                                         // 0.0
/*268 */     }                                                                                       // 0.0
/*272 */     // Move pointer to offset from start of file                                            // 0.0
/*274 */     buf =  avpkt->data + offset;                                                            // 0.0
/*278 */     for (i=0; i<AV_NUM_DATA_POINTERS; i++)                                                  // 0.0
/*280 */         ptr[i] = p->data[i];                                                                // 0.0
/*284 */     if (total_size > avpkt->size) {                                                         // 0.0
/*286 */         av_log(avctx, AV_LOG_ERROR, "Overread buffer. Invalid header?\n");                  // 0.0
/*288 */         return AVERROR_INVALIDDATA;                                                         // 0.0
/*290 */     }                                                                                       // 0.0
/*292 */     switch (bits_per_color) {                                                               // 0.0
/*294 */     case 10:                                                                                // 0.0
/*296 */         for (x = 0; x < avctx->height; x++) {                                               // 0.0
/*298 */             uint16_t *dst[3] = {(uint16_t*)ptr[0],                                          // 0.0
/*300 */                                 (uint16_t*)ptr[1],                                          // 0.0
/*302 */                                 (uint16_t*)ptr[2]};                                         // 0.0
/*304 */             for (y = 0; y < avctx->width; y++) {                                            // 0.0
/*306 */                 *dst[2]++ = read10in32(&buf, &rgbBuffer,                                    // 0.0
/*308 */                                        &n_datum, endian);                                   // 0.0
/*310 */                 *dst[0]++ = read10in32(&buf, &rgbBuffer,                                    // 0.0
/*312 */                                        &n_datum, endian);                                   // 0.0
/*314 */                 *dst[1]++ = read10in32(&buf, &rgbBuffer,                                    // 0.0
/*316 */                                        &n_datum, endian);                                   // 0.0
/*318 */                 // For 10 bit, ignore alpha                                                 // 0.0
/*320 */                 if (elements == 4)                                                          // 0.0
/*322 */                     read10in32(&buf, &rgbBuffer,                                            // 0.0
/*324 */                                &n_datum, endian);                                           // 0.0
/*326 */             }                                                                               // 0.0
/*328 */             for (i = 0; i < 3; i++)                                                         // 0.0
/*330 */                 ptr[i] += p->linesize[i];                                                   // 0.0
/*332 */         }                                                                                   // 0.0
/*334 */         break;                                                                              // 0.0
/*336 */     case 12:                                                                                // 0.0
/*338 */         for (x = 0; x < avctx->height; x++) {                                               // 0.0
/*340 */             uint16_t *dst[3] = {(uint16_t*)ptr[0],                                          // 0.0
/*342 */                                 (uint16_t*)ptr[1],                                          // 0.0
/*344 */                                 (uint16_t*)ptr[2]};                                         // 0.0
/*346 */             for (y = 0; y < avctx->width; y++) {                                            // 0.0
/*348 */                 *dst[2] = *((uint16_t*)buf);                                                // 0.0
/*350 */                 *dst[2] = (*dst[2] >> 4) | (*dst[2] << 12);                                 // 0.0
/*352 */                 dst[2]++;                                                                   // 0.0
/*354 */                 buf += 2;                                                                   // 0.0
/*356 */                 *dst[0] = *((uint16_t*)buf);                                                // 0.0
/*358 */                 *dst[0] = (*dst[0] >> 4) | (*dst[0] << 12);                                 // 0.0
/*360 */                 dst[0]++;                                                                   // 0.0
/*362 */                 buf += 2;                                                                   // 0.0
/*364 */                 *dst[1] = *((uint16_t*)buf);                                                // 0.0
/*366 */                 *dst[1] = (*dst[1] >> 4) | (*dst[1] << 12);                                 // 0.0
/*368 */                 dst[1]++;                                                                   // 0.0
/*370 */                 buf += 2;                                                                   // 0.0
/*372 */                 // For 12 bit, ignore alpha                                                 // 0.0
/*374 */                 if (elements == 4)                                                          // 0.0
/*376 */                     buf += 2;                                                               // 0.0
/*378 */             }                                                                               // 0.0
/*380 */             for (i = 0; i < 3; i++)                                                         // 0.0
/*382 */                 ptr[i] += p->linesize[i];                                                   // 0.0
/*384 */         }                                                                                   // 0.0
/*386 */         break;                                                                              // 0.0
/*388 */     case 16:                                                                                // 0.0
/*390 */         elements *= 2;                                                                      // 0.0
/*392 */     case 8:                                                                                 // 0.0
/*394 */         for (x = 0; x < avctx->height; x++) {                                               // 0.0
/*396 */             memcpy(ptr[0], buf, elements*avctx->width);                                     // 0.0
/*398 */             ptr[0] += p->linesize[0];                                                       // 0.0
/*400 */             buf += elements*avctx->width;                                                   // 0.0
/*402 */         }                                                                                   // 0.0
/*404 */         break;                                                                              // 0.0
/*406 */     }                                                                                       // 0.0
/*410 */     *picture   = s->picture;                                                                // 0.0
/*412 */     *got_frame = 1;                                                                         // 0.0
/*416 */     return buf_size;                                                                        // 0.0
/*418 */ }                                                                                           // 0.0

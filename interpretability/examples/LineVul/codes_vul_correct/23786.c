// commit message FFmpeg@8cd1c0febe (target=1, prob=0.670502, correct=True): pcx: convert to bytestream2 API
/*0   */ static int pcx_decode_frame(AVCodecContext *avctx, void *data, int *data_size,    // (1) 0.06172
/*2   */                             AVPacket *avpkt) {                                    // (0) 0.06881
/*4   */     const uint8_t *buf = avpkt->data;                                             // (10) 0.0327
/*6   */     int buf_size = avpkt->size;                                                   // (18) 0.02703
/*8   */     PCXContext * const s = avctx->priv_data;                                      // (9) 0.03322
/*10  */     AVFrame *picture = data;                                                      // (22) 0.01977
/*12  */     AVFrame * const p = &s->picture;                                              // (17) 0.02779
/*14  */     int compressed, xmin, ymin, xmax, ymax;                                       // (7) 0.03527
/*16  */     unsigned int w, h, bits_per_pixel, bytes_per_line, nplanes, stride, y, x,     // (3) 0.05778
/*18  */                  bytes_per_scanline;                                              // (6) 0.04386
/*20  */     uint8_t *ptr;                                                                 // (23) 0.01921
/*22  */     uint8_t const *bufstart = buf;                                                // (19) 0.02685
/*24  */     uint8_t *scanline;                                                            // (21) 0.02112
/*26  */     int ret = -1;                                                                 // (24) 0.01815
/*30  */     if (buf[0] != 0x0a || buf[1] > 5) {                                           // (5) 0.04904
/*32  */         av_log(avctx, AV_LOG_ERROR, "this is not PCX encoded data\n");            // (2) 0.05939
/*34  */         return AVERROR_INVALIDDATA;                                               // (12) 0.03244
/*36  */     }                                                                             // (27) 0.007732
/*40  */     compressed = buf[2];                                                          // (25) 0.01726
/*42  */     xmin = AV_RL16(buf+ 4);                                                       // (16) 0.02867
/*44  */     ymin = AV_RL16(buf+ 6);                                                       // (15) 0.02868
/*46  */     xmax = AV_RL16(buf+ 8);                                                       // (14) 0.02872
/*48  */     ymax = AV_RL16(buf+10);                                                       // (13) 0.02876
/*52  */     if (xmax < xmin || ymax < ymin) {                                             // (8) 0.03445
/*54  */         av_log(avctx, AV_LOG_ERROR, "invalid image dimensions\n");                // (4) 0.05346
/*56  */         return AVERROR_INVALIDDATA;                                               // (11) 0.03246
/*58  */     }                                                                             // (26) 0.007874
/*62  */     w = xmax - xmin + 1;                                                          // (20) 0.02486
/*64  */     h = ymax - ymin + 1;                                                          // 0.0
/*68  */     bits_per_pixel     = buf[3];                                                  // 0.0
/*70  */     bytes_per_line     = AV_RL16(buf+66);                                         // 0.0
/*72  */     nplanes            = buf[65];                                                 // 0.0
/*74  */     bytes_per_scanline = nplanes * bytes_per_line;                                // 0.0
/*78  */     if (bytes_per_scanline < w * bits_per_pixel * nplanes / 8) {                  // 0.0
/*80  */         av_log(avctx, AV_LOG_ERROR, "PCX data is corrupted\n");                   // 0.0
/*82  */         return AVERROR_INVALIDDATA;                                               // 0.0
/*84  */     }                                                                             // 0.0
/*88  */     switch ((nplanes<<8) + bits_per_pixel) {                                      // 0.0
/*90  */         case 0x0308:                                                              // 0.0
/*92  */             avctx->pix_fmt = AV_PIX_FMT_RGB24;                                    // 0.0
/*94  */             break;                                                                // 0.0
/*96  */         case 0x0108:                                                              // 0.0
/*98  */         case 0x0104:                                                              // 0.0
/*100 */         case 0x0102:                                                              // 0.0
/*102 */         case 0x0101:                                                              // 0.0
/*104 */         case 0x0401:                                                              // 0.0
/*106 */         case 0x0301:                                                              // 0.0
/*108 */         case 0x0201:                                                              // 0.0
/*110 */             avctx->pix_fmt = AV_PIX_FMT_PAL8;                                     // 0.0
/*112 */             break;                                                                // 0.0
/*114 */         default:                                                                  // 0.0
/*116 */             av_log(avctx, AV_LOG_ERROR, "invalid PCX file\n");                    // 0.0
/*118 */             return AVERROR_INVALIDDATA;                                           // 0.0
/*120 */     }                                                                             // 0.0
/*124 */     buf += 128;                                                                   // 0.0
/*128 */     if (p->data[0])                                                               // 0.0
/*130 */         avctx->release_buffer(avctx, p);                                          // 0.0
/*134 */     if (av_image_check_size(w, h, 0, avctx))                                      // 0.0
/*136 */         return AVERROR_INVALIDDATA;                                               // 0.0
/*138 */     if (w != avctx->width || h != avctx->height)                                  // 0.0
/*140 */         avcodec_set_dimensions(avctx, w, h);                                      // 0.0
/*142 */     if ((ret = avctx->get_buffer(avctx, p)) < 0) {                                // 0.0
/*144 */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                     // 0.0
/*146 */         return ret;                                                               // 0.0
/*148 */     }                                                                             // 0.0
/*152 */     p->pict_type = AV_PICTURE_TYPE_I;                                             // 0.0
/*156 */     ptr    = p->data[0];                                                          // 0.0
/*158 */     stride = p->linesize[0];                                                      // 0.0
/*162 */     scanline = av_malloc(bytes_per_scanline);                                     // 0.0
/*164 */     if (!scanline)                                                                // 0.0
/*166 */         return AVERROR(ENOMEM);                                                   // 0.0
/*170 */     if (nplanes == 3 && bits_per_pixel == 8) {                                    // 0.0
/*172 */         for (y=0; y<h; y++) {                                                     // 0.0
/*174 */             buf = pcx_rle_decode(buf, scanline, bytes_per_scanline, compressed);  // 0.0
/*178 */             for (x=0; x<w; x++) {                                                 // 0.0
/*180 */                 ptr[3*x  ] = scanline[x                    ];                     // 0.0
/*182 */                 ptr[3*x+1] = scanline[x+ bytes_per_line    ];                     // 0.0
/*184 */                 ptr[3*x+2] = scanline[x+(bytes_per_line<<1)];                     // 0.0
/*186 */             }                                                                     // 0.0
/*190 */             ptr += stride;                                                        // 0.0
/*192 */         }                                                                         // 0.0
/*196 */     } else if (nplanes == 1 && bits_per_pixel == 8) {                             // 0.0
/*198 */         const uint8_t *palstart = bufstart + buf_size - 769;                      // 0.0
/*202 */         for (y=0; y<h; y++, ptr+=stride) {                                        // 0.0
/*204 */             buf = pcx_rle_decode(buf, scanline, bytes_per_scanline, compressed);  // 0.0
/*206 */             memcpy(ptr, scanline, w);                                             // 0.0
/*208 */         }                                                                         // 0.0
/*212 */         if (buf != palstart) {                                                    // 0.0
/*214 */             av_log(avctx, AV_LOG_WARNING, "image data possibly corrupted\n");     // 0.0
/*216 */             buf = palstart;                                                       // 0.0
/*218 */         }                                                                         // 0.0
/*220 */         if (*buf++ != 12) {                                                       // 0.0
/*222 */             av_log(avctx, AV_LOG_ERROR, "expected palette after image data\n");   // 0.0
/*224 */             ret = AVERROR_INVALIDDATA;                                            // 0.0
/*226 */             goto end;                                                             // 0.0
/*228 */         }                                                                         // 0.0
/*232 */     } else if (nplanes == 1) {   /* all packed formats, max. 16 colors */         // 0.0
/*234 */         GetBitContext s;                                                          // 0.0
/*238 */         for (y=0; y<h; y++) {                                                     // 0.0
/*240 */             init_get_bits(&s, scanline, bytes_per_scanline<<3);                   // 0.0
/*244 */             buf = pcx_rle_decode(buf, scanline, bytes_per_scanline, compressed);  // 0.0
/*248 */             for (x=0; x<w; x++)                                                   // 0.0
/*250 */                 ptr[x] = get_bits(&s, bits_per_pixel);                            // 0.0
/*252 */             ptr += stride;                                                        // 0.0
/*254 */         }                                                                         // 0.0
/*258 */     } else {    /* planar, 4, 8 or 16 colors */                                   // 0.0
/*260 */         int i;                                                                    // 0.0
/*264 */         for (y=0; y<h; y++) {                                                     // 0.0
/*266 */             buf = pcx_rle_decode(buf, scanline, bytes_per_scanline, compressed);  // 0.0
/*270 */             for (x=0; x<w; x++) {                                                 // 0.0
/*272 */                 int m = 0x80 >> (x&7), v = 0;                                     // 0.0
/*274 */                 for (i=nplanes - 1; i>=0; i--) {                                  // 0.0
/*276 */                     v <<= 1;                                                      // 0.0
/*278 */                     v  += !!(scanline[i*bytes_per_line + (x>>3)] & m);            // 0.0
/*280 */                 }                                                                 // 0.0
/*282 */                 ptr[x] = v;                                                       // 0.0
/*284 */             }                                                                     // 0.0
/*286 */             ptr += stride;                                                        // 0.0
/*288 */         }                                                                         // 0.0
/*290 */     }                                                                             // 0.0
/*294 */     if (nplanes == 1 && bits_per_pixel == 8) {                                    // 0.0
/*296 */         pcx_palette(&buf, (uint32_t *) p->data[1], 256);                          // 0.0
/*298 */     } else if (bits_per_pixel * nplanes == 1) {                                   // 0.0
/*300 */         AV_WN32A(p->data[1]  , 0xFF000000);                                       // 0.0
/*302 */         AV_WN32A(p->data[1]+4, 0xFFFFFFFF);                                       // 0.0
/*304 */     } else if (bits_per_pixel < 8) {                                              // 0.0
/*306 */         const uint8_t *palette = bufstart+16;                                     // 0.0
/*308 */         pcx_palette(&palette, (uint32_t *) p->data[1], 16);                       // 0.0
/*310 */     }                                                                             // 0.0
/*314 */     *picture = s->picture;                                                        // 0.0
/*316 */     *data_size = sizeof(AVFrame);                                                 // 0.0
/*320 */     ret = buf - bufstart;                                                         // 0.0
/*322 */ end:                                                                              // 0.0
/*324 */     av_free(scanline);                                                            // 0.0
/*326 */     return ret;                                                                   // 0.0
/*328 */ }                                                                                 // 0.0

// commit message FFmpeg@03d83ba34b (target=0, prob=0.6177305, correct=False): avcodec/gif: Fix lzw buffer size
/*0   */ static int gif_image_write_image(AVCodecContext *avctx,                                          // (12) 0.03516
/*2   */                                  uint8_t **bytestream, uint8_t *end,                             // (0) 0.09375
/*4   */                                  const uint32_t *palette,                                        // (2) 0.08007
/*6   */                                  const uint8_t *buf, const int linesize,                         // (1) 0.08788
/*8   */                                  AVPacket *pkt)                                                  // (3) 0.07617
/*10  */ {                                                                                                // (18) 0.001965
/*12  */     GIFContext *s = avctx->priv_data;                                                            // (14) 0.0293
/*14  */     int len = 0, height = avctx->height, width = avctx->width, x, y;                             // (6) 0.05078
/*16  */     int x_start = 0, y_start = 0, trans = s->transparent_index;                                  // (7) 0.04883
/*18  */     int honor_transparency = (s->flags & GF_TRANSDIFF) && s->last_frame;                         // (4) 0.05468
/*20  */     const uint8_t *ptr;                                                                          // (16) 0.02148
/*24  */     /* Crop image */                                                                             // (17) 0.01563
/*26  */     if ((s->flags & GF_OFFSETTING) && s->last_frame && !palette) {                               // (5) 0.05273
/*28  */         const uint8_t *ref = s->last_frame->data[0];                                             // (8) 0.04882
/*30  */         const int ref_linesize = s->last_frame->linesize[0];                                     // (9) 0.04882
/*32  */         int x_end = avctx->width  - 1,                                                           // (11) 0.03906
/*34  */             y_end = avctx->height - 1;                                                           // (10) 0.04297
/*38  */         /* skip common lines */                                                                  // (15) 0.02344
/*40  */         while (y_start < y_end) {                                                                // (13) 0.03515
/*42  */             if (memcmp(ref + y_start*ref_linesize, buf + y_start*linesize, width))               // 0.0
/*44  */                 break;                                                                           // 0.0
/*46  */             y_start++;                                                                           // 0.0
/*48  */         }                                                                                        // 0.0
/*50  */         while (y_end > y_start) {                                                                // 0.0
/*52  */             if (memcmp(ref + y_end*ref_linesize, buf + y_end*linesize, width))                   // 0.0
/*54  */                 break;                                                                           // 0.0
/*56  */             y_end--;                                                                             // 0.0
/*58  */         }                                                                                        // 0.0
/*60  */         height = y_end + 1 - y_start;                                                            // 0.0
/*64  */         /* skip common columns */                                                                // 0.0
/*66  */         while (x_start < x_end) {                                                                // 0.0
/*68  */             int same_column = 1;                                                                 // 0.0
/*70  */             for (y = y_start; y <= y_end; y++) {                                                 // 0.0
/*72  */                 if (ref[y*ref_linesize + x_start] != buf[y*linesize + x_start]) {                // 0.0
/*74  */                     same_column = 0;                                                             // 0.0
/*76  */                     break;                                                                       // 0.0
/*78  */                 }                                                                                // 0.0
/*80  */             }                                                                                    // 0.0
/*82  */             if (!same_column)                                                                    // 0.0
/*84  */                 break;                                                                           // 0.0
/*86  */             x_start++;                                                                           // 0.0
/*88  */         }                                                                                        // 0.0
/*90  */         while (x_end > x_start) {                                                                // 0.0
/*92  */             int same_column = 1;                                                                 // 0.0
/*94  */             for (y = y_start; y <= y_end; y++) {                                                 // 0.0
/*96  */                 if (ref[y*ref_linesize + x_end] != buf[y*linesize + x_end]) {                    // 0.0
/*98  */                     same_column = 0;                                                             // 0.0
/*100 */                     break;                                                                       // 0.0
/*102 */                 }                                                                                // 0.0
/*104 */             }                                                                                    // 0.0
/*106 */             if (!same_column)                                                                    // 0.0
/*108 */                 break;                                                                           // 0.0
/*110 */             x_end--;                                                                             // 0.0
/*112 */         }                                                                                        // 0.0
/*114 */         width = x_end + 1 - x_start;                                                             // 0.0
/*118 */         av_log(avctx, AV_LOG_DEBUG,"%dx%d image at pos (%d;%d) [area:%dx%d]\n",                  // 0.0
/*120 */                width, height, x_start, y_start, avctx->width, avctx->height);                    // 0.0
/*122 */     }                                                                                            // 0.0
/*126 */     /* image block */                                                                            // 0.0
/*128 */     bytestream_put_byte(bytestream, GIF_IMAGE_SEPARATOR);                                        // 0.0
/*130 */     bytestream_put_le16(bytestream, x_start);                                                    // 0.0
/*132 */     bytestream_put_le16(bytestream, y_start);                                                    // 0.0
/*134 */     bytestream_put_le16(bytestream, width);                                                      // 0.0
/*136 */     bytestream_put_le16(bytestream, height);                                                     // 0.0
/*140 */     if (!palette) {                                                                              // 0.0
/*142 */         bytestream_put_byte(bytestream, 0x00); /* flags */                                       // 0.0
/*144 */     } else {                                                                                     // 0.0
/*146 */         unsigned i;                                                                              // 0.0
/*148 */         bytestream_put_byte(bytestream, 1<<7 | 0x7); /* flags */                                 // 0.0
/*150 */         for (i = 0; i < AVPALETTE_COUNT; i++) {                                                  // 0.0
/*152 */             const uint32_t v = palette[i];                                                       // 0.0
/*154 */             bytestream_put_be24(bytestream, v);                                                  // 0.0
/*156 */         }                                                                                        // 0.0
/*158 */     }                                                                                            // 0.0
/*162 */     if (honor_transparency && trans < 0) {                                                       // 0.0
/*164 */         trans = pick_palette_entry(buf + y_start*linesize + x_start,                             // 0.0
/*166 */                                    linesize, width, height);                                     // 0.0
/*168 */         if (trans < 0) { // TODO, patch welcome                                                  // 0.0
/*170 */             av_log(avctx, AV_LOG_DEBUG, "No available color, can not use transparency\n");       // 0.0
/*172 */         } else {                                                                                 // 0.0
/*174 */             uint8_t *pal_exdata = s->pal_exdata;                                                 // 0.0
/*176 */             if (!pal_exdata)                                                                     // 0.0
/*178 */                 pal_exdata = av_packet_new_side_data(pkt, AV_PKT_DATA_PALETTE, AVPALETTE_SIZE);  // 0.0
/*180 */             if (!pal_exdata)                                                                     // 0.0
/*182 */                 return AVERROR(ENOMEM);                                                          // 0.0
/*184 */             memcpy(pal_exdata, s->palette, AVPALETTE_SIZE);                                      // 0.0
/*186 */             pal_exdata[trans*4 + 3*!HAVE_BIGENDIAN] = 0x00;                                      // 0.0
/*188 */         }                                                                                        // 0.0
/*190 */     }                                                                                            // 0.0
/*192 */     if (trans < 0)                                                                               // 0.0
/*194 */         honor_transparency = 0;                                                                  // 0.0
/*198 */     bytestream_put_byte(bytestream, 0x08);                                                       // 0.0
/*202 */     ff_lzw_encode_init(s->lzw, s->buf, 2 * width * height,                                       // 0.0
/*204 */                        12, FF_LZW_GIF, put_bits);                                                // 0.0
/*208 */     ptr = buf + y_start*linesize + x_start;                                                      // 0.0
/*210 */     if (honor_transparency) {                                                                    // 0.0
/*212 */         const int ref_linesize = s->last_frame->linesize[0];                                     // 0.0
/*214 */         const uint8_t *ref = s->last_frame->data[0] + y_start*ref_linesize + x_start;            // 0.0
/*218 */         for (y = 0; y < height; y++) {                                                           // 0.0
/*220 */             memcpy(s->tmpl, ptr, width);                                                         // 0.0
/*222 */             for (x = 0; x < width; x++)                                                          // 0.0
/*224 */                 if (ref[x] == ptr[x])                                                            // 0.0
/*226 */                     s->tmpl[x] = trans;                                                          // 0.0
/*228 */             len += ff_lzw_encode(s->lzw, s->tmpl, width);                                        // 0.0
/*230 */             ptr += linesize;                                                                     // 0.0
/*232 */             ref += ref_linesize;                                                                 // 0.0
/*234 */         }                                                                                        // 0.0
/*236 */     } else {                                                                                     // 0.0
/*238 */         for (y = 0; y < height; y++) {                                                           // 0.0
/*240 */             len += ff_lzw_encode(s->lzw, ptr, width);                                            // 0.0
/*242 */             ptr += linesize;                                                                     // 0.0
/*244 */         }                                                                                        // 0.0
/*246 */     }                                                                                            // 0.0
/*248 */     len += ff_lzw_encode_flush(s->lzw, flush_put_bits);                                          // 0.0
/*252 */     ptr = s->buf;                                                                                // 0.0
/*254 */     while (len > 0) {                                                                            // 0.0
/*256 */         int size = FFMIN(255, len);                                                              // 0.0
/*258 */         bytestream_put_byte(bytestream, size);                                                   // 0.0
/*260 */         if (end - *bytestream < size)                                                            // 0.0
/*262 */             return -1;                                                                           // 0.0
/*264 */         bytestream_put_buffer(bytestream, ptr, size);                                            // 0.0
/*266 */         ptr += size;                                                                             // 0.0
/*268 */         len -= size;                                                                             // 0.0
/*270 */     }                                                                                            // 0.0
/*272 */     bytestream_put_byte(bytestream, 0x00); /* end of image block */                              // 0.0
/*274 */     return 0;                                                                                    // 0.0
/*276 */ }                                                                                                // 0.0

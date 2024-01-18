// commit message FFmpeg@41abc9da50 (target=1, prob=0.7481039, correct=True): iff: fix null ptr dereference
/*0   */ static int decode_frame_ilbm(AVCodecContext *avctx,                                                            // (11) 0.0332
/*2   */                             void *data, int *data_size,                                                        // (2) 0.07227
/*4   */                             AVPacket *avpkt)                                                                   // (4) 0.06836
/*6   */ {                                                                                                              // (19) 0.001953
/*8   */     IffContext *s = avctx->priv_data;                                                                          // (12) 0.03125
/*10  */     const uint8_t *buf = avpkt->size >= 2 ? avpkt->data + AV_RB16(avpkt->data) : NULL;                         // (1) 0.07617
/*12  */     const int buf_size = avpkt->size >= 2 ? avpkt->size - AV_RB16(avpkt->data) : 0;                            // (3) 0.07227
/*14  */     const uint8_t *buf_end = buf+buf_size;                                                                     // (10) 0.03711
/*16  */     int y, plane, res;                                                                                         // (14) 0.01954
/*20  */     if ((res = extract_header(avctx, avpkt)) < 0)                                                              // (9) 0.04102
/*22  */         return res;                                                                                            // (16) 0.01953
/*26  */     if (s->init) {                                                                                             // (15) 0.01953
/*28  */         if ((res = avctx->reget_buffer(avctx, &s->frame)) < 0) {                                               // (6) 0.06055
/*30  */             av_log(avctx, AV_LOG_ERROR, "reget_buffer() failed\n");                                            // (5) 0.06641
/*32  */             return res;                                                                                        // (13) 0.02734
/*34  */         }                                                                                                      // (18) 0.01562
/*36  */     } else if ((res = avctx->get_buffer(avctx, &s->frame)) < 0) {                                              // (8) 0.05469
/*38  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                                  // (7) 0.05664
/*40  */         return res;                                                                                            // (17) 0.01953
/*42  */     } else if (avctx->bits_per_coded_sample <= 8 && avctx->pix_fmt != PIX_FMT_GRAY8) {                         // (0) 0.07812
/*44  */         if ((res = ff_cmap_read_palette(avctx, (uint32_t*)s->frame.data[1])) < 0)                              // 0.0
/*46  */             return res;                                                                                        // 0.0
/*48  */     }                                                                                                          // 0.0
/*50  */     s->init = 1;                                                                                               // 0.0
/*54  */     if (avctx->codec_tag == MKTAG('A','C','B','M')) {                                                          // 0.0
/*56  */         if (avctx->pix_fmt == PIX_FMT_PAL8 || avctx->pix_fmt == PIX_FMT_GRAY8) {                               // 0.0
/*58  */             memset(s->frame.data[0], 0, avctx->height * s->frame.linesize[0]);                                 // 0.0
/*60  */             for (plane = 0; plane < s->bpp; plane++) {                                                         // 0.0
/*62  */                 for(y = 0; y < avctx->height && buf < buf_end; y++ ) {                                         // 0.0
/*64  */                     uint8_t *row = &s->frame.data[0][ y*s->frame.linesize[0] ];                                // 0.0
/*66  */                     decodeplane8(row, buf, FFMIN(s->planesize, buf_end - buf), plane);                         // 0.0
/*68  */                     buf += s->planesize;                                                                       // 0.0
/*70  */                 }                                                                                              // 0.0
/*72  */             }                                                                                                  // 0.0
/*74  */         } else if (s->ham) { // HAM to PIX_FMT_BGR32                                                           // 0.0
/*76  */             memset(s->frame.data[0], 0, avctx->height * s->frame.linesize[0]);                                 // 0.0
/*78  */             for(y = 0; y < avctx->height; y++) {                                                               // 0.0
/*80  */                 uint8_t *row = &s->frame.data[0][y * s->frame.linesize[0]];                                    // 0.0
/*82  */                 memset(s->ham_buf, 0, s->planesize * 8);                                                       // 0.0
/*84  */                 for (plane = 0; plane < s->bpp; plane++) {                                                     // 0.0
/*86  */                     const uint8_t * start = buf + (plane * avctx->height + y) * s->planesize;                  // 0.0
/*88  */                     if (start >= buf_end)                                                                      // 0.0
/*90  */                         break;                                                                                 // 0.0
/*92  */                     decodeplane8(s->ham_buf, start, FFMIN(s->planesize, buf_end - start), plane);              // 0.0
/*94  */                 }                                                                                              // 0.0
/*96  */                 decode_ham_plane32((uint32_t *) row, s->ham_buf, s->ham_palbuf, s->planesize);                 // 0.0
/*98  */             }                                                                                                  // 0.0
/*100 */         }                                                                                                      // 0.0
/*102 */     } else if (avctx->codec_tag == MKTAG('D','E','E','P')) {                                                   // 0.0
/*104 */         int raw_width = avctx->width * (av_get_bits_per_pixel(&av_pix_fmt_descriptors[avctx->pix_fmt]) >> 3);  // 0.0
/*106 */         int x;                                                                                                 // 0.0
/*108 */         for(y = 0; y < avctx->height && buf < buf_end; y++ ) {                                                 // 0.0
/*110 */             uint8_t *row = &s->frame.data[0][y * s->frame.linesize[0]];                                        // 0.0
/*112 */             memcpy(row, buf, FFMIN(raw_width, buf_end - buf));                                                 // 0.0
/*114 */             buf += raw_width;                                                                                  // 0.0
/*116 */             if (avctx->pix_fmt == PIX_FMT_BGR32) {                                                             // 0.0
/*118 */                 for(x = 0; x < avctx->width; x++)                                                              // 0.0
/*120 */                     row[4 * x + 3] = row[4 * x + 3] & 0xF0 | (row[4 * x + 3] >> 4);                            // 0.0
/*122 */             }                                                                                                  // 0.0
/*124 */         }                                                                                                      // 0.0
/*126 */     } else if (avctx->codec_tag == MKTAG('I','L','B','M')) { // interleaved                                    // 0.0
/*128 */         if (avctx->pix_fmt == PIX_FMT_PAL8 || avctx->pix_fmt == PIX_FMT_GRAY8) {                               // 0.0
/*130 */             for(y = 0; y < avctx->height; y++ ) {                                                              // 0.0
/*132 */                 uint8_t *row = &s->frame.data[0][ y*s->frame.linesize[0] ];                                    // 0.0
/*134 */                 memset(row, 0, avctx->width);                                                                  // 0.0
/*136 */                 for (plane = 0; plane < s->bpp && buf < buf_end; plane++) {                                    // 0.0
/*138 */                     decodeplane8(row, buf, FFMIN(s->planesize, buf_end - buf), plane);                         // 0.0
/*140 */                     buf += s->planesize;                                                                       // 0.0
/*142 */                 }                                                                                              // 0.0
/*144 */             }                                                                                                  // 0.0
/*146 */         } else if (s->ham) { // HAM to PIX_FMT_BGR32                                                           // 0.0
/*148 */             for (y = 0; y < avctx->height; y++) {                                                              // 0.0
/*150 */                 uint8_t *row = &s->frame.data[0][ y*s->frame.linesize[0] ];                                    // 0.0
/*152 */                 memset(s->ham_buf, 0, s->planesize * 8);                                                       // 0.0
/*154 */                 for (plane = 0; plane < s->bpp && buf < buf_end; plane++) {                                    // 0.0
/*156 */                     decodeplane8(s->ham_buf, buf, FFMIN(s->planesize, buf_end - buf), plane);                  // 0.0
/*158 */                     buf += s->planesize;                                                                       // 0.0
/*160 */                 }                                                                                              // 0.0
/*162 */                 decode_ham_plane32((uint32_t *) row, s->ham_buf, s->ham_palbuf, s->planesize);                 // 0.0
/*164 */             }                                                                                                  // 0.0
/*166 */         } else { // PIX_FMT_BGR32                                                                              // 0.0
/*168 */             for(y = 0; y < avctx->height; y++ ) {                                                              // 0.0
/*170 */                 uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];                                      // 0.0
/*172 */                 memset(row, 0, avctx->width << 2);                                                             // 0.0
/*174 */                 for (plane = 0; plane < s->bpp && buf < buf_end; plane++) {                                    // 0.0
/*176 */                     decodeplane32((uint32_t *) row, buf, FFMIN(s->planesize, buf_end - buf), plane);           // 0.0
/*178 */                     buf += s->planesize;                                                                       // 0.0
/*180 */                 }                                                                                              // 0.0
/*182 */             }                                                                                                  // 0.0
/*184 */         }                                                                                                      // 0.0
/*186 */     } else if (avctx->codec_tag == MKTAG('P','B','M',' ')) { // IFF-PBM                                        // 0.0
/*188 */         if (avctx->pix_fmt == PIX_FMT_PAL8 || avctx->pix_fmt == PIX_FMT_GRAY8) {                               // 0.0
/*190 */             for(y = 0; y < avctx->height; y++ ) {                                                              // 0.0
/*192 */                 uint8_t *row = &s->frame.data[0][y * s->frame.linesize[0]];                                    // 0.0
/*194 */                 memcpy(row, buf, FFMIN(avctx->width, buf_end - buf));                                          // 0.0
/*196 */                 buf += avctx->width + (avctx->width % 2); // padding if odd                                    // 0.0
/*198 */             }                                                                                                  // 0.0
/*200 */         } else if (s->ham) { // IFF-PBM: HAM to PIX_FMT_BGR32                                                  // 0.0
/*202 */             for (y = 0; y < avctx->height; y++) {                                                              // 0.0
/*204 */                 uint8_t *row = &s->frame.data[0][ y*s->frame.linesize[0] ];                                    // 0.0
/*206 */                 memcpy(s->ham_buf, buf, FFMIN(avctx->width, buf_end - buf));                                   // 0.0
/*208 */                 buf += avctx->width + (avctx->width & 1); // padding if odd                                    // 0.0
/*210 */                 decode_ham_plane32((uint32_t *) row, s->ham_buf, s->ham_palbuf, s->planesize);                 // 0.0
/*212 */             }                                                                                                  // 0.0
/*214 */         } else {                                                                                               // 0.0
/*216 */             av_log_ask_for_sample(avctx, "unsupported bpp\n");                                                 // 0.0
/*218 */             return AVERROR_INVALIDDATA;                                                                        // 0.0
/*220 */         }                                                                                                      // 0.0
/*222 */     }                                                                                                          // 0.0
/*226 */     *data_size = sizeof(AVFrame);                                                                              // 0.0
/*228 */     *(AVFrame*)data = s->frame;                                                                                // 0.0
/*230 */     return buf_size;                                                                                           // 0.0
/*232 */ }                                                                                                              // 0.0

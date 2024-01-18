// commit message FFmpeg@b488679510 (target=1, prob=0.74670964, correct=True): iff: fix invalid reads (ticket 689)
/*0   */ static int decode_frame_byterun1(AVCodecContext *avctx,                                         // (11) 0.03516
/*2   */                             void *data, int *data_size,                                         // (3) 0.07227
/*4   */                             AVPacket *avpkt)                                                    // (4) 0.06836
/*6   */ {                                                                                               // (19) 0.001953
/*8   */     IffContext *s = avctx->priv_data;                                                           // (12) 0.03125
/*10  */     const uint8_t *buf = avpkt->size >= 2 ? avpkt->data + AV_RB16(avpkt->data) : NULL;          // (1) 0.07617
/*12  */     const int buf_size = avpkt->size >= 2 ? avpkt->size - AV_RB16(avpkt->data) : 0;             // (2) 0.07227
/*14  */     const uint8_t *buf_end = buf+buf_size;                                                      // (10) 0.03711
/*16  */     int y, plane, res;                                                                          // (14) 0.01953
/*20  */     if ((res = extract_header(avctx, avpkt)) < 0)                                               // (9) 0.04102
/*22  */         return res;                                                                             // (17) 0.01953
/*24  */     if (s->init) {                                                                              // (15) 0.01953
/*26  */         if ((res = avctx->reget_buffer(avctx, &s->frame)) < 0) {                                // (6) 0.06055
/*28  */             av_log(avctx, AV_LOG_ERROR, "reget_buffer() failed\n");                             // (5) 0.06641
/*30  */             return res;                                                                         // (13) 0.02734
/*32  */         }                                                                                       // (18) 0.01562
/*34  */     } else if ((res = avctx->get_buffer(avctx, &s->frame)) < 0) {                               // (8) 0.05469
/*36  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                                   // (7) 0.05664
/*38  */         return res;                                                                             // (16) 0.01953
/*40  */     } else if (avctx->bits_per_coded_sample <= 8 && avctx->pix_fmt != PIX_FMT_GRAY8) {          // (0) 0.07812
/*42  */         if ((res = ff_cmap_read_palette(avctx, (uint32_t*)s->frame.data[1])) < 0)               // 0.0
/*44  */             return res;                                                                         // 0.0
/*46  */     }                                                                                           // 0.0
/*48  */     s->init = 1;                                                                                // 0.0
/*52  */     if (avctx->codec_tag == MKTAG('I','L','B','M')) { //interleaved                             // 0.0
/*54  */         if (avctx->pix_fmt == PIX_FMT_PAL8 || avctx->pix_fmt == PIX_FMT_GRAY8) {                // 0.0
/*56  */             for(y = 0; y < avctx->height ; y++ ) {                                              // 0.0
/*58  */                 uint8_t *row = &s->frame.data[0][ y*s->frame.linesize[0] ];                     // 0.0
/*60  */                 memset(row, 0, avctx->width);                                                   // 0.0
/*62  */                 for (plane = 0; plane < s->bpp; plane++) {                                      // 0.0
/*64  */                     buf += decode_byterun(s->planebuf, s->planesize, buf, buf_end);             // 0.0
/*66  */                     decodeplane8(row, s->planebuf, s->planesize, plane);                        // 0.0
/*68  */                 }                                                                               // 0.0
/*70  */             }                                                                                   // 0.0
/*72  */         } else if (s->ham) { // HAM to PIX_FMT_BGR32                                            // 0.0
/*74  */             for (y = 0; y < avctx->height ; y++) {                                              // 0.0
/*76  */                 uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];                       // 0.0
/*78  */                 memset(s->ham_buf, 0, avctx->width);                                            // 0.0
/*80  */                 for (plane = 0; plane < s->bpp; plane++) {                                      // 0.0
/*82  */                     buf += decode_byterun(s->planebuf, s->planesize, buf, buf_end);             // 0.0
/*84  */                     decodeplane8(s->ham_buf, s->planebuf, s->planesize, plane);                 // 0.0
/*86  */                 }                                                                               // 0.0
/*88  */                 decode_ham_plane32((uint32_t *) row, s->ham_buf, s->ham_palbuf, s->planesize);  // 0.0
/*90  */             }                                                                                   // 0.0
/*92  */         } else { //PIX_FMT_BGR32                                                                // 0.0
/*94  */             for(y = 0; y < avctx->height ; y++ ) {                                              // 0.0
/*96  */                 uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];                       // 0.0
/*98  */                 memset(row, 0, avctx->width << 2);                                              // 0.0
/*100 */                 for (plane = 0; plane < s->bpp; plane++) {                                      // 0.0
/*102 */                     buf += decode_byterun(s->planebuf, s->planesize, buf, buf_end);             // 0.0
/*104 */                     decodeplane32((uint32_t *) row, s->planebuf, s->planesize, plane);          // 0.0
/*106 */                 }                                                                               // 0.0
/*108 */             }                                                                                   // 0.0
/*110 */         }                                                                                       // 0.0
/*112 */     } else if (avctx->pix_fmt == PIX_FMT_PAL8 || avctx->pix_fmt == PIX_FMT_GRAY8) { // IFF-PBM  // 0.0
/*114 */         for(y = 0; y < avctx->height ; y++ ) {                                                  // 0.0
/*116 */             uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];                           // 0.0
/*118 */             buf += decode_byterun(row, avctx->width, buf, buf_end);                             // 0.0
/*120 */         }                                                                                       // 0.0
/*122 */     } else { // IFF-PBM: HAM to PIX_FMT_BGR32                                                   // 0.0
/*124 */         for (y = 0; y < avctx->height ; y++) {                                                  // 0.0
/*126 */             uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];                           // 0.0
/*128 */             buf += decode_byterun(s->ham_buf, avctx->width, buf, buf_end);                      // 0.0
/*130 */             decode_ham_plane32((uint32_t *) row, s->ham_buf, s->ham_palbuf, avctx->width);      // 0.0
/*132 */         }                                                                                       // 0.0
/*134 */     }                                                                                           // 0.0
/*138 */     *data_size = sizeof(AVFrame);                                                               // 0.0
/*140 */     *(AVFrame*)data = s->frame;                                                                 // 0.0
/*142 */     return buf_size;                                                                            // 0.0
/*144 */ }                                                                                               // 0.0

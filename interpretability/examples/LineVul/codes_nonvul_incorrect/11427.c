// commit message FFmpeg@2862b63783 (target=0, prob=0.8914919, correct=False): lavc: Move prediction_method to codec private options
/*0   */ static int encode_picture_ls(AVCodecContext *avctx, AVPacket *pkt,                // (6) 0.04492
/*2   */                              const AVFrame *pict, int *got_packet)                // (1) 0.08008
/*4   */ {                                                                                 // (28) 0.001953
/*6   */     const AVFrame *const p = pict;                                                // (14) 0.02344
/*8   */     const int near         = avctx->prediction_method;                            // (7) 0.04492
/*10  */     PutBitContext pb, pb2;                                                        // (11) 0.02539
/*12  */     GetBitContext gb;                                                             // (23) 0.01758
/*14  */     uint8_t *buf2 = NULL;                                                         // (12) 0.02539
/*16  */     uint8_t *zero = NULL;                                                         // (18) 0.02344
/*18  */     uint8_t *cur  = NULL;                                                         // (13) 0.02539
/*20  */     uint8_t *last = NULL;                                                         // (17) 0.02344
/*22  */     JLSState *state;                                                              // (22) 0.01758
/*24  */     int i, size, ret;                                                             // (20) 0.01953
/*26  */     int comps;                                                                    // (25) 0.01367
/*30  */     if (avctx->pix_fmt == AV_PIX_FMT_GRAY8 ||                                     // (5) 0.05078
/*32  */         avctx->pix_fmt == AV_PIX_FMT_GRAY16)                                      // (4) 0.05469
/*34  */         comps = 1;                                                                // (16) 0.02344
/*36  */     else                                                                          // (26) 0.007813
/*38  */         comps = 3;                                                                // (15) 0.02344
/*42  */     if ((ret = ff_alloc_packet(pkt, avctx->width * avctx->height * comps * 4 +    // (2) 0.0625
/*44  */                                AV_INPUT_BUFFER_MIN_SIZE)) < 0) {                  // (0) 0.08984
/*46  */         av_log(avctx, AV_LOG_ERROR, "Error getting output packet.\n");            // (3) 0.05664
/*48  */         return ret;                                                               // (21) 0.01953
/*50  */     }                                                                             // (27) 0.007813
/*54  */     buf2 = av_malloc(pkt->size);                                                  // (10) 0.03125
/*56  */     if (!buf2)                                                                    // (24) 0.01562
/*58  */         goto memfail;                                                             // (19) 0.02148
/*62  */     init_put_bits(&pb, pkt->data, pkt->size);                                     // (8) 0.04102
/*64  */     init_put_bits(&pb2, buf2, pkt->size);                                         // (9) 0.03906
/*68  */     /* write our own JPEG header, can't use mjpeg_picture_header */               // 0.0
/*70  */     put_marker(&pb, SOI);                                                         // 0.0
/*72  */     put_marker(&pb, SOF48);                                                       // 0.0
/*74  */     put_bits(&pb, 16, 8 + comps * 3); // header size depends on components        // 0.0
/*76  */     put_bits(&pb, 8, (avctx->pix_fmt == AV_PIX_FMT_GRAY16) ? 16 : 8);  // bpp     // 0.0
/*78  */     put_bits(&pb, 16, avctx->height);                                             // 0.0
/*80  */     put_bits(&pb, 16, avctx->width);                                              // 0.0
/*82  */     put_bits(&pb, 8, comps);          // components                               // 0.0
/*84  */     for (i = 1; i <= comps; i++) {                                                // 0.0
/*86  */         put_bits(&pb, 8, i);     // component ID                                  // 0.0
/*88  */         put_bits(&pb, 8, 0x11);  // subsampling: none                             // 0.0
/*90  */         put_bits(&pb, 8, 0);     // Tiq, used by JPEG-LS ext                      // 0.0
/*92  */     }                                                                             // 0.0
/*96  */     put_marker(&pb, SOS);                                                         // 0.0
/*98  */     put_bits(&pb, 16, 6 + comps * 2);                                             // 0.0
/*100 */     put_bits(&pb, 8, comps);                                                      // 0.0
/*102 */     for (i = 1; i <= comps; i++) {                                                // 0.0
/*104 */         put_bits(&pb, 8, i);   // component ID                                    // 0.0
/*106 */         put_bits(&pb, 8, 0);   // mapping index: none                             // 0.0
/*108 */     }                                                                             // 0.0
/*110 */     put_bits(&pb, 8, near);                                                       // 0.0
/*112 */     put_bits(&pb, 8, (comps > 1) ? 1 : 0);  // interleaving: 0 - plane, 1 - line  // 0.0
/*114 */     put_bits(&pb, 8, 0);  // point transform: none                                // 0.0
/*118 */     state = av_mallocz(sizeof(JLSState));                                         // 0.0
/*120 */     if (!state)                                                                   // 0.0
/*122 */         goto memfail;                                                             // 0.0
/*126 */     /* initialize JPEG-LS state from JPEG parameters */                           // 0.0
/*128 */     state->near = near;                                                           // 0.0
/*130 */     state->bpp  = (avctx->pix_fmt == AV_PIX_FMT_GRAY16) ? 16 : 8;                 // 0.0
/*132 */     ff_jpegls_reset_coding_parameters(state, 0);                                  // 0.0
/*134 */     ff_jpegls_init_state(state);                                                  // 0.0
/*138 */     ls_store_lse(state, &pb);                                                     // 0.0
/*142 */     zero = last = av_mallocz(p->linesize[0]);                                     // 0.0
/*144 */     if (!zero)                                                                    // 0.0
/*146 */         goto memfail;                                                             // 0.0
/*150 */     cur  = p->data[0];                                                            // 0.0
/*152 */     if (avctx->pix_fmt == AV_PIX_FMT_GRAY8) {                                     // 0.0
/*154 */         int t = 0;                                                                // 0.0
/*158 */         for (i = 0; i < avctx->height; i++) {                                     // 0.0
/*160 */             ls_encode_line(state, &pb2, last, cur, t, avctx->width, 1, 0, 8);     // 0.0
/*162 */             t    = last[0];                                                       // 0.0
/*164 */             last = cur;                                                           // 0.0
/*166 */             cur += p->linesize[0];                                                // 0.0
/*168 */         }                                                                         // 0.0
/*170 */     } else if (avctx->pix_fmt == AV_PIX_FMT_GRAY16) {                             // 0.0
/*172 */         int t = 0;                                                                // 0.0
/*176 */         for (i = 0; i < avctx->height; i++) {                                     // 0.0
/*178 */             ls_encode_line(state, &pb2, last, cur, t, avctx->width, 1, 0, 16);    // 0.0
/*180 */             t    = *((uint16_t *)last);                                           // 0.0
/*182 */             last = cur;                                                           // 0.0
/*184 */             cur += p->linesize[0];                                                // 0.0
/*186 */         }                                                                         // 0.0
/*188 */     } else if (avctx->pix_fmt == AV_PIX_FMT_RGB24) {                              // 0.0
/*190 */         int j, width;                                                             // 0.0
/*192 */         int Rc[3] = { 0, 0, 0 };                                                  // 0.0
/*196 */         width = avctx->width * 3;                                                 // 0.0
/*198 */         for (i = 0; i < avctx->height; i++) {                                     // 0.0
/*200 */             for (j = 0; j < 3; j++) {                                             // 0.0
/*202 */                 ls_encode_line(state, &pb2, last + j, cur + j, Rc[j],             // 0.0
/*204 */                                width, 3, j, 8);                                   // 0.0
/*206 */                 Rc[j] = last[j];                                                  // 0.0
/*208 */             }                                                                     // 0.0
/*210 */             last = cur;                                                           // 0.0
/*212 */             cur += p->linesize[0];                                                // 0.0
/*214 */         }                                                                         // 0.0
/*216 */     } else if (avctx->pix_fmt == AV_PIX_FMT_BGR24) {                              // 0.0
/*218 */         int j, width;                                                             // 0.0
/*220 */         int Rc[3] = { 0, 0, 0 };                                                  // 0.0
/*224 */         width = avctx->width * 3;                                                 // 0.0
/*226 */         for (i = 0; i < avctx->height; i++) {                                     // 0.0
/*228 */             for (j = 2; j >= 0; j--) {                                            // 0.0
/*230 */                 ls_encode_line(state, &pb2, last + j, cur + j, Rc[j],             // 0.0
/*232 */                                width, 3, j, 8);                                   // 0.0
/*234 */                 Rc[j] = last[j];                                                  // 0.0
/*236 */             }                                                                     // 0.0
/*238 */             last = cur;                                                           // 0.0
/*240 */             cur += p->linesize[0];                                                // 0.0
/*242 */         }                                                                         // 0.0
/*244 */     }                                                                             // 0.0
/*248 */     av_freep(&zero);                                                              // 0.0
/*250 */     av_freep(&state);                                                             // 0.0
/*254 */     /* the specification says that after doing 0xff escaping unused bits in       // 0.0
/*256 */      * the last byte must be set to 0, so just append 7 "optional" zero-bits      // 0.0
/*258 */      * to avoid special-casing. */                                                // 0.0
/*260 */     put_bits(&pb2, 7, 0);                                                         // 0.0
/*262 */     size = put_bits_count(&pb2);                                                  // 0.0
/*264 */     flush_put_bits(&pb2);                                                         // 0.0
/*266 */     /* do escape coding */                                                        // 0.0
/*268 */     init_get_bits(&gb, buf2, size);                                               // 0.0
/*270 */     size -= 7;                                                                    // 0.0
/*272 */     while (get_bits_count(&gb) < size) {                                          // 0.0
/*274 */         int v;                                                                    // 0.0
/*276 */         v = get_bits(&gb, 8);                                                     // 0.0
/*278 */         put_bits(&pb, 8, v);                                                      // 0.0
/*280 */         if (v == 0xFF) {                                                          // 0.0
/*282 */             v = get_bits(&gb, 7);                                                 // 0.0
/*284 */             put_bits(&pb, 8, v);                                                  // 0.0
/*286 */         }                                                                         // 0.0
/*288 */     }                                                                             // 0.0
/*290 */     avpriv_align_put_bits(&pb);                                                   // 0.0
/*292 */     av_freep(&buf2);                                                              // 0.0
/*296 */     /* End of image */                                                            // 0.0
/*298 */     put_marker(&pb, EOI);                                                         // 0.0
/*300 */     flush_put_bits(&pb);                                                          // 0.0
/*304 */     emms_c();                                                                     // 0.0
/*308 */     pkt->size   = put_bits_count(&pb) >> 3;                                       // 0.0
/*310 */     pkt->flags |= AV_PKT_FLAG_KEY;                                                // 0.0
/*312 */     *got_packet = 1;                                                              // 0.0
/*314 */     return 0;                                                                     // 0.0
/*318 */ memfail:                                                                          // 0.0
/*320 */     av_packet_unref(pkt);                                                         // 0.0
/*322 */     av_freep(&buf2);                                                              // 0.0
/*324 */     av_freep(&state);                                                             // 0.0
/*326 */     av_freep(&zero);                                                              // 0.0
/*328 */     return AVERROR(ENOMEM);                                                       // 0.0
/*330 */ }                                                                                 // 0.0

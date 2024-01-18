// commit message FFmpeg@850c6db97d (target=0, prob=0.7768589, correct=False): avcodec/utvideodec: Factor multiply out of inner loop
/*0   */ static int decode_plane(UtvideoContext *c, int plane_no,                                                                                                            // (10) 0.03516
/*2   */                         uint8_t *dst, int step, ptrdiff_t stride,                                                                                                   // (1) 0.07812
/*4   */                         int width, int height,                                                                                                                      // (5) 0.05664
/*6   */                         const uint8_t *src, int use_pred)                                                                                                           // (2) 0.07031
/*8   */ {                                                                                                                                                                   // (21) 0.001953
/*10  */     int i, j, slice, pix;                                                                                                                                           // (14) 0.02539
/*12  */     int sstart, send;                                                                                                                                               // (18) 0.01758
/*14  */     VLC vlc;                                                                                                                                                        // (19) 0.01563
/*16  */     GetBitContext gb;                                                                                                                                               // (16) 0.01758
/*18  */     int prev, fsym;                                                                                                                                                 // (17) 0.01758
/*20  */     const int cmask = c->interlaced ? ~(1 + 2 * (!plane_no && c->avctx->pix_fmt == AV_PIX_FMT_YUV420P)) : ~(!plane_no && c->avctx->pix_fmt == AV_PIX_FMT_YUV420P);  // (0) 0.1582
/*24  */     if (build_huff(src, &vlc, &fsym)) {                                                                                                                             // (9) 0.04102
/*26  */         av_log(c->avctx, AV_LOG_ERROR, "Cannot build Huffman codes\n");                                                                                             // (4) 0.0625
/*28  */         return AVERROR_INVALIDDATA;                                                                                                                                 // (12) 0.0332
/*30  */     }                                                                                                                                                               // (20) 0.007812
/*32  */     if (fsym >= 0) { // build_huff reported a symbol to fill slices with                                                                                            // (7) 0.04492
/*34  */         send = 0;                                                                                                                                                   // (15) 0.02148
/*36  */         for (slice = 0; slice < c->slices; slice++) {                                                                                                               // (6) 0.04687
/*38  */             uint8_t *dest;                                                                                                                                          // (11) 0.03516
/*42  */             sstart = send;                                                                                                                                          // (13) 0.03125
/*44  */             send   = (height * (slice + 1) / c->slices) & cmask;                                                                                                    // (3) 0.06641
/*46  */             dest   = dst + sstart * stride;                                                                                                                         // (8) 0.04297
/*50  */             prev = 0x80;                                                                                                                                            // 0.0
/*52  */             for (j = sstart; j < send; j++) {                                                                                                                       // 0.0
/*54  */                 for (i = 0; i < width * step; i += step) {                                                                                                          // 0.0
/*56  */                     pix = fsym;                                                                                                                                     // 0.0
/*58  */                     if (use_pred) {                                                                                                                                 // 0.0
/*60  */                         prev += pix;                                                                                                                                // 0.0
/*62  */                         pix   = prev;                                                                                                                               // 0.0
/*64  */                     }                                                                                                                                               // 0.0
/*66  */                     dest[i] = pix;                                                                                                                                  // 0.0
/*68  */                 }                                                                                                                                                   // 0.0
/*70  */                 dest += stride;                                                                                                                                     // 0.0
/*72  */             }                                                                                                                                                       // 0.0
/*74  */         }                                                                                                                                                           // 0.0
/*76  */         return 0;                                                                                                                                                   // 0.0
/*78  */     }                                                                                                                                                               // 0.0
/*82  */     src      += 256;                                                                                                                                                // 0.0
/*86  */     send = 0;                                                                                                                                                       // 0.0
/*88  */     for (slice = 0; slice < c->slices; slice++) {                                                                                                                   // 0.0
/*90  */         uint8_t *dest;                                                                                                                                              // 0.0
/*92  */         int slice_data_start, slice_data_end, slice_size;                                                                                                           // 0.0
/*96  */         sstart = send;                                                                                                                                              // 0.0
/*98  */         send   = (height * (slice + 1) / c->slices) & cmask;                                                                                                        // 0.0
/*100 */         dest   = dst + sstart * stride;                                                                                                                             // 0.0
/*104 */         // slice offset and size validation was done earlier                                                                                                        // 0.0
/*106 */         slice_data_start = slice ? AV_RL32(src + slice * 4 - 4) : 0;                                                                                                // 0.0
/*108 */         slice_data_end   = AV_RL32(src + slice * 4);                                                                                                                // 0.0
/*110 */         slice_size       = slice_data_end - slice_data_start;                                                                                                       // 0.0
/*114 */         if (!slice_size) {                                                                                                                                          // 0.0
/*116 */             av_log(c->avctx, AV_LOG_ERROR, "Plane has more than one symbol "                                                                                        // 0.0
/*118 */                    "yet a slice has a length of zero.\n");                                                                                                          // 0.0
/*120 */             goto fail;                                                                                                                                              // 0.0
/*122 */         }                                                                                                                                                           // 0.0
/*126 */         memset(c->slice_bits + slice_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);                                                                                        // 0.0
/*128 */         c->bdsp.bswap_buf((uint32_t *) c->slice_bits,                                                                                                               // 0.0
/*130 */                           (uint32_t *)(src + slice_data_start + c->slices * 4),                                                                                     // 0.0
/*132 */                           (slice_data_end - slice_data_start + 3) >> 2);                                                                                            // 0.0
/*134 */         init_get_bits(&gb, c->slice_bits, slice_size * 8);                                                                                                          // 0.0
/*138 */         prev = 0x80;                                                                                                                                                // 0.0
/*140 */         for (j = sstart; j < send; j++) {                                                                                                                           // 0.0
/*142 */             for (i = 0; i < width * step; i += step) {                                                                                                              // 0.0
/*144 */                 pix = get_vlc2(&gb, vlc.table, VLC_BITS, 3);                                                                                                        // 0.0
/*146 */                 if (pix < 0) {                                                                                                                                      // 0.0
/*148 */                     av_log(c->avctx, AV_LOG_ERROR, "Decoding error\n");                                                                                             // 0.0
/*150 */                     goto fail;                                                                                                                                      // 0.0
/*152 */                 }                                                                                                                                                   // 0.0
/*154 */                 if (use_pred) {                                                                                                                                     // 0.0
/*156 */                     prev += pix;                                                                                                                                    // 0.0
/*158 */                     pix   = prev;                                                                                                                                   // 0.0
/*160 */                 }                                                                                                                                                   // 0.0
/*162 */                 dest[i] = pix;                                                                                                                                      // 0.0
/*164 */             }                                                                                                                                                       // 0.0
/*166 */             if (get_bits_left(&gb) < 0) {                                                                                                                           // 0.0
/*168 */                 av_log(c->avctx, AV_LOG_ERROR,                                                                                                                      // 0.0
/*170 */                         "Slice decoding ran out of bits\n");                                                                                                        // 0.0
/*172 */                 goto fail;                                                                                                                                          // 0.0
/*174 */             }                                                                                                                                                       // 0.0
/*176 */             dest += stride;                                                                                                                                         // 0.0
/*178 */         }                                                                                                                                                           // 0.0
/*180 */         if (get_bits_left(&gb) > 32)                                                                                                                                // 0.0
/*182 */             av_log(c->avctx, AV_LOG_WARNING,                                                                                                                        // 0.0
/*184 */                    "%d bits left after decoding slice\n", get_bits_left(&gb));                                                                                      // 0.0
/*186 */     }                                                                                                                                                               // 0.0
/*190 */     ff_free_vlc(&vlc);                                                                                                                                              // 0.0
/*194 */     return 0;                                                                                                                                                       // 0.0
/*196 */ fail:                                                                                                                                                               // 0.0
/*198 */     ff_free_vlc(&vlc);                                                                                                                                              // 0.0
/*200 */     return AVERROR_INVALIDDATA;                                                                                                                                     // 0.0
/*202 */ }                                                                                                                                                                   // 0.0

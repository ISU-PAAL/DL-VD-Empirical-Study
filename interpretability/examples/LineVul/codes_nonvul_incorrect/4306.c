// commit message FFmpeg@6a6bc43f5f (target=0, prob=0.8239171, correct=False): dxtory: Factorize slice size checks
/*0   */ static int dxtory_decode_v2_420(AVCodecContext *avctx, AVFrame *pic,                    // (3) 0.05273
/*2   */                                 const uint8_t *src, int src_size)                       // (0) 0.08594
/*4   */ {                                                                                       // (24) 0.001953
/*6   */     GetByteContext gb;                                                                  // (20) 0.01758
/*8   */     GetBitContext  gb2;                                                                 // (19) 0.02148
/*10  */     int nslices, slice, slice_height, ref_slice_height;                                 // (7) 0.03906
/*12  */     int cur_y, next_y;                                                                  // (17) 0.02344
/*14  */     uint32_t off, slice_size;                                                           // (16) 0.02539
/*16  */     uint8_t *Y, *U, *V;                                                                 // (15) 0.03125
/*18  */     int ret;                                                                            // (21) 0.01172
/*22  */     bytestream2_init(&gb, src, src_size);                                               // (12) 0.03516
/*24  */     nslices = bytestream2_get_le16(&gb);                                                // (8) 0.03711
/*26  */     off = FFALIGN(nslices * 4 + 2, 16);                                                 // (9) 0.03711
/*28  */     if (src_size < off) {                                                               // (18) 0.02344
/*30  */         av_log(avctx, AV_LOG_ERROR, "no slice data\n");                                 // (4) 0.05273
/*32  */         return AVERROR_INVALIDDATA;                                                     // (14) 0.0332
/*34  */     }                                                                                   // (22) 0.007812
/*38  */     if (!nslices || avctx->height % nslices) {                                          // (10) 0.03711
/*40  */         avpriv_request_sample(avctx, "%d slices for %dx%d", nslices,                    // (2) 0.05859
/*42  */                               avctx->width, avctx->height);                             // (1) 0.07617
/*44  */         return AVERROR_PATCHWELCOME;                                                    // (11) 0.03711
/*46  */     }                                                                                   // (23) 0.007812
/*50  */     ref_slice_height = avctx->height / nslices;                                         // (13) 0.03516
/*52  */     if ((avctx->width & 1) || (avctx->height & 1)) {                                    // (6) 0.04297
/*54  */         avpriv_request_sample(avctx, "Frame dimensions %dx%d",                          // (5) 0.04883
/*56  */                               avctx->width, avctx->height);                             // 0.0
/*58  */     }                                                                                   // 0.0
/*62  */     avctx->pix_fmt = AV_PIX_FMT_YUV420P;                                                // 0.0
/*64  */     if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)                                       // 0.0
/*66  */         return ret;                                                                     // 0.0
/*70  */     Y = pic->data[0];                                                                   // 0.0
/*72  */     U = pic->data[1];                                                                   // 0.0
/*74  */     V = pic->data[2];                                                                   // 0.0
/*78  */     cur_y  = 0;                                                                         // 0.0
/*80  */     next_y = ref_slice_height;                                                          // 0.0
/*82  */     for (slice = 0; slice < nslices; slice++) {                                         // 0.0
/*84  */         slice_size   = bytestream2_get_le32(&gb);                                       // 0.0
/*86  */         slice_height = (next_y & ~1) - (cur_y & ~1);                                    // 0.0
/*88  */         if (slice_size > src_size - off) {                                              // 0.0
/*90  */             av_log(avctx, AV_LOG_ERROR,                                                 // 0.0
/*92  */                    "invalid slice size %"PRIu32" (only %"PRIu32" bytes left)\n",        // 0.0
/*94  */                    slice_size, src_size - off);                                         // 0.0
/*96  */             return AVERROR_INVALIDDATA;                                                 // 0.0
/*98  */         }                                                                               // 0.0
/*100 */         if (slice_size <= 16) {                                                         // 0.0
/*102 */             av_log(avctx, AV_LOG_ERROR, "invalid slice size %"PRIu32"\n", slice_size);  // 0.0
/*104 */             return AVERROR_INVALIDDATA;                                                 // 0.0
/*106 */         }                                                                               // 0.0
/*110 */         if (AV_RL32(src + off) != slice_size - 16) {                                    // 0.0
/*112 */             av_log(avctx, AV_LOG_ERROR,                                                 // 0.0
/*114 */                    "Slice sizes mismatch: got %"PRIu32" instead of %"PRIu32"\n",        // 0.0
/*116 */                    AV_RL32(src + off), slice_size - 16);                                // 0.0
/*118 */         }                                                                               // 0.0
/*120 */         init_get_bits(&gb2, src + off + 16, (slice_size - 16) * 8);                     // 0.0
/*122 */         dx2_decode_slice_420(&gb2, avctx->width, slice_height, Y, U, V,                 // 0.0
/*124 */                              pic->linesize[0], pic->linesize[1],                        // 0.0
/*126 */                              pic->linesize[2]);                                         // 0.0
/*130 */         Y += pic->linesize[0] *  slice_height;                                          // 0.0
/*132 */         U += pic->linesize[1] * (slice_height >> 1);                                    // 0.0
/*134 */         V += pic->linesize[2] * (slice_height >> 1);                                    // 0.0
/*136 */         off += slice_size;                                                              // 0.0
/*138 */         cur_y   = next_y;                                                               // 0.0
/*140 */         next_y += ref_slice_height;                                                     // 0.0
/*142 */     }                                                                                   // 0.0
/*146 */     return 0;                                                                           // 0.0
/*148 */ }                                                                                       // 0.0

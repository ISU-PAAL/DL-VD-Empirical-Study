// commit message FFmpeg@ccc27e2139 (target=1, prob=0.8114475, correct=True): bfi: Use bytestream2 functions to prevent buffer overreads.
/*0   */ static int bfi_decode_frame(AVCodecContext *avctx, void *data,               // (8) 0.04297
/*2   */                             int *data_size, AVPacket *avpkt)                 // (0) 0.08008
/*4   */ {                                                                            // (24) 0.001953
/*6   */     const uint8_t *buf = avpkt->data, *buf_end = avpkt->data + avpkt->size;  // (1) 0.06641
/*8   */     int buf_size = avpkt->size;                                              // (16) 0.02734
/*10  */     BFIContext *bfi = avctx->priv_data;                                      // (11) 0.03516
/*12  */     uint8_t *dst = bfi->dst;                                                 // (13) 0.0332
/*14  */     uint8_t *src, *dst_offset, colour1, colour2;                             // (9) 0.04297
/*16  */     uint8_t *frame_end = bfi->dst + avctx->width * avctx->height;            // (4) 0.05469
/*18  */     uint32_t *pal;                                                           // (22) 0.01953
/*20  */     int i, j, height = avctx->height;                                        // (14) 0.0293
/*24  */     if (bfi->frame.data[0])                                                  // (15) 0.02734
/*26  */         avctx->release_buffer(avctx, &bfi->frame);                           // (7) 0.04492
/*30  */     bfi->frame.reference = 1;                                                // (19) 0.02344
/*34  */     if (avctx->get_buffer(avctx, &bfi->frame) < 0) {                         // (6) 0.04883
/*36  */         av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");                // (3) 0.05664
/*38  */         return -1;                                                           // (21) 0.02148
/*40  */     }                                                                        // (23) 0.007812
/*44  */     /* Set frame parameters and palette, if necessary */                     // (17) 0.02539
/*46  */     if (!avctx->frame_number) {                                              // (18) 0.02539
/*48  */         bfi->frame.pict_type = AV_PICTURE_TYPE_I;                            // (5) 0.05078
/*50  */         bfi->frame.key_frame = 1;                                            // (12) 0.03516
/*52  */         /* Setting the palette */                                            // (20) 0.02344
/*54  */         if (avctx->extradata_size > 768) {                                   // (10) 0.04102
/*56  */             av_log(NULL, AV_LOG_ERROR, "Palette is too large.\n");           // (2) 0.06445
/*58  */             return -1;                                                       // 0.0
/*60  */         }                                                                    // 0.0
/*62  */         pal = (uint32_t *)bfi->frame.data[1];                                // 0.0
/*64  */         for (i = 0; i < avctx->extradata_size / 3; i++) {                    // 0.0
/*66  */             int shift = 16;                                                  // 0.0
/*68  */             *pal = 0;                                                        // 0.0
/*70  */             for (j = 0; j < 3; j++, shift -= 8)                              // 0.0
/*72  */                 *pal +=                                                      // 0.0
/*74  */                     ((avctx->extradata[i * 3 + j] << 2) |                    // 0.0
/*76  */                     (avctx->extradata[i * 3 + j] >> 4)) << shift;            // 0.0
/*78  */             pal++;                                                           // 0.0
/*80  */         }                                                                    // 0.0
/*82  */         bfi->frame.palette_has_changed = 1;                                  // 0.0
/*84  */     } else {                                                                 // 0.0
/*86  */         bfi->frame.pict_type = AV_PICTURE_TYPE_P;                            // 0.0
/*88  */         bfi->frame.key_frame = 0;                                            // 0.0
/*90  */     }                                                                        // 0.0
/*94  */     buf += 4; // Unpacked size, not required.                                // 0.0
/*98  */     while (dst != frame_end) {                                               // 0.0
/*100 */         static const uint8_t lentab[4] = { 0, 2, 0, 1 };                     // 0.0
/*102 */         unsigned int byte   = *buf++, av_uninit(offset);                     // 0.0
/*104 */         unsigned int code   = byte >> 6;                                     // 0.0
/*106 */         unsigned int length = byte & ~0xC0;                                  // 0.0
/*110 */         if (buf >= buf_end) {                                                // 0.0
/*112 */             av_log(avctx, AV_LOG_ERROR,                                      // 0.0
/*114 */                    "Input resolution larger than actual frame.\n");          // 0.0
/*116 */             return -1;                                                       // 0.0
/*118 */         }                                                                    // 0.0
/*122 */         /* Get length and offset(if required) */                             // 0.0
/*124 */         if (length == 0) {                                                   // 0.0
/*126 */             if (code == 1) {                                                 // 0.0
/*128 */                 length = bytestream_get_byte(&buf);                          // 0.0
/*130 */                 offset = bytestream_get_le16(&buf);                          // 0.0
/*132 */             } else {                                                         // 0.0
/*134 */                 length = bytestream_get_le16(&buf);                          // 0.0
/*136 */                 if (code == 2 && length == 0)                                // 0.0
/*138 */                     break;                                                   // 0.0
/*140 */             }                                                                // 0.0
/*142 */         } else {                                                             // 0.0
/*144 */             if (code == 1)                                                   // 0.0
/*146 */                 offset = bytestream_get_byte(&buf);                          // 0.0
/*148 */         }                                                                    // 0.0
/*152 */         /* Do boundary check */                                              // 0.0
/*154 */         if (dst + (length << lentab[code]) > frame_end)                      // 0.0
/*156 */             break;                                                           // 0.0
/*160 */         switch (code) {                                                      // 0.0
/*164 */         case 0:                //Normal Chain                                // 0.0
/*166 */             if (length >= buf_end - buf) {                                   // 0.0
/*168 */                 av_log(avctx, AV_LOG_ERROR, "Frame larger than buffer.\n");  // 0.0
/*170 */                 return -1;                                                   // 0.0
/*172 */             }                                                                // 0.0
/*174 */             bytestream_get_buffer(&buf, dst, length);                        // 0.0
/*176 */             dst += length;                                                   // 0.0
/*178 */             break;                                                           // 0.0
/*182 */         case 1:                //Back Chain                                  // 0.0
/*184 */             dst_offset = dst - offset;                                       // 0.0
/*186 */             length *= 4;        //Convert dwords to bytes.                   // 0.0
/*188 */             if (dst_offset < bfi->dst)                                       // 0.0
/*190 */                 break;                                                       // 0.0
/*192 */             while (length--)                                                 // 0.0
/*194 */                 *dst++ = *dst_offset++;                                      // 0.0
/*196 */             break;                                                           // 0.0
/*200 */         case 2:                //Skip Chain                                  // 0.0
/*202 */             dst += length;                                                   // 0.0
/*204 */             break;                                                           // 0.0
/*208 */         case 3:                //Fill Chain                                  // 0.0
/*210 */             colour1 = bytestream_get_byte(&buf);                             // 0.0
/*212 */             colour2 = bytestream_get_byte(&buf);                             // 0.0
/*214 */             while (length--) {                                               // 0.0
/*216 */                 *dst++ = colour1;                                            // 0.0
/*218 */                 *dst++ = colour2;                                            // 0.0
/*220 */             }                                                                // 0.0
/*222 */             break;                                                           // 0.0
/*226 */         }                                                                    // 0.0
/*228 */     }                                                                        // 0.0
/*232 */     src = bfi->dst;                                                          // 0.0
/*234 */     dst = bfi->frame.data[0];                                                // 0.0
/*236 */     while (height--) {                                                       // 0.0
/*238 */         memcpy(dst, src, avctx->width);                                      // 0.0
/*240 */         src += avctx->width;                                                 // 0.0
/*242 */         dst += bfi->frame.linesize[0];                                       // 0.0
/*244 */     }                                                                        // 0.0
/*246 */     *data_size = sizeof(AVFrame);                                            // 0.0
/*248 */     *(AVFrame *)data = bfi->frame;                                           // 0.0
/*250 */     return buf_size;                                                         // 0.0
/*252 */ }                                                                            // 0.0

// commit message FFmpeg@842e98b4d8 (target=0, prob=0.52299374, correct=False): pgssubdec: reset rle_data_len/rle_remaining_len on allocation error
/*0   */ static int parse_object_segment(AVCodecContext *avctx,                                                 // (8) 0.03321
/*2   */                                   const uint8_t *buf, int buf_size)                                    // (0) 0.08984
/*4   */ {                                                                                                      // (28) 0.00196
/*6   */     PGSSubContext *ctx = avctx->priv_data;                                                             // (10) 0.0332
/*8   */     PGSSubObject *object;                                                                              // (20) 0.01953
/*12  */     uint8_t sequence_desc;                                                                             // (18) 0.02148
/*14  */     unsigned int rle_bitmap_len, width, height;                                                        // (9) 0.0332
/*16  */     int id;                                                                                            // (26) 0.01172
/*20  */     if (buf_size <= 4)                                                                                 // (19) 0.02148
/*22  */         return AVERROR_INVALIDDATA;                                                                    // (12) 0.0332
/*24  */     buf_size -= 4;                                                                                     // (21) 0.01758
/*28  */     id = bytestream_get_be16(&buf);                                                                    // (13) 0.03125
/*30  */     object = find_object(id, &ctx->objects);                                                           // (14) 0.03125
/*32  */     if (!object) {                                                                                     // (24) 0.01562
/*34  */         if (ctx->objects.count >= MAX_EPOCH_OBJECTS) {                                                 // (2) 0.05273
/*36  */             av_log(avctx, AV_LOG_ERROR, "Too many objects in epoch\n");                                // (1) 0.06445
/*38  */             return AVERROR_INVALIDDATA;                                                                // (7) 0.04101
/*40  */         }                                                                                              // (23) 0.01562
/*42  */         object = &ctx->objects.object[ctx->objects.count++];                                           // (5) 0.04492
/*44  */         object->id = id;                                                                               // (17) 0.02539
/*46  */     }                                                                                                  // (27) 0.007812
/*50  */     /* skip object version number */                                                                   // (22) 0.01758
/*52  */     buf += 1;                                                                                          // (25) 0.01367
/*56  */     /* Read the Sequence Description to determine if start of RLE data or appended to previous RLE */  // (3) 0.04687
/*58  */     sequence_desc = bytestream_get_byte(&buf);                                                         // (11) 0.0332
/*62  */     if (!(sequence_desc & 0x80)) {                                                                     // (15) 0.0293
/*64  */         /* Additional RLE data */                                                                      // (16) 0.02539
/*66  */         if (buf_size > object->rle_remaining_len)                                                      // (4) 0.04492
/*68  */             return AVERROR_INVALIDDATA;                                                                // (6) 0.04101
/*72  */         memcpy(object->rle + object->rle_data_len, buf, buf_size);                                     // 0.0
/*74  */         object->rle_data_len += buf_size;                                                              // 0.0
/*76  */         object->rle_remaining_len -= buf_size;                                                         // 0.0
/*80  */         return 0;                                                                                      // 0.0
/*82  */     }                                                                                                  // 0.0
/*86  */     if (buf_size <= 7)                                                                                 // 0.0
/*88  */         return AVERROR_INVALIDDATA;                                                                    // 0.0
/*90  */     buf_size -= 7;                                                                                     // 0.0
/*94  */     /* Decode rle bitmap length, stored size includes width/height data */                             // 0.0
/*96  */     rle_bitmap_len = bytestream_get_be24(&buf) - 2*2;                                                  // 0.0
/*100 */     if (buf_size > rle_bitmap_len) {                                                                   // 0.0
/*102 */         av_log(avctx, AV_LOG_ERROR,                                                                    // 0.0
/*104 */                "Buffer dimension %d larger than the expected RLE data %d\n",                           // 0.0
/*106 */                buf_size, rle_bitmap_len);                                                              // 0.0
/*108 */         return AVERROR_INVALIDDATA;                                                                    // 0.0
/*110 */     }                                                                                                  // 0.0
/*114 */     /* Get bitmap dimensions from data */                                                              // 0.0
/*116 */     width  = bytestream_get_be16(&buf);                                                                // 0.0
/*118 */     height = bytestream_get_be16(&buf);                                                                // 0.0
/*122 */     /* Make sure the bitmap is not too large */                                                        // 0.0
/*124 */     if (avctx->width < width || avctx->height < height || !width || !height) {                         // 0.0
/*126 */         av_log(avctx, AV_LOG_ERROR, "Bitmap dimensions (%dx%d) invalid.\n", width, height);            // 0.0
/*128 */         return AVERROR_INVALIDDATA;                                                                    // 0.0
/*130 */     }                                                                                                  // 0.0
/*134 */     object->w = width;                                                                                 // 0.0
/*136 */     object->h = height;                                                                                // 0.0
/*140 */     av_fast_padded_malloc(&object->rle, &object->rle_buffer_size, rle_bitmap_len);                     // 0.0
/*144 */     if (!object->rle)                                                                                  // 0.0
/*146 */         return AVERROR(ENOMEM);                                                                        // 0.0
/*150 */     memcpy(object->rle, buf, buf_size);                                                                // 0.0
/*152 */     object->rle_data_len = buf_size;                                                                   // 0.0
/*154 */     object->rle_remaining_len = rle_bitmap_len - buf_size;                                             // 0.0
/*158 */     return 0;                                                                                          // 0.0
/*160 */ }                                                                                                      // 0.0

// commit message FFmpeg@5ecabd3c54 (target=1, prob=0.63758034, correct=True): msrle: Use FFABS to determine the frame size in msrle_decode_pal4
/*0   */ static int msrle_decode_pal4(AVCodecContext *avctx, AVPicture *pic,                       // (3) 0.05273
/*2   */                              GetByteContext *gb)                                          // (1) 0.06641
/*4   */ {                                                                                         // (24) 0.001953
/*6   */     unsigned char rle_code;                                                               // (20) 0.01953
/*8   */     unsigned char extra_byte, odd_pixel;                                                  // (17) 0.02539
/*10  */     unsigned char stream_byte;                                                            // (21) 0.01758
/*12  */     unsigned int pixel_ptr = 0;                                                           // (19) 0.02148
/*14  */     int row_dec = pic->linesize[0];                                                       // (16) 0.0293
/*16  */     int row_ptr = (avctx->height - 1) * row_dec;                                          // (11) 0.04102
/*18  */     int frame_size = row_dec * avctx->height;                                             // (14) 0.0332
/*20  */     int i;                                                                                // (23) 0.01172
/*24  */     while (row_ptr >= 0) {                                                                // (18) 0.02344
/*26  */         if (bytestream2_get_bytes_left(gb) <= 0) {                                        // (4) 0.05078
/*28  */             av_log(avctx, AV_LOG_ERROR,                                                   // (8) 0.04687
/*30  */                    "MS RLE: bytestream overrun, %d rows left\n",                          // (0) 0.06836
/*32  */                    row_ptr);                                                              // (10) 0.04297
/*34  */             return AVERROR_INVALIDDATA;                                                   // (12) 0.04102
/*36  */         }                                                                                 // (22) 0.01562
/*38  */         rle_code = stream_byte = bytestream2_get_byteu(gb);                               // (2) 0.05469
/*40  */         if (rle_code == 0) {                                                              // (15) 0.0332
/*42  */             /* fetch the next byte to see how to handle escape code */                    // (7) 0.04687
/*44  */             stream_byte = bytestream2_get_byte(gb);                                       // (5) 0.05078
/*46  */             if (stream_byte == 0) {                                                       // (13) 0.03906
/*48  */                 /* line is done, goto the next one */                                     // (6) 0.04883
/*50  */                 row_ptr -= row_dec;                                                       // (9) 0.04492
/*52  */                 pixel_ptr = 0;                                                            // 0.0
/*54  */             } else if (stream_byte == 1) {                                                // 0.0
/*56  */                 /* decode is done */                                                      // 0.0
/*58  */                 return 0;                                                                 // 0.0
/*60  */             } else if (stream_byte == 2) {                                                // 0.0
/*62  */                 /* reposition frame decode coordinates */                                 // 0.0
/*64  */                 stream_byte = bytestream2_get_byte(gb);                                   // 0.0
/*66  */                 pixel_ptr += stream_byte;                                                 // 0.0
/*68  */                 stream_byte = bytestream2_get_byte(gb);                                   // 0.0
/*70  */                 row_ptr -= stream_byte * row_dec;                                         // 0.0
/*72  */             } else {                                                                      // 0.0
/*74  */                 // copy pixels from encoded stream                                        // 0.0
/*76  */                 odd_pixel =  stream_byte & 1;                                             // 0.0
/*78  */                 rle_code = (stream_byte + 1) / 2;                                         // 0.0
/*80  */                 extra_byte = rle_code & 0x01;                                             // 0.0
/*82  */                 if (row_ptr + pixel_ptr + stream_byte > frame_size ||                     // 0.0
/*84  */                     bytestream2_get_bytes_left(gb) < rle_code) {                          // 0.0
/*86  */                     av_log(avctx, AV_LOG_ERROR,                                           // 0.0
/*88  */                            "MS RLE: frame/stream ptr just went out of bounds (copy)\n");  // 0.0
/*90  */                     return AVERROR_INVALIDDATA;                                           // 0.0
/*92  */                 }                                                                         // 0.0
/*96  */                 for (i = 0; i < rle_code; i++) {                                          // 0.0
/*98  */                     if (pixel_ptr >= avctx->width)                                        // 0.0
/*100 */                         break;                                                            // 0.0
/*102 */                     stream_byte = bytestream2_get_byteu(gb);                              // 0.0
/*104 */                     pic->data[0][row_ptr + pixel_ptr] = stream_byte >> 4;                 // 0.0
/*106 */                     pixel_ptr++;                                                          // 0.0
/*108 */                     if (i + 1 == rle_code && odd_pixel)                                   // 0.0
/*110 */                         break;                                                            // 0.0
/*112 */                     if (pixel_ptr >= avctx->width)                                        // 0.0
/*114 */                         break;                                                            // 0.0
/*116 */                     pic->data[0][row_ptr + pixel_ptr] = stream_byte & 0x0F;               // 0.0
/*118 */                     pixel_ptr++;                                                          // 0.0
/*120 */                 }                                                                         // 0.0
/*124 */                 // if the RLE code is odd, skip a byte in the stream                      // 0.0
/*126 */                 if (extra_byte)                                                           // 0.0
/*128 */                     bytestream2_skip(gb, 1);                                              // 0.0
/*130 */             }                                                                             // 0.0
/*132 */         } else {                                                                          // 0.0
/*134 */             // decode a run of data                                                       // 0.0
/*136 */             if (row_ptr + pixel_ptr + stream_byte > frame_size) {                         // 0.0
/*138 */                 av_log(avctx, AV_LOG_ERROR,                                               // 0.0
/*140 */                        "MS RLE: frame ptr just went out of bounds (run)\n");              // 0.0
/*142 */                 return AVERROR_INVALIDDATA;                                               // 0.0
/*144 */             }                                                                             // 0.0
/*146 */             stream_byte = bytestream2_get_byte(gb);                                       // 0.0
/*148 */             for (i = 0; i < rle_code; i++) {                                              // 0.0
/*150 */                 if (pixel_ptr >= avctx->width)                                            // 0.0
/*152 */                     break;                                                                // 0.0
/*154 */                 if ((i & 1) == 0)                                                         // 0.0
/*156 */                     pic->data[0][row_ptr + pixel_ptr] = stream_byte >> 4;                 // 0.0
/*158 */                 else                                                                      // 0.0
/*160 */                     pic->data[0][row_ptr + pixel_ptr] = stream_byte & 0x0F;               // 0.0
/*162 */                 pixel_ptr++;                                                              // 0.0
/*164 */             }                                                                             // 0.0
/*166 */         }                                                                                 // 0.0
/*168 */     }                                                                                     // 0.0
/*172 */     /* one last sanity check on the way out */                                            // 0.0
/*174 */     if (bytestream2_get_bytes_left(gb)) {                                                 // 0.0
/*176 */         av_log(avctx, AV_LOG_ERROR,                                                       // 0.0
/*178 */                "MS RLE: ended frame decode with %d bytes left over\n",                    // 0.0
/*180 */                bytestream2_get_bytes_left(gb));                                           // 0.0
/*182 */         return AVERROR_INVALIDDATA;                                                       // 0.0
/*184 */     }                                                                                     // 0.0
/*188 */     return 0;                                                                             // 0.0
/*190 */ }                                                                                         // 0.0

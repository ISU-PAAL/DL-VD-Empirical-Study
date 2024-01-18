// commit message FFmpeg@5a08ba5381 (target=0, prob=0.65032107, correct=False): avcodec/hnm4video: check offset in decode_interframe_v4() more completely
/*0   */ static void decode_interframe_v4(AVCodecContext *avctx, uint8_t *src, uint32_t size)                 // (3) 0.06055
/*2   */ {                                                                                                    // (21) 0.001953
/*4   */     Hnm4VideoContext *hnm = avctx->priv_data;                                                        // (12) 0.03711
/*6   */     GetByteContext gb;                                                                               // (20) 0.01758
/*8   */     uint32_t writeoffset = 0, count, left, offset;                                                   // (15) 0.03516
/*10  */     uint8_t tag, previous, backline, backward, swap;                                                 // (13) 0.03516
/*14  */     bytestream2_init(&gb, src, size);                                                                // (18) 0.03125
/*18  */     while (bytestream2_tell(&gb) < size) {                                                           // (14) 0.03516
/*20  */         count = bytestream2_peek_byte(&gb) & 0x1F;                                                   // (6) 0.05273
/*22  */         if (count == 0) {                                                                            // (19) 0.02734
/*24  */             tag = bytestream2_get_byte(&gb) & 0xE0;                                                  // (4) 0.05859
/*26  */             tag = tag >> 5;                                                                          // (17) 0.0332
/*28  */             if (tag == 0) {                                                                          // (16) 0.03516
/*30  */                 hnm->current[writeoffset++] = bytestream2_get_byte(&gb);                             // (0) 0.07031
/*32  */                 hnm->current[writeoffset++] = bytestream2_get_byte(&gb);                             // (1) 0.07031
/*34  */             } else if (tag == 1) {                                                                   // (7) 0.03906
/*36  */                 writeoffset += bytestream2_get_byte(&gb) * 2;                                        // (2) 0.0625
/*38  */             } else if (tag == 2) {                                                                   // (9) 0.03906
/*40  */                 count = bytestream2_get_le16(&gb);                                                   // (5) 0.05664
/*42  */                 count *= 2;                                                                          // (11) 0.03906
/*44  */                 writeoffset += count;                                                                // (8) 0.03906
/*46  */             } else if (tag == 3) {                                                                   // (10) 0.03906
/*48  */                 count = bytestream2_get_byte(&gb) * 2;                                               // 0.0
/*50  */                 while (count > 0) {                                                                  // 0.0
/*52  */                     hnm->current[writeoffset++] = bytestream2_peek_byte(&gb);                        // 0.0
/*54  */                     count--;                                                                         // 0.0
/*56  */                 }                                                                                    // 0.0
/*58  */                 bytestream2_skip(&gb, 1);                                                            // 0.0
/*60  */             } else {                                                                                 // 0.0
/*62  */                 break;                                                                               // 0.0
/*64  */             }                                                                                        // 0.0
/*66  */         } else {                                                                                     // 0.0
/*68  */             previous = bytestream2_peek_byte(&gb) & 0x20;                                            // 0.0
/*70  */             backline = bytestream2_peek_byte(&gb) & 0x40;                                            // 0.0
/*72  */             backward = bytestream2_peek_byte(&gb) & 0x80;                                            // 0.0
/*74  */             bytestream2_skip(&gb, 1);                                                                // 0.0
/*76  */             swap   = bytestream2_peek_byte(&gb) & 0x01;                                              // 0.0
/*78  */             offset = bytestream2_get_le16(&gb);                                                      // 0.0
/*80  */             offset = (offset >> 1) & 0x7FFF;                                                         // 0.0
/*82  */             offset = writeoffset + (offset * 2) - 0x8000;                                            // 0.0
/*86  */             left = count;                                                                            // 0.0
/*90  */             if (!backward && offset + count >= hnm->width * hnm->height) {                           // 0.0
/*92  */                 av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds");                     // 0.0
/*94  */                 break;                                                                               // 0.0
/*96  */             } else if (backward && offset >= hnm->width * hnm->height) {                             // 0.0
/*98  */                 av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds");                     // 0.0
/*100 */                 break;                                                                               // 0.0
/*102 */             } else if (writeoffset + count >= hnm->width * hnm->height) {                            // 0.0
/*104 */                 av_log(avctx, AV_LOG_ERROR,                                                          // 0.0
/*106 */                        "Attempting to write out of bounds");                                         // 0.0
/*108 */                 break;                                                                               // 0.0
/*110 */             }                                                                                        // 0.0
/*114 */             if (previous) {                                                                          // 0.0
/*116 */                 while (left > 0) {                                                                   // 0.0
/*118 */                     if (backline) {                                                                  // 0.0
/*120 */                         hnm->current[writeoffset++] = hnm->previous[offset - (2 * hnm->width) + 1];  // 0.0
/*122 */                         hnm->current[writeoffset++] = hnm->previous[offset++];                       // 0.0
/*124 */                         offset++;                                                                    // 0.0
/*126 */                     } else {                                                                         // 0.0
/*128 */                         hnm->current[writeoffset++] = hnm->previous[offset++];                       // 0.0
/*130 */                         hnm->current[writeoffset++] = hnm->previous[offset++];                       // 0.0
/*132 */                     }                                                                                // 0.0
/*134 */                     if (backward)                                                                    // 0.0
/*136 */                         offset -= 4;                                                                 // 0.0
/*138 */                     left--;                                                                          // 0.0
/*140 */                 }                                                                                    // 0.0
/*142 */             } else {                                                                                 // 0.0
/*144 */                 while (left > 0) {                                                                   // 0.0
/*146 */                     if (backline) {                                                                  // 0.0
/*148 */                         hnm->current[writeoffset++] = hnm->current[offset - (2 * hnm->width) + 1];   // 0.0
/*150 */                         hnm->current[writeoffset++] = hnm->current[offset++];                        // 0.0
/*152 */                         offset++;                                                                    // 0.0
/*154 */                     } else {                                                                         // 0.0
/*156 */                         hnm->current[writeoffset++] = hnm->current[offset++];                        // 0.0
/*158 */                         hnm->current[writeoffset++] = hnm->current[offset++];                        // 0.0
/*160 */                     }                                                                                // 0.0
/*162 */                     if (backward)                                                                    // 0.0
/*164 */                         offset -= 4;                                                                 // 0.0
/*166 */                     left--;                                                                          // 0.0
/*168 */                 }                                                                                    // 0.0
/*170 */             }                                                                                        // 0.0
/*174 */             if (swap) {                                                                              // 0.0
/*176 */                 left         = count;                                                                // 0.0
/*178 */                 writeoffset -= count * 2;                                                            // 0.0
/*180 */                 while (left > 0) {                                                                   // 0.0
/*182 */                     swap = hnm->current[writeoffset];                                                // 0.0
/*184 */                     hnm->current[writeoffset] = hnm->current[writeoffset + 1];                       // 0.0
/*186 */                     hnm->current[writeoffset + 1] = swap;                                            // 0.0
/*188 */                     left--;                                                                          // 0.0
/*190 */                     writeoffset += 2;                                                                // 0.0
/*192 */                 }                                                                                    // 0.0
/*194 */             }                                                                                        // 0.0
/*196 */         }                                                                                            // 0.0
/*198 */     }                                                                                                // 0.0
/*200 */ }                                                                                                    // 0.0

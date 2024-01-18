// commit message FFmpeg@03acb035d1 (target=1, prob=0.62033886, correct=True): avcodec/vqavideo: clear uninitialized parts of the decode buffer
/*0   */ static int decode_format80(VqaContext *s, int src_size,                                                                         // (10) 0.03517
/*2   */     unsigned char *dest, int dest_size, int check_size) {                                                                       // (9) 0.03711
/*6   */     int dest_index = 0;                                                                                                         // (19) 0.01953
/*8   */     int count, opcode, start;                                                                                                   // (18) 0.02149
/*10  */     int src_pos;                                                                                                                // (20) 0.01562
/*12  */     unsigned char color;                                                                                                        // (22) 0.01367
/*14  */     int i;                                                                                                                      // (23) 0.01172
/*18  */     start = bytestream2_tell(&s->gb);                                                                                           // (15) 0.03125
/*20  */     while (bytestream2_tell(&s->gb) - start < src_size) {                                                                       // (5) 0.04687
/*22  */         opcode = bytestream2_get_byte(&s->gb);                                                                                  // (6) 0.04492
/*24  */         av_dlog(s->avctx, "opcode %02X: ", opcode);                                                                             // (4) 0.05468
/*28  */         /* 0x80 means that frame is finished */                                                                                 // (12) 0.03321
/*30  */         if (opcode == 0x80)                                                                                                     // (16) 0.03125
/*32  */             break;                                                                                                              // (17) 0.02539
/*36  */         if (dest_index >= dest_size) {                                                                                          // (11) 0.03515
/*38  */             av_log(s->avctx, AV_LOG_ERROR, "decode_format80 problem: dest_index (%d) exceeded dest_size (%d)\n",                // (0) 0.0957
/*40  */                 dest_index, dest_size);                                                                                         // (7) 0.04492
/*42  */             return AVERROR_INVALIDDATA;                                                                                         // (8) 0.04101
/*44  */         }                                                                                                                       // (21) 0.01562
/*48  */         if (opcode == 0xFF) {                                                                                                   // (14) 0.0332
/*52  */             count   = bytestream2_get_le16(&s->gb);                                                                             // (3) 0.05664
/*54  */             src_pos = bytestream2_get_le16(&s->gb);                                                                             // (2) 0.05664
/*56  */             av_dlog(s->avctx, "(1) copy %X bytes from absolute pos %X\n", count, src_pos);                                      // (1) 0.08204
/*58  */             CHECK_COUNT();                                                                                                      // (13) 0.0332
/*60  */             CHECK_COPY(src_pos);                                                                                                // 0.0
/*62  */             for (i = 0; i < count; i++)                                                                                         // 0.0
/*64  */                 dest[dest_index + i] = dest[src_pos + i];                                                                       // 0.0
/*66  */             dest_index += count;                                                                                                // 0.0
/*70  */         } else if (opcode == 0xFE) {                                                                                            // 0.0
/*74  */             count = bytestream2_get_le16(&s->gb);                                                                               // 0.0
/*76  */             color = bytestream2_get_byte(&s->gb);                                                                               // 0.0
/*78  */             av_dlog(s->avctx, "(2) set %X bytes to %02X\n", count, color);                                                      // 0.0
/*80  */             CHECK_COUNT();                                                                                                      // 0.0
/*82  */             memset(&dest[dest_index], color, count);                                                                            // 0.0
/*84  */             dest_index += count;                                                                                                // 0.0
/*88  */         } else if ((opcode & 0xC0) == 0xC0) {                                                                                   // 0.0
/*92  */             count = (opcode & 0x3F) + 3;                                                                                        // 0.0
/*94  */             src_pos = bytestream2_get_le16(&s->gb);                                                                             // 0.0
/*96  */             av_dlog(s->avctx, "(3) copy %X bytes from absolute pos %X\n", count, src_pos);                                      // 0.0
/*98  */             CHECK_COUNT();                                                                                                      // 0.0
/*100 */             CHECK_COPY(src_pos);                                                                                                // 0.0
/*102 */             for (i = 0; i < count; i++)                                                                                         // 0.0
/*104 */                 dest[dest_index + i] = dest[src_pos + i];                                                                       // 0.0
/*106 */             dest_index += count;                                                                                                // 0.0
/*110 */         } else if (opcode > 0x80) {                                                                                             // 0.0
/*114 */             count = opcode & 0x3F;                                                                                              // 0.0
/*116 */             av_dlog(s->avctx, "(4) copy %X bytes from source to dest\n", count);                                                // 0.0
/*118 */             CHECK_COUNT();                                                                                                      // 0.0
/*120 */             bytestream2_get_buffer(&s->gb, &dest[dest_index], count);                                                           // 0.0
/*122 */             dest_index += count;                                                                                                // 0.0
/*126 */         } else {                                                                                                                // 0.0
/*130 */             count = ((opcode & 0x70) >> 4) + 3;                                                                                 // 0.0
/*132 */             src_pos = bytestream2_get_byte(&s->gb) | ((opcode & 0x0F) << 8);                                                    // 0.0
/*134 */             av_dlog(s->avctx, "(5) copy %X bytes from relpos %X\n", count, src_pos);                                            // 0.0
/*136 */             CHECK_COUNT();                                                                                                      // 0.0
/*138 */             CHECK_COPY(dest_index - src_pos);                                                                                   // 0.0
/*140 */             for (i = 0; i < count; i++)                                                                                         // 0.0
/*142 */                 dest[dest_index + i] = dest[dest_index - src_pos + i];                                                          // 0.0
/*144 */             dest_index += count;                                                                                                // 0.0
/*146 */         }                                                                                                                       // 0.0
/*148 */     }                                                                                                                           // 0.0
/*152 */     /* validate that the entire destination buffer was filled; this is                                                          // 0.0
/*154 */      * important for decoding frame maps since each vector needs to have a                                                      // 0.0
/*156 */      * codebook entry; it is not important for compressed codebooks because                                                     // 0.0
/*158 */      * not every entry needs to be filled */                                                                                    // 0.0
/*160 */     if (check_size)                                                                                                             // 0.0
/*162 */         if (dest_index < dest_size)                                                                                             // 0.0
/*164 */             av_log(s->avctx, AV_LOG_ERROR, "decode_format80 problem: decode finished with dest_index (%d) < dest_size (%d)\n",  // 0.0
/*166 */                 dest_index, dest_size);                                                                                         // 0.0
/*170 */     return 0; // let's display what we decoded anyway                                                                           // 0.0
/*172 */ }                                                                                                                               // 0.0

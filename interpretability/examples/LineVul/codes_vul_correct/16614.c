// commit message FFmpeg@9c85329cd0 (target=1, prob=0.761494, correct=True): avcodec/pafvideo: Check for bitstream end in decode_0()
/*0   */ static int decode_0(PAFVideoDecContext *c, uint8_t *pkt, uint8_t code)          // (6) 0.0547
/*2   */ {                                                                               // (22) 0.001959
/*4   */     uint32_t opcode_size, offset;                                               // (16) 0.02734
/*6   */     uint8_t *dst, *dend, mask = 0, color = 0;                                   // (9) 0.04494
/*8   */     const uint8_t *src, *send, *opcodes;                                        // (12) 0.03517
/*10  */     int i, j, op = 0;                                                           // (18) 0.02347
/*14  */     i = bytestream2_get_byte(&c->gb);                                           // (13) 0.03515
/*16  */     if (i) {                                                                    // (20) 0.01562
/*18  */         if (code & 0x10) {                                                      // (14) 0.03125
/*20  */             int align;                                                          // (17) 0.02734
/*24  */             align = bytestream2_tell(&c->gb) & 3;                               // (7) 0.05273
/*26  */             if (align)                                                          // (15) 0.02929
/*28  */                 bytestream2_skip(&c->gb, 4 - align);                            // (3) 0.05859
/*30  */         }                                                                       // (21) 0.01562
/*32  */         do {                                                                    // (19) 0.01758
/*34  */             int page, val, x, y;                                                // (10) 0.03906
/*36  */             val    = bytestream2_get_be16(&c->gb);                              // (2) 0.05859
/*38  */             page   = val >> 14;                                                 // (11) 0.0371
/*40  */             x      = (val & 0x7F) * 2;                                          // (4) 0.05663
/*42  */             y      = ((val >> 7) & 0x7F) * 2;                                   // (0) 0.06249
/*44  */             dst    = c->frame[page] + x + y * c->width;                         // (1) 0.06054
/*46  */             dend   = c->frame[page] + c->frame_size;                            // (5) 0.05663
/*48  */             offset = (x & 0x7F) * 2;                                            // (8) 0.04687
/*50  */             j      = bytestream2_get_le16(&c->gb) + offset;                     // 0.0
/*52  */             do {                                                                // 0.0
/*54  */                 offset++;                                                       // 0.0
/*56  */                 if (dst + 3 * c->width + 4 > dend)                              // 0.0
/*58  */                     return AVERROR_INVALIDDATA;                                 // 0.0
/*60  */                 read4x4block(c, dst, c->width);                                 // 0.0
/*62  */                 if ((offset & 0x3F) == 0)                                       // 0.0
/*64  */                     dst += c->width * 3;                                        // 0.0
/*66  */                 dst += 4;                                                       // 0.0
/*68  */             } while (offset < j);                                               // 0.0
/*70  */         } while (--i);                                                          // 0.0
/*72  */     }                                                                           // 0.0
/*76  */     dst  = c->frame[c->current_frame];                                          // 0.0
/*78  */     dend = c->frame[c->current_frame] + c->frame_size;                          // 0.0
/*80  */     do {                                                                        // 0.0
/*82  */         set_src_position(c, &src, &send);                                       // 0.0
/*84  */         if ((src + 3 * c->width + 4 > send) ||                                  // 0.0
/*86  */             (dst + 3 * c->width + 4 > dend))                                    // 0.0
/*88  */             return AVERROR_INVALIDDATA;                                         // 0.0
/*90  */         copy_block4(dst, src, c->width, c->width, 4);                           // 0.0
/*92  */         i++;                                                                    // 0.0
/*94  */         if ((i & 0x3F) == 0)                                                    // 0.0
/*96  */             dst += c->width * 3;                                                // 0.0
/*98  */         dst += 4;                                                               // 0.0
/*100 */     } while (i < c->video_size / 16);                                           // 0.0
/*104 */     opcode_size = bytestream2_get_le16(&c->gb);                                 // 0.0
/*106 */     bytestream2_skip(&c->gb, 2);                                                // 0.0
/*110 */     if (bytestream2_get_bytes_left(&c->gb) < opcode_size)                       // 0.0
/*112 */         return AVERROR_INVALIDDATA;                                             // 0.0
/*116 */     opcodes = pkt + bytestream2_tell(&c->gb);                                   // 0.0
/*118 */     bytestream2_skipu(&c->gb, opcode_size);                                     // 0.0
/*122 */     dst = c->frame[c->current_frame];                                           // 0.0
/*126 */     for (i = 0; i < c->height; i += 4, dst += c->width * 3)                     // 0.0
/*128 */         for (j = 0; j < c->width; j += 4, dst += 4) {                           // 0.0
/*130 */             int opcode, k = 0;                                                  // 0.0
/*132 */             if (op > opcode_size)                                               // 0.0
/*134 */                 return AVERROR_INVALIDDATA;                                     // 0.0
/*136 */             if (j & 4) {                                                        // 0.0
/*138 */                 opcode = opcodes[op] & 15;                                      // 0.0
/*140 */                 op++;                                                           // 0.0
/*142 */             } else {                                                            // 0.0
/*144 */                 opcode = opcodes[op] >> 4;                                      // 0.0
/*146 */             }                                                                   // 0.0
/*150 */             while (block_sequences[opcode][k]) {                                // 0.0
/*152 */                 offset = c->width * 2;                                          // 0.0
/*154 */                 code   = block_sequences[opcode][k++];                          // 0.0
/*158 */                 switch (code) {                                                 // 0.0
/*160 */                 case 2:                                                         // 0.0
/*162 */                     offset = 0;                                                 // 0.0
/*164 */                 case 3:                                                         // 0.0
/*166 */                     color = bytestream2_get_byte(&c->gb);                       // 0.0
/*168 */                 case 4:                                                         // 0.0
/*170 */                     mask = bytestream2_get_byte(&c->gb);                        // 0.0
/*172 */                     copy_color_mask(dst + offset, c->width, mask, color);       // 0.0
/*174 */                     break;                                                      // 0.0
/*176 */                 case 5:                                                         // 0.0
/*178 */                     offset = 0;                                                 // 0.0
/*180 */                 case 6:                                                         // 0.0
/*182 */                     set_src_position(c, &src, &send);                           // 0.0
/*184 */                 case 7:                                                         // 0.0
/*186 */                     if (src + offset + c->width + 4 > send)                     // 0.0
/*188 */                         return AVERROR_INVALIDDATA;                             // 0.0
/*190 */                     mask = bytestream2_get_byte(&c->gb);                        // 0.0
/*192 */                     copy_src_mask(dst + offset, c->width, mask, src + offset);  // 0.0
/*194 */                     break;                                                      // 0.0
/*196 */                 }                                                               // 0.0
/*198 */             }                                                                   // 0.0
/*200 */         }                                                                       // 0.0
/*204 */     return 0;                                                                   // 0.0
/*206 */ }                                                                               // 0.0

// commit message FFmpeg@612ecfbbbb (target=0, prob=0.6167519, correct=False): gifdec: check ff_lzw_decode_init() return value, fix out of array reads
/*0   */ static int gif_read_image(GifState *s)                                                       // (20) 0.02735
/*2   */ {                                                                                            // (25) 0.001953
/*4   */     int left, top, width, height, bits_per_pixel, code_size, flags;                          // (3) 0.04688
/*6   */     int is_interleaved, has_local_palette, y, pass, y1, linesize, n, i;                      // (2) 0.06055
/*8   */     uint8_t *ptr, *spal, *palette, *ptr1;                                                    // (4) 0.04297
/*12  */     left = bytestream_get_le16(&s->bytestream);                                              // (6) 0.03906
/*14  */     top = bytestream_get_le16(&s->bytestream);                                               // (8) 0.03906
/*16  */     width = bytestream_get_le16(&s->bytestream);                                             // (7) 0.03906
/*18  */     height = bytestream_get_le16(&s->bytestream);                                            // (9) 0.03906
/*20  */     flags = bytestream_get_byte(&s->bytestream);                                             // (10) 0.03711
/*22  */     is_interleaved = flags & 0x40;                                                           // (19) 0.0293
/*24  */     has_local_palette = flags & 0x80;                                                        // (14) 0.03125
/*26  */     bits_per_pixel = (flags & 0x07) + 1;                                                     // (11) 0.03711
/*30  */     av_dlog(s->avctx, "image x=%d y=%d w=%d h=%d\n", left, top, width, height);              // (0) 0.08203
/*34  */     if (has_local_palette) {                                                                 // (21) 0.02539
/*36  */         bytestream_get_buffer(&s->bytestream, s->local_palette, 3 * (1 << bits_per_pixel));  // (1) 0.07617
/*38  */         palette = s->local_palette;                                                          // (15) 0.03125
/*40  */     } else {                                                                                 // (23) 0.01172
/*42  */         palette = s->global_palette;                                                         // (16) 0.03125
/*44  */         bits_per_pixel = s->bits_per_pixel;                                                  // (5) 0.04102
/*46  */     }                                                                                        // (24) 0.007812
/*50  */     /* verify that all the image is inside the screen dimensions */                          // (17) 0.0293
/*52  */     if (left + width > s->screen_width ||                                                    // (18) 0.0293
/*54  */         top + height > s->screen_height)                                                     // (12) 0.0332
/*56  */         return AVERROR(EINVAL);                                                              // (13) 0.03125
/*60  */     /* build the palette */                                                                  // (22) 0.01562
/*62  */     n = (1 << bits_per_pixel);                                                               // 0.0
/*64  */     spal = palette;                                                                          // 0.0
/*66  */     for(i = 0; i < n; i++) {                                                                 // 0.0
/*68  */         s->image_palette[i] = (0xffu << 24) | AV_RB24(spal);                                 // 0.0
/*70  */         spal += 3;                                                                           // 0.0
/*72  */     }                                                                                        // 0.0
/*74  */     for(; i < 256; i++)                                                                      // 0.0
/*76  */         s->image_palette[i] = (0xffu << 24);                                                 // 0.0
/*78  */     /* handle transparency */                                                                // 0.0
/*80  */     if (s->transparent_color_index >= 0)                                                     // 0.0
/*82  */         s->image_palette[s->transparent_color_index] = 0;                                    // 0.0
/*86  */     /* now get the image data */                                                             // 0.0
/*88  */     code_size = bytestream_get_byte(&s->bytestream);                                         // 0.0
/*90  */     ff_lzw_decode_init(s->lzw, code_size, s->bytestream,                                     // 0.0
/*92  */                        s->bytestream_end - s->bytestream, FF_LZW_GIF);                       // 0.0
/*96  */     /* read all the image */                                                                 // 0.0
/*98  */     linesize = s->picture.linesize[0];                                                       // 0.0
/*100 */     ptr1 = s->picture.data[0] + top * linesize + left;                                       // 0.0
/*102 */     ptr = ptr1;                                                                              // 0.0
/*104 */     pass = 0;                                                                                // 0.0
/*106 */     y1 = 0;                                                                                  // 0.0
/*108 */     for (y = 0; y < height; y++) {                                                           // 0.0
/*110 */         ff_lzw_decode(s->lzw, ptr, width);                                                   // 0.0
/*112 */         if (is_interleaved) {                                                                // 0.0
/*114 */             switch(pass) {                                                                   // 0.0
/*116 */             default:                                                                         // 0.0
/*118 */             case 0:                                                                          // 0.0
/*120 */             case 1:                                                                          // 0.0
/*122 */                 y1 += 8;                                                                     // 0.0
/*124 */                 ptr += linesize * 8;                                                         // 0.0
/*126 */                 if (y1 >= height) {                                                          // 0.0
/*128 */                     y1 = pass ? 2 : 4;                                                       // 0.0
/*130 */                     ptr = ptr1 + linesize * y1;                                              // 0.0
/*132 */                     pass++;                                                                  // 0.0
/*134 */                 }                                                                            // 0.0
/*136 */                 break;                                                                       // 0.0
/*138 */             case 2:                                                                          // 0.0
/*140 */                 y1 += 4;                                                                     // 0.0
/*142 */                 ptr += linesize * 4;                                                         // 0.0
/*144 */                 if (y1 >= height) {                                                          // 0.0
/*146 */                     y1 = 1;                                                                  // 0.0
/*148 */                     ptr = ptr1 + linesize;                                                   // 0.0
/*150 */                     pass++;                                                                  // 0.0
/*152 */                 }                                                                            // 0.0
/*154 */                 break;                                                                       // 0.0
/*156 */             case 3:                                                                          // 0.0
/*158 */                 y1 += 2;                                                                     // 0.0
/*160 */                 ptr += linesize * 2;                                                         // 0.0
/*162 */                 break;                                                                       // 0.0
/*164 */             }                                                                                // 0.0
/*166 */         } else {                                                                             // 0.0
/*168 */             ptr += linesize;                                                                 // 0.0
/*170 */         }                                                                                    // 0.0
/*172 */     }                                                                                        // 0.0
/*174 */     /* read the garbage data until end marker is found */                                    // 0.0
/*176 */     ff_lzw_decode_tail(s->lzw);                                                              // 0.0
/*178 */     s->bytestream = ff_lzw_cur_ptr(s->lzw);                                                  // 0.0
/*180 */     return 0;                                                                                // 0.0
/*182 */ }                                                                                            // 0.0

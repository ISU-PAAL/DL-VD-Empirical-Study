// commit message qemu@bc210eb163 (target=0, prob=0.28515822, correct=True): pixman: fix vnc tight png/jpeg support
/*0   */ static int send_png_rect(VncState *vs, int x, int y, int w, int h,                // (4) 0.05078
/*2   */                          VncPalette *palette)                                     // (3) 0.0625
/*4   */ {                                                                                 // (24) 0.001953
/*6   */     png_byte color_type;                                                          // (16) 0.02148
/*8   */     png_structp png_ptr;                                                          // (13) 0.02539
/*10  */     png_infop info_ptr;                                                           // (15) 0.02344
/*12  */     png_colorp png_palette = NULL;                                                // (11) 0.03125
/*14  */     pixman_image_t *linebuf;                                                      // (12) 0.02734
/*16  */     int level = tight_png_conf[vs->tight.compression].png_zlib_level;             // (5) 0.05078
/*18  */     int filters = tight_png_conf[vs->tight.compression].png_filters;              // (7) 0.04688
/*20  */     uint8_t *buf;                                                                 // (20) 0.01953
/*22  */     int dy;                                                                       // (22) 0.01172
/*26  */     png_ptr = png_create_write_struct_2(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL,  // (1) 0.07227
/*28  */                                         NULL, vnc_png_malloc, vnc_png_free);      // (0) 0.1094
/*32  */     if (png_ptr == NULL)                                                          // (17) 0.02148
/*34  */         return -1;                                                                // (19) 0.02148
/*38  */     info_ptr = png_create_info_struct(png_ptr);                                   // (9) 0.03906
/*42  */     if (info_ptr == NULL) {                                                       // (14) 0.02344
/*44  */         png_destroy_write_struct(&png_ptr, NULL);                                 // (8) 0.04297
/*46  */         return -1;                                                                // (18) 0.02148
/*48  */     }                                                                             // (23) 0.007813
/*52  */     png_set_write_fn(png_ptr, (void *) vs, png_write_data, png_flush_data);       // (2) 0.06836
/*54  */     png_set_compression_level(png_ptr, level);                                    // (10) 0.03711
/*56  */     png_set_filter(png_ptr, PNG_FILTER_TYPE_DEFAULT, filters);                    // (6) 0.05078
/*60  */     if (palette) {                                                                // (21) 0.01758
/*62  */         color_type = PNG_COLOR_TYPE_PALETTE;                                      // 0.0
/*64  */     } else {                                                                      // 0.0
/*66  */         color_type = PNG_COLOR_TYPE_RGB;                                          // 0.0
/*68  */     }                                                                             // 0.0
/*72  */     png_set_IHDR(png_ptr, info_ptr, w, h,                                         // 0.0
/*74  */                  8, color_type, PNG_INTERLACE_NONE,                               // 0.0
/*76  */                  PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);          // 0.0
/*80  */     if (color_type == PNG_COLOR_TYPE_PALETTE) {                                   // 0.0
/*82  */         struct palette_cb_priv priv;                                              // 0.0
/*86  */         png_palette = png_malloc(png_ptr, sizeof(*png_palette) *                  // 0.0
/*88  */                                  palette_size(palette));                          // 0.0
/*92  */         priv.vs = vs;                                                             // 0.0
/*94  */         priv.png_palette = png_palette;                                           // 0.0
/*96  */         palette_iter(palette, write_png_palette, &priv);                          // 0.0
/*100 */         png_set_PLTE(png_ptr, info_ptr, png_palette, palette_size(palette));      // 0.0
/*104 */         if (vs->client_pf.bytes_per_pixel == 4) {                                 // 0.0
/*106 */             tight_encode_indexed_rect32(vs->tight.tight.buffer, w * h, palette);  // 0.0
/*108 */         } else {                                                                  // 0.0
/*110 */             tight_encode_indexed_rect16(vs->tight.tight.buffer, w * h, palette);  // 0.0
/*112 */         }                                                                         // 0.0
/*114 */     }                                                                             // 0.0
/*118 */     png_write_info(png_ptr, info_ptr);                                            // 0.0
/*122 */     buffer_reserve(&vs->tight.png, 2048);                                         // 0.0
/*124 */     linebuf = qemu_pixman_linebuf_create(PIXMAN_BE_r8g8b8, w);                    // 0.0
/*126 */     buf = (uint8_t *)pixman_image_get_data(linebuf);                              // 0.0
/*128 */     for (dy = 0; dy < h; dy++)                                                    // 0.0
/*130 */     {                                                                             // 0.0
/*132 */         if (color_type == PNG_COLOR_TYPE_PALETTE) {                               // 0.0
/*134 */             memcpy(buf, vs->tight.tight.buffer + (dy * w), w);                    // 0.0
/*136 */         } else {                                                                  // 0.0
/*138 */             qemu_pixman_linebuf_fill(linebuf, vs->vd->server, w, dy);             // 0.0
/*140 */         }                                                                         // 0.0
/*142 */         png_write_row(png_ptr, buf);                                              // 0.0
/*144 */     }                                                                             // 0.0
/*146 */     qemu_pixman_image_unref(linebuf);                                             // 0.0
/*150 */     png_write_end(png_ptr, NULL);                                                 // 0.0
/*154 */     if (color_type == PNG_COLOR_TYPE_PALETTE) {                                   // 0.0
/*156 */         png_free(png_ptr, png_palette);                                           // 0.0
/*158 */     }                                                                             // 0.0
/*162 */     png_destroy_write_struct(&png_ptr, &info_ptr);                                // 0.0
/*166 */     vnc_write_u8(vs, VNC_TIGHT_PNG << 4);                                         // 0.0
/*170 */     tight_send_compact_size(vs, vs->tight.png.offset);                            // 0.0
/*172 */     vnc_write(vs, vs->tight.png.buffer, vs->tight.png.offset);                    // 0.0
/*174 */     buffer_reset(&vs->tight.png);                                                 // 0.0
/*176 */     return 1;                                                                     // 0.0
/*178 */ }                                                                                 // 0.0

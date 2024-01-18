// commit message qemu@94ef4f337f (target=1, prob=0.66972303, correct=True): vga: add sr_vbe register set
/*0   */ static void vga_draw_text(VGACommonState *s, int full_update)                   // (7) 0.04297
/*2   */ {                                                                               // (25) 0.00196
/*4   */     DisplaySurface *surface = qemu_console_surface(s->con);                     // (8) 0.04101
/*6   */     int cx, cy, cheight, cw, ch, cattr, height, width, ch_attr;                 // (3) 0.05273
/*8   */     int cx_min, cx_max, linesize, x_incr, line, line1;                          // (5) 0.04883
/*10  */     uint32_t offset, fgcol, bgcol, v, cursor_offset;                            // (6) 0.04492
/*12  */     uint8_t *d1, *d, *src, *dest, *cursor_ptr;                                  // (4) 0.05078
/*14  */     const uint8_t *font_ptr, *font_base[2];                                     // (10) 0.03906
/*16  */     int dup9, line_offset;                                                      // (21) 0.02148
/*18  */     uint32_t *palette;                                                          // (22) 0.02148
/*20  */     uint32_t *ch_attr_ptr;                                                      // (18) 0.02734
/*22  */     int64_t now = qemu_clock_get_ms(QEMU_CLOCK_VIRTUAL);                        // (2) 0.05859
/*26  */     /* compute font data address (in plane 2) */                                // (17) 0.02734
/*28  */     v = s->sr[VGA_SEQ_CHARACTER_MAP];                                           // (9) 0.04101
/*30  */     offset = (((v >> 4) & 1) | ((v << 1) & 6)) * 8192 * 4 + 2;                  // (1) 0.06054
/*32  */     if (offset != s->font_offsets[0]) {                                         // (15) 0.0332
/*34  */         s->font_offsets[0] = offset;                                            // (14) 0.03711
/*36  */         full_update = 1;                                                        // (20) 0.02539
/*38  */     }                                                                           // (24) 0.007812
/*40  */     font_base[0] = s->vram_ptr + offset;                                        // (11) 0.03711
/*44  */     offset = (((v >> 5) & 1) | ((v >> 1) & 6)) * 8192 * 4 + 2;                  // (0) 0.06055
/*46  */     font_base[1] = s->vram_ptr + offset;                                        // (12) 0.03711
/*48  */     if (offset != s->font_offsets[1]) {                                         // (16) 0.0332
/*50  */         s->font_offsets[1] = offset;                                            // (13) 0.03711
/*52  */         full_update = 1;                                                        // (19) 0.02539
/*54  */     }                                                                           // (23) 0.007812
/*56  */     if (s->plane_updated & (1 << 2) || s->has_chain4_alias) {                   // 0.0
/*58  */         /* if the plane 2 was modified since the last display, it               // 0.0
/*60  */            indicates the font may have been modified */                         // 0.0
/*62  */         s->plane_updated = 0;                                                   // 0.0
/*64  */         full_update = 1;                                                        // 0.0
/*66  */     }                                                                           // 0.0
/*68  */     full_update |= update_basic_params(s);                                      // 0.0
/*72  */     line_offset = s->line_offset;                                               // 0.0
/*76  */     vga_get_text_resolution(s, &width, &height, &cw, &cheight);                 // 0.0
/*78  */     if ((height * width) <= 1) {                                                // 0.0
/*80  */         /* better than nothing: exit if transient size is too small */          // 0.0
/*82  */         return;                                                                 // 0.0
/*84  */     }                                                                           // 0.0
/*86  */     if ((height * width) > CH_ATTR_SIZE) {                                      // 0.0
/*88  */         /* better than nothing: exit if transient size is too big */            // 0.0
/*90  */         return;                                                                 // 0.0
/*92  */     }                                                                           // 0.0
/*96  */     if (width != s->last_width || height != s->last_height ||                   // 0.0
/*98  */         cw != s->last_cw || cheight != s->last_ch || s->last_depth) {           // 0.0
/*100 */         s->last_scr_width = width * cw;                                         // 0.0
/*102 */         s->last_scr_height = height * cheight;                                  // 0.0
/*104 */         qemu_console_resize(s->con, s->last_scr_width, s->last_scr_height);     // 0.0
/*106 */         surface = qemu_console_surface(s->con);                                 // 0.0
/*108 */         dpy_text_resize(s->con, width, height);                                 // 0.0
/*110 */         s->last_depth = 0;                                                      // 0.0
/*112 */         s->last_width = width;                                                  // 0.0
/*114 */         s->last_height = height;                                                // 0.0
/*116 */         s->last_ch = cheight;                                                   // 0.0
/*118 */         s->last_cw = cw;                                                        // 0.0
/*120 */         full_update = 1;                                                        // 0.0
/*122 */     }                                                                           // 0.0
/*124 */     full_update |= update_palette16(s);                                         // 0.0
/*126 */     palette = s->last_palette;                                                  // 0.0
/*128 */     x_incr = cw * surface_bytes_per_pixel(surface);                             // 0.0
/*132 */     if (full_update) {                                                          // 0.0
/*134 */         s->full_update_text = 1;                                                // 0.0
/*136 */     }                                                                           // 0.0
/*138 */     if (s->full_update_gfx) {                                                   // 0.0
/*140 */         s->full_update_gfx = 0;                                                 // 0.0
/*142 */         full_update |= 1;                                                       // 0.0
/*144 */     }                                                                           // 0.0
/*148 */     cursor_offset = ((s->cr[VGA_CRTC_CURSOR_HI] << 8) |                         // 0.0
/*150 */                      s->cr[VGA_CRTC_CURSOR_LO]) - s->start_addr;                // 0.0
/*152 */     if (cursor_offset != s->cursor_offset ||                                    // 0.0
/*154 */         s->cr[VGA_CRTC_CURSOR_START] != s->cursor_start ||                      // 0.0
/*156 */         s->cr[VGA_CRTC_CURSOR_END] != s->cursor_end) {                          // 0.0
/*158 */       /* if the cursor position changed, we update the old and new              // 0.0
/*160 */          chars */                                                               // 0.0
/*162 */         if (s->cursor_offset < CH_ATTR_SIZE)                                    // 0.0
/*164 */             s->last_ch_attr[s->cursor_offset] = -1;                             // 0.0
/*166 */         if (cursor_offset < CH_ATTR_SIZE)                                       // 0.0
/*168 */             s->last_ch_attr[cursor_offset] = -1;                                // 0.0
/*170 */         s->cursor_offset = cursor_offset;                                       // 0.0
/*172 */         s->cursor_start = s->cr[VGA_CRTC_CURSOR_START];                         // 0.0
/*174 */         s->cursor_end = s->cr[VGA_CRTC_CURSOR_END];                             // 0.0
/*176 */     }                                                                           // 0.0
/*178 */     cursor_ptr = s->vram_ptr + (s->start_addr + cursor_offset) * 4;             // 0.0
/*180 */     if (now >= s->cursor_blink_time) {                                          // 0.0
/*182 */         s->cursor_blink_time = now + VGA_TEXT_CURSOR_PERIOD_MS / 2;             // 0.0
/*184 */         s->cursor_visible_phase = !s->cursor_visible_phase;                     // 0.0
/*186 */     }                                                                           // 0.0
/*190 */     dest = surface_data(surface);                                               // 0.0
/*192 */     linesize = surface_stride(surface);                                         // 0.0
/*194 */     ch_attr_ptr = s->last_ch_attr;                                              // 0.0
/*196 */     line = 0;                                                                   // 0.0
/*198 */     offset = s->start_addr * 4;                                                 // 0.0
/*200 */     for(cy = 0; cy < height; cy++) {                                            // 0.0
/*202 */         d1 = dest;                                                              // 0.0
/*204 */         src = s->vram_ptr + offset;                                             // 0.0
/*206 */         cx_min = width;                                                         // 0.0
/*208 */         cx_max = -1;                                                            // 0.0
/*210 */         for(cx = 0; cx < width; cx++) {                                         // 0.0
/*212 */             ch_attr = *(uint16_t *)src;                                         // 0.0
/*214 */             if (full_update || ch_attr != *ch_attr_ptr || src == cursor_ptr) {  // 0.0
/*216 */                 if (cx < cx_min)                                                // 0.0
/*218 */                     cx_min = cx;                                                // 0.0
/*220 */                 if (cx > cx_max)                                                // 0.0
/*222 */                     cx_max = cx;                                                // 0.0
/*224 */                 *ch_attr_ptr = ch_attr;                                         // 0.0
/*226 */ #ifdef HOST_WORDS_BIGENDIAN                                                     // 0.0
/*228 */                 ch = ch_attr >> 8;                                              // 0.0
/*230 */                 cattr = ch_attr & 0xff;                                         // 0.0
/*232 */ #else                                                                           // 0.0
/*234 */                 ch = ch_attr & 0xff;                                            // 0.0
/*236 */                 cattr = ch_attr >> 8;                                           // 0.0
/*238 */ #endif                                                                          // 0.0
/*240 */                 font_ptr = font_base[(cattr >> 3) & 1];                         // 0.0
/*242 */                 font_ptr += 32 * 4 * ch;                                        // 0.0
/*244 */                 bgcol = palette[cattr >> 4];                                    // 0.0
/*246 */                 fgcol = palette[cattr & 0x0f];                                  // 0.0
/*248 */                 if (cw == 16) {                                                 // 0.0
/*250 */                     vga_draw_glyph16(d1, linesize,                              // 0.0
/*252 */                                      font_ptr, cheight, fgcol, bgcol);          // 0.0
/*254 */                 } else if (cw != 9) {                                           // 0.0
/*256 */                     vga_draw_glyph8(d1, linesize,                               // 0.0
/*258 */                                     font_ptr, cheight, fgcol, bgcol);           // 0.0
/*260 */                 } else {                                                        // 0.0
/*262 */                     dup9 = 0;                                                   // 0.0
/*264 */                     if (ch >= 0xb0 && ch <= 0xdf &&                             // 0.0
/*266 */                         (s->ar[VGA_ATC_MODE] & 0x04)) {                         // 0.0
/*268 */                         dup9 = 1;                                               // 0.0
/*270 */                     }                                                           // 0.0
/*272 */                     vga_draw_glyph9(d1, linesize,                               // 0.0
/*274 */                                     font_ptr, cheight, fgcol, bgcol, dup9);     // 0.0
/*276 */                 }                                                               // 0.0
/*278 */                 if (src == cursor_ptr &&                                        // 0.0
/*280 */                     !(s->cr[VGA_CRTC_CURSOR_START] & 0x20) &&                   // 0.0
/*282 */                     s->cursor_visible_phase) {                                  // 0.0
/*284 */                     int line_start, line_last, h;                               // 0.0
/*286 */                     /* draw the cursor */                                       // 0.0
/*288 */                     line_start = s->cr[VGA_CRTC_CURSOR_START] & 0x1f;           // 0.0
/*290 */                     line_last = s->cr[VGA_CRTC_CURSOR_END] & 0x1f;              // 0.0
/*292 */                     /* XXX: check that */                                       // 0.0
/*294 */                     if (line_last > cheight - 1)                                // 0.0
/*296 */                         line_last = cheight - 1;                                // 0.0
/*298 */                     if (line_last >= line_start && line_start < cheight) {      // 0.0
/*300 */                         h = line_last - line_start + 1;                         // 0.0
/*302 */                         d = d1 + linesize * line_start;                         // 0.0
/*304 */                         if (cw == 16) {                                         // 0.0
/*306 */                             vga_draw_glyph16(d, linesize,                       // 0.0
/*308 */                                              cursor_glyph, h, fgcol, bgcol);    // 0.0
/*310 */                         } else if (cw != 9) {                                   // 0.0
/*312 */                             vga_draw_glyph8(d, linesize,                        // 0.0
/*314 */                                             cursor_glyph, h, fgcol, bgcol);     // 0.0
/*316 */                         } else {                                                // 0.0
/*318 */                             vga_draw_glyph9(d, linesize,                        // 0.0
/*320 */                                             cursor_glyph, h, fgcol, bgcol, 1);  // 0.0
/*322 */                         }                                                       // 0.0
/*324 */                     }                                                           // 0.0
/*326 */                 }                                                               // 0.0
/*328 */             }                                                                   // 0.0
/*330 */             d1 += x_incr;                                                       // 0.0
/*332 */             src += 4;                                                           // 0.0
/*334 */             ch_attr_ptr++;                                                      // 0.0
/*336 */         }                                                                       // 0.0
/*338 */         if (cx_max != -1) {                                                     // 0.0
/*340 */             dpy_gfx_update(s->con, cx_min * cw, cy * cheight,                   // 0.0
/*342 */                            (cx_max - cx_min + 1) * cw, cheight);                // 0.0
/*344 */         }                                                                       // 0.0
/*346 */         dest += linesize * cheight;                                             // 0.0
/*348 */         line1 = line + cheight;                                                 // 0.0
/*350 */         offset += line_offset;                                                  // 0.0
/*352 */         if (line < s->line_compare && line1 >= s->line_compare) {               // 0.0
/*354 */             offset = 0;                                                         // 0.0
/*356 */         }                                                                       // 0.0
/*358 */         line = line1;                                                           // 0.0
/*360 */     }                                                                           // 0.0
/*362 */ }                                                                               // 0.0

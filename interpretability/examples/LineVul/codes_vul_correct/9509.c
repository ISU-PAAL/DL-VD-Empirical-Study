// commit message qemu@e369709222 (target=1, prob=0.6045075, correct=True): Fix vga on PPC
/*0   */ static void vga_draw_graphic(VGAState *s, int full_update)                                                // (4) 0.04102
/*2   */ {                                                                                                         // (29) 0.001953
/*4   */     int y1, y, update, page_min, page_max, linesize, y_start, double_scan, mask, depth;                   // (1) 0.06641
/*6   */     int width, height, shift_control, line_offset, page0, page1, bwidth, bits;                            // (2) 0.05273
/*8   */     int disp_width, multi_scan, multi_run;                                                                // (13) 0.03125
/*10  */     uint8_t *d;                                                                                           // (23) 0.01953
/*12  */     uint32_t v, addr1, addr;                                                                              // (18) 0.02734
/*14  */     vga_draw_line_func *vga_draw_line;                                                                    // (5) 0.03711
/*18  */     full_update |= update_basic_params(s);                                                                // (14) 0.03125
/*22  */     if (!full_update)                                                                                     // (25) 0.01758
/*24  */         vga_sync_dirty_bitmap(s);                                                                         // (6) 0.03711
/*28  */     s->get_resolution(s, &width, &height);                                                                // (10) 0.0332
/*30  */     disp_width = width;                                                                                   // (24) 0.01758
/*34  */     shift_control = (s->gr[0x05] >> 5) & 3;                                                               // (3) 0.04297
/*36  */     double_scan = (s->cr[0x09] >> 7);                                                                     // (7) 0.03711
/*38  */     if (shift_control != 1) {                                                                             // (21) 0.02344
/*40  */         multi_scan = (((s->cr[0x09] & 0x1f) + 1) << double_scan) - 1;                                     // (0) 0.07422
/*42  */     } else {                                                                                              // (26) 0.01172
/*44  */         /* in CGA modes, multi_scan is ignored */                                                         // (8) 0.03711
/*46  */         /* XXX: is it correct ? */                                                                        // (17) 0.0293
/*48  */         multi_scan = double_scan;                                                                         // (16) 0.0293
/*50  */     }                                                                                                     // (28) 0.007812
/*52  */     multi_run = multi_scan;                                                                               // (22) 0.02148
/*54  */     if (shift_control != s->shift_control ||                                                              // (15) 0.0293
/*56  */         double_scan != s->double_scan) {                                                                  // (9) 0.03516
/*58  */         full_update = 1;                                                                                  // (19) 0.02539
/*60  */         s->shift_control = shift_control;                                                                 // (12) 0.0332
/*62  */         s->double_scan = double_scan;                                                                     // (11) 0.0332
/*64  */     }                                                                                                     // (27) 0.007812
/*68  */     if (shift_control == 0) {                                                                             // (20) 0.02344
/*70  */         full_update |= update_palette16(s);                                                               // 0.0
/*72  */         if (s->sr[0x01] & 8) {                                                                            // 0.0
/*74  */             v = VGA_DRAW_LINE4D2;                                                                         // 0.0
/*76  */             disp_width <<= 1;                                                                             // 0.0
/*78  */         } else {                                                                                          // 0.0
/*80  */             v = VGA_DRAW_LINE4;                                                                           // 0.0
/*82  */         }                                                                                                 // 0.0
/*84  */         bits = 4;                                                                                         // 0.0
/*86  */     } else if (shift_control == 1) {                                                                      // 0.0
/*88  */         full_update |= update_palette16(s);                                                               // 0.0
/*90  */         if (s->sr[0x01] & 8) {                                                                            // 0.0
/*92  */             v = VGA_DRAW_LINE2D2;                                                                         // 0.0
/*94  */             disp_width <<= 1;                                                                             // 0.0
/*96  */         } else {                                                                                          // 0.0
/*98  */             v = VGA_DRAW_LINE2;                                                                           // 0.0
/*100 */         }                                                                                                 // 0.0
/*102 */         bits = 4;                                                                                         // 0.0
/*104 */     } else {                                                                                              // 0.0
/*106 */         switch(s->get_bpp(s)) {                                                                           // 0.0
/*108 */         default:                                                                                          // 0.0
/*110 */         case 0:                                                                                           // 0.0
/*112 */             full_update |= update_palette256(s);                                                          // 0.0
/*114 */             v = VGA_DRAW_LINE8D2;                                                                         // 0.0
/*116 */             bits = 4;                                                                                     // 0.0
/*118 */             break;                                                                                        // 0.0
/*120 */         case 8:                                                                                           // 0.0
/*122 */             full_update |= update_palette256(s);                                                          // 0.0
/*124 */             v = VGA_DRAW_LINE8;                                                                           // 0.0
/*126 */             bits = 8;                                                                                     // 0.0
/*128 */             break;                                                                                        // 0.0
/*130 */         case 15:                                                                                          // 0.0
/*132 */             v = VGA_DRAW_LINE15;                                                                          // 0.0
/*134 */             bits = 16;                                                                                    // 0.0
/*136 */             break;                                                                                        // 0.0
/*138 */         case 16:                                                                                          // 0.0
/*140 */             v = VGA_DRAW_LINE16;                                                                          // 0.0
/*142 */             bits = 16;                                                                                    // 0.0
/*144 */             break;                                                                                        // 0.0
/*146 */         case 24:                                                                                          // 0.0
/*148 */             v = VGA_DRAW_LINE24;                                                                          // 0.0
/*150 */             bits = 24;                                                                                    // 0.0
/*152 */             break;                                                                                        // 0.0
/*154 */         case 32:                                                                                          // 0.0
/*156 */             v = VGA_DRAW_LINE32;                                                                          // 0.0
/*158 */             bits = 32;                                                                                    // 0.0
/*160 */             break;                                                                                        // 0.0
/*162 */         }                                                                                                 // 0.0
/*164 */     }                                                                                                     // 0.0
/*166 */     vga_draw_line = vga_draw_line_table[v * NB_DEPTHS + get_depth_index(s->ds)];                          // 0.0
/*170 */     depth = s->get_bpp(s);                                                                                // 0.0
/*172 */     if (s->line_offset != s->last_line_offset ||                                                          // 0.0
/*174 */         disp_width != s->last_width ||                                                                    // 0.0
/*176 */         height != s->last_height ||                                                                       // 0.0
/*178 */         s->last_depth != depth) {                                                                         // 0.0
/*180 */         if (depth == 16 || depth == 32) {                                                                 // 0.0
/*182 */             if (is_graphic_console()) {                                                                   // 0.0
/*184 */                 qemu_free_displaysurface(s->ds->surface);                                                 // 0.0
/*186 */                 s->ds->surface = qemu_create_displaysurface_from(disp_width, height, depth,               // 0.0
/*188 */                                                                s->line_offset,                            // 0.0
/*190 */                                                                s->vram_ptr + (s->start_addr * 4));        // 0.0
/*192 */                 dpy_resize(s->ds);                                                                        // 0.0
/*194 */             } else {                                                                                      // 0.0
/*196 */                 qemu_console_resize(s->ds, disp_width, height);                                           // 0.0
/*198 */             }                                                                                             // 0.0
/*200 */         } else {                                                                                          // 0.0
/*202 */             qemu_console_resize(s->ds, disp_width, height);                                               // 0.0
/*204 */         }                                                                                                 // 0.0
/*206 */         s->last_scr_width = disp_width;                                                                   // 0.0
/*208 */         s->last_scr_height = height;                                                                      // 0.0
/*210 */         s->last_width = disp_width;                                                                       // 0.0
/*212 */         s->last_height = height;                                                                          // 0.0
/*214 */         s->last_line_offset = s->line_offset;                                                             // 0.0
/*216 */         s->last_depth = depth;                                                                            // 0.0
/*218 */         full_update = 1;                                                                                  // 0.0
/*220 */     } else if (is_graphic_console() && is_buffer_shared(s->ds->surface) &&                                // 0.0
/*222 */                (full_update || s->ds->surface->data != s->vram_ptr + (s->start_addr * 4))) {              // 0.0
/*224 */         s->ds->surface->data = s->vram_ptr + (s->start_addr * 4);                                         // 0.0
/*226 */         dpy_setdata(s->ds);                                                                               // 0.0
/*228 */     }                                                                                                     // 0.0
/*232 */     s->rgb_to_pixel =                                                                                     // 0.0
/*234 */         rgb_to_pixel_dup_table[get_depth_index(s->ds)];                                                   // 0.0
/*238 */     if (!is_buffer_shared(s->ds->surface) && s->cursor_invalidate)                                        // 0.0
/*240 */         s->cursor_invalidate(s);                                                                          // 0.0
/*244 */     line_offset = s->line_offset;                                                                         // 0.0
/*246 */ #if 0                                                                                                     // 0.0
/*248 */     printf("w=%d h=%d v=%d line_offset=%d cr[0x09]=0x%02x cr[0x17]=0x%02x linecmp=%d sr[0x01]=0x%02x\n",  // 0.0
/*250 */            width, height, v, line_offset, s->cr[9], s->cr[0x17], s->line_compare, s->sr[0x01]);           // 0.0
/*252 */ #endif                                                                                                    // 0.0
/*254 */     addr1 = (s->start_addr * 4);                                                                          // 0.0
/*256 */     bwidth = (width * bits + 7) / 8;                                                                      // 0.0
/*258 */     y_start = -1;                                                                                         // 0.0
/*260 */     page_min = 0x7fffffff;                                                                                // 0.0
/*262 */     page_max = -1;                                                                                        // 0.0
/*264 */     d = ds_get_data(s->ds);                                                                               // 0.0
/*266 */     linesize = ds_get_linesize(s->ds);                                                                    // 0.0
/*268 */     y1 = 0;                                                                                               // 0.0
/*270 */     for(y = 0; y < height; y++) {                                                                         // 0.0
/*272 */         addr = addr1;                                                                                     // 0.0
/*274 */         if (!(s->cr[0x17] & 1)) {                                                                         // 0.0
/*276 */             int shift;                                                                                    // 0.0
/*278 */             /* CGA compatibility handling */                                                              // 0.0
/*280 */             shift = 14 + ((s->cr[0x17] >> 6) & 1);                                                        // 0.0
/*282 */             addr = (addr & ~(1 << shift)) | ((y1 & 1) << shift);                                          // 0.0
/*284 */         }                                                                                                 // 0.0
/*286 */         if (!(s->cr[0x17] & 2)) {                                                                         // 0.0
/*288 */             addr = (addr & ~0x8000) | ((y1 & 2) << 14);                                                   // 0.0
/*290 */         }                                                                                                 // 0.0
/*292 */         page0 = s->vram_offset + (addr & TARGET_PAGE_MASK);                                               // 0.0
/*294 */         page1 = s->vram_offset + ((addr + bwidth - 1) & TARGET_PAGE_MASK);                                // 0.0
/*296 */         update = full_update |                                                                            // 0.0
/*298 */             cpu_physical_memory_get_dirty(page0, VGA_DIRTY_FLAG) |                                        // 0.0
/*300 */             cpu_physical_memory_get_dirty(page1, VGA_DIRTY_FLAG);                                         // 0.0
/*302 */         if ((page1 - page0) > TARGET_PAGE_SIZE) {                                                         // 0.0
/*304 */             /* if wide line, can use another page */                                                      // 0.0
/*306 */             update |= cpu_physical_memory_get_dirty(page0 + TARGET_PAGE_SIZE,                             // 0.0
/*308 */                                                     VGA_DIRTY_FLAG);                                      // 0.0
/*310 */         }                                                                                                 // 0.0
/*312 */         /* explicit invalidation for the hardware cursor */                                               // 0.0
/*314 */         update |= (s->invalidated_y_table[y >> 5] >> (y & 0x1f)) & 1;                                     // 0.0
/*316 */         if (update) {                                                                                     // 0.0
/*318 */             if (y_start < 0)                                                                              // 0.0
/*320 */                 y_start = y;                                                                              // 0.0
/*322 */             if (page0 < page_min)                                                                         // 0.0
/*324 */                 page_min = page0;                                                                         // 0.0
/*326 */             if (page1 > page_max)                                                                         // 0.0
/*328 */                 page_max = page1;                                                                         // 0.0
/*330 */             if (!(is_buffer_shared(s->ds->surface))) {                                                    // 0.0
/*332 */                 vga_draw_line(s, d, s->vram_ptr + addr, width);                                           // 0.0
/*334 */                 if (s->cursor_draw_line)                                                                  // 0.0
/*336 */                     s->cursor_draw_line(s, d, y);                                                         // 0.0
/*338 */             }                                                                                             // 0.0
/*340 */         } else {                                                                                          // 0.0
/*342 */             if (y_start >= 0) {                                                                           // 0.0
/*344 */                 /* flush to display */                                                                    // 0.0
/*346 */                 dpy_update(s->ds, 0, y_start,                                                             // 0.0
/*348 */                            disp_width, y - y_start);                                                      // 0.0
/*350 */                 y_start = -1;                                                                             // 0.0
/*352 */             }                                                                                             // 0.0
/*354 */         }                                                                                                 // 0.0
/*356 */         if (!multi_run) {                                                                                 // 0.0
/*358 */             mask = (s->cr[0x17] & 3) ^ 3;                                                                 // 0.0
/*360 */             if ((y1 & mask) == mask)                                                                      // 0.0
/*362 */                 addr1 += line_offset;                                                                     // 0.0
/*364 */             y1++;                                                                                         // 0.0
/*366 */             multi_run = multi_scan;                                                                       // 0.0
/*368 */         } else {                                                                                          // 0.0
/*370 */             multi_run--;                                                                                  // 0.0
/*372 */         }                                                                                                 // 0.0
/*374 */         /* line compare acts on the displayed lines */                                                    // 0.0
/*376 */         if (y == s->line_compare)                                                                         // 0.0
/*378 */             addr1 = 0;                                                                                    // 0.0
/*380 */         d += linesize;                                                                                    // 0.0
/*382 */     }                                                                                                     // 0.0
/*384 */     if (y_start >= 0) {                                                                                   // 0.0
/*386 */         /* flush to display */                                                                            // 0.0
/*388 */         dpy_update(s->ds, 0, y_start,                                                                     // 0.0
/*390 */                    disp_width, y - y_start);                                                              // 0.0
/*392 */     }                                                                                                     // 0.0
/*394 */     /* reset modified pages */                                                                            // 0.0
/*396 */     if (page_max != -1) {                                                                                 // 0.0
/*398 */         cpu_physical_memory_reset_dirty(page_min, page_max + TARGET_PAGE_SIZE,                            // 0.0
/*400 */                                         VGA_DIRTY_FLAG);                                                  // 0.0
/*402 */     }                                                                                                     // 0.0
/*404 */     memset(s->invalidated_y_table, 0, ((height + 31) >> 5) * 4);                                          // 0.0
/*406 */ }                                                                                                         // 0.0

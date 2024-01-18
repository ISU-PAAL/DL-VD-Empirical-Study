// commit message qemu@0d7937974c (target=0, prob=0.62734795, correct=False): vmware_vga: Coding style cleanup
/*0  */ static inline void vmsvga_cursor_define(struct vmsvga_state_s *s,         // (8) 0.04883
/*2  */                 struct vmsvga_cursor_definition_s *c)                     // (5) 0.05859
/*4  */ {                                                                         // (29) 0.001953
/*6  */     QEMUCursor *qc;                                                       // (16) 0.02148
/*8  */     int i, pixels;                                                        // (20) 0.01563
/*12 */     qc = cursor_alloc(c->width, c->height);                               // (11) 0.03516
/*14 */     qc->hot_x = c->hot_x;                                                 // (13) 0.03125
/*16 */     qc->hot_y = c->hot_y;                                                 // (14) 0.03125
/*18 */     switch (c->bpp) {                                                     // (17) 0.02148
/*20 */     case 1:                                                               // (23) 0.01172
/*22 */         cursor_set_mono(qc, 0xffffff, 0x000000, (void*)c->image,          // (0) 0.06445
/*24 */                         1, (void*)c->mask);                               // (2) 0.0625
/*26 */ #ifdef DEBUG                                                              // (26) 0.007812
/*28 */         cursor_print_ascii_art(qc, "vmware/mono");                        // (7) 0.05273
/*30 */ #endif                                                                    // (28) 0.003906
/*32 */         break;                                                            // (18) 0.01758
/*34 */     case 32:                                                              // (22) 0.01172
/*36 */         /* fill alpha channel from mask, set color to zero */             // (10) 0.03711
/*38 */         cursor_set_mono(qc, 0x000000, 0x000000, (void*)c->mask,           // (1) 0.0625
/*40 */                         1, (void*)c->mask);                               // (3) 0.0625
/*42 */         /* add in rgb values */                                           // (15) 0.02539
/*44 */         pixels = c->width * c->height;                                    // (12) 0.0332
/*46 */         for (i = 0; i < pixels; i++) {                                    // (9) 0.03906
/*48 */             qc->data[i] |= c->image[i] & 0xffffff;                        // (4) 0.0625
/*50 */         }                                                                 // (21) 0.01563
/*52 */ #ifdef DEBUG                                                              // (25) 0.007813
/*54 */         cursor_print_ascii_art(qc, "vmware/32bit");                       // (6) 0.05273
/*56 */ #endif                                                                    // (27) 0.003906
/*58 */         break;                                                            // (19) 0.01758
/*60 */     default:                                                              // (24) 0.009766
/*62 */         fprintf(stderr, "%s: unhandled bpp %d, using fallback cursor\n",  // 0.0
/*64 */                 __FUNCTION__, c->bpp);                                    // 0.0
/*66 */         cursor_put(qc);                                                   // 0.0
/*68 */         qc = cursor_builtin_left_ptr();                                   // 0.0
/*70 */     }                                                                     // 0.0
/*74 */     dpy_cursor_define(s->vga.ds, qc);                                     // 0.0
/*76 */     cursor_put(qc);                                                       // 0.0
/*78 */ }                                                                         // 0.0

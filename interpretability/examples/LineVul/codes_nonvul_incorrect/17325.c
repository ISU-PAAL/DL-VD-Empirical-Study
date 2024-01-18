// commit message qemu@026aeffcb4 (target=0, prob=0.7024945, correct=False): cirrus: stop passing around dst pointers in the blitter
/*0   */ static int cirrus_do_copy(CirrusVGAState *s, int dst, int src, int w, int h)  // (3) 0.05859
/*2   */ {                                                                             // (24) 0.001953
/*4   */     int sx = 0, sy = 0;                                                       // (14) 0.02539
/*6   */     int dx = 0, dy = 0;                                                       // (16) 0.02344
/*8   */     int depth = 0;                                                            // (22) 0.01562
/*10  */     int notify = 0;                                                           // (21) 0.01563
/*14  */     /* make sure to only copy if it's a plain copy ROP */                     // (11) 0.03516
/*16  */     if (*s->cirrus_rop == cirrus_bitblt_rop_fwd_src ||                        // (5) 0.05273
/*18  */         *s->cirrus_rop == cirrus_bitblt_rop_bkwd_src) {                       // (0) 0.0625
/*22  */         int width, height;                                                    // (17) 0.02344
/*26  */         depth = s->vga.get_bpp(&s->vga) / 8;                                  // (8) 0.05273
/*28  */         if (!depth) {                                                         // (18) 0.02344
/*30  */             return 0;                                                         // (12) 0.02734
/*32  */         }                                                                     // (23) 0.01562
/*34  */         s->vga.get_resolution(&s->vga, &width, &height);                      // (6) 0.05273
/*38  */         /* extra x, y */                                                      // (15) 0.02539
/*40  */         sx = (src % ABS(s->cirrus_blt_srcpitch)) / depth;                     // (2) 0.06055
/*42  */         sy = (src / ABS(s->cirrus_blt_srcpitch));                             // (7) 0.05273
/*44  */         dx = (dst % ABS(s->cirrus_blt_dstpitch)) / depth;                     // (1) 0.0625
/*46  */         dy = (dst / ABS(s->cirrus_blt_dstpitch));                             // (4) 0.05664
/*50  */         /* normalize width */                                                 // (19) 0.02344
/*52  */         w /= depth;                                                           // (20) 0.02344
/*56  */         /* if we're doing a backward copy, we have to adjust                  // (10) 0.03906
/*58  */            our x/y to be the upper left corner (instead of the lower          // (9) 0.04883
/*60  */            right corner) */                                                   // (13) 0.02734
/*62  */         if (s->cirrus_blt_dstpitch < 0) {                                     // 0.0
/*64  */             sx -= (s->cirrus_blt_width / depth) - 1;                          // 0.0
/*66  */             dx -= (s->cirrus_blt_width / depth) - 1;                          // 0.0
/*68  */             sy -= s->cirrus_blt_height - 1;                                   // 0.0
/*70  */             dy -= s->cirrus_blt_height - 1;                                   // 0.0
/*72  */         }                                                                     // 0.0
/*76  */         /* are we in the visible portion of memory? */                        // 0.0
/*78  */         if (sx >= 0 && sy >= 0 && dx >= 0 && dy >= 0 &&                       // 0.0
/*80  */             (sx + w) <= width && (sy + h) <= height &&                        // 0.0
/*82  */             (dx + w) <= width && (dy + h) <= height) {                        // 0.0
/*84  */             notify = 1;                                                       // 0.0
/*86  */         }                                                                     // 0.0
/*88  */     }                                                                         // 0.0
/*92  */     (*s->cirrus_rop) (s, s->vga.vram_ptr + s->cirrus_blt_dstaddr,             // 0.0
/*94  */                       s->vga.vram_ptr + s->cirrus_blt_srcaddr,                // 0.0
/*96  */ 		      s->cirrus_blt_dstpitch, s->cirrus_blt_srcpitch,                       // 0.0
/*98  */ 		      s->cirrus_blt_width, s->cirrus_blt_height);                           // 0.0
/*102 */     if (notify) {                                                             // 0.0
/*104 */         dpy_gfx_update(s->vga.con, dx, dy,                                    // 0.0
/*106 */                        s->cirrus_blt_width / depth,                           // 0.0
/*108 */                        s->cirrus_blt_height);                                 // 0.0
/*110 */     }                                                                         // 0.0
/*114 */     /* we don't have to notify the display that this portion has              // 0.0
/*116 */        changed since qemu_console_copy implies this */                        // 0.0
/*120 */     cirrus_invalidate_region(s, s->cirrus_blt_dstaddr,                        // 0.0
/*122 */ 				s->cirrus_blt_dstpitch, s->cirrus_blt_width,                              // 0.0
/*124 */ 				s->cirrus_blt_height);                                                    // 0.0
/*128 */     return 1;                                                                 // 0.0
/*130 */ }                                                                             // 0.0

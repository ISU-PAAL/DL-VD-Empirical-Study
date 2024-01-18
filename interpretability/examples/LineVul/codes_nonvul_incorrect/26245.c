// commit message qemu@245f7b51c0 (target=0, prob=0.67134583, correct=False): vnc: rename vnc-encoding-* vnc-enc-*
/*0  */ int vnc_hextile_send_framebuffer_update(VncState *vs, int x,               // (7) 0.05418
/*2  */                                         int y, int w, int h)               // (2) 0.1084
/*4  */ {                                                                          // (20) 0.002257
/*6  */     int i, j;                                                              // (16) 0.01806
/*8  */     int has_fg, has_bg;                                                    // (12) 0.02709
/*10 */     uint8_t *last_fg, *last_bg;                                            // (9) 0.03837
/*12 */     VncDisplay *vd = vs->vd;                                               // (10) 0.02935
/*16 */     last_fg = (uint8_t *) qemu_malloc(vd->server->pf.bytes_per_pixel);     // (4) 0.07449
/*18 */     last_bg = (uint8_t *) qemu_malloc(vd->server->pf.bytes_per_pixel);     // (3) 0.07449
/*20 */     has_fg = has_bg = 0;                                                   // (11) 0.02935
/*22 */     for (j = y; j < (y + h); j += 16) {                                    // (8) 0.0474
/*24 */         for (i = x; i < (x + w); i += 16) {                                // (6) 0.05643
/*26 */             vs->send_hextile_tile(vs, i, j,                                // (5) 0.06095
/*28 */                                   MIN(16, x + w - i), MIN(16, y + h - j),  // (0) 0.1196
/*30 */                                   last_bg, last_fg, &has_bg, &has_fg);     // (1) 0.1151
/*32 */         }                                                                  // (15) 0.01806
/*34 */     }                                                                      // (18) 0.009029
/*36 */     free(last_fg);                                                         // (14) 0.02032
/*38 */     free(last_bg);                                                         // (13) 0.02032
/*42 */     return 1;                                                              // (17) 0.01354
/*44 */ }                                                                          // (19) 0.002257

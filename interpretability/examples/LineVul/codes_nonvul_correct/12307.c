// commit message qemu@245f7b51c0 (target=0, prob=0.11330333, correct=True): vnc: rename vnc-encoding-* vnc-enc-*
/*0  */ static void find_best_solid_area(VncState *vs, int x, int y, int w, int h,  // (8) 0.05469
/*2  */                                  uint32_t color, int *w_ptr, int *h_ptr)    // (0) 0.09766
/*4  */ {                                                                           // (21) 0.001953
/*6  */     int dx, dy, dw, dh;                                                     // (15) 0.02344
/*8  */     int w_prev;                                                             // (19) 0.01562
/*10 */     int w_best = 0, h_best = 0;                                             // (11) 0.03125
/*14 */     w_prev = w;                                                             // (17) 0.01758
/*18 */     for (dy = y; dy < y + h; dy += VNC_TIGHT_MAX_SPLIT_TILE_SIZE) {         // (2) 0.06836
/*22 */         dh = MIN(VNC_TIGHT_MAX_SPLIT_TILE_SIZE, y + h - dy);                // (4) 0.06641
/*24 */         dw = MIN(VNC_TIGHT_MAX_SPLIT_TILE_SIZE, w_prev);                    // (5) 0.0625
/*28 */         if (!check_solid_tile(vs, x, dy, dw, dh, &color, true)) {           // (6) 0.06055
/*30 */             break;                                                          // (14) 0.02539
/*32 */         }                                                                   // (20) 0.01562
/*36 */         for (dx = x + dw; dx < x + w_prev;) {                               // (9) 0.04883
/*38 */             dw = MIN(VNC_TIGHT_MAX_SPLIT_TILE_SIZE, x + w_prev - dx);       // (1) 0.07812
/*42 */             if (!check_solid_tile(vs, dx, dy, dw, dh, &color, true)) {      // (3) 0.06836
/*44 */                 break;                                                      // (10) 0.0332
/*46 */             }                                                               // (16) 0.02344
/*48 */             dx += dw;                                                       // (12) 0.0293
/*50 */         }                                                                   // (18) 0.01563
/*54 */         w_prev = dx - x;                                                    // (13) 0.0293
/*56 */         if (w_prev * (dy + dh - y) > w_best * h_best) {                     // (7) 0.05859
/*58 */             w_best = w_prev;                                                // 0.0
/*60 */             h_best = dy + dh - y;                                           // 0.0
/*62 */         }                                                                   // 0.0
/*64 */     }                                                                       // 0.0
/*68 */     *w_ptr = w_best;                                                        // 0.0
/*70 */     *h_ptr = h_best;                                                        // 0.0
/*72 */ }                                                                           // 0.0

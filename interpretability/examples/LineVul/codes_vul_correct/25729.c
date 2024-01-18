// commit message FFmpeg@24947d4988 (target=1, prob=0.6357245, correct=True): vorbis: fix overflows in floor1[] vector and inverse db table index.
/*0  */ static void render_line(int x0, uint8_t y0, int x1, int y1, float *buf)  // (2) 0.06488
/*2  */ {                                                                        // (24) 0.002237
/*4  */     int dy  = y1 - y0;                                                   // (18) 0.02908
/*6  */     int adx = x1 - x0;                                                   // (19) 0.02908
/*8  */     int ady = FFABS(dy);                                                 // (17) 0.02908
/*10 */     int sy  = dy < 0 ? -1 : 1;                                           // (10) 0.03579
/*12 */     buf[x0] = ff_vorbis_floor1_inverse_db_table[y0];                     // (3) 0.0604
/*14 */     if (ady*2 <= adx) { // optimized common case                         // (8) 0.03803
/*16 */         render_line_unrolled(x0, y0, x1, sy, ady, adx, buf);             // (0) 0.07383
/*18 */     } else {                                                             // (22) 0.01342
/*20 */         int base  = dy / adx;                                            // (11) 0.03579
/*22 */         int x     = x0;                                                  // (9) 0.03803
/*24 */         uint8_t y = y0;                                                  // (12) 0.03579
/*26 */         int err   = -adx;                                                // (13) 0.03579
/*28 */         ady -= FFABS(base) * adx;                                        // (5) 0.04474
/*30 */         while (++x < x1) {                                               // (14) 0.03579
/*32 */             y += base;                                                   // (16) 0.03356
/*34 */             err += ady;                                                  // (15) 0.03579
/*36 */             if (err >= 0) {                                              // (7) 0.04027
/*38 */                 err -= adx;                                              // (6) 0.04474
/*40 */                 y   += sy;                                               // (4) 0.04698
/*42 */             }                                                            // (20) 0.02685
/*44 */             buf[x] = ff_vorbis_floor1_inverse_db_table[y];               // (1) 0.07383
/*46 */         }                                                                // (21) 0.0179
/*48 */     }                                                                    // (23) 0.008949
/*50 */ }                                                                        // (25) 0.002237

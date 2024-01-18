// commit message FFmpeg@5ad4335c22 (target=0, prob=0.76052636, correct=False): VP8: merge chroma MC calls
/*0  */ void vp8_mc(VP8Context *s, int luma,                                                                 // (14) 0.0332
/*2  */             uint8_t *dst, uint8_t *src, const VP56mv *mv,                                            // (5) 0.06836
/*4  */             int x_off, int y_off, int block_w, int block_h,                                          // (7) 0.06055
/*6  */             int width, int height, int linesize,                                                     // (12) 0.04102
/*8  */             vp8_mc_func mc_func[3][3])                                                               // (8) 0.05078
/*10 */ {                                                                                                    // (18) 0.001953
/*12 */     if (AV_RN32A(mv)) {                                                                              // (15) 0.0293
/*14 */         static const uint8_t idx[3][8] = {                                                           // (11) 0.04297
/*16 */             { 0, 1, 2, 1, 2, 1, 2, 1 }, // nr. of left extra pixels,                                 // (1) 0.07227
/*18 */                                         // also function pointer index                               // (0) 0.08594
/*20 */             { 0, 3, 5, 3, 5, 3, 5, 3 }, // nr. of extra pixels required                              // (3) 0.07031
/*22 */             { 0, 2, 3, 2, 3, 2, 3, 2 }, // nr. of right extra pixels                                 // (2) 0.07031
/*24 */         };                                                                                           // (17) 0.01562
/*26 */         int mx = (mv->x << luma)&7, mx_idx = idx[0][mx];                                             // (4) 0.07031
/*28 */         int my = (mv->y << luma)&7, my_idx = idx[0][my];                                             // (6) 0.06641
/*32 */         x_off += mv->x >> (3 - luma);                                                                // (10) 0.04297
/*34 */         y_off += mv->y >> (3 - luma);                                                                // (9) 0.04297
/*38 */         // edge emulation                                                                            // (16) 0.01953
/*40 */         src += y_off * linesize + x_off;                                                             // (13) 0.03906
/*42 */         if (x_off < mx_idx || x_off >= width  - block_w - idx[2][mx] ||                              // 0.0
/*44 */             y_off < my_idx || y_off >= height - block_h - idx[2][my]) {                              // 0.0
/*46 */             s->dsp.emulated_edge_mc(s->edge_emu_buffer, src - my_idx * linesize - mx_idx, linesize,  // 0.0
/*48 */                                 block_w + idx[1][mx], block_h + idx[1][my],                          // 0.0
/*50 */                                 x_off - mx_idx, y_off - my_idx, width, height);                      // 0.0
/*52 */             src = s->edge_emu_buffer + mx_idx + linesize * my_idx;                                   // 0.0
/*54 */         }                                                                                            // 0.0
/*56 */         mc_func[my_idx][mx_idx](dst, linesize, src, linesize, block_h, mx, my);                      // 0.0
/*58 */     } else                                                                                           // 0.0
/*60 */         mc_func[0][0](dst, linesize, src + y_off * linesize + x_off, linesize, block_h, 0, 0);       // 0.0
/*62 */ }                                                                                                    // 0.0

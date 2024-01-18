// commit message FFmpeg@c341f734e5 (target=1, prob=0.7708081, correct=True): Convert multiplier for MV from int to ptrdiff_t.
/*0  */ void vp8_mc_chroma(VP8Context *s, VP8ThreadData *td, uint8_t *dst1, uint8_t *dst2,                      // (2) 0.08008
/*2  */                    ThreadFrame *ref, const VP56mv *mv, int x_off, int y_off,                            // (1) 0.08203
/*4  */                    int block_w, int block_h, int width, int height, int linesize,                       // (5) 0.07422
/*6  */                    vp8_mc_func mc_func[3][3])                                                           // (7) 0.06445
/*8  */ {                                                                                                       // (16) 0.001953
/*10 */     uint8_t *src1 = ref->f->data[1], *src2 = ref->f->data[2];                                           // (9) 0.06055
/*14 */     if (AV_RN32A(mv)) {                                                                                 // (14) 0.0293
/*16 */         int mx = mv->x&7, mx_idx = subpel_idx[0][mx];                                                   // (6) 0.06641
/*18 */         int my = mv->y&7, my_idx = subpel_idx[0][my];                                                   // (8) 0.0625
/*22 */         x_off += mv->x >> 3;                                                                            // (13) 0.03516
/*24 */         y_off += mv->y >> 3;                                                                            // (12) 0.03516
/*28 */         // edge emulation                                                                               // (15) 0.01953
/*30 */         src1 += y_off * linesize + x_off;                                                               // (10) 0.04102
/*32 */         src2 += y_off * linesize + x_off;                                                               // (11) 0.04102
/*34 */         ff_thread_await_progress(ref, (3 + y_off + block_h + subpel_idx[2][my]) >> 3, 0);               // (0) 0.08594
/*36 */         if (x_off < mx_idx || x_off >= width  - block_w - subpel_idx[2][mx] ||                          // (3) 0.08008
/*38 */             y_off < my_idx || y_off >= height - block_h - subpel_idx[2][my]) {                          // (4) 0.08008
/*40 */             s->vdsp.emulated_edge_mc(td->edge_emu_buffer, src1 - my_idx * linesize - mx_idx, linesize,  // 0.0
/*42 */                                      block_w + subpel_idx[1][mx], block_h + subpel_idx[1][my],          // 0.0
/*44 */                                      x_off - mx_idx, y_off - my_idx, width, height);                    // 0.0
/*46 */             src1 = td->edge_emu_buffer + mx_idx + linesize * my_idx;                                    // 0.0
/*48 */             mc_func[my_idx][mx_idx](dst1, linesize, src1, linesize, block_h, mx, my);                   // 0.0
/*52 */             s->vdsp.emulated_edge_mc(td->edge_emu_buffer, src2 - my_idx * linesize - mx_idx, linesize,  // 0.0
/*54 */                                      block_w + subpel_idx[1][mx], block_h + subpel_idx[1][my],          // 0.0
/*56 */                                      x_off - mx_idx, y_off - my_idx, width, height);                    // 0.0
/*58 */             src2 = td->edge_emu_buffer + mx_idx + linesize * my_idx;                                    // 0.0
/*60 */             mc_func[my_idx][mx_idx](dst2, linesize, src2, linesize, block_h, mx, my);                   // 0.0
/*62 */         } else {                                                                                        // 0.0
/*64 */             mc_func[my_idx][mx_idx](dst1, linesize, src1, linesize, block_h, mx, my);                   // 0.0
/*66 */             mc_func[my_idx][mx_idx](dst2, linesize, src2, linesize, block_h, mx, my);                   // 0.0
/*68 */         }                                                                                               // 0.0
/*70 */     } else {                                                                                            // 0.0
/*72 */         ff_thread_await_progress(ref, (3 + y_off + block_h) >> 3, 0);                                   // 0.0
/*74 */         mc_func[0][0](dst1, linesize, src1 + y_off * linesize + x_off, linesize, block_h, 0, 0);        // 0.0
/*76 */         mc_func[0][0](dst2, linesize, src2 + y_off * linesize + x_off, linesize, block_h, 0, 0);        // 0.0
/*78 */     }                                                                                                   // 0.0
/*80 */ }                                                                                                       // 0.0

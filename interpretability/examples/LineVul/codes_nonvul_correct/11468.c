// commit message FFmpeg@5bca5f87d1 (target=0, prob=0.34752485, correct=True): Revert "x86/videodsp: add emulated_edge_mc_mmxext"
/*0  */ static av_noinline void emulated_edge_mc_sse(uint8_t *buf, const uint8_t *src,    // (7) 0.07809
/*2  */                                              ptrdiff_t buf_stride,                // (3) 0.1335
/*4  */                                              ptrdiff_t src_stride,                // (4) 0.1335
/*6  */                                              int block_w, int block_h,            // (1) 0.136
/*8  */                                              int src_x, int src_y, int w, int h)  // (0) 0.1511
/*10 */ {                                                                                 // (8) 0.002519
/*12 */     emulated_edge_mc(buf, src, buf_stride, src_stride, block_w, block_h,          // (6) 0.0806
/*14 */                      src_x, src_y, w, h, vfixtbl_sse, &ff_emu_edge_vvar_sse,      // (2) 0.136
/*16 */                      hfixtbl_mmxext, &ff_emu_edge_hvar_mmxext);                   // (5) 0.1108
/*18 */ }                                                                                 // (9) 0.002519

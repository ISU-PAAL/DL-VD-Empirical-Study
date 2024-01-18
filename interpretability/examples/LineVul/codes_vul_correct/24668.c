// commit message FFmpeg@e6bc38fd49 (target=1, prob=0.7330727, correct=True): wmv2: move IDCT to its own DSP context.
/*0 */ static void ff_wmv2_idct_put_c(uint8_t *dest, int line_size, DCTELEM *block)  // (0) 0.4217
/*2 */ {                                                                             // (3) 0.01205
/*4 */     ff_wmv2_idct_c(block);                                                    // (2) 0.1928
/*6 */     put_pixels_clamped_c(block, dest, line_size);                             // (1) 0.253
/*8 */ }                                                                             // (4) 0.01205

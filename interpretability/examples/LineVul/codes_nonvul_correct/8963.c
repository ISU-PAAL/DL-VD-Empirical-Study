// commit message FFmpeg@73bb8f61d4 (target=0, prob=0.017850878, correct=True): hevcdsp: remove an unneeded variable in the loop filter
/*0  */ static void FUNC(hevc_h_loop_filter_luma)(uint8_t *pix, ptrdiff_t stride,     // (3) 0.1409
/*2  */                                           int *beta, int *tc, uint8_t *no_p,  // (0) 0.2636
/*4  */                                           uint8_t *no_q)                      // (1) 0.2273
/*6  */ {                                                                             // (5) 0.004545
/*8  */     FUNC(hevc_loop_filter_luma)(pix, stride, sizeof(pixel),                   // (4) 0.1136
/*10 */                                 beta, tc, no_p, no_q);                        // (2) 0.1955
/*12 */ }                                                                             // (6) 0.004545

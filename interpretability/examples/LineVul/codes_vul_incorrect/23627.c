// commit message FFmpeg@3ab9a2a557 (target=1, prob=0.48722097, correct=False): rv34: change most "int stride" into "ptrdiff_t stride".
/*0  */ static void rv40_h_weak_loop_filter(uint8_t *src, const int stride,            // (6) 0.08333
/*2  */                                     const int filter_p1, const int filter_q1,  // (1) 0.1633
/*4  */                                     const int alpha, const int beta,           // (3) 0.1433
/*6  */                                     const int lim_p0q0, const int lim_q1,      // (0) 0.17
/*8  */                                     const int lim_p1)                          // (4) 0.14
/*10 */ {                                                                              // (7) 0.003333
/*12 */     rv40_weak_loop_filter(src, stride, 1, filter_p1, filter_q1,                // (5) 0.09667
/*14 */                           alpha, beta, lim_p0q0, lim_q1, lim_p1);              // (2) 0.1533
/*16 */ }                                                                              // (8) 0.003333

// commit message FFmpeg@b8664c9294 (target=0, prob=0.95640063, correct=False): avcodec/vp8dsp: add VP7 idct and loop filter
/*0  */ static void vp8_h_loop_filter_simple_c(uint8_t *dst, ptrdiff_t stride, int flim)  // (0) 0.2787
/*2  */ {                                                                                 // (5) 0.008197
/*4  */     int i;                                                                        // (4) 0.04918
/*8  */     for (i = 0; i < 16; i++)                                                      // (3) 0.123
/*10 */         if (simple_limit(dst+i*stride, 1, flim))                                  // (2) 0.2131
/*12 */             filter_common(dst+i*stride, 1, 1);                                    // (1) 0.2213
/*14 */ }                                                                                 // (6) 0.008197

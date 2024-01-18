// commit message FFmpeg@6e42e6c4b4 (target=1, prob=0.9258211, correct=True): cosmetics attack, part I: Remove all tabs and prettyprint/reindent the code.
/*0  */ static inline void RENAME(yuv422ptoyuy2)(const uint8_t *ysrc, const uint8_t *usrc, const uint8_t *vsrc, uint8_t *dst,  // (0) 0.3936
/*2  */ 	long width, long height,                                                                                              // (3) 0.05509
/*4  */ 	long lumStride, long chromStride, long dstStride)                                                                     // (2) 0.1259
/*6  */ {                                                                                                                      // (4) 0.007884
/*8  */ 	RENAME(yuvPlanartoyuy2)(ysrc, usrc, vsrc, dst, width, height, lumStride, chromStride, dstStride, 1);                  // (1) 0.3309
/*10 */ }                                                                                                                      // (5) 0.007873

// commit message FFmpeg@d1adad3cca (target=0, prob=0.15735774, correct=True): Merge swscale bloatup This will be cleaned up in the next merge
/*0  */ static inline void RENAME(yuv422ptoyuy2)(const uint8_t *ysrc, const uint8_t *usrc, const uint8_t *vsrc, uint8_t *dst,  // (1) 0.2415
/*2  */                                          long width, long height,                                                      // (2) 0.2222
/*4  */                                          long lumStride, long chromStride, long dstStride)                             // (0) 0.2657
/*6  */ {                                                                                                                      // (4) 0.004831
/*8  */     RENAME(yuvPlanartoyuy2)(ysrc, usrc, vsrc, dst, width, height, lumStride, chromStride, dstStride, 1);               // (3) 0.2126
/*10 */ }                                                                                                                      // (5) 0.004831

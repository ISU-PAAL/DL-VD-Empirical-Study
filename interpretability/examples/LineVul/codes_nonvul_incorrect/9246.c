// commit message FFmpeg@d1adad3cca (target=0, prob=0.91451555, correct=False): Merge swscale bloatup This will be cleaned up in the next merge
/*0  */ static inline void RENAME(nv21ToUV)(uint8_t *dstU, uint8_t *dstV,              // (2) 0.1818
/*2  */                                     const uint8_t *src1, const uint8_t *src2,  // (0) 0.3212
/*4  */                                     long width, uint32_t *unused)              // (1) 0.2788
/*6  */ {                                                                              // (4) 0.006061
/*8  */     RENAME(nvXXtoUV)(dstV, dstU, src1, width);                                 // (3) 0.1455
/*10 */ }                                                                              // (5) 0.006061

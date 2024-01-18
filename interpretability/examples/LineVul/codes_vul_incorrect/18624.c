// commit message FFmpeg@d1916d13e2 (target=1, prob=0.13984099, correct=False): dsputil/pngdsp: fix signed/unsigned type in end comparison
/*0  */ static void add_bytes_l2_c(uint8_t *dst, uint8_t *src1, uint8_t *src2, int w)  // (1) 0.1784
/*2  */ {                                                                              // (9) 0.004695
/*4  */     long i;                                                                    // (7) 0.02817
/*6  */     for (i = 0; i <= w - sizeof(long); i += sizeof(long)) {                    // (2) 0.1127
/*8  */         long a = *(long *)(src1 + i);                                          // (4) 0.0939
/*10 */         long b = *(long *)(src2 + i);                                          // (5) 0.0939
/*12 */         *(long *)(dst + i) = ((a & pb_7f) + (b & pb_7f)) ^ ((a ^ b) & pb_80);  // (0) 0.23
/*14 */     }                                                                          // (8) 0.01878
/*16 */     for (; i < w; i++)                                                         // (6) 0.05634
/*18 */         dst[i] = src1[i] + src2[i];                                            // (3) 0.108
/*20 */ }                                                                              // (10) 0.004695

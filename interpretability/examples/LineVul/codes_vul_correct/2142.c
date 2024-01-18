// commit message FFmpeg@26227d9186 (target=1, prob=0.99218833, correct=True): avcodec/aacdec_fixed: Fix runtime error: left shift of negative value -1
/*0  */ static inline int *DEC_UQUAD(int *dst, unsigned idx, unsigned sign)  // (4) 0.08907
/*2  */ {                                                                    // (13) 0.004049
/*4  */     unsigned nz = idx >> 12;                                         // (5) 0.04858
/*8  */     dst[0] = (idx & 3) * (1 + (((int)sign >> 31) << 1));             // (3) 0.1174
/*10 */     sign <<= nz & 1;                                                 // (6) 0.04453
/*12 */     nz >>= 1;                                                        // (9) 0.03644
/*14 */     dst[1] = (idx >> 2 & 3) * (1 + (((int)sign >> 31) << 1));        // (2) 0.1255
/*16 */     sign <<= nz & 1;                                                 // (7) 0.04453
/*18 */     nz >>= 1;                                                        // (10) 0.03644
/*20 */     dst[2] = (idx >> 4 & 3) * (1 + (((int)sign >> 31) << 1));        // (0) 0.1255
/*22 */     sign <<= nz & 1;                                                 // (8) 0.04453
/*24 */     nz >>= 1;                                                        // (11) 0.03644
/*26 */     dst[3] = (idx >> 6 & 3) * (1 + (((int)sign >> 31) << 1));        // (1) 0.1255
/*30 */     return dst + 4;                                                  // (12) 0.03239
/*32 */ }                                                                    // (14) 0.004049

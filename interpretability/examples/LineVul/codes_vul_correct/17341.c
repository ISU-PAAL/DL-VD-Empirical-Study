// commit message FFmpeg@cf818be4f2 (target=1, prob=0.9919458, correct=True): avcodec/truemotion1: Fix undefined behavior (left shift of negative value)
/*0  */ static int make_cdt24_entry(int p1, int p2, int16_t *cdt)  // (0) 0.3059
/*2  */ {                                                          // (5) 0.01176
/*4  */     int r, b;                                              // (4) 0.09412
/*8  */     b = cdt[p2];                                           // (3) 0.1294
/*10 */     r = cdt[p1]<<16;                                       // (1) 0.1647
/*12 */     return (b+r) << 1;                                     // (2) 0.1412
/*14 */ }                                                          // (6) 0.01176

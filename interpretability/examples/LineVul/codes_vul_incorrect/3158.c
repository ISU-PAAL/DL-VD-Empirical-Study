// commit message FFmpeg@0a467a9b59 (target=1, prob=0.011590499, correct=False): tiffdec: use bytestream2 to simplify overread/overwrite protection
/*0  */ static unsigned tget(const uint8_t **p, int type, int le)  // (0) 0.131
/*2  */ {                                                          // (11) 0.006897
/*4  */     switch (type) {                                        // (8) 0.05517
/*6  */     case TIFF_BYTE:                                        // (5) 0.06897
/*8  */         return *(*p)++;                                    // (3) 0.08966
/*10 */     case TIFF_SHORT:                                       // (6) 0.06897
/*12 */         return tget_short(p, le);                          // (1) 0.1172
/*14 */     case TIFF_LONG:                                        // (7) 0.06897
/*16 */         return tget_long(p, le);                           // (2) 0.1172
/*18 */     default:                                               // (9) 0.03448
/*20 */         return UINT_MAX;                                   // (4) 0.08966
/*22 */     }                                                      // (10) 0.02759
/*24 */ }                                                          // (12) 0.006897

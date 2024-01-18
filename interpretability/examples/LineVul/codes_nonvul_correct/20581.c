// commit message FFmpeg@d1adad3cca (target=0, prob=0.060538396, correct=True): Merge swscale bloatup This will be cleaned up in the next merge
/*0  */ static void RENAME(chrRangeToJpeg)(int16_t *dst, int width)                  // (2) 0.1538
/*2  */ {                                                                            // (6) 0.00641
/*4  */     int i;                                                                   // (4) 0.03846
/*6  */     for (i = 0; i < width; i++) {                                            // (3) 0.1026
/*8  */         dst[i     ] = (FFMIN(dst[i     ],30775)*4663 - 9289992)>>12; //-264  // (0) 0.2949
/*10 */         dst[i+VOFW] = (FFMIN(dst[i+VOFW],30775)*4663 - 9289992)>>12; //-264  // (1) 0.2949
/*12 */     }                                                                        // (5) 0.02564
/*14 */ }                                                                            // (7) 0.00641

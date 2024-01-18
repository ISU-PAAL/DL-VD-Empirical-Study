// commit message FFmpeg@c3afa4db91 (target=1, prob=0.5955845, correct=True): bink: prevent overflows within binkidct by using int-sized intermediate array
/*0  */ void ff_bink_idct_c(DCTELEM *block)               // (2) 0.1348
/*2  */ {                                                 // (8) 0.007092
/*4  */     int i;                                        // (6) 0.04255
/*6  */     DCTELEM temp[64];                             // (5) 0.08511
/*10 */     for (i = 0; i < 8; i++)                       // (4) 0.1064
/*12 */         bink_idct_col(&temp[i], &block[i]);       // (1) 0.1702
/*14 */     for (i = 0; i < 8; i++) {                     // (3) 0.1135
/*16 */         IDCT_ROW( (&block[8*i]), (&temp[8*i]) );  // (0) 0.1986
/*18 */     }                                             // (7) 0.02837
/*20 */ }                                                 // (9) 0.007092

// commit message FFmpeg@a494792961 (target=1, prob=0.9746021, correct=True): yuv2rgb: fix integer overflow in fill_table
/*0  */ static void fill_table(uint8_t* table[256 + 2*YUVRGB_TABLE_HEADROOM], const int elemsize,  // (1) 0.156
/*2  */                        const int inc, void *y_tab)                                         // (2) 0.1468
/*4  */ {                                                                                          // (9) 0.004587
/*6  */     int i;                                                                                 // (7) 0.02752
/*8  */     uint8_t *y_table = y_tab;                                                              // (6) 0.07339
/*12 */     y_table -= elemsize * (inc >> 9);                                                      // (5) 0.07339
/*16 */     for (i = 0; i < 256 + 2*YUVRGB_TABLE_HEADROOM; i++) {                                  // (3) 0.133
/*18 */         int64_t cb = av_clip(i-YUVRGB_TABLE_HEADROOM, 0, 255)*inc;                         // (0) 0.1697
/*20 */         table[i] = y_table + elemsize * (cb >> 16);                                        // (4) 0.1147
/*22 */     }                                                                                      // (8) 0.01835
/*24 */ }                                                                                          // (10) 0.004587

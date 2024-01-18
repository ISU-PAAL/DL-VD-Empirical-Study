// commit message FFmpeg@e3e6a2cff4 (target=1, prob=0.51334274, correct=True): avformat/rtpdec_jpeg: fix low contrast image on low quality setting
/*0  */ static void create_default_qtables(uint8_t *qtables, uint8_t q)  // (1) 0.1045
/*2  */ {                                                                // (14) 0.004545
/*4  */     int factor = q;                                              // (10) 0.03636
/*6  */     int i;                                                       // (11) 0.02727
/*10 */     factor = av_clip(q, 1, 99);                                  // (6) 0.06818
/*14 */     if (q < 50)                                                  // (9) 0.04091
/*16 */         q = 5000 / factor;                                       // (8) 0.05909
/*18 */     else                                                         // (12) 0.01818
/*20 */         q = 200 - factor * 2;                                    // (7) 0.06818
/*24 */     for (i = 0; i < 128; i++) {                                  // (4) 0.07273
/*26 */         int val = (default_quantizers[i] * q + 50) / 100;        // (0) 0.1182
/*30 */         /* Limit the quantizers to 1 <= q <= 255. */             // (2) 0.09091
/*32 */         val = av_clip(val, 1, 255);                              // (3) 0.08636
/*34 */         qtables[i] = val;                                        // (5) 0.07273
/*36 */     }                                                            // (13) 0.01818
/*38 */ }                                                                // (15) 0.004545

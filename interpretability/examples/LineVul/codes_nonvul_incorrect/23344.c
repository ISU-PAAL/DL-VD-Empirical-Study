// commit message FFmpeg@289520fd97 (target=0, prob=0.63077384, correct=False): Reduce the verbosity of a mpeg1/2 invalid intra-matrix warning.
/*0  */ static int load_matrix(MpegEncContext *s, uint16_t matrix0[64], uint16_t matrix1[64], int intra)              // (1) 0.09695
/*2  */ {                                                                                                             // (18) 0.00277
/*4  */     int i;                                                                                                    // (15) 0.01662
/*8  */     for (i = 0; i < 64; i++) {                                                                                // (8) 0.04432
/*10 */         int j = s->dsp.idct_permutation[ff_zigzag_direct[i]];                                                 // (3) 0.08587
/*12 */         int v = get_bits(&s->gb, 8);                                                                          // (6) 0.0554
/*14 */         if (v == 0) {                                                                                         // (11) 0.03878
/*16 */             av_log(s->avctx, AV_LOG_ERROR, "matrix damaged\n");                                               // (2) 0.09141
/*18 */             return -1;                                                                                        // (9) 0.04155
/*20 */         }                                                                                                     // (13) 0.02216
/*22 */         if (intra && i == 0 && v != 8) {                                                                      // (5) 0.05817
/*24 */             av_log(s->avctx, AV_LOG_ERROR, "intra matrix specifies invalid DC quantizer %d, ignoring\n", v);  // (0) 0.1219
/*26 */             v = 8; // needed by pink.mpg / issue1046                                                          // (4) 0.07202
/*28 */         }                                                                                                     // (14) 0.02216
/*30 */         matrix0[j] = v;                                                                                       // (10) 0.04155
/*32 */         if (matrix1)                                                                                          // (12) 0.03601
/*34 */             matrix1[j] = v;                                                                                   // (7) 0.05263
/*36 */     }                                                                                                         // (17) 0.01108
/*38 */     return 0;                                                                                                 // (16) 0.01662
/*40 */ }                                                                                                             // (19) 0.00277

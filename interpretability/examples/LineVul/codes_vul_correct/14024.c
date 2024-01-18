// commit message FFmpeg@f264d336fe (target=1, prob=0.9990109, correct=True): truespeech: fix invalid reads in truespeech_apply_twopoint_filter()
/*0  */ static void truespeech_apply_twopoint_filter(TSContext *dec, int quart)  // (3) 0.06301
/*2  */ {                                                                        // (21) 0.00274
/*4  */     int16_t tmp[146 + 60], *ptr0, *ptr1;                                 // (5) 0.05753
/*6  */     const int16_t *filter;                                               // (13) 0.03014
/*8  */     int i, t, off;                                                       // (14) 0.0274
/*12 */     t = dec->offset2[quart];                                             // (11) 0.03288
/*14 */     if(t == 127){                                                        // (17) 0.02466
/*16 */         memset(dec->newvec, 0, 60 * sizeof(*dec->newvec));               // (2) 0.07123
/*18 */         return;                                                          // (18) 0.02466
/*20 */     }                                                                    // (19) 0.01096
/*22 */     for(i = 0; i < 146; i++)                                             // (9) 0.0411
/*24 */         tmp[i] = dec->filtbuf[i];                                        // (6) 0.05479
/*26 */     off = (t / 25) + dec->offset1[quart >> 1] + 18;                      // (4) 0.06301
/*29 */     ptr0 = tmp + 145 - off;                                              // (12) 0.03288
/*31 */     ptr1 = tmp + 146;                                                    // (15) 0.0274
/*33 */     filter = (const int16_t*)ts_order2_coeffs + (t % 25) * 2;            // (1) 0.07945
/*35 */     for(i = 0; i < 60; i++){                                             // (8) 0.04384
/*37 */         t = (ptr0[0] * filter[0] + ptr0[1] * filter[1] + 0x2000) >> 14;  // (0) 0.1068
/*39 */         ptr0++;                                                          // (16) 0.0274
/*41 */         dec->newvec[i] = t;                                              // (7) 0.04658
/*43 */         ptr1[i] = t;                                                     // (10) 0.0411
/*45 */     }                                                                    // (20) 0.01096
/*47 */ }                                                                        // (22) 0.00274

// commit message FFmpeg@ca32f7f208 (target=0, prob=0.20342502, correct=True): H.264: eliminate non-transposed scantable support. It was an ugly hack to begin with and didn't give any performance.
/*0  */ static void init_dequant8_coeff_table(H264Context *h){                                                      // (11) 0.03711
/*2  */     int i,q,x;                                                                                              // (15) 0.01953
/*4  */     const int transpose = (h->h264dsp.h264_idct8_add != ff_h264_idct8_add_c); //FIXME ugly                  // (3) 0.08203
/*6  */     h->dequant8_coeff[0] = h->dequant8_buffer[0];                                                           // (6) 0.04883
/*8  */     h->dequant8_coeff[1] = h->dequant8_buffer[1];                                                           // (7) 0.04883
/*12 */     for(i=0; i<2; i++ ){                                                                                    // (13) 0.0332
/*14 */         if(i && !memcmp(h->pps.scaling_matrix8[0], h->pps.scaling_matrix8[1], 64*sizeof(uint8_t))){         // (1) 0.1016
/*16 */             h->dequant8_coeff[1] = h->dequant8_buffer[0];                                                   // (5) 0.06445
/*18 */             break;                                                                                          // (14) 0.02539
/*20 */         }                                                                                                   // (16) 0.01562
/*24 */         for(q=0; q<52; q++){                                                                                // (9) 0.03906
/*26 */             int shift = div6[q];                                                                            // (12) 0.03711
/*28 */             int idx = rem6[q];                                                                              // (10) 0.03906
/*30 */             for(x=0; x<64; x++)                                                                             // (8) 0.04492
/*32 */                 h->dequant8_coeff[i][q][transpose ? (x>>3)|((x&7)<<3) : x] =                                // (2) 0.09375
/*34 */                     ((uint32_t)dequant8_coeff_init[idx][ dequant8_coeff_init_scan[((x>>1)&12) | (x&3)] ] *  // (0) 0.125
/*36 */                     h->pps.scaling_matrix8[i][x]) << shift;                                                 // (4) 0.07227
/*38 */         }                                                                                                   // (17) 0.01562
/*40 */     }                                                                                                       // (18) 0.007812
/*42 */ }                                                                                                           // (19) 0.001953

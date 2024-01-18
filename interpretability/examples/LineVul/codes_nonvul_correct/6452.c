// commit message FFmpeg@fdbbf2e0fc (target=0, prob=0.015464134, correct=True): rewrite h261 loop filter no malloc(64) memcpy free stuff no filter1 A->B then filter2 A->B (yes not B->A) no incorrect rouding after the 1d filter
/*0  */ static void h261_v_loop_filter_c(uint8_t *dest,uint8_t *src, int stride){          // (1) 0.1154
/*2  */     int i,j,xy,yz;                                                                 // (9) 0.04615
/*4  */     int res;                                                                       // (11) 0.02308
/*6  */     for(i=0; i<8; i++){                                                            // (6) 0.06154
/*8  */         for(j=1; j<7; j++){                                                        // (4) 0.07692
/*10 */             xy = j * stride + i;                                                   // (3) 0.07692
/*12 */             yz = j * 8 + i;                                                        // (5) 0.07692
/*14 */             res = (int)src[yz-1*8] + ((int)(src[yz+0*8]) * 2) + (int)src[yz+1*8];  // (0) 0.1962
/*16 */             res +=2;                                                               // (8) 0.05769
/*18 */             res >>=2;                                                              // (7) 0.06154
/*20 */             dest[xy] = (uint8_t)res;                                               // (2) 0.09231
/*22 */         }                                                                          // (10) 0.03077
/*24 */     }                                                                              // (12) 0.01538
/*26 */ }                                                                                  // (13) 0.003846

// commit message FFmpeg@02591641f8 (target=1, prob=0.119487524, correct=False): shorten: remove VLA and check for buffer overflow
/*0  */ static void decode_subframe_lpc(ShortenContext *s, int channel, int residual_size, int pred_order)  // (3) 0.1111
/*2  */ {                                                                                                   // (11) 0.003831
/*4  */     int sum, i, j;                                                                                  // (9) 0.03831
/*6  */     int coeffs[pred_order];                                                                         // (8) 0.04598
/*10 */     for (i=0; i<pred_order; i++)                                                                    // (6) 0.06513
/*12 */         coeffs[i] = get_sr_golomb_shorten(&s->gb, LPCQUANT);                                        // (1) 0.1303
/*16 */     for (i=0; i < s->blocksize; i++) {                                                              // (5) 0.0728
/*18 */         sum = s->lpcqoffset;                                                                        // (7) 0.0613
/*20 */         for (j=0; j<pred_order; j++)                                                                // (4) 0.08046
/*22 */             sum += coeffs[j] * s->decoded[channel][i-j-1];                                          // (2) 0.1264
/*24 */         s->decoded[channel][i] = get_sr_golomb_shorten(&s->gb, residual_size) + (sum >> LPCQUANT);  // (0) 0.1724
/*26 */     }                                                                                               // (10) 0.01533
/*28 */ }                                                                                                   // (12) 0.003831

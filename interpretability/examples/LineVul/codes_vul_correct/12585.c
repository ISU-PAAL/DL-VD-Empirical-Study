// commit message FFmpeg@ac4b32df71 (target=1, prob=0.56834483, correct=True): On2 VP7 decoder
/*0  */ int decode_block_coeffs(VP56RangeCoder *c, int16_t block[16],                   // (4) 0.1092
/*2  */                         uint8_t probs[16][3][NUM_DCT_TOKENS - 1],               // (0) 0.1965
/*4  */                         int i, int zero_nhood, int16_t qmul[2])                 // (1) 0.1834
/*6  */ {                                                                               // (7) 0.004367
/*8  */     uint8_t *token_prob = probs[i][zero_nhood];                                 // (5) 0.1004
/*10 */     if (!vp56_rac_get_prob_branchy(c, token_prob[0]))   // DCT_EOB              // (2) 0.1616
/*12 */         return 0;                                                               // (6) 0.04367
/*14 */     return decode_block_coeffs_internal(c, block, probs, i, token_prob, qmul);  // (3) 0.1397
/*16 */ }                                                                               // (8) 0.004367

// commit message FFmpeg@0058584580 (target=0, prob=0.28144404, correct=True): AC-3 decoder, soc revision 31, Jul 14 23:53:28 2006 UTC by cloud9 Removed _ from names Removed temporary storage for the exponents Removed ctx->samples Now each transform coefficients are stored in audio block as an array of transform coefficients for each channel added ctx->delay (output of later half of previous block) added audio_block->block_output(output of this block)
/*0  */ static inline int16_t calc_lowcomp(int16_t a, int16_t b0, int16_t b1, uint8_t bin)  // (0) 0.1386
/*2  */ {                                                                                   // (17) 0.003745
/*4  */     if (bin < 7) {                                                                  // (11) 0.03745
/*6  */         if ((b0 + 256) == b1)                                                       // (5) 0.06742
/*8  */             a = 384;                                                                // (9) 0.05618
/*10 */         else if (b0 > b1)                                                           // (7) 0.05993
/*12 */             a = FFMAX(0, a - 64);                                                   // (2) 0.0824
/*14 */     }                                                                               // (15) 0.01498
/*16 */     else if (bin < 20) {                                                            // (10) 0.0412
/*18 */         if ((b0 + 256) == b1)                                                       // (4) 0.06742
/*20 */             a = 320;                                                                // (8) 0.05618
/*22 */         else if (b0 > b1)                                                           // (6) 0.05993
/*24 */             a = FFMAX(0, a - 64);                                                   // (1) 0.0824
/*26 */     }                                                                               // (14) 0.01498
/*28 */     else {                                                                          // (13) 0.01873
/*30 */         a = FFMAX(0, a - 128);                                                      // (3) 0.06742
/*32 */     }                                                                               // (16) 0.01498
/*36 */     return a;                                                                       // (12) 0.02247
/*38 */ }                                                                                   // (18) 0.003745

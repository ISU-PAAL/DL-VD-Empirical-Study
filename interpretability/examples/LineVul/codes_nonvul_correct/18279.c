// commit message FFmpeg@1acd7d594c (target=0, prob=0.019578906, correct=True): h264: integrate clear_blocks calls with IDCT.
/*0  */ static void FUNCC(pred4x4_horizontal_add)(uint8_t *_pix, const int16_t *_block,  // (1) 0.1142
/*2  */                                           ptrdiff_t stride)                      // (0) 0.1626
/*4  */ {                                                                                // (15) 0.00346
/*6  */     int i;                                                                       // (13) 0.02076
/*8  */     pixel *pix = (pixel*)_pix;                                                   // (9) 0.0519
/*10 */     const dctcoef *block = (const dctcoef*)_block;                               // (2) 0.07266
/*12 */     stride >>= sizeof(pixel)-1;                                                  // (10) 0.04152
/*14 */     for(i=0; i<4; i++){                                                          // (8) 0.05536
/*16 */         pixel v = pix[-1];                                                       // (7) 0.05536
/*18 */         pix[0]= v += block[0];                                                   // (4) 0.06228
/*20 */         pix[1]= v += block[1];                                                   // (5) 0.06228
/*22 */         pix[2]= v += block[2];                                                   // (6) 0.06228
/*24 */         pix[3]= v +  block[3];                                                   // (3) 0.06574
/*26 */         pix+= stride;                                                            // (11) 0.04152
/*28 */         block+= 4;                                                               // (12) 0.03806
/*30 */     }                                                                            // (14) 0.01384
/*32 */ }                                                                                // (16) 0.00346

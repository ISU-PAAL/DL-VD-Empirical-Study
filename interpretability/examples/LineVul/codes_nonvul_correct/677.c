// commit message FFmpeg@5cd8afee99 (target=0, prob=0.4231821, correct=True): diracdec: Check for negative quants which would cause out of array reads.
/*0  */ static inline void codeblock(DiracContext *s, SubBand *b,                         // (9) 0.0332
/*2  */                              GetBitContext *gb, DiracArith *c,                    // (1) 0.08008
/*4  */                              int left, int right, int top, int bottom,            // (3) 0.07813
/*6  */                              int blockcnt_one, int is_arith)                      // (2) 0.08008
/*8  */ {                                                                                 // (24) 0.001953
/*10 */     int x, y, zero_block;                                                         // (17) 0.02344
/*12 */     int qoffset, qfactor;                                                         // (19) 0.01953
/*14 */     IDWTELEM *buf;                                                                // (18) 0.02148
/*18 */     /* check for any coded coefficients in this codeblock */                      // (11) 0.02734
/*20 */     if (!blockcnt_one) {                                                          // (16) 0.02344
/*22 */         if (is_arith)                                                             // (12) 0.02734
/*24 */             zero_block = dirac_get_arith_bit(c, CTX_ZERO_BLOCK);                  // (4) 0.07031
/*26 */         else                                                                      // (21) 0.01562
/*28 */             zero_block = get_bits1(gb);                                           // (7) 0.04297
/*32 */         if (zero_block)                                                           // (15) 0.02539
/*34 */             return;                                                               // (14) 0.02539
/*36 */     }                                                                             // (22) 0.007813
/*40 */     if (s->codeblock_mode && !(s->old_delta_quant && blockcnt_one)) {             // (5) 0.05859
/*42 */         if (is_arith)                                                             // (13) 0.02734
/*44 */             b->quant += dirac_get_arith_int(c, CTX_DELTA_Q_F, CTX_DELTA_Q_DATA);  // (0) 0.0957
/*46 */         else                                                                      // (20) 0.01563
/*48 */             b->quant += dirac_get_se_golomb(gb);                                  // (6) 0.05469
/*50 */     }                                                                             // (23) 0.007812
/*54 */     b->quant = FFMIN(b->quant, MAX_QUANT);                                        // (8) 0.03711
/*58 */     qfactor = qscale_tab[b->quant];                                               // (10) 0.0293
/*60 */     /* TODO: context pointer? */                                                  // 0.0
/*62 */     if (!s->num_refs)                                                             // 0.0
/*64 */         qoffset = qoffset_intra_tab[b->quant];                                    // 0.0
/*66 */     else                                                                          // 0.0
/*68 */         qoffset = qoffset_inter_tab[b->quant];                                    // 0.0
/*72 */     buf = b->ibuf + top * b->stride;                                              // 0.0
/*74 */     for (y = top; y < bottom; y++) {                                              // 0.0
/*76 */         for (x = left; x < right; x++) {                                          // 0.0
/*78 */             /* [DIRAC_STD] 13.4.4 Subband coefficients. coeff_unpack() */         // 0.0
/*80 */             if (is_arith)                                                         // 0.0
/*82 */                 coeff_unpack_arith(c, qfactor, qoffset, b, buf+x, x, y);          // 0.0
/*84 */             else                                                                  // 0.0
/*86 */                 buf[x] = coeff_unpack_golomb(gb, qfactor, qoffset);               // 0.0
/*88 */         }                                                                         // 0.0
/*90 */         buf += b->stride;                                                         // 0.0
/*92 */     }                                                                             // 0.0
/*94 */ }                                                                                 // 0.0

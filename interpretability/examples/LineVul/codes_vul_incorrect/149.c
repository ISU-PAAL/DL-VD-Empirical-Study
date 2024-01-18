// commit message FFmpeg@323e6fead0 (target=1, prob=0.43657485, correct=False): ac3enc: do not right-shift fixed-point coefficients in the final MDCT stage.
/*0  */ static void compute_rematrixing_strategy(AC3EncodeContext *s)                          // (13) 0.03906
/*2  */ {                                                                                      // (20) 0.001953
/*4  */     int nb_coefs;                                                                      // (18) 0.02148
/*6  */     int blk, bnd, i;                                                                   // (17) 0.02344
/*8  */     AC3Block *block, *block0;                                                          // (16) 0.02539
/*12 */     s->num_rematrixing_bands = 4;                                                      // (15) 0.03125
/*16 */     if (s->rematrixing & AC3_REMATRIXING_IS_STATIC)                                    // (7) 0.05078
/*18 */         return;                                                                        // (19) 0.01758
/*22 */     nb_coefs = FFMIN(s->nb_coefs[0], s->nb_coefs[1]);                                  // (1) 0.06445
/*26 */     for (blk = 0; blk < AC3_MAX_BLOCKS; blk++) {                                       // (8) 0.05078
/*28 */         block = &s->blocks[blk];                                                       // (14) 0.0332
/*30 */         block->new_rematrixing_strategy = !blk;                                        // (12) 0.04492
/*32 */         for (bnd = 0; bnd < s->num_rematrixing_bands; bnd++) {                         // (4) 0.0625
/*34 */             /* calculate calculate sum of squared coeffs for one band in one block */  // (6) 0.05273
/*36 */             int start = ff_ac3_rematrix_band_tab[bnd];                                 // (5) 0.05859
/*38 */             int end   = FFMIN(nb_coefs, ff_ac3_rematrix_band_tab[bnd+1]);              // (0) 0.08398
/*40 */             CoefSumType sum[4] = {0,};                                                 // (10) 0.04687
/*42 */             for (i = start; i < end; i++) {                                            // (11) 0.04687
/*44 */                 CoefType lt = block->mdct_coef[0][i];                                  // (2) 0.06445
/*46 */                 CoefType rt = block->mdct_coef[1][i];                                  // (3) 0.06445
/*48 */                 CoefType md = lt + rt;                                                 // (9) 0.05078
/*50 */                 CoefType sd = lt - rt;                                                 // 0.0
/*52 */                 sum[0] += lt * lt;                                                     // 0.0
/*54 */                 sum[1] += rt * rt;                                                     // 0.0
/*56 */                 sum[2] += md * md;                                                     // 0.0
/*58 */                 sum[3] += sd * sd;                                                     // 0.0
/*60 */             }                                                                          // 0.0
/*64 */             /* compare sums to determine if rematrixing will be used for this band */  // 0.0
/*66 */             if (FFMIN(sum[2], sum[3]) < FFMIN(sum[0], sum[1]))                         // 0.0
/*68 */                 block->rematrixing_flags[bnd] = 1;                                     // 0.0
/*70 */             else                                                                       // 0.0
/*72 */                 block->rematrixing_flags[bnd] = 0;                                     // 0.0
/*76 */             /* determine if new rematrixing flags will be sent */                      // 0.0
/*78 */             if (blk &&                                                                 // 0.0
/*80 */                 block->rematrixing_flags[bnd] != block0->rematrixing_flags[bnd]) {     // 0.0
/*82 */                 block->new_rematrixing_strategy = 1;                                   // 0.0
/*84 */             }                                                                          // 0.0
/*86 */         }                                                                              // 0.0
/*88 */         block0 = block;                                                                // 0.0
/*90 */     }                                                                                  // 0.0
/*92 */ }                                                                                      // 0.0

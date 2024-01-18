// commit message FFmpeg@5ff998a233 (target=1, prob=0.4171282, correct=False): flacenc: use uint64_t for bit counts
/*0  */ static int subframe_count_exact(FlacEncodeContext *s, FlacSubframe *sub,    // (2) 0.04883
/*2  */                                 int pred_order)                             // (0) 0.07031
/*4  */ {                                                                           // (28) 0.001953
/*6  */     int p, porder, psize;                                                   // (17) 0.02344
/*8  */     int i, part_end;                                                        // (21) 0.01953
/*10 */     int count = 0;                                                          // (24) 0.01563
/*14 */     /* subframe header */                                                   // (23) 0.01563
/*16 */     count += 8;                                                             // (26) 0.01367
/*20 */     /* subframe */                                                          // (25) 0.01367
/*22 */     if (sub->type == FLAC_SUBFRAME_CONSTANT) {                              // (6) 0.04297
/*24 */         count += sub->obits;                                                // (14) 0.02734
/*26 */     } else if (sub->type == FLAC_SUBFRAME_VERBATIM) {                       // (3) 0.04688
/*28 */         count += s->frame.blocksize * sub->obits;                           // (8) 0.04102
/*30 */     } else {                                                                // (27) 0.01172
/*32 */         /* warm-up samples */                                               // (15) 0.02539
/*34 */         count += pred_order * sub->obits;                                   // (10) 0.03516
/*38 */         /* LPC coefficients */                                              // (16) 0.02344
/*40 */         if (sub->type == FLAC_SUBFRAME_LPC)                                 // (4) 0.04688
/*42 */             count += 4 + 5 + pred_order * s->options.lpc_coeff_precision;   // (1) 0.06641
/*46 */         /* rice-encoded block */                                            // (13) 0.02734
/*48 */         count += 2;                                                         // (19) 0.02148
/*52 */         /* partition order */                                               // (18) 0.02148
/*54 */         porder = sub->rc.porder;                                            // (11) 0.0332
/*56 */         psize  = s->frame.blocksize >> porder;                              // (7) 0.04102
/*58 */         count += 4;                                                         // (20) 0.02148
/*62 */         /* residual */                                                      // (22) 0.01953
/*64 */         i        = pred_order;                                              // (9) 0.03906
/*66 */         part_end = psize;                                                   // (12) 0.02734
/*68 */         for (p = 0; p < 1 << porder; p++) {                                 // (5) 0.04492
/*70 */             int k = sub->rc.params[p];                                      // 0.0
/*72 */             count += 4;                                                     // 0.0
/*74 */             count += rice_count_exact(&sub->residual[i], part_end - i, k);  // 0.0
/*76 */             i = part_end;                                                   // 0.0
/*78 */             part_end = FFMIN(s->frame.blocksize, part_end + psize);         // 0.0
/*80 */         }                                                                   // 0.0
/*82 */     }                                                                       // 0.0
/*86 */     return count;                                                           // 0.0
/*88 */ }                                                                           // 0.0

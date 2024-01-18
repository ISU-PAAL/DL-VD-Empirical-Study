// commit message qemu@c24a8a0b6d (target=1, prob=0.27234635, correct=False): target-alpha: Raise IOV from CVTTQ
/*0  */ IEEE_ARITH2(sqrtt)                                                         // (15) 0.02517
/*2  */ IEEE_ARITH2(cvtst)                                                         // (16) 0.02517
/*4  */ IEEE_ARITH2(cvtts)                                                         // (17) 0.02517
/*8  */ static void gen_cvttq(DisasContext *ctx, int rb, int rc, int fn11)         // (3) 0.05721
/*10 */ {                                                                          // (25) 0.002288
/*12 */     TCGv vb, vc;                                                           // (14) 0.02746
/*16 */     /* No need to set flushzero, since we have an integer output.  */      // (8) 0.04577
/*18 */     vb = gen_ieee_input(ctx, rb, fn11, 0);                                 // (5) 0.05263
/*20 */     vc = dest_fpr(ctx, rc);                                                // (12) 0.03432
/*24 */     /* Almost all integer conversions use cropped rounding, and most       // (13) 0.03204
/*26 */        also do not have integer overflow enabled.  Special case that.  */  // (6) 0.04805
/*28 */     switch (fn11) {                                                        // (19) 0.02059
/*30 */     case QUAL_RM_C:                                                        // (18) 0.02517
/*32 */         gen_helper_cvttq_c(vc, cpu_env, vb);                               // (1) 0.06178
/*34 */         break;                                                             // (20) 0.02059
/*36 */     case QUAL_V | QUAL_RM_C:                                               // (10) 0.03661
/*38 */     case QUAL_S | QUAL_V | QUAL_RM_C:                                      // (7) 0.04805
/*40 */     case QUAL_S | QUAL_V | QUAL_I | QUAL_RM_C:                             // (2) 0.0595
/*42 */         gen_helper_cvttq_svic(vc, cpu_env, vb);                            // (0) 0.06407
/*44 */         break;                                                             // (21) 0.02059
/*46 */     default:                                                               // (23) 0.01144
/*48 */         gen_qual_roundmode(ctx, fn11);                                     // (9) 0.04348
/*50 */         gen_helper_cvttq(vc, cpu_env, vb);                                 // (4) 0.05721
/*52 */         break;                                                             // (22) 0.02059
/*54 */     }                                                                      // (24) 0.009153
/*58 */     gen_fp_exc_raise(rc, fn11);                                            // (11) 0.03661
/*60 */ }                                                                          // (26) 0.002288

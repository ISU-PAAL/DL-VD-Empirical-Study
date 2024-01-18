// commit message qemu@8e7a6db965 (target=1, prob=0.26547542, correct=False): target-ppc: fix nego and subf*o instructions
/*0  */ static inline void gen_op_arith_compute_ov(DisasContext *ctx, TCGv arg0,   // (3) 0.07584
/*2  */                                            TCGv arg1, TCGv arg2, int sub)  // (0) 0.1601
/*4  */ {                                                                          // (16) 0.002809
/*6  */     TCGv t0 = tcg_temp_new();                                              // (9) 0.04494
/*10 */     tcg_gen_xor_tl(cpu_ov, arg0, arg1);                                    // (7) 0.06461
/*12 */     tcg_gen_xor_tl(t0, arg1, arg2);                                        // (8) 0.0618
/*14 */     if (sub) {                                                             // (12) 0.02247
/*16 */         tcg_gen_and_tl(cpu_ov, cpu_ov, t0);                                // (4) 0.07584
/*18 */     } else {                                                               // (13) 0.01685
/*20 */         tcg_gen_andc_tl(cpu_ov, cpu_ov, t0);                               // (2) 0.07865
/*22 */     }                                                                      // (14) 0.01124
/*24 */     tcg_temp_free(t0);                                                     // (11) 0.03652
/*26 */     if (NARROW_MODE(ctx)) {                                                // (10) 0.03933
/*28 */         tcg_gen_ext32s_tl(cpu_ov, cpu_ov);                                 // (5) 0.07303
/*30 */     }                                                                      // (15) 0.01124
/*32 */     tcg_gen_shri_tl(cpu_ov, cpu_ov, TARGET_LONG_BITS - 1);                 // (1) 0.08989
/*34 */     tcg_gen_or_tl(cpu_so, cpu_so, cpu_ov);                                 // (6) 0.06742
/*36 */ }                                                                          // (17) 0.002809

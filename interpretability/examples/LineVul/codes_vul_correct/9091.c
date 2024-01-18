// commit message qemu@eff235eb2b (target=1, prob=0.9364445, correct=True): hppa: avoid anonymous unions in designated initializers.
/*0  */ static ExitStatus trans_log(DisasContext *ctx, uint32_t insn,  // (2) 0.07042
/*2  */                             const DisasInsn *di)               // (0) 0.1232
/*4  */ {                                                              // (15) 0.003521
/*6  */     unsigned r2 = extract32(insn, 21, 5);                      // (7) 0.05986
/*8  */     unsigned r1 = extract32(insn, 16, 5);                      // (8) 0.05986
/*10 */     unsigned cf = extract32(insn, 12, 4);                      // (9) 0.05634
/*12 */     unsigned rt = extract32(insn,  0, 5);                      // (6) 0.06338
/*14 */     TCGv tcg_r1, tcg_r2;                                       // (5) 0.06338
/*16 */     ExitStatus ret;                                            // (13) 0.02465
/*20 */     if (cf) {                                                  // (12) 0.02817
/*22 */         nullify_over(ctx);                                     // (10) 0.0493
/*24 */     }                                                          // (14) 0.01408
/*26 */     tcg_r1 = load_gpr(ctx, r1);                                // (3) 0.0669
/*28 */     tcg_r2 = load_gpr(ctx, r2);                                // (4) 0.0669
/*30 */     ret = do_log(ctx, rt, tcg_r1, tcg_r2, cf, di->f_ttt);      // (1) 0.1232
/*32 */     return nullify_end(ctx, ret);                              // (11) 0.04577
/*34 */ }                                                              // (16) 0.003521

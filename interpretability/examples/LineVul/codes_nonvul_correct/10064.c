// commit message qemu@42a268c241 (target=0, prob=0.057113048, correct=True): tcg: Change translator-side labels to a pointer
/*0  */ static ExitStatus gen_bcond_internal(DisasContext *ctx, TCGCond cond,  // (10) 0.04102
/*2  */                                      TCGv cmp, int32_t disp)           // (0) 0.09375
/*4  */ {                                                                      // (20) 0.001953
/*6  */     uint64_t dest = ctx->pc + (disp << 2);                             // (11) 0.03906
/*8  */     int lab_true = gen_new_label();                                    // (18) 0.02734
/*12 */     if (use_goto_tb(ctx, dest)) {                                      // (15) 0.03516
/*14 */         tcg_gen_brcondi_i64(cond, cmp, 0, lab_true);                   // (2) 0.05859
/*18 */         tcg_gen_goto_tb(0);                                            // (12) 0.03906
/*20 */         tcg_gen_movi_i64(cpu_pc, ctx->pc);                             // (4) 0.05273
/*22 */         tcg_gen_exit_tb((uintptr_t)ctx->tb);                           // (5) 0.05273
/*26 */         gen_set_label(lab_true);                                       // (16) 0.0332
/*28 */         tcg_gen_goto_tb(1);                                            // (13) 0.03906
/*30 */         tcg_gen_movi_i64(cpu_pc, dest);                                // (9) 0.04688
/*32 */         tcg_gen_exit_tb((uintptr_t)ctx->tb + 1);                       // (3) 0.05664
/*36 */         return EXIT_GOTO_TB;                                           // (17) 0.03125
/*38 */     } else {                                                           // (19) 0.01172
/*40 */         TCGv_i64 z = tcg_const_i64(0);                                 // (7) 0.04883
/*42 */         TCGv_i64 d = tcg_const_i64(dest);                              // (8) 0.04883
/*44 */         TCGv_i64 p = tcg_const_i64(ctx->pc);                           // (6) 0.05273
/*48 */         tcg_gen_movcond_i64(cond, cpu_pc, cmp, z, d, p);               // (1) 0.06641
/*52 */         tcg_temp_free_i64(z);                                          // (14) 0.03711
/*54 */         tcg_temp_free_i64(d);                                          // 0.0
/*56 */         tcg_temp_free_i64(p);                                          // 0.0
/*58 */         return EXIT_PC_UPDATED;                                        // 0.0
/*60 */     }                                                                  // 0.0
/*62 */ }                                                                      // 0.0

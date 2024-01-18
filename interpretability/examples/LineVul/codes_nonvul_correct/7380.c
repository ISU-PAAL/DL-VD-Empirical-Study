// commit message qemu@7d08d85645 (target=0, prob=0.25624597, correct=True): target-ppc: add support for extended mtfsf/mtfsfi forms
/*0  */ static void gen_mtfsfi(DisasContext *ctx)                                      // (14) 0.03233
/*2  */ {                                                                              // (24) 0.002309
/*4  */     int bf, sh;                                                                // (20) 0.02079
/*6  */     TCGv_i64 t0;                                                               // (15) 0.02771
/*8  */     TCGv_i32 t1;                                                               // (16) 0.02771
/*12 */     if (unlikely(!ctx->fpu_enabled)) {                                         // (11) 0.03926
/*14 */         gen_exception(ctx, POWERPC_EXCP_FPU);                                  // (3) 0.05312
/*16 */         return;                                                                // (21) 0.02079
/*18 */     }                                                                          // (22) 0.009238
/*20 */     bf = crbD(ctx->opcode) >> 2;                                               // (7) 0.04157
/*22 */     sh = 7 - bf;                                                               // (18) 0.02309
/*24 */     /* NIP cannot be restored if the memory exception comes from an helper */  // (8) 0.04157
/*26 */     gen_update_nip(ctx, ctx->nip - 4);                                         // (5) 0.04619
/*28 */     gen_reset_fpstatus();                                                      // (19) 0.02309
/*30 */     t0 = tcg_const_i64(FPIMM(ctx->opcode) << (4 * sh));                        // (2) 0.06697
/*32 */     t1 = tcg_const_i32(1 << sh);                                               // (9) 0.04157
/*34 */     gen_helper_store_fpscr(cpu_env, t0, t1);                                   // (4) 0.05312
/*36 */     tcg_temp_free_i64(t0);                                                     // (12) 0.03695
/*38 */     tcg_temp_free_i32(t1);                                                     // (13) 0.03695
/*40 */     if (unlikely(Rc(ctx->opcode) != 0)) {                                      // (6) 0.04619
/*42 */         tcg_gen_trunc_tl_i32(cpu_crf[1], cpu_fpscr);                           // (1) 0.0739
/*44 */         tcg_gen_shri_i32(cpu_crf[1], cpu_crf[1], FPSCR_OX);                    // (0) 0.08545
/*46 */     }                                                                          // (23) 0.009238
/*48 */     /* We can raise a differed exception */                                    // (17) 0.0254
/*50 */     gen_helper_float_check_status(cpu_env);                                    // (10) 0.04157
/*52 */ }                                                                              // (25) 0.002309

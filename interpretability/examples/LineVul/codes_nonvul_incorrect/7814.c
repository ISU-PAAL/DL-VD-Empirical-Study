// commit message qemu@42a268c241 (target=0, prob=0.9983537, correct=False): tcg: Change translator-side labels to a pointer
/*0  */ static void gen_tlbsx_440(DisasContext *ctx)                                // (7) 0.04061
/*2  */ {                                                                           // (21) 0.002538
/*4  */ #if defined(CONFIG_USER_ONLY)                                               // (14) 0.03046
/*6  */     gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);                        // (5) 0.06345
/*8  */ #else                                                                       // (19) 0.005076
/*10 */     TCGv t0;                                                                // (15) 0.02284
/*12 */     if (unlikely(ctx->pr)) {                                                // (11) 0.03299
/*14 */         gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);                    // (4) 0.0736
/*16 */         return;                                                             // (16) 0.02284
/*18 */     }                                                                       // (17) 0.01015
/*20 */     t0 = tcg_temp_new();                                                    // (12) 0.03299
/*22 */     gen_addr_reg_index(ctx, t0);                                            // (8) 0.04061
/*24 */     gen_helper_440_tlbsx(cpu_gpr[rD(ctx->opcode)], cpu_env, t0);            // (1) 0.08883
/*26 */     tcg_temp_free(t0);                                                      // (13) 0.03299
/*28 */     if (Rc(ctx->opcode)) {                                                  // (10) 0.03553
/*30 */         int l1 = gen_new_label();                                           // (6) 0.04315
/*32 */         tcg_gen_trunc_tl_i32(cpu_crf[0], cpu_so);                           // (3) 0.07868
/*34 */         tcg_gen_brcondi_tl(TCG_COND_EQ, cpu_gpr[rD(ctx->opcode)], -1, l1);  // (0) 0.1193
/*36 */         tcg_gen_ori_i32(cpu_crf[0], cpu_crf[0], 0x02);                      // (2) 0.08883
/*38 */         gen_set_label(l1);                                                  // (9) 0.04061
/*40 */     }                                                                       // (18) 0.01015
/*42 */ #endif                                                                      // (20) 0.005076
/*44 */ }                                                                           // (22) 0.002538

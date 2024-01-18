// commit message qemu@9b2fadda3e (target=1, prob=0.9989814, correct=True): ppc: Rework generation of priv and inval interrupts
/*0  */ static void gen_mtmsr(DisasContext *ctx)                                                    // (14) 0.02734
/*2  */ {                                                                                           // (23) 0.001953
/*4  */ #if defined(CONFIG_USER_ONLY)                                                               // (16) 0.02344
/*6  */     gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);                                        // (5) 0.04688
/*8  */ #else                                                                                       // (22) 0.003906
/*10 */     if (unlikely(ctx->pr)) {                                                                // (15) 0.02539
/*12 */         gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);                                    // (3) 0.05469
/*14 */         return;                                                                             // (18) 0.01758
/*16 */     }                                                                                       // (21) 0.007812
/*18 */     if (ctx->opcode & 0x00010000) {                                                         // (13) 0.03125
/*20 */         /* Special form that does not need any synchronisation */                           // (11) 0.03516
/*22 */         TCGv t0 = tcg_temp_new();                                                           // (8) 0.03906
/*24 */         tcg_gen_andi_tl(t0, cpu_gpr[rS(ctx->opcode)], (1 << MSR_RI) | (1 << MSR_EE));       // (1) 0.09766
/*26 */         tcg_gen_andi_tl(cpu_msr, cpu_msr, ~(target_ulong)((1 << MSR_RI) | (1 << MSR_EE)));  // (0) 0.09961
/*28 */         tcg_gen_or_tl(cpu_msr, cpu_msr, t0);                                                // (2) 0.05664
/*30 */         tcg_temp_free(t0);                                                                  // (12) 0.0332
/*32 */     } else {                                                                                // (20) 0.01172
/*34 */         TCGv msr = tcg_temp_new();                                                          // (9) 0.03906
/*38 */         /* XXX: we need to update nip before the store                                      // (10) 0.03711
/*40 */          *      if we enter power saving mode, we will exit the loop                        // (4) 0.05078
/*42 */          *      directly from ppc_store_msr                                                 // (6) 0.04492
/*44 */          */                                                                                 // (19) 0.01758
/*46 */         gen_update_nip(ctx, ctx->nip);                                                      // (7) 0.04297
/*48 */ #if defined(TARGET_PPC64)                                                                   // (17) 0.02148
/*50 */         tcg_gen_deposit_tl(msr, cpu_msr, cpu_gpr[rS(ctx->opcode)], 0, 32);                  // 0.0
/*52 */ #else                                                                                       // 0.0
/*54 */         tcg_gen_mov_tl(msr, cpu_gpr[rS(ctx->opcode)]);                                      // 0.0
/*56 */ #endif                                                                                      // 0.0
/*58 */         gen_helper_store_msr(cpu_env, msr);                                                 // 0.0
/*60 */         tcg_temp_free(msr);                                                                 // 0.0
/*62 */         /* Must stop the translation as machine state (may have) changed */                 // 0.0
/*64 */         /* Note that mtmsr is not always defined as context-synchronizing */                // 0.0
/*66 */         gen_stop_exception(ctx);                                                            // 0.0
/*68 */     }                                                                                       // 0.0
/*70 */ #endif                                                                                      // 0.0
/*72 */ }                                                                                           // 0.0

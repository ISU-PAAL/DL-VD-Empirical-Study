// commit message qemu@27a69bb088 (target=0, prob=0.010092826, correct=True): PPC: E500: Inject SPE exception on invalid SPE access
/*0  */ static inline void gen_evfsnabs(DisasContext *ctx)                                             // (4) 0.06531
/*2  */ {                                                                                              // (11) 0.004082
/*4  */     if (unlikely(!ctx->spe_enabled)) {                                                         // (5) 0.06531
/*6  */         gen_exception(ctx, POWERPC_EXCP_APU);                                                  // (3) 0.09388
/*8  */         return;                                                                                // (7) 0.03673
/*10 */     }                                                                                          // (8) 0.01633
/*12 */ #if defined(TARGET_PPC64)                                                                      // (6) 0.0449
/*14 */     tcg_gen_ori_tl(cpu_gpr[rD(ctx->opcode)], cpu_gpr[rA(ctx->opcode)], 0x8000000080000000LL);  // (0) 0.1959
/*16 */ #else                                                                                          // (9) 0.008163
/*18 */     tcg_gen_ori_tl(cpu_gpr[rD(ctx->opcode)], cpu_gpr[rA(ctx->opcode)], 0x80000000);            // (2) 0.1837
/*20 */     tcg_gen_ori_tl(cpu_gprh[rD(ctx->opcode)], cpu_gprh[rA(ctx->opcode)], 0x80000000);          // (1) 0.1918
/*22 */ #endif                                                                                         // (10) 0.008163
/*24 */ }                                                                                              // (12) 0.004082

// commit message qemu@27a69bb088 (target=0, prob=0.010015693, correct=True): PPC: E500: Inject SPE exception on invalid SPE access
/*0  */ static inline void gen_efdneg(DisasContext *ctx)                                                // (5) 0.06224
/*2  */ {                                                                                               // (11) 0.004149
/*4  */     if (unlikely(!ctx->spe_enabled)) {                                                          // (4) 0.06639
/*6  */         gen_exception(ctx, POWERPC_EXCP_APU);                                                   // (3) 0.09544
/*8  */         return;                                                                                 // (7) 0.03734
/*10 */     }                                                                                           // (8) 0.0166
/*12 */ #if defined(TARGET_PPC64)                                                                       // (6) 0.04564
/*14 */     tcg_gen_xori_tl(cpu_gpr[rD(ctx->opcode)], cpu_gpr[rA(ctx->opcode)], 0x8000000000000000LL);  // (0) 0.1992
/*16 */ #else                                                                                           // (10) 0.008299
/*18 */     tcg_gen_mov_tl(cpu_gpr[rD(ctx->opcode)], cpu_gpr[rA(ctx->opcode)]);                         // (2) 0.1701
/*20 */     tcg_gen_xori_tl(cpu_gprh[rD(ctx->opcode)], cpu_gprh[rA(ctx->opcode)], 0x80000000);          // (1) 0.1992
/*22 */ #endif                                                                                          // (9) 0.008299
/*24 */ }                                                                                               // (12) 0.004149

// commit message qemu@9b2fadda3e (target=1, prob=0.9990784, correct=True): ppc: Rework generation of priv and inval interrupts
/*0  */ static void gen_mfrom(DisasContext *ctx)                                       // (3) 0.07602
/*2  */ {                                                                              // (10) 0.005848
/*4  */ #if defined(CONFIG_USER_ONLY)                                                  // (5) 0.07018
/*6  */     gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);                           // (2) 0.1462
/*8  */ #else                                                                          // (8) 0.0117
/*10 */     if (unlikely(ctx->pr)) {                                                   // (4) 0.07602
/*12 */         gen_inval_exception(ctx, POWERPC_EXCP_PRIV_OPC);                       // (1) 0.1696
/*14 */         return;                                                                // (6) 0.05263
/*16 */     }                                                                          // (7) 0.02339
/*18 */     gen_helper_602_mfrom(cpu_gpr[rD(ctx->opcode)], cpu_gpr[rA(ctx->opcode)]);  // (0) 0.2398
/*20 */ #endif                                                                         // (9) 0.0117
/*22 */ }                                                                              // (11) 0.005848

// commit message qemu@9b2fadda3e (target=1, prob=0.9990563, correct=True): ppc: Rework generation of priv and inval interrupts
/*0  */ static void gen_mtdcrx(DisasContext *ctx)                                      // (7) 0.05747
/*2  */ {                                                                              // (14) 0.003831
/*4  */ #if defined(CONFIG_USER_ONLY)                                                  // (9) 0.04598
/*6  */     gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);                           // (3) 0.09195
/*8  */ #else                                                                          // (12) 0.007663
/*10 */     if (unlikely(ctx->pr)) {                                                   // (8) 0.04981
/*12 */         gen_inval_exception(ctx, POWERPC_EXCP_PRIV_REG);                       // (2) 0.1073
/*14 */         return;                                                                // (10) 0.03448
/*16 */     }                                                                          // (11) 0.01533
/*18 */     /* NIP cannot be restored if the memory exception comes from an helper */  // (6) 0.06897
/*20 */     gen_update_nip(ctx, ctx->nip - 4);                                         // (4) 0.07663
/*22 */     gen_helper_store_dcr(cpu_env, cpu_gpr[rA(ctx->opcode)],                    // (1) 0.1188
/*24 */                          cpu_gpr[rS(ctx->opcode)]);                            // (0) 0.1456
/*26 */     /* Note: Rc update flag set leads to undefined state of Rc0 */             // (5) 0.07663
/*28 */ #endif                                                                         // (13) 0.007663
/*30 */ }                                                                              // (15) 0.003831

// commit message qemu@e41029b378 (target=1, prob=0.6278666, correct=True): ppc: Don't update NIP in lswi/lswx/stswi/stswx
/*0  */ static void gen_dst(DisasContext *ctx)                      // (3) 0.1327
/*2  */ {                                                           // (6) 0.0102
/*4  */     if (rA(ctx->opcode) == 0) {                             // (1) 0.1735
/*6  */         gen_inval_exception(ctx, POWERPC_EXCP_INVAL_LSWX);  // (0) 0.3061
/*8  */     } else {                                                // (4) 0.06122
/*10 */         /* interpreted as no-op */                          // (2) 0.1429
/*12 */     }                                                       // (5) 0.04082
/*14 */ }                                                           // (7) 0.0102

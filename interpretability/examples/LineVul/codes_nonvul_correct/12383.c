// commit message qemu@075a1fe788 (target=0, prob=0.3458421, correct=True): target/mips: fix delay slot detection in gen_msa_branch()
/*0  */ static void gen_msa_branch(CPUMIPSState *env, DisasContext *ctx, uint32_t op1)  // (4) 0.05859
/*2  */ {                                                                               // (23) 0.001953
/*4  */     uint8_t df = (ctx->opcode >> 21) & 0x3;                                     // (9) 0.04297
/*6  */     uint8_t wt = (ctx->opcode >> 16) & 0x1f;                                    // (7) 0.04688
/*8  */     int64_t s16 = (int16_t)ctx->opcode;                                         // (10) 0.04102
/*12 */     check_msa_access(ctx);                                                      // (12) 0.02344
/*16 */     if (ctx->insn_flags & ISA_MIPS32R6 && ctx->hflags & MIPS_HFLAG_BMASK) {     // (2) 0.07422
/*18 */         generate_exception_end(ctx, EXCP_RI);                                   // (11) 0.04102
/*20 */         return;                                                                 // (17) 0.01758
/*22 */     }                                                                           // (22) 0.007812
/*24 */     switch (op1) {                                                              // (18) 0.01758
/*26 */     case OPC_BZ_V:                                                              // (13) 0.02344
/*28 */     case OPC_BNZ_V:                                                             // (14) 0.02344
/*30 */         {                                                                       // (20) 0.01562
/*32 */             TCGv_i64 t0 = tcg_temp_new_i64();                                   // (5) 0.05859
/*34 */             tcg_gen_or_i64(t0, msa_wr_d[wt<<1], msa_wr_d[(wt<<1)+1]);           // (0) 0.0957
/*36 */             tcg_gen_setcondi_i64((op1 == OPC_BZ_V) ?                            // (3) 0.06836
/*38 */                     TCG_COND_EQ : TCG_COND_NE, t0, t0, 0);                      // (1) 0.08594
/*40 */             tcg_gen_trunc_i64_tl(bcond, t0);                                    // (6) 0.05859
/*42 */             tcg_temp_free_i64(t0);                                              // (8) 0.04688
/*44 */         }                                                                       // (21) 0.01562
/*46 */         break;                                                                  // (19) 0.01758
/*48 */     case OPC_BZ_B:                                                              // (15) 0.02344
/*50 */     case OPC_BZ_H:                                                              // (16) 0.02344
/*52 */     case OPC_BZ_W:                                                              // 0.0
/*54 */     case OPC_BZ_D:                                                              // 0.0
/*56 */         gen_check_zero_element(bcond, df, wt);                                  // 0.0
/*58 */         break;                                                                  // 0.0
/*60 */     case OPC_BNZ_B:                                                             // 0.0
/*62 */     case OPC_BNZ_H:                                                             // 0.0
/*64 */     case OPC_BNZ_W:                                                             // 0.0
/*66 */     case OPC_BNZ_D:                                                             // 0.0
/*68 */         gen_check_zero_element(bcond, df, wt);                                  // 0.0
/*70 */         tcg_gen_setcondi_tl(TCG_COND_EQ, bcond, bcond, 0);                      // 0.0
/*72 */         break;                                                                  // 0.0
/*74 */     }                                                                           // 0.0
/*78 */     ctx->btarget = ctx->pc + (s16 << 2) + 4;                                    // 0.0
/*82 */     ctx->hflags |= MIPS_HFLAG_BC;                                               // 0.0
/*84 */     ctx->hflags |= MIPS_HFLAG_BDS32;                                            // 0.0
/*86 */ }                                                                               // 0.0

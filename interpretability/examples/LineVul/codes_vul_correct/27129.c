// commit message qemu@f678f671ba (target=1, prob=0.96033543, correct=True): target-tricore: add illegal opcode trap generation
/*0   */ static void decode_sys_interrupts(CPUTriCoreState *env, DisasContext *ctx)     // (3) 0.04688
/*2   */ {                                                                              // (30) 0.001953
/*4   */     uint32_t op2;                                                              // (17) 0.01953
/*6   */     uint32_t r1;                                                               // (18) 0.01953
/*8   */     TCGLabel *l1;                                                              // (19) 0.01953
/*10  */     TCGv tmp;                                                                  // (29) 0.01563
/*14  */     op2 = MASK_OP_SYS_OP2(ctx->opcode);                                        // (5) 0.04297
/*16  */     r1  = MASK_OP_SYS_S1D(ctx->opcode);                                        // (4) 0.04688
/*20  */     switch (op2) {                                                             // (20) 0.01758
/*22  */     case OPC2_32_SYS_DEBUG:                                                    // (13) 0.0293
/*24  */         /* raise EXCP_DEBUG */                                                 // (15) 0.02734
/*26  */         break;                                                                 // (21) 0.01758
/*28  */     case OPC2_32_SYS_DISABLE:                                                  // (8) 0.03125
/*30  */         tcg_gen_andi_tl(cpu_ICR, cpu_ICR, ~MASK_ICR_IE);                       // (0) 0.06836
/*32  */         break;                                                                 // (22) 0.01758
/*34  */     case OPC2_32_SYS_DSYNC:                                                    // (6) 0.0332
/*36  */         break;                                                                 // (23) 0.01758
/*38  */     case OPC2_32_SYS_ENABLE:                                                   // (9) 0.03125
/*40  */         tcg_gen_ori_tl(cpu_ICR, cpu_ICR, MASK_ICR_IE);                         // (1) 0.06641
/*42  */         break;                                                                 // (24) 0.01758
/*44  */     case OPC2_32_SYS_ISYNC:                                                    // (7) 0.0332
/*46  */         break;                                                                 // (25) 0.01758
/*48  */     case OPC2_32_SYS_NOP:                                                      // (10) 0.03125
/*50  */         break;                                                                 // (26) 0.01758
/*52  */     case OPC2_32_SYS_RET:                                                      // (14) 0.0293
/*54  */         gen_compute_branch(ctx, op2, 0, 0, 0, 0);                              // (2) 0.05469
/*56  */         break;                                                                 // (27) 0.01758
/*58  */     case OPC2_32_SYS_FRET:                                                     // (11) 0.03125
/*60  */         gen_fret(ctx);                                                         // (16) 0.02734
/*62  */         break;                                                                 // (28) 0.01758
/*64  */     case OPC2_32_SYS_RFE:                                                      // (12) 0.03125
/*66  */         gen_helper_rfe(cpu_env);                                               // 0.0
/*68  */         tcg_gen_exit_tb(0);                                                    // 0.0
/*70  */         ctx->bstate = BS_BRANCH;                                               // 0.0
/*72  */         break;                                                                 // 0.0
/*74  */     case OPC2_32_SYS_RFM:                                                      // 0.0
/*76  */         if ((ctx->hflags & TRICORE_HFLAG_KUU) == TRICORE_HFLAG_SM) {           // 0.0
/*78  */             tmp = tcg_temp_new();                                              // 0.0
/*80  */             l1 = gen_new_label();                                              // 0.0
/*84  */             tcg_gen_ld32u_tl(tmp, cpu_env, offsetof(CPUTriCoreState, DBGSR));  // 0.0
/*86  */             tcg_gen_andi_tl(tmp, tmp, MASK_DBGSR_DE);                          // 0.0
/*88  */             tcg_gen_brcondi_tl(TCG_COND_NE, tmp, 1, l1);                       // 0.0
/*90  */             gen_helper_rfm(cpu_env);                                           // 0.0
/*92  */             gen_set_label(l1);                                                 // 0.0
/*94  */             tcg_gen_exit_tb(0);                                                // 0.0
/*96  */             ctx->bstate = BS_BRANCH;                                           // 0.0
/*98  */             tcg_temp_free(tmp);                                                // 0.0
/*100 */         } else {                                                               // 0.0
/*102 */             /* generate privilege trap */                                      // 0.0
/*104 */         }                                                                      // 0.0
/*106 */         break;                                                                 // 0.0
/*108 */     case OPC2_32_SYS_RSLCX:                                                    // 0.0
/*110 */         gen_helper_rslcx(cpu_env);                                             // 0.0
/*112 */         break;                                                                 // 0.0
/*114 */     case OPC2_32_SYS_SVLCX:                                                    // 0.0
/*116 */         gen_helper_svlcx(cpu_env);                                             // 0.0
/*118 */         break;                                                                 // 0.0
/*120 */     case OPC2_32_SYS_RESTORE:                                                  // 0.0
/*122 */         if (tricore_feature(env, TRICORE_FEATURE_16)) {                        // 0.0
/*124 */             if ((ctx->hflags & TRICORE_HFLAG_KUU) == TRICORE_HFLAG_SM ||       // 0.0
/*126 */                 (ctx->hflags & TRICORE_HFLAG_KUU) == TRICORE_HFLAG_UM1) {      // 0.0
/*128 */                 tcg_gen_deposit_tl(cpu_ICR, cpu_ICR, cpu_gpr_d[r1], 8, 1);     // 0.0
/*130 */             } /* else raise privilege trap */                                  // 0.0
/*132 */         } /* else raise illegal opcode trap */                                 // 0.0
/*134 */         break;                                                                 // 0.0
/*136 */     case OPC2_32_SYS_TRAPSV:                                                   // 0.0
/*138 */         l1 = gen_new_label();                                                  // 0.0
/*140 */         tcg_gen_brcondi_tl(TCG_COND_GE, cpu_PSW_SV, 0, l1);                    // 0.0
/*142 */         generate_trap(ctx, TRAPC_ASSERT, TIN5_SOVF);                           // 0.0
/*144 */         gen_set_label(l1);                                                     // 0.0
/*146 */         break;                                                                 // 0.0
/*148 */     case OPC2_32_SYS_TRAPV:                                                    // 0.0
/*150 */         l1 = gen_new_label();                                                  // 0.0
/*152 */         tcg_gen_brcondi_tl(TCG_COND_GE, cpu_PSW_V, 0, l1);                     // 0.0
/*154 */         generate_trap(ctx, TRAPC_ASSERT, TIN5_OVF);                            // 0.0
/*156 */         gen_set_label(l1);                                                     // 0.0
/*158 */         break;                                                                 // 0.0
/*160 */     }                                                                          // 0.0
/*162 */ }                                                                              // 0.0

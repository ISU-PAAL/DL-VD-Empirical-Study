// commit message qemu@42a268c241 (target=0, prob=0.35540786, correct=True): tcg: Change translator-side labels to a pointer
/*0   */ static void gen_branch(DisasContext *ctx, int insn_bytes)                     // (11) 0.03711
/*2   */ {                                                                             // (22) 0.001953
/*4   */     if (ctx->hflags & MIPS_HFLAG_BMASK) {                                     // (8) 0.04102
/*6   */         int proc_hflags = ctx->hflags & MIPS_HFLAG_BMASK;                     // (2) 0.05664
/*8   */         /* Branches completion */                                             // (20) 0.02344
/*10  */         ctx->hflags &= ~MIPS_HFLAG_BMASK;                                     // (6) 0.04883
/*12  */         ctx->bstate = BS_BRANCH;                                              // (12) 0.03711
/*14  */         save_cpu_state(ctx, 0);                                               // (14) 0.0332
/*16  */         /* FIXME: Need to clear can_do_io.  */                                // (7) 0.04297
/*18  */         switch (proc_hflags & MIPS_HFLAG_BMASK_BASE) {                        // (4) 0.05469
/*20  */         case MIPS_HFLAG_FBNSLOT:                                              // (13) 0.03711
/*22  */             MIPS_DEBUG("forbidden slot");                                     // (10) 0.03906
/*24  */             gen_goto_tb(ctx, 0, ctx->pc + insn_bytes);                        // (1) 0.06445
/*26  */             break;                                                            // (18) 0.02539
/*28  */         case MIPS_HFLAG_B:                                                    // (15) 0.03125
/*30  */             /* unconditional branch */                                        // (17) 0.0293
/*32  */             MIPS_DEBUG("unconditional branch");                               // (9) 0.04102
/*34  */             if (proc_hflags & MIPS_HFLAG_BX) {                                // (5) 0.05469
/*36  */                 tcg_gen_xori_i32(hflags, hflags, MIPS_HFLAG_M16);             // (0) 0.08008
/*38  */             }                                                                 // (21) 0.02344
/*40  */             gen_goto_tb(ctx, 0, ctx->btarget);                                // (3) 0.05664
/*42  */             break;                                                            // (19) 0.02539
/*44  */         case MIPS_HFLAG_BL:                                                   // (16) 0.03125
/*46  */             /* blikely taken case */                                          // 0.0
/*48  */             MIPS_DEBUG("blikely branch taken");                               // 0.0
/*50  */             gen_goto_tb(ctx, 0, ctx->btarget);                                // 0.0
/*52  */             break;                                                            // 0.0
/*54  */         case MIPS_HFLAG_BC:                                                   // 0.0
/*56  */             /* Conditional branch */                                          // 0.0
/*58  */             MIPS_DEBUG("conditional branch");                                 // 0.0
/*60  */             {                                                                 // 0.0
/*62  */                 int l1 = gen_new_label();                                     // 0.0
/*66  */                 tcg_gen_brcondi_tl(TCG_COND_NE, bcond, 0, l1);                // 0.0
/*68  */                 gen_goto_tb(ctx, 1, ctx->pc + insn_bytes);                    // 0.0
/*70  */                 gen_set_label(l1);                                            // 0.0
/*72  */                 gen_goto_tb(ctx, 0, ctx->btarget);                            // 0.0
/*74  */             }                                                                 // 0.0
/*76  */             break;                                                            // 0.0
/*78  */         case MIPS_HFLAG_BR:                                                   // 0.0
/*80  */             /* unconditional branch to register */                            // 0.0
/*82  */             MIPS_DEBUG("branch to register");                                 // 0.0
/*84  */             if (ctx->insn_flags & (ASE_MIPS16 | ASE_MICROMIPS)) {             // 0.0
/*86  */                 TCGv t0 = tcg_temp_new();                                     // 0.0
/*88  */                 TCGv_i32 t1 = tcg_temp_new_i32();                             // 0.0
/*92  */                 tcg_gen_andi_tl(t0, btarget, 0x1);                            // 0.0
/*94  */                 tcg_gen_trunc_tl_i32(t1, t0);                                 // 0.0
/*96  */                 tcg_temp_free(t0);                                            // 0.0
/*98  */                 tcg_gen_andi_i32(hflags, hflags, ~(uint32_t)MIPS_HFLAG_M16);  // 0.0
/*100 */                 tcg_gen_shli_i32(t1, t1, MIPS_HFLAG_M16_SHIFT);               // 0.0
/*102 */                 tcg_gen_or_i32(hflags, hflags, t1);                           // 0.0
/*104 */                 tcg_temp_free_i32(t1);                                        // 0.0
/*108 */                 tcg_gen_andi_tl(cpu_PC, btarget, ~(target_ulong)0x1);         // 0.0
/*110 */             } else {                                                          // 0.0
/*112 */                 tcg_gen_mov_tl(cpu_PC, btarget);                              // 0.0
/*114 */             }                                                                 // 0.0
/*116 */             if (ctx->singlestep_enabled) {                                    // 0.0
/*118 */                 save_cpu_state(ctx, 0);                                       // 0.0
/*120 */                 gen_helper_0e0i(raise_exception, EXCP_DEBUG);                 // 0.0
/*122 */             }                                                                 // 0.0
/*124 */             tcg_gen_exit_tb(0);                                               // 0.0
/*126 */             break;                                                            // 0.0
/*128 */         default:                                                              // 0.0
/*130 */             MIPS_DEBUG("unknown branch");                                     // 0.0
/*132 */             break;                                                            // 0.0
/*134 */         }                                                                     // 0.0
/*136 */     }                                                                         // 0.0
/*138 */ }                                                                             // 0.0

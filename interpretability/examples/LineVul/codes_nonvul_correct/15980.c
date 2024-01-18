// commit message qemu@aea14095ea (target=0, prob=0.3423863, correct=True): target-mips: add BadInstr and BadInstrP support
/*0    */ static void decode_opc (CPUMIPSState *env, DisasContext *ctx)                          // (8) 0.03906
/*2    */ {                                                                                      // (25) 0.001953
/*4    */     int32_t offset;                                                                    // (20) 0.01758
/*6    */     int rs, rt, rd, sa;                                                                // (14) 0.02734
/*8    */     uint32_t op, op1;                                                                  // (18) 0.02344
/*10   */     int16_t imm;                                                                       // (19) 0.01758
/*14   */     /* make sure instructions are on a word boundary */                                // (16) 0.02539
/*16   */     if (ctx->pc & 0x3) {                                                               // (15) 0.02734
/*18   */         env->CP0_BadVAddr = ctx->pc;                                                   // (7) 0.04297
/*20   */         generate_exception(ctx, EXCP_AdEL);                                            // (9) 0.03906
/*22   */         return;                                                                        // (21) 0.01758
/*24   */     }                                                                                  // (22) 0.007812
/*28   */     /* Handle blikely not taken case */                                                // (17) 0.02344
/*30   */     if ((ctx->hflags & MIPS_HFLAG_BMASK_BASE) == MIPS_HFLAG_BL) {                      // (4) 0.06445
/*32   */         int l1 = gen_new_label();                                                      // (12) 0.0332
/*36   */         MIPS_DEBUG("blikely condition (" TARGET_FMT_lx ")", ctx->pc + 4);              // (3) 0.06445
/*38   */         tcg_gen_brcondi_tl(TCG_COND_NE, bcond, 0, l1);                                 // (2) 0.06641
/*40   */         tcg_gen_movi_i32(hflags, ctx->hflags & ~MIPS_HFLAG_BMASK);                     // (1) 0.07422
/*42   */         gen_goto_tb(ctx, 1, ctx->pc + 4);                                              // (5) 0.05078
/*44   */         gen_set_label(l1);                                                             // (13) 0.03125
/*46   */     }                                                                                  // (24) 0.007812
/*50   */     if (unlikely(qemu_loglevel_mask(CPU_LOG_TB_OP | CPU_LOG_TB_OP_OPT))) {             // (0) 0.07422
/*52   */         tcg_gen_debug_insn_start(ctx->pc);                                             // (6) 0.04492
/*54   */     }                                                                                  // (23) 0.007812
/*58   */     op = MASK_OP_MAJOR(ctx->opcode);                                                   // (10) 0.03711
/*60   */     rs = (ctx->opcode >> 21) & 0x1f;                                                   // (11) 0.03711
/*62   */     rt = (ctx->opcode >> 16) & 0x1f;                                                   // 0.0
/*64   */     rd = (ctx->opcode >> 11) & 0x1f;                                                   // 0.0
/*66   */     sa = (ctx->opcode >> 6) & 0x1f;                                                    // 0.0
/*68   */     imm = (int16_t)ctx->opcode;                                                        // 0.0
/*70   */     switch (op) {                                                                      // 0.0
/*72   */     case OPC_SPECIAL:                                                                  // 0.0
/*74   */         decode_opc_special(env, ctx);                                                  // 0.0
/*76   */         break;                                                                         // 0.0
/*78   */     case OPC_SPECIAL2:                                                                 // 0.0
/*80   */         decode_opc_special2_legacy(env, ctx);                                          // 0.0
/*82   */         break;                                                                         // 0.0
/*84   */     case OPC_SPECIAL3:                                                                 // 0.0
/*86   */         decode_opc_special3(env, ctx);                                                 // 0.0
/*88   */         break;                                                                         // 0.0
/*90   */     case OPC_REGIMM:                                                                   // 0.0
/*92   */         op1 = MASK_REGIMM(ctx->opcode);                                                // 0.0
/*94   */         switch (op1) {                                                                 // 0.0
/*96   */         case OPC_BLTZL: /* REGIMM branches */                                          // 0.0
/*98   */         case OPC_BGEZL:                                                                // 0.0
/*100  */         case OPC_BLTZALL:                                                              // 0.0
/*102  */         case OPC_BGEZALL:                                                              // 0.0
/*104  */             check_insn_opc_removed(ctx, ISA_MIPS32R6);                                 // 0.0
/*106  */         case OPC_BLTZ:                                                                 // 0.0
/*108  */         case OPC_BGEZ:                                                                 // 0.0
/*110  */             gen_compute_branch(ctx, op1, 4, rs, -1, imm << 2, 4);                      // 0.0
/*112  */             break;                                                                     // 0.0
/*114  */         case OPC_BLTZAL:                                                               // 0.0
/*116  */         case OPC_BGEZAL:                                                               // 0.0
/*118  */             if (ctx->insn_flags & ISA_MIPS32R6) {                                      // 0.0
/*120  */                 if (rs == 0) {                                                         // 0.0
/*122  */                     /* OPC_NAL, OPC_BAL */                                             // 0.0
/*124  */                     gen_compute_branch(ctx, op1, 4, 0, -1, imm << 2, 4);               // 0.0
/*126  */                 } else {                                                               // 0.0
/*128  */                     generate_exception(ctx, EXCP_RI);                                  // 0.0
/*130  */                 }                                                                      // 0.0
/*132  */             } else {                                                                   // 0.0
/*134  */                 gen_compute_branch(ctx, op1, 4, rs, -1, imm << 2, 4);                  // 0.0
/*136  */             }                                                                          // 0.0
/*138  */             break;                                                                     // 0.0
/*140  */         case OPC_TGEI ... OPC_TEQI: /* REGIMM traps */                                 // 0.0
/*142  */         case OPC_TNEI:                                                                 // 0.0
/*144  */             check_insn_opc_removed(ctx, ISA_MIPS32R6);                                 // 0.0
/*146  */             gen_trap(ctx, op1, rs, -1, imm);                                           // 0.0
/*148  */             break;                                                                     // 0.0
/*150  */         case OPC_SYNCI:                                                                // 0.0
/*152  */             check_insn(ctx, ISA_MIPS32R2);                                             // 0.0
/*154  */             /* Break the TB to be able to sync copied instructions                     // 0.0
/*156  */                immediately */                                                          // 0.0
/*158  */             ctx->bstate = BS_STOP;                                                     // 0.0
/*160  */             break;                                                                     // 0.0
/*162  */         case OPC_BPOSGE32:    /* MIPS DSP branch */                                    // 0.0
/*164  */ #if defined(TARGET_MIPS64)                                                             // 0.0
/*166  */         case OPC_BPOSGE64:                                                             // 0.0
/*168  */ #endif                                                                                 // 0.0
/*170  */             check_dsp(ctx);                                                            // 0.0
/*172  */             gen_compute_branch(ctx, op1, 4, -1, -2, (int32_t)imm << 2, 4);             // 0.0
/*174  */             break;                                                                     // 0.0
/*176  */ #if defined(TARGET_MIPS64)                                                             // 0.0
/*178  */         case OPC_DAHI:                                                                 // 0.0
/*180  */             check_insn(ctx, ISA_MIPS32R6);                                             // 0.0
/*182  */             check_mips_64(ctx);                                                        // 0.0
/*184  */             if (rs != 0) {                                                             // 0.0
/*186  */                 tcg_gen_addi_tl(cpu_gpr[rs], cpu_gpr[rs], (int64_t)imm << 32);         // 0.0
/*188  */             }                                                                          // 0.0
/*190  */             MIPS_DEBUG("dahi %s, %04x", regnames[rs], imm);                            // 0.0
/*192  */             break;                                                                     // 0.0
/*194  */         case OPC_DATI:                                                                 // 0.0
/*196  */             check_insn(ctx, ISA_MIPS32R6);                                             // 0.0
/*198  */             check_mips_64(ctx);                                                        // 0.0
/*200  */             if (rs != 0) {                                                             // 0.0
/*202  */                 tcg_gen_addi_tl(cpu_gpr[rs], cpu_gpr[rs], (int64_t)imm << 48);         // 0.0
/*204  */             }                                                                          // 0.0
/*206  */             MIPS_DEBUG("dati %s, %04x", regnames[rs], imm);                            // 0.0
/*208  */             break;                                                                     // 0.0
/*210  */ #endif                                                                                 // 0.0
/*212  */         default:            /* Invalid */                                              // 0.0
/*214  */             MIPS_INVAL("regimm");                                                      // 0.0
/*216  */             generate_exception(ctx, EXCP_RI);                                          // 0.0
/*218  */             break;                                                                     // 0.0
/*220  */         }                                                                              // 0.0
/*222  */         break;                                                                         // 0.0
/*224  */     case OPC_CP0:                                                                      // 0.0
/*226  */         check_cp0_enabled(ctx);                                                        // 0.0
/*228  */         op1 = MASK_CP0(ctx->opcode);                                                   // 0.0
/*230  */         switch (op1) {                                                                 // 0.0
/*232  */         case OPC_MFC0:                                                                 // 0.0
/*234  */         case OPC_MTC0:                                                                 // 0.0
/*236  */         case OPC_MFTR:                                                                 // 0.0
/*238  */         case OPC_MTTR:                                                                 // 0.0
/*240  */ #if defined(TARGET_MIPS64)                                                             // 0.0
/*242  */         case OPC_DMFC0:                                                                // 0.0
/*244  */         case OPC_DMTC0:                                                                // 0.0
/*246  */ #endif                                                                                 // 0.0
/*248  */ #ifndef CONFIG_USER_ONLY                                                               // 0.0
/*250  */             gen_cp0(env, ctx, op1, rt, rd);                                            // 0.0
/*252  */ #endif /* !CONFIG_USER_ONLY */                                                         // 0.0
/*254  */             break;                                                                     // 0.0
/*256  */         case OPC_C0_FIRST ... OPC_C0_LAST:                                             // 0.0
/*258  */ #ifndef CONFIG_USER_ONLY                                                               // 0.0
/*260  */             gen_cp0(env, ctx, MASK_C0(ctx->opcode), rt, rd);                           // 0.0
/*262  */ #endif /* !CONFIG_USER_ONLY */                                                         // 0.0
/*264  */             break;                                                                     // 0.0
/*266  */         case OPC_MFMC0:                                                                // 0.0
/*268  */ #ifndef CONFIG_USER_ONLY                                                               // 0.0
/*270  */             {                                                                          // 0.0
/*272  */                 uint32_t op2;                                                          // 0.0
/*274  */                 TCGv t0 = tcg_temp_new();                                              // 0.0
/*278  */                 op2 = MASK_MFMC0(ctx->opcode);                                         // 0.0
/*280  */                 switch (op2) {                                                         // 0.0
/*282  */                 case OPC_DMT:                                                          // 0.0
/*284  */                     check_insn(ctx, ASE_MT);                                           // 0.0
/*286  */                     gen_helper_dmt(t0);                                                // 0.0
/*288  */                     gen_store_gpr(t0, rt);                                             // 0.0
/*290  */                     break;                                                             // 0.0
/*292  */                 case OPC_EMT:                                                          // 0.0
/*294  */                     check_insn(ctx, ASE_MT);                                           // 0.0
/*296  */                     gen_helper_emt(t0);                                                // 0.0
/*298  */                     gen_store_gpr(t0, rt);                                             // 0.0
/*300  */                     break;                                                             // 0.0
/*302  */                 case OPC_DVPE:                                                         // 0.0
/*304  */                     check_insn(ctx, ASE_MT);                                           // 0.0
/*306  */                     gen_helper_dvpe(t0, cpu_env);                                      // 0.0
/*308  */                     gen_store_gpr(t0, rt);                                             // 0.0
/*310  */                     break;                                                             // 0.0
/*312  */                 case OPC_EVPE:                                                         // 0.0
/*314  */                     check_insn(ctx, ASE_MT);                                           // 0.0
/*316  */                     gen_helper_evpe(t0, cpu_env);                                      // 0.0
/*318  */                     gen_store_gpr(t0, rt);                                             // 0.0
/*320  */                     break;                                                             // 0.0
/*322  */                 case OPC_DI:                                                           // 0.0
/*324  */                     check_insn(ctx, ISA_MIPS32R2);                                     // 0.0
/*326  */                     save_cpu_state(ctx, 1);                                            // 0.0
/*328  */                     gen_helper_di(t0, cpu_env);                                        // 0.0
/*330  */                     gen_store_gpr(t0, rt);                                             // 0.0
/*332  */                     /* Stop translation as we may have switched the execution mode */  // 0.0
/*334  */                     ctx->bstate = BS_STOP;                                             // 0.0
/*336  */                     break;                                                             // 0.0
/*338  */                 case OPC_EI:                                                           // 0.0
/*340  */                     check_insn(ctx, ISA_MIPS32R2);                                     // 0.0
/*342  */                     save_cpu_state(ctx, 1);                                            // 0.0
/*344  */                     gen_helper_ei(t0, cpu_env);                                        // 0.0
/*346  */                     gen_store_gpr(t0, rt);                                             // 0.0
/*348  */                     /* Stop translation as we may have switched the execution mode */  // 0.0
/*350  */                     ctx->bstate = BS_STOP;                                             // 0.0
/*352  */                     break;                                                             // 0.0
/*354  */                 default:            /* Invalid */                                      // 0.0
/*356  */                     MIPS_INVAL("mfmc0");                                               // 0.0
/*358  */                     generate_exception(ctx, EXCP_RI);                                  // 0.0
/*360  */                     break;                                                             // 0.0
/*362  */                 }                                                                      // 0.0
/*364  */                 tcg_temp_free(t0);                                                     // 0.0
/*366  */             }                                                                          // 0.0
/*368  */ #endif /* !CONFIG_USER_ONLY */                                                         // 0.0
/*370  */             break;                                                                     // 0.0
/*372  */         case OPC_RDPGPR:                                                               // 0.0
/*374  */             check_insn(ctx, ISA_MIPS32R2);                                             // 0.0
/*376  */             gen_load_srsgpr(rt, rd);                                                   // 0.0
/*378  */             break;                                                                     // 0.0
/*380  */         case OPC_WRPGPR:                                                               // 0.0
/*382  */             check_insn(ctx, ISA_MIPS32R2);                                             // 0.0
/*384  */             gen_store_srsgpr(rt, rd);                                                  // 0.0
/*386  */             break;                                                                     // 0.0
/*388  */         default:                                                                       // 0.0
/*390  */             MIPS_INVAL("cp0");                                                         // 0.0
/*392  */             generate_exception(ctx, EXCP_RI);                                          // 0.0
/*394  */             break;                                                                     // 0.0
/*396  */         }                                                                              // 0.0
/*398  */         break;                                                                         // 0.0
/*400  */     case OPC_BOVC: /* OPC_BEQZALC, OPC_BEQC, OPC_ADDI */                               // 0.0
/*402  */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*404  */             /* OPC_BOVC, OPC_BEQZALC, OPC_BEQC */                                      // 0.0
/*406  */             gen_compute_compact_branch(ctx, op, rs, rt, imm << 2);                     // 0.0
/*408  */         } else {                                                                       // 0.0
/*410  */             /* OPC_ADDI */                                                             // 0.0
/*412  */             /* Arithmetic with immediate opcode */                                     // 0.0
/*414  */             gen_arith_imm(ctx, op, rt, rs, imm);                                       // 0.0
/*416  */         }                                                                              // 0.0
/*418  */         break;                                                                         // 0.0
/*420  */     case OPC_ADDIU:                                                                    // 0.0
/*422  */          gen_arith_imm(ctx, op, rt, rs, imm);                                          // 0.0
/*424  */          break;                                                                        // 0.0
/*426  */     case OPC_SLTI: /* Set on less than with immediate opcode */                        // 0.0
/*428  */     case OPC_SLTIU:                                                                    // 0.0
/*430  */          gen_slt_imm(ctx, op, rt, rs, imm);                                            // 0.0
/*432  */          break;                                                                        // 0.0
/*434  */     case OPC_ANDI: /* Arithmetic with immediate opcode */                              // 0.0
/*436  */     case OPC_LUI: /* OPC_AUI */                                                        // 0.0
/*438  */     case OPC_ORI:                                                                      // 0.0
/*440  */     case OPC_XORI:                                                                     // 0.0
/*442  */          gen_logic_imm(ctx, op, rt, rs, imm);                                          // 0.0
/*444  */          break;                                                                        // 0.0
/*446  */     case OPC_J ... OPC_JAL: /* Jump */                                                 // 0.0
/*448  */          offset = (int32_t)(ctx->opcode & 0x3FFFFFF) << 2;                             // 0.0
/*450  */          gen_compute_branch(ctx, op, 4, rs, rt, offset, 4);                            // 0.0
/*452  */          break;                                                                        // 0.0
/*454  */     /* Branch */                                                                       // 0.0
/*456  */     case OPC_BLEZC: /* OPC_BGEZC, OPC_BGEC, OPC_BLEZL */                               // 0.0
/*458  */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*460  */             if (rt == 0) {                                                             // 0.0
/*462  */                 generate_exception(ctx, EXCP_RI);                                      // 0.0
/*464  */                 break;                                                                 // 0.0
/*466  */             }                                                                          // 0.0
/*468  */             /* OPC_BLEZC, OPC_BGEZC, OPC_BGEC */                                       // 0.0
/*470  */             gen_compute_compact_branch(ctx, op, rs, rt, imm << 2);                     // 0.0
/*472  */         } else {                                                                       // 0.0
/*474  */             /* OPC_BLEZL */                                                            // 0.0
/*476  */             gen_compute_branch(ctx, op, 4, rs, rt, imm << 2, 4);                       // 0.0
/*478  */         }                                                                              // 0.0
/*480  */         break;                                                                         // 0.0
/*482  */     case OPC_BGTZC: /* OPC_BLTZC, OPC_BLTC, OPC_BGTZL */                               // 0.0
/*484  */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*486  */             if (rt == 0) {                                                             // 0.0
/*488  */                 generate_exception(ctx, EXCP_RI);                                      // 0.0
/*490  */                 break;                                                                 // 0.0
/*492  */             }                                                                          // 0.0
/*494  */             /* OPC_BGTZC, OPC_BLTZC, OPC_BLTC */                                       // 0.0
/*496  */             gen_compute_compact_branch(ctx, op, rs, rt, imm << 2);                     // 0.0
/*498  */         } else {                                                                       // 0.0
/*500  */             /* OPC_BGTZL */                                                            // 0.0
/*502  */             gen_compute_branch(ctx, op, 4, rs, rt, imm << 2, 4);                       // 0.0
/*504  */         }                                                                              // 0.0
/*506  */         break;                                                                         // 0.0
/*508  */     case OPC_BLEZALC: /* OPC_BGEZALC, OPC_BGEUC, OPC_BLEZ */                           // 0.0
/*510  */         if (rt == 0) {                                                                 // 0.0
/*512  */             /* OPC_BLEZ */                                                             // 0.0
/*514  */             gen_compute_branch(ctx, op, 4, rs, rt, imm << 2, 4);                       // 0.0
/*516  */         } else {                                                                       // 0.0
/*518  */             check_insn(ctx, ISA_MIPS32R6);                                             // 0.0
/*520  */             /* OPC_BLEZALC, OPC_BGEZALC, OPC_BGEUC */                                  // 0.0
/*522  */             gen_compute_compact_branch(ctx, op, rs, rt, imm << 2);                     // 0.0
/*524  */         }                                                                              // 0.0
/*526  */         break;                                                                         // 0.0
/*528  */     case OPC_BGTZALC: /* OPC_BLTZALC, OPC_BLTUC, OPC_BGTZ */                           // 0.0
/*530  */         if (rt == 0) {                                                                 // 0.0
/*532  */             /* OPC_BGTZ */                                                             // 0.0
/*534  */             gen_compute_branch(ctx, op, 4, rs, rt, imm << 2, 4);                       // 0.0
/*536  */         } else {                                                                       // 0.0
/*538  */             check_insn(ctx, ISA_MIPS32R6);                                             // 0.0
/*540  */             /* OPC_BGTZALC, OPC_BLTZALC, OPC_BLTUC */                                  // 0.0
/*542  */             gen_compute_compact_branch(ctx, op, rs, rt, imm << 2);                     // 0.0
/*544  */         }                                                                              // 0.0
/*546  */         break;                                                                         // 0.0
/*548  */     case OPC_BEQL:                                                                     // 0.0
/*550  */     case OPC_BNEL:                                                                     // 0.0
/*552  */          check_insn_opc_removed(ctx, ISA_MIPS32R6);                                    // 0.0
/*554  */     case OPC_BEQ:                                                                      // 0.0
/*556  */     case OPC_BNE:                                                                      // 0.0
/*558  */          gen_compute_branch(ctx, op, 4, rs, rt, imm << 2, 4);                          // 0.0
/*560  */          break;                                                                        // 0.0
/*562  */     case OPC_LWL: /* Load and stores */                                                // 0.0
/*564  */     case OPC_LWR:                                                                      // 0.0
/*566  */     case OPC_LL:                                                                       // 0.0
/*568  */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*570  */     case OPC_LB ... OPC_LH:                                                            // 0.0
/*572  */     case OPC_LW ... OPC_LHU:                                                           // 0.0
/*574  */          gen_ld(ctx, op, rt, rs, imm);                                                 // 0.0
/*576  */          break;                                                                        // 0.0
/*578  */     case OPC_SWL:                                                                      // 0.0
/*580  */     case OPC_SWR:                                                                      // 0.0
/*582  */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*584  */     case OPC_SB ... OPC_SH:                                                            // 0.0
/*586  */     case OPC_SW:                                                                       // 0.0
/*588  */          gen_st(ctx, op, rt, rs, imm);                                                 // 0.0
/*590  */          break;                                                                        // 0.0
/*592  */     case OPC_SC:                                                                       // 0.0
/*594  */          check_insn_opc_removed(ctx, ISA_MIPS32R6);                                    // 0.0
/*596  */          gen_st_cond(ctx, op, rt, rs, imm);                                            // 0.0
/*598  */          break;                                                                        // 0.0
/*600  */     case OPC_CACHE:                                                                    // 0.0
/*602  */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*604  */         check_cp0_enabled(ctx);                                                        // 0.0
/*606  */         check_insn(ctx, ISA_MIPS3 | ISA_MIPS32);                                       // 0.0
/*608  */         /* Treat as NOP. */                                                            // 0.0
/*610  */         break;                                                                         // 0.0
/*612  */     case OPC_PREF:                                                                     // 0.0
/*614  */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*616  */         check_insn(ctx, ISA_MIPS4 | ISA_MIPS32);                                       // 0.0
/*618  */         /* Treat as NOP. */                                                            // 0.0
/*620  */         break;                                                                         // 0.0
/*624  */     /* Floating point (COP1). */                                                       // 0.0
/*626  */     case OPC_LWC1:                                                                     // 0.0
/*628  */     case OPC_LDC1:                                                                     // 0.0
/*630  */     case OPC_SWC1:                                                                     // 0.0
/*632  */     case OPC_SDC1:                                                                     // 0.0
/*634  */         gen_cop1_ldst(ctx, op, rt, rs, imm);                                           // 0.0
/*636  */         break;                                                                         // 0.0
/*640  */     case OPC_CP1:                                                                      // 0.0
/*642  */         if (ctx->CP0_Config1 & (1 << CP0C1_FP)) {                                      // 0.0
/*644  */             check_cp1_enabled(ctx);                                                    // 0.0
/*646  */             op1 = MASK_CP1(ctx->opcode);                                               // 0.0
/*648  */             switch (op1) {                                                             // 0.0
/*650  */             case OPC_MFHC1:                                                            // 0.0
/*652  */             case OPC_MTHC1:                                                            // 0.0
/*654  */                 check_insn(ctx, ISA_MIPS32R2);                                         // 0.0
/*656  */             case OPC_MFC1:                                                             // 0.0
/*658  */             case OPC_CFC1:                                                             // 0.0
/*660  */             case OPC_MTC1:                                                             // 0.0
/*662  */             case OPC_CTC1:                                                             // 0.0
/*664  */                 gen_cp1(ctx, op1, rt, rd);                                             // 0.0
/*666  */                 break;                                                                 // 0.0
/*668  */ #if defined(TARGET_MIPS64)                                                             // 0.0
/*670  */             case OPC_DMFC1:                                                            // 0.0
/*672  */             case OPC_DMTC1:                                                            // 0.0
/*674  */                 check_insn(ctx, ISA_MIPS3);                                            // 0.0
/*676  */                 gen_cp1(ctx, op1, rt, rd);                                             // 0.0
/*678  */                 break;                                                                 // 0.0
/*680  */ #endif                                                                                 // 0.0
/*682  */             case OPC_BC1EQZ: /* OPC_BC1ANY2 */                                         // 0.0
/*684  */                 if (ctx->insn_flags & ISA_MIPS32R6) {                                  // 0.0
/*686  */                     /* OPC_BC1EQZ */                                                   // 0.0
/*688  */                     gen_compute_branch1_r6(ctx, MASK_CP1(ctx->opcode),                 // 0.0
/*690  */                                     rt, imm << 2);                                     // 0.0
/*692  */                 } else {                                                               // 0.0
/*694  */                     /* OPC_BC1ANY2 */                                                  // 0.0
/*696  */                     check_cop1x(ctx);                                                  // 0.0
/*698  */                     check_insn(ctx, ASE_MIPS3D);                                       // 0.0
/*700  */                     gen_compute_branch1(ctx, MASK_BC1(ctx->opcode),                    // 0.0
/*702  */                                     (rt >> 2) & 0x7, imm << 2);                        // 0.0
/*704  */                 }                                                                      // 0.0
/*706  */                 break;                                                                 // 0.0
/*708  */             case OPC_BC1NEZ:                                                           // 0.0
/*710  */                 check_insn(ctx, ISA_MIPS32R6);                                         // 0.0
/*712  */                 gen_compute_branch1_r6(ctx, MASK_CP1(ctx->opcode),                     // 0.0
/*714  */                                 rt, imm << 2);                                         // 0.0
/*716  */                 break;                                                                 // 0.0
/*718  */             case OPC_BC1ANY4:                                                          // 0.0
/*720  */                 check_insn_opc_removed(ctx, ISA_MIPS32R6);                             // 0.0
/*722  */                 check_cop1x(ctx);                                                      // 0.0
/*724  */                 check_insn(ctx, ASE_MIPS3D);                                           // 0.0
/*726  */                 /* fall through */                                                     // 0.0
/*728  */             case OPC_BC1:                                                              // 0.0
/*730  */                 check_insn_opc_removed(ctx, ISA_MIPS32R6);                             // 0.0
/*732  */                 gen_compute_branch1(ctx, MASK_BC1(ctx->opcode),                        // 0.0
/*734  */                                     (rt >> 2) & 0x7, imm << 2);                        // 0.0
/*736  */                 break;                                                                 // 0.0
/*738  */             case OPC_PS_FMT:                                                           // 0.0
/*740  */                 check_insn_opc_removed(ctx, ISA_MIPS32R6);                             // 0.0
/*742  */             case OPC_S_FMT:                                                            // 0.0
/*744  */             case OPC_D_FMT:                                                            // 0.0
/*746  */                 gen_farith(ctx, ctx->opcode & FOP(0x3f, 0x1f), rt, rd, sa,             // 0.0
/*748  */                            (imm >> 8) & 0x7);                                          // 0.0
/*750  */                 break;                                                                 // 0.0
/*752  */             case OPC_W_FMT:                                                            // 0.0
/*754  */             case OPC_L_FMT:                                                            // 0.0
/*756  */             {                                                                          // 0.0
/*758  */                 int r6_op = ctx->opcode & FOP(0x3f, 0x1f);                             // 0.0
/*760  */                 if (ctx->insn_flags & ISA_MIPS32R6) {                                  // 0.0
/*762  */                     switch (r6_op) {                                                   // 0.0
/*764  */                     case R6_OPC_CMP_AF_S:                                              // 0.0
/*766  */                     case R6_OPC_CMP_UN_S:                                              // 0.0
/*768  */                     case R6_OPC_CMP_EQ_S:                                              // 0.0
/*770  */                     case R6_OPC_CMP_UEQ_S:                                             // 0.0
/*772  */                     case R6_OPC_CMP_LT_S:                                              // 0.0
/*774  */                     case R6_OPC_CMP_ULT_S:                                             // 0.0
/*776  */                     case R6_OPC_CMP_LE_S:                                              // 0.0
/*778  */                     case R6_OPC_CMP_ULE_S:                                             // 0.0
/*780  */                     case R6_OPC_CMP_SAF_S:                                             // 0.0
/*782  */                     case R6_OPC_CMP_SUN_S:                                             // 0.0
/*784  */                     case R6_OPC_CMP_SEQ_S:                                             // 0.0
/*786  */                     case R6_OPC_CMP_SEUQ_S:                                            // 0.0
/*788  */                     case R6_OPC_CMP_SLT_S:                                             // 0.0
/*790  */                     case R6_OPC_CMP_SULT_S:                                            // 0.0
/*792  */                     case R6_OPC_CMP_SLE_S:                                             // 0.0
/*794  */                     case R6_OPC_CMP_SULE_S:                                            // 0.0
/*796  */                     case R6_OPC_CMP_OR_S:                                              // 0.0
/*798  */                     case R6_OPC_CMP_UNE_S:                                             // 0.0
/*800  */                     case R6_OPC_CMP_NE_S:                                              // 0.0
/*802  */                     case R6_OPC_CMP_SOR_S:                                             // 0.0
/*804  */                     case R6_OPC_CMP_SUNE_S:                                            // 0.0
/*806  */                     case R6_OPC_CMP_SNE_S:                                             // 0.0
/*808  */                         gen_r6_cmp_s(ctx, ctx->opcode & 0x1f, rt, rd, sa);             // 0.0
/*810  */                         break;                                                         // 0.0
/*812  */                     case R6_OPC_CMP_AF_D:                                              // 0.0
/*814  */                     case R6_OPC_CMP_UN_D:                                              // 0.0
/*816  */                     case R6_OPC_CMP_EQ_D:                                              // 0.0
/*818  */                     case R6_OPC_CMP_UEQ_D:                                             // 0.0
/*820  */                     case R6_OPC_CMP_LT_D:                                              // 0.0
/*822  */                     case R6_OPC_CMP_ULT_D:                                             // 0.0
/*824  */                     case R6_OPC_CMP_LE_D:                                              // 0.0
/*826  */                     case R6_OPC_CMP_ULE_D:                                             // 0.0
/*828  */                     case R6_OPC_CMP_SAF_D:                                             // 0.0
/*830  */                     case R6_OPC_CMP_SUN_D:                                             // 0.0
/*832  */                     case R6_OPC_CMP_SEQ_D:                                             // 0.0
/*834  */                     case R6_OPC_CMP_SEUQ_D:                                            // 0.0
/*836  */                     case R6_OPC_CMP_SLT_D:                                             // 0.0
/*838  */                     case R6_OPC_CMP_SULT_D:                                            // 0.0
/*840  */                     case R6_OPC_CMP_SLE_D:                                             // 0.0
/*842  */                     case R6_OPC_CMP_SULE_D:                                            // 0.0
/*844  */                     case R6_OPC_CMP_OR_D:                                              // 0.0
/*846  */                     case R6_OPC_CMP_UNE_D:                                             // 0.0
/*848  */                     case R6_OPC_CMP_NE_D:                                              // 0.0
/*850  */                     case R6_OPC_CMP_SOR_D:                                             // 0.0
/*852  */                     case R6_OPC_CMP_SUNE_D:                                            // 0.0
/*854  */                     case R6_OPC_CMP_SNE_D:                                             // 0.0
/*856  */                         gen_r6_cmp_d(ctx, ctx->opcode & 0x1f, rt, rd, sa);             // 0.0
/*858  */                         break;                                                         // 0.0
/*860  */                     default:                                                           // 0.0
/*862  */                         gen_farith(ctx, ctx->opcode & FOP(0x3f, 0x1f), rt, rd, sa,     // 0.0
/*864  */                                                        (imm >> 8) & 0x7);              // 0.0
/*866  */                         break;                                                         // 0.0
/*868  */                     }                                                                  // 0.0
/*870  */                 } else {                                                               // 0.0
/*872  */                     gen_farith(ctx, ctx->opcode & FOP(0x3f, 0x1f), rt, rd, sa,         // 0.0
/*874  */                                (imm >> 8) & 0x7);                                      // 0.0
/*876  */                 }                                                                      // 0.0
/*878  */                 break;                                                                 // 0.0
/*880  */             }                                                                          // 0.0
/*882  */             default:                                                                   // 0.0
/*884  */                 MIPS_INVAL("cp1");                                                     // 0.0
/*886  */                 generate_exception (ctx, EXCP_RI);                                     // 0.0
/*888  */                 break;                                                                 // 0.0
/*890  */             }                                                                          // 0.0
/*892  */         } else {                                                                       // 0.0
/*894  */             generate_exception_err(ctx, EXCP_CpU, 1);                                  // 0.0
/*896  */         }                                                                              // 0.0
/*898  */         break;                                                                         // 0.0
/*902  */     /* Compact branches [R6] and COP2 [non-R6] */                                      // 0.0
/*904  */     case OPC_BC: /* OPC_LWC2 */                                                        // 0.0
/*906  */     case OPC_BALC: /* OPC_SWC2 */                                                      // 0.0
/*908  */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*910  */             /* OPC_BC, OPC_BALC */                                                     // 0.0
/*912  */             gen_compute_compact_branch(ctx, op, 0, 0,                                  // 0.0
/*914  */                                        sextract32(ctx->opcode << 2, 0, 28));           // 0.0
/*916  */         } else {                                                                       // 0.0
/*918  */             /* OPC_LWC2, OPC_SWC2 */                                                   // 0.0
/*920  */             /* COP2: Not implemented. */                                               // 0.0
/*922  */             generate_exception_err(ctx, EXCP_CpU, 2);                                  // 0.0
/*924  */         }                                                                              // 0.0
/*926  */         break;                                                                         // 0.0
/*928  */     case OPC_BEQZC: /* OPC_JIC, OPC_LDC2 */                                            // 0.0
/*930  */     case OPC_BNEZC: /* OPC_JIALC, OPC_SDC2 */                                          // 0.0
/*932  */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*934  */             if (rs != 0) {                                                             // 0.0
/*936  */                 /* OPC_BEQZC, OPC_BNEZC */                                             // 0.0
/*938  */                 gen_compute_compact_branch(ctx, op, rs, 0,                             // 0.0
/*940  */                                            sextract32(ctx->opcode << 2, 0, 23));       // 0.0
/*942  */             } else {                                                                   // 0.0
/*944  */                 /* OPC_JIC, OPC_JIALC */                                               // 0.0
/*946  */                 gen_compute_compact_branch(ctx, op, 0, rt, imm);                       // 0.0
/*948  */             }                                                                          // 0.0
/*950  */         } else {                                                                       // 0.0
/*952  */             /* OPC_LWC2, OPC_SWC2 */                                                   // 0.0
/*954  */             /* COP2: Not implemented. */                                               // 0.0
/*956  */             generate_exception_err(ctx, EXCP_CpU, 2);                                  // 0.0
/*958  */         }                                                                              // 0.0
/*960  */         break;                                                                         // 0.0
/*962  */     case OPC_CP2:                                                                      // 0.0
/*964  */         check_insn(ctx, INSN_LOONGSON2F);                                              // 0.0
/*966  */         /* Note that these instructions use different fields.  */                      // 0.0
/*968  */         gen_loongson_multimedia(ctx, sa, rd, rt);                                      // 0.0
/*970  */         break;                                                                         // 0.0
/*974  */     case OPC_CP3:                                                                      // 0.0
/*976  */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*978  */         if (ctx->CP0_Config1 & (1 << CP0C1_FP)) {                                      // 0.0
/*980  */             check_cp1_enabled(ctx);                                                    // 0.0
/*982  */             op1 = MASK_CP3(ctx->opcode);                                               // 0.0
/*984  */             switch (op1) {                                                             // 0.0
/*986  */             case OPC_LWXC1:                                                            // 0.0
/*988  */             case OPC_LDXC1:                                                            // 0.0
/*990  */             case OPC_LUXC1:                                                            // 0.0
/*992  */             case OPC_SWXC1:                                                            // 0.0
/*994  */             case OPC_SDXC1:                                                            // 0.0
/*996  */             case OPC_SUXC1:                                                            // 0.0
/*998  */                 gen_flt3_ldst(ctx, op1, sa, rd, rs, rt);                               // 0.0
/*1000 */                 break;                                                                 // 0.0
/*1002 */             case OPC_PREFX:                                                            // 0.0
/*1004 */                 /* Treat as NOP. */                                                    // 0.0
/*1006 */                 break;                                                                 // 0.0
/*1008 */             case OPC_ALNV_PS:                                                          // 0.0
/*1010 */             case OPC_MADD_S:                                                           // 0.0
/*1012 */             case OPC_MADD_D:                                                           // 0.0
/*1014 */             case OPC_MADD_PS:                                                          // 0.0
/*1016 */             case OPC_MSUB_S:                                                           // 0.0
/*1018 */             case OPC_MSUB_D:                                                           // 0.0
/*1020 */             case OPC_MSUB_PS:                                                          // 0.0
/*1022 */             case OPC_NMADD_S:                                                          // 0.0
/*1024 */             case OPC_NMADD_D:                                                          // 0.0
/*1026 */             case OPC_NMADD_PS:                                                         // 0.0
/*1028 */             case OPC_NMSUB_S:                                                          // 0.0
/*1030 */             case OPC_NMSUB_D:                                                          // 0.0
/*1032 */             case OPC_NMSUB_PS:                                                         // 0.0
/*1034 */                 gen_flt3_arith(ctx, op1, sa, rs, rd, rt);                              // 0.0
/*1036 */                 break;                                                                 // 0.0
/*1038 */             default:                                                                   // 0.0
/*1040 */                 MIPS_INVAL("cp3");                                                     // 0.0
/*1042 */                 generate_exception (ctx, EXCP_RI);                                     // 0.0
/*1044 */                 break;                                                                 // 0.0
/*1046 */             }                                                                          // 0.0
/*1048 */         } else {                                                                       // 0.0
/*1050 */             generate_exception_err(ctx, EXCP_CpU, 1);                                  // 0.0
/*1052 */         }                                                                              // 0.0
/*1054 */         break;                                                                         // 0.0
/*1058 */ #if defined(TARGET_MIPS64)                                                             // 0.0
/*1060 */     /* MIPS64 opcodes */                                                               // 0.0
/*1062 */     case OPC_LDL ... OPC_LDR:                                                          // 0.0
/*1064 */     case OPC_LLD:                                                                      // 0.0
/*1066 */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*1068 */     case OPC_LWU:                                                                      // 0.0
/*1070 */     case OPC_LD:                                                                       // 0.0
/*1072 */         check_insn(ctx, ISA_MIPS3);                                                    // 0.0
/*1074 */         check_mips_64(ctx);                                                            // 0.0
/*1076 */         gen_ld(ctx, op, rt, rs, imm);                                                  // 0.0
/*1078 */         break;                                                                         // 0.0
/*1080 */     case OPC_SDL ... OPC_SDR:                                                          // 0.0
/*1082 */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*1084 */     case OPC_SD:                                                                       // 0.0
/*1086 */         check_insn(ctx, ISA_MIPS3);                                                    // 0.0
/*1088 */         check_mips_64(ctx);                                                            // 0.0
/*1090 */         gen_st(ctx, op, rt, rs, imm);                                                  // 0.0
/*1092 */         break;                                                                         // 0.0
/*1094 */     case OPC_SCD:                                                                      // 0.0
/*1096 */         check_insn_opc_removed(ctx, ISA_MIPS32R6);                                     // 0.0
/*1098 */         check_insn(ctx, ISA_MIPS3);                                                    // 0.0
/*1100 */         check_mips_64(ctx);                                                            // 0.0
/*1102 */         gen_st_cond(ctx, op, rt, rs, imm);                                             // 0.0
/*1104 */         break;                                                                         // 0.0
/*1106 */     case OPC_BNVC: /* OPC_BNEZALC, OPC_BNEC, OPC_DADDI */                              // 0.0
/*1108 */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*1110 */             /* OPC_BNVC, OPC_BNEZALC, OPC_BNEC */                                      // 0.0
/*1112 */             gen_compute_compact_branch(ctx, op, rs, rt, imm << 2);                     // 0.0
/*1114 */         } else {                                                                       // 0.0
/*1116 */             /* OPC_DADDI */                                                            // 0.0
/*1118 */             check_insn(ctx, ISA_MIPS3);                                                // 0.0
/*1120 */             check_mips_64(ctx);                                                        // 0.0
/*1122 */             gen_arith_imm(ctx, op, rt, rs, imm);                                       // 0.0
/*1124 */         }                                                                              // 0.0
/*1126 */         break;                                                                         // 0.0
/*1128 */     case OPC_DADDIU:                                                                   // 0.0
/*1130 */         check_insn(ctx, ISA_MIPS3);                                                    // 0.0
/*1132 */         check_mips_64(ctx);                                                            // 0.0
/*1134 */         gen_arith_imm(ctx, op, rt, rs, imm);                                           // 0.0
/*1136 */         break;                                                                         // 0.0
/*1138 */ #else                                                                                  // 0.0
/*1140 */     case OPC_BNVC: /* OPC_BNEZALC, OPC_BNEC */                                         // 0.0
/*1142 */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*1144 */             gen_compute_compact_branch(ctx, op, rs, rt, imm << 2);                     // 0.0
/*1146 */         } else {                                                                       // 0.0
/*1148 */             MIPS_INVAL("major opcode");                                                // 0.0
/*1150 */             generate_exception(ctx, EXCP_RI);                                          // 0.0
/*1152 */         }                                                                              // 0.0
/*1154 */         break;                                                                         // 0.0
/*1156 */ #endif                                                                                 // 0.0
/*1158 */     case OPC_DAUI: /* OPC_JALX */                                                      // 0.0
/*1160 */         if (ctx->insn_flags & ISA_MIPS32R6) {                                          // 0.0
/*1162 */ #if defined(TARGET_MIPS64)                                                             // 0.0
/*1164 */             /* OPC_DAUI */                                                             // 0.0
/*1166 */             check_mips_64(ctx);                                                        // 0.0
/*1168 */             if (rt != 0) {                                                             // 0.0
/*1170 */                 TCGv t0 = tcg_temp_new();                                              // 0.0
/*1172 */                 gen_load_gpr(t0, rs);                                                  // 0.0
/*1174 */                 tcg_gen_addi_tl(cpu_gpr[rt], t0, imm << 16);                           // 0.0
/*1176 */                 tcg_temp_free(t0);                                                     // 0.0
/*1178 */             }                                                                          // 0.0
/*1180 */             MIPS_DEBUG("daui %s, %s, %04x", regnames[rt], regnames[rs], imm);          // 0.0
/*1182 */ #else                                                                                  // 0.0
/*1184 */             generate_exception(ctx, EXCP_RI);                                          // 0.0
/*1186 */             MIPS_INVAL("major opcode");                                                // 0.0
/*1188 */ #endif                                                                                 // 0.0
/*1190 */         } else {                                                                       // 0.0
/*1192 */             /* OPC_JALX */                                                             // 0.0
/*1194 */             check_insn(ctx, ASE_MIPS16 | ASE_MICROMIPS);                               // 0.0
/*1196 */             offset = (int32_t)(ctx->opcode & 0x3FFFFFF) << 2;                          // 0.0
/*1198 */             gen_compute_branch(ctx, op, 4, rs, rt, offset, 4);                         // 0.0
/*1200 */         }                                                                              // 0.0
/*1202 */         break;                                                                         // 0.0
/*1204 */     case OPC_MDMX:                                                                     // 0.0
/*1206 */         check_insn(ctx, ASE_MDMX);                                                     // 0.0
/*1208 */         /* MDMX: Not implemented. */                                                   // 0.0
/*1210 */         break;                                                                         // 0.0
/*1212 */     case OPC_PCREL:                                                                    // 0.0
/*1214 */         check_insn(ctx, ISA_MIPS32R6);                                                 // 0.0
/*1216 */         gen_pcrel(ctx, rs, imm);                                                       // 0.0
/*1218 */         break;                                                                         // 0.0
/*1220 */     default:            /* Invalid */                                                  // 0.0
/*1222 */         MIPS_INVAL("major opcode");                                                    // 0.0
/*1224 */         generate_exception(ctx, EXCP_RI);                                              // 0.0
/*1226 */         break;                                                                         // 0.0
/*1228 */     }                                                                                  // 0.0
/*1230 */ }                                                                                      // 0.0

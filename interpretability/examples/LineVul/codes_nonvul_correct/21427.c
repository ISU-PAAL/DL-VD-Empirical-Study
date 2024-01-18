// commit message qemu@03e6e50177 (target=0, prob=0.41212785, correct=True): MIPS/user: Fix reset CPU state initialization
/*0   */ void cpu_state_reset(CPUMIPSState *env)                                      // (17) 0.02734
/*2   */ {                                                                            // (23) 0.001953
/*4   */     if (qemu_loglevel_mask(CPU_LOG_RESET)) {                                 // (5) 0.04492
/*6   */         qemu_log("CPU Reset (CPU %d)\n", env->cpu_index);                    // (3) 0.05469
/*8   */         log_cpu_state(env, 0);                                               // (15) 0.0332
/*10  */     }                                                                        // (21) 0.007812
/*14  */     memset(env, 0, offsetof(CPUMIPSState, breakpoints));                     // (14) 0.04102
/*16  */     tlb_flush(env, 1);                                                       // (19) 0.02344
/*20  */     /* Reset registers to their default values */                            // (20) 0.02148
/*22  */     env->CP0_PRid = env->cpu_model->CP0_PRid;                                // (6) 0.04492
/*24  */     env->CP0_Config0 = env->cpu_model->CP0_Config0;                          // (7) 0.04492
/*26  */ #ifdef TARGET_WORDS_BIGENDIAN                                                // (18) 0.02539
/*28  */     env->CP0_Config0 |= (1 << CP0C0_BE);                                     // (13) 0.04297
/*30  */ #endif                                                                       // (22) 0.003906
/*32  */     env->CP0_Config1 = env->cpu_model->CP0_Config1;                          // (8) 0.04492
/*34  */     env->CP0_Config2 = env->cpu_model->CP0_Config2;                          // (9) 0.04492
/*36  */     env->CP0_Config3 = env->cpu_model->CP0_Config3;                          // (10) 0.04492
/*38  */     env->CP0_Config6 = env->cpu_model->CP0_Config6;                          // (11) 0.04492
/*40  */     env->CP0_Config7 = env->cpu_model->CP0_Config7;                          // (12) 0.04492
/*42  */     env->CP0_LLAddr_rw_bitmask = env->cpu_model->CP0_LLAddr_rw_bitmask       // (1) 0.06641
/*44  */                                  << env->cpu_model->CP0_LLAddr_shift;        // (0) 0.09375
/*46  */     env->CP0_LLAddr_shift = env->cpu_model->CP0_LLAddr_shift;                // (2) 0.05664
/*48  */     env->SYNCI_Step = env->cpu_model->SYNCI_Step;                            // (4) 0.04492
/*50  */     env->CCRes = env->cpu_model->CCRes;                                      // (16) 0.0332
/*52  */     env->CP0_Status_rw_bitmask = env->cpu_model->CP0_Status_rw_bitmask;      // 0.0
/*54  */     env->CP0_TCStatus_rw_bitmask = env->cpu_model->CP0_TCStatus_rw_bitmask;  // 0.0
/*56  */     env->CP0_SRSCtl = env->cpu_model->CP0_SRSCtl;                            // 0.0
/*58  */     env->current_tc = 0;                                                     // 0.0
/*60  */     env->SEGBITS = env->cpu_model->SEGBITS;                                  // 0.0
/*62  */     env->SEGMask = (target_ulong)((1ULL << env->cpu_model->SEGBITS) - 1);    // 0.0
/*64  */ #if defined(TARGET_MIPS64)                                                   // 0.0
/*66  */     if (env->cpu_model->insn_flags & ISA_MIPS3) {                            // 0.0
/*68  */         env->SEGMask |= 3ULL << 62;                                          // 0.0
/*70  */     }                                                                        // 0.0
/*72  */ #endif                                                                       // 0.0
/*74  */     env->PABITS = env->cpu_model->PABITS;                                    // 0.0
/*76  */     env->PAMask = (target_ulong)((1ULL << env->cpu_model->PABITS) - 1);      // 0.0
/*78  */     env->CP0_SRSConf0_rw_bitmask = env->cpu_model->CP0_SRSConf0_rw_bitmask;  // 0.0
/*80  */     env->CP0_SRSConf0 = env->cpu_model->CP0_SRSConf0;                        // 0.0
/*82  */     env->CP0_SRSConf1_rw_bitmask = env->cpu_model->CP0_SRSConf1_rw_bitmask;  // 0.0
/*84  */     env->CP0_SRSConf1 = env->cpu_model->CP0_SRSConf1;                        // 0.0
/*86  */     env->CP0_SRSConf2_rw_bitmask = env->cpu_model->CP0_SRSConf2_rw_bitmask;  // 0.0
/*88  */     env->CP0_SRSConf2 = env->cpu_model->CP0_SRSConf2;                        // 0.0
/*90  */     env->CP0_SRSConf3_rw_bitmask = env->cpu_model->CP0_SRSConf3_rw_bitmask;  // 0.0
/*92  */     env->CP0_SRSConf3 = env->cpu_model->CP0_SRSConf3;                        // 0.0
/*94  */     env->CP0_SRSConf4_rw_bitmask = env->cpu_model->CP0_SRSConf4_rw_bitmask;  // 0.0
/*96  */     env->CP0_SRSConf4 = env->cpu_model->CP0_SRSConf4;                        // 0.0
/*98  */     env->active_fpu.fcr0 = env->cpu_model->CP1_fcr0;                         // 0.0
/*100 */     env->insn_flags = env->cpu_model->insn_flags;                            // 0.0
/*104 */ #if defined(CONFIG_USER_ONLY)                                                // 0.0
/*106 */     env->hflags = MIPS_HFLAG_UM;                                             // 0.0
/*108 */     /* Enable access to the CPUNum, SYNCI_Step, CC, and CCRes RDHWR          // 0.0
/*110 */        hardware registers.  */                                               // 0.0
/*112 */     env->CP0_HWREna |= 0x0000000F;                                           // 0.0
/*114 */     if (env->CP0_Config1 & (1 << CP0C1_FP)) {                                // 0.0
/*116 */         env->hflags |= MIPS_HFLAG_FPU;                                       // 0.0
/*118 */     }                                                                        // 0.0
/*120 */ #ifdef TARGET_MIPS64                                                         // 0.0
/*122 */     if (env->active_fpu.fcr0 & (1 << FCR0_F64)) {                            // 0.0
/*124 */         env->hflags |= MIPS_HFLAG_F64;                                       // 0.0
/*126 */     }                                                                        // 0.0
/*128 */ #endif                                                                       // 0.0
/*130 */ #else                                                                        // 0.0
/*132 */     if (env->hflags & MIPS_HFLAG_BMASK) {                                    // 0.0
/*134 */         /* If the exception was raised from a delay slot,                    // 0.0
/*136 */            come back to the jump.  */                                        // 0.0
/*138 */         env->CP0_ErrorEPC = env->active_tc.PC - 4;                           // 0.0
/*140 */     } else {                                                                 // 0.0
/*142 */         env->CP0_ErrorEPC = env->active_tc.PC;                               // 0.0
/*144 */     }                                                                        // 0.0
/*146 */     env->active_tc.PC = (int32_t)0xBFC00000;                                 // 0.0
/*148 */     env->CP0_Random = env->tlb->nb_tlb - 1;                                  // 0.0
/*150 */     env->tlb->tlb_in_use = env->tlb->nb_tlb;                                 // 0.0
/*152 */     env->CP0_Wired = 0;                                                      // 0.0
/*154 */     env->CP0_EBase = 0x80000000 | (env->cpu_index & 0x3FF);                  // 0.0
/*156 */     env->CP0_Status = (1 << CP0St_BEV) | (1 << CP0St_ERL);                   // 0.0
/*158 */     /* vectored interrupts not implemented, timer on int 7,                  // 0.0
/*160 */        no performance counters. */                                           // 0.0
/*162 */     env->CP0_IntCtl = 0xe0000000;                                            // 0.0
/*164 */     {                                                                        // 0.0
/*166 */         int i;                                                               // 0.0
/*170 */         for (i = 0; i < 7; i++) {                                            // 0.0
/*172 */             env->CP0_WatchLo[i] = 0;                                         // 0.0
/*174 */             env->CP0_WatchHi[i] = 0x80000000;                                // 0.0
/*176 */         }                                                                    // 0.0
/*178 */         env->CP0_WatchLo[7] = 0;                                             // 0.0
/*180 */         env->CP0_WatchHi[7] = 0;                                             // 0.0
/*182 */     }                                                                        // 0.0
/*184 */     /* Count register increments in debug mode, EJTAG version 1 */           // 0.0
/*186 */     env->CP0_Debug = (1 << CP0DB_CNT) | (0x1 << CP0DB_VER);                  // 0.0
/*188 */     env->hflags = MIPS_HFLAG_CP0;                                            // 0.0
/*192 */     if (env->CP0_Config3 & (1 << CP0C3_MT)) {                                // 0.0
/*194 */         int i;                                                               // 0.0
/*198 */         /* Only TC0 on VPE 0 starts as active.  */                           // 0.0
/*200 */         for (i = 0; i < ARRAY_SIZE(env->tcs); i++) {                         // 0.0
/*202 */             env->tcs[i].CP0_TCBind = env->cpu_index << CP0TCBd_CurVPE;       // 0.0
/*204 */             env->tcs[i].CP0_TCHalt = 1;                                      // 0.0
/*206 */         }                                                                    // 0.0
/*208 */         env->active_tc.CP0_TCHalt = 1;                                       // 0.0
/*210 */         env->halted = 1;                                                     // 0.0
/*214 */         if (!env->cpu_index) {                                               // 0.0
/*216 */             /* VPE0 starts up enabled.  */                                   // 0.0
/*218 */             env->mvp->CP0_MVPControl |= (1 << CP0MVPCo_EVP);                 // 0.0
/*220 */             env->CP0_VPEConf0 |= (1 << CP0VPEC0_MVP) | (1 << CP0VPEC0_VPA);  // 0.0
/*224 */             /* TC0 starts up unhalted.  */                                   // 0.0
/*226 */             env->halted = 0;                                                 // 0.0
/*228 */             env->active_tc.CP0_TCHalt = 0;                                   // 0.0
/*230 */             env->tcs[0].CP0_TCHalt = 0;                                      // 0.0
/*232 */             /* With thread 0 active.  */                                     // 0.0
/*234 */             env->active_tc.CP0_TCStatus = (1 << CP0TCSt_A);                  // 0.0
/*236 */             env->tcs[0].CP0_TCStatus = (1 << CP0TCSt_A);                     // 0.0
/*238 */         }                                                                    // 0.0
/*240 */     }                                                                        // 0.0
/*242 */ #endif                                                                       // 0.0
/*244 */ #if defined(TARGET_MIPS64)                                                   // 0.0
/*246 */     if (env->cpu_model->insn_flags & ISA_MIPS3) {                            // 0.0
/*248 */         env->hflags |= MIPS_HFLAG_64;                                        // 0.0
/*250 */     }                                                                        // 0.0
/*252 */ #endif                                                                       // 0.0
/*254 */     env->exception_index = EXCP_NONE;                                        // 0.0
/*256 */ }                                                                            // 0.0

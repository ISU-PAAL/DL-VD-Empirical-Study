// commit message qemu@5d98bf8f38 (target=0, prob=0.421562, correct=True): target-arm: Fix CPU breakpoint handling
/*0   */ void gen_intermediate_code_a64(ARMCPU *cpu, TranslationBlock *tb)                 // (5) 0.04492
/*2   */ {                                                                                 // (29) 0.001953
/*4   */     CPUState *cs = CPU(cpu);                                                      // (16) 0.02344
/*6   */     CPUARMState *env = &cpu->env;                                                 // (11) 0.02734
/*8   */     DisasContext dc1, *dc = &dc1;                                                 // (8) 0.03125
/*10  */     target_ulong pc_start;                                                        // (19) 0.02148
/*12  */     target_ulong next_page_start;                                                 // (12) 0.02539
/*14  */     int num_insns;                                                                // (26) 0.01758
/*16  */     int max_insns;                                                                // (25) 0.01758
/*20  */     pc_start = tb->pc;                                                            // (15) 0.02344
/*24  */     dc->tb = tb;                                                                  // (22) 0.02148
/*28  */     dc->is_jmp = DISAS_NEXT;                                                      // (9) 0.03125
/*30  */     dc->pc = pc_start;                                                            // (21) 0.02148
/*32  */     dc->singlestep_enabled = cs->singlestep_enabled;                              // (7) 0.03711
/*34  */     dc->condjmp = 0;                                                              // (23) 0.02148
/*38  */     dc->aarch64 = 1;                                                              // (20) 0.02148
/*40  */     /* If we are coming from secure EL0 in a system with a 32-bit EL3, then       // (4) 0.04687
/*42  */      * there is no secure EL1, so we route exceptions to EL3.                     // (6) 0.03906
/*44  */      */                                                                           // (27) 0.009766
/*46  */     dc->secure_routed_to_el3 = arm_feature(env, ARM_FEATURE_EL3) &&               // (1) 0.05859
/*48  */                                !arm_el_is_aa64(env, 3);                           // (0) 0.08594
/*50  */     dc->thumb = 0;                                                                // (24) 0.01953
/*52  */     dc->bswap_code = 0;                                                           // (14) 0.02539
/*54  */     dc->condexec_mask = 0;                                                        // (18) 0.02344
/*56  */     dc->condexec_cond = 0;                                                        // (17) 0.02344
/*58  */     dc->mmu_idx = ARM_TBFLAG_MMUIDX(tb->flags);                                   // (3) 0.04883
/*60  */     dc->current_el = arm_mmu_idx_to_el(dc->mmu_idx);                              // (2) 0.05664
/*62  */ #if !defined(CONFIG_USER_ONLY)                                                    // (13) 0.02539
/*64  */     dc->user = (dc->current_el == 0);                                             // (10) 0.03125
/*66  */ #endif                                                                            // (28) 0.003906
/*68  */     dc->fp_excp_el = ARM_TBFLAG_FPEXC_EL(tb->flags);                              // 0.0
/*70  */     dc->vec_len = 0;                                                              // 0.0
/*72  */     dc->vec_stride = 0;                                                           // 0.0
/*74  */     dc->cp_regs = cpu->cp_regs;                                                   // 0.0
/*76  */     dc->features = env->features;                                                 // 0.0
/*80  */     /* Single step state. The code-generation logic here is:                      // 0.0
/*82  */      *  SS_ACTIVE == 0:                                                           // 0.0
/*84  */      *   generate code with no special handling for single-stepping (except       // 0.0
/*86  */      *   that anything that can make us go to SS_ACTIVE == 1 must end the TB;     // 0.0
/*88  */      *   this happens anyway because those changes are all system register or     // 0.0
/*90  */      *   PSTATE writes).                                                          // 0.0
/*92  */      *  SS_ACTIVE == 1, PSTATE.SS == 1: (active-not-pending)                      // 0.0
/*94  */      *   emit code for one insn                                                   // 0.0
/*96  */      *   emit code to clear PSTATE.SS                                             // 0.0
/*98  */      *   emit code to generate software step exception for completed step         // 0.0
/*100 */      *   end TB (as usual for having generated an exception)                      // 0.0
/*102 */      *  SS_ACTIVE == 1, PSTATE.SS == 0: (active-pending)                          // 0.0
/*104 */      *   emit code to generate a software step exception                          // 0.0
/*106 */      *   end the TB                                                               // 0.0
/*108 */      */                                                                           // 0.0
/*110 */     dc->ss_active = ARM_TBFLAG_SS_ACTIVE(tb->flags);                              // 0.0
/*112 */     dc->pstate_ss = ARM_TBFLAG_PSTATE_SS(tb->flags);                              // 0.0
/*114 */     dc->is_ldex = false;                                                          // 0.0
/*116 */     dc->ss_same_el = (arm_debug_target_el(env) == dc->current_el);                // 0.0
/*120 */     init_tmp_a64_array(dc);                                                       // 0.0
/*124 */     next_page_start = (pc_start & TARGET_PAGE_MASK) + TARGET_PAGE_SIZE;           // 0.0
/*126 */     num_insns = 0;                                                                // 0.0
/*128 */     max_insns = tb->cflags & CF_COUNT_MASK;                                       // 0.0
/*130 */     if (max_insns == 0) {                                                         // 0.0
/*132 */         max_insns = CF_COUNT_MASK;                                                // 0.0
/*134 */     }                                                                             // 0.0
/*136 */     if (max_insns > TCG_MAX_INSNS) {                                              // 0.0
/*138 */         max_insns = TCG_MAX_INSNS;                                                // 0.0
/*140 */     }                                                                             // 0.0
/*144 */     gen_tb_start(tb);                                                             // 0.0
/*148 */     tcg_clear_temp_count();                                                       // 0.0
/*152 */     do {                                                                          // 0.0
/*154 */         tcg_gen_insn_start(dc->pc, 0);                                            // 0.0
/*156 */         num_insns++;                                                              // 0.0
/*160 */         if (unlikely(!QTAILQ_EMPTY(&cs->breakpoints))) {                          // 0.0
/*162 */             CPUBreakpoint *bp;                                                    // 0.0
/*164 */             QTAILQ_FOREACH(bp, &cs->breakpoints, entry) {                         // 0.0
/*166 */                 if (bp->pc == dc->pc) {                                           // 0.0
/*168 */                     gen_exception_internal_insn(dc, 0, EXCP_DEBUG);               // 0.0
/*170 */                     /* Advance PC so that clearing the breakpoint will            // 0.0
/*172 */                        invalidate this TB.  */                                    // 0.0
/*174 */                     dc->pc += 2;                                                  // 0.0
/*176 */                     goto done_generating;                                         // 0.0
/*178 */                 }                                                                 // 0.0
/*180 */             }                                                                     // 0.0
/*182 */         }                                                                         // 0.0
/*186 */         if (num_insns == max_insns && (tb->cflags & CF_LAST_IO)) {                // 0.0
/*188 */             gen_io_start();                                                       // 0.0
/*190 */         }                                                                         // 0.0
/*194 */         if (dc->ss_active && !dc->pstate_ss) {                                    // 0.0
/*196 */             /* Singlestep state is Active-pending.                                // 0.0
/*198 */              * If we're in this state at the start of a TB then either            // 0.0
/*200 */              *  a) we just took an exception to an EL which is being debugged     // 0.0
/*202 */              *     and this is the first insn in the exception handler            // 0.0
/*204 */              *  b) debug exceptions were masked and we just unmasked them         // 0.0
/*206 */              *     without changing EL (eg by clearing PSTATE.D)                  // 0.0
/*208 */              * In either case we're going to take a swstep exception in the       // 0.0
/*210 */              * "did not step an insn" case, and so the syndrome ISV and EX        // 0.0
/*212 */              * bits should be zero.                                               // 0.0
/*214 */              */                                                                   // 0.0
/*216 */             assert(num_insns == 1);                                               // 0.0
/*218 */             gen_exception(EXCP_UDEF, syn_swstep(dc->ss_same_el, 0, 0),            // 0.0
/*220 */                           default_exception_el(dc));                              // 0.0
/*222 */             dc->is_jmp = DISAS_EXC;                                               // 0.0
/*224 */             break;                                                                // 0.0
/*226 */         }                                                                         // 0.0
/*230 */         disas_a64_insn(env, dc);                                                  // 0.0
/*234 */         if (tcg_check_temp_count()) {                                             // 0.0
/*236 */             fprintf(stderr, "TCG temporary leak before "TARGET_FMT_lx"\n",        // 0.0
/*238 */                     dc->pc);                                                      // 0.0
/*240 */         }                                                                         // 0.0
/*244 */         /* Translation stops when a conditional branch is encountered.            // 0.0
/*246 */          * Otherwise the subsequent code could get translated several times.      // 0.0
/*248 */          * Also stop translation when a page boundary is reached.  This           // 0.0
/*250 */          * ensures prefetch aborts occur at the right place.                      // 0.0
/*252 */          */                                                                       // 0.0
/*254 */     } while (!dc->is_jmp && !tcg_op_buf_full() &&                                 // 0.0
/*256 */              !cs->singlestep_enabled &&                                           // 0.0
/*258 */              !singlestep &&                                                       // 0.0
/*260 */              !dc->ss_active &&                                                    // 0.0
/*262 */              dc->pc < next_page_start &&                                          // 0.0
/*264 */              num_insns < max_insns);                                              // 0.0
/*268 */     if (tb->cflags & CF_LAST_IO) {                                                // 0.0
/*270 */         gen_io_end();                                                             // 0.0
/*272 */     }                                                                             // 0.0
/*276 */     if (unlikely(cs->singlestep_enabled || dc->ss_active)                         // 0.0
/*278 */         && dc->is_jmp != DISAS_EXC) {                                             // 0.0
/*280 */         /* Note that this means single stepping WFI doesn't halt the CPU.         // 0.0
/*282 */          * For conditional branch insns this is harmless unreachable code as      // 0.0
/*284 */          * gen_goto_tb() has already handled emitting the debug exception         // 0.0
/*286 */          * (and thus a tb-jump is not possible when singlestepping).              // 0.0
/*288 */          */                                                                       // 0.0
/*290 */         assert(dc->is_jmp != DISAS_TB_JUMP);                                      // 0.0
/*292 */         if (dc->is_jmp != DISAS_JUMP) {                                           // 0.0
/*294 */             gen_a64_set_pc_im(dc->pc);                                            // 0.0
/*296 */         }                                                                         // 0.0
/*298 */         if (cs->singlestep_enabled) {                                             // 0.0
/*300 */             gen_exception_internal(EXCP_DEBUG);                                   // 0.0
/*302 */         } else {                                                                  // 0.0
/*304 */             gen_step_complete_exception(dc);                                      // 0.0
/*306 */         }                                                                         // 0.0
/*308 */     } else {                                                                      // 0.0
/*310 */         switch (dc->is_jmp) {                                                     // 0.0
/*312 */         case DISAS_NEXT:                                                          // 0.0
/*314 */             gen_goto_tb(dc, 1, dc->pc);                                           // 0.0
/*316 */             break;                                                                // 0.0
/*318 */         default:                                                                  // 0.0
/*320 */         case DISAS_UPDATE:                                                        // 0.0
/*322 */             gen_a64_set_pc_im(dc->pc);                                            // 0.0
/*324 */             /* fall through */                                                    // 0.0
/*326 */         case DISAS_JUMP:                                                          // 0.0
/*328 */             /* indicate that the hash table must be used to find the next TB */   // 0.0
/*330 */             tcg_gen_exit_tb(0);                                                   // 0.0
/*332 */             break;                                                                // 0.0
/*334 */         case DISAS_TB_JUMP:                                                       // 0.0
/*336 */         case DISAS_EXC:                                                           // 0.0
/*338 */         case DISAS_SWI:                                                           // 0.0
/*340 */             break;                                                                // 0.0
/*342 */         case DISAS_WFE:                                                           // 0.0
/*344 */             gen_a64_set_pc_im(dc->pc);                                            // 0.0
/*346 */             gen_helper_wfe(cpu_env);                                              // 0.0
/*348 */             break;                                                                // 0.0
/*350 */         case DISAS_YIELD:                                                         // 0.0
/*352 */             gen_a64_set_pc_im(dc->pc);                                            // 0.0
/*354 */             gen_helper_yield(cpu_env);                                            // 0.0
/*356 */             break;                                                                // 0.0
/*358 */         case DISAS_WFI:                                                           // 0.0
/*360 */             /* This is a special case because we don't want to just halt the CPU  // 0.0
/*362 */              * if trying to debug across a WFI.                                   // 0.0
/*364 */              */                                                                   // 0.0
/*366 */             gen_a64_set_pc_im(dc->pc);                                            // 0.0
/*368 */             gen_helper_wfi(cpu_env);                                              // 0.0
/*370 */             /* The helper doesn't necessarily throw an exception, but we          // 0.0
/*372 */              * must go back to the main loop to check for interrupts anyway.      // 0.0
/*374 */              */                                                                   // 0.0
/*376 */             tcg_gen_exit_tb(0);                                                   // 0.0
/*378 */             break;                                                                // 0.0
/*380 */         }                                                                         // 0.0
/*382 */     }                                                                             // 0.0
/*386 */ done_generating:                                                                  // 0.0
/*388 */     gen_tb_end(tb, num_insns);                                                    // 0.0
/*392 */ #ifdef DEBUG_DISAS                                                                // 0.0
/*394 */     if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {                                  // 0.0
/*396 */         qemu_log("----------------\n");                                           // 0.0
/*398 */         qemu_log("IN: %s\n", lookup_symbol(pc_start));                            // 0.0
/*400 */         log_target_disas(cs, pc_start, dc->pc - pc_start,                         // 0.0
/*402 */                          4 | (dc->bswap_code << 1));                              // 0.0
/*404 */         qemu_log("\n");                                                           // 0.0
/*406 */     }                                                                             // 0.0
/*408 */ #endif                                                                            // 0.0
/*410 */     tb->size = dc->pc - pc_start;                                                 // 0.0
/*412 */     tb->icount = num_insns;                                                       // 0.0
/*414 */ }                                                                                 // 0.0

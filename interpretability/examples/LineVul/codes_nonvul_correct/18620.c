// commit message qemu@23979dc541 (target=0, prob=0.45203897, correct=True): microblaze: Use more TB chaining
/*0   */ gen_intermediate_code_internal(CPUState *env, TranslationBlock *tb,        // (6) 0.03906
/*2   */                                int search_pc)                              // (0) 0.06836
/*4   */ {                                                                          // (29) 0.001953
/*6   */     uint16_t *gen_opc_end;                                                 // (12) 0.0293
/*8   */     uint32_t pc_start;                                                     // (18) 0.02148
/*10  */     int j, lj;                                                             // (25) 0.01758
/*12  */     struct DisasContext ctx;                                               // (21) 0.01953
/*14  */     struct DisasContext *dc = &ctx;                                        // (13) 0.02539
/*16  */     uint32_t next_page_start, org_flags;                                   // (9) 0.0332
/*18  */     target_ulong npc;                                                      // (22) 0.01953
/*20  */     int num_insns;                                                         // (26) 0.01758
/*22  */     int max_insns;                                                         // (24) 0.01758
/*26  */     qemu_log_try_set_file(stderr);                                         // (7) 0.03711
/*30  */     pc_start = tb->pc;                                                     // (16) 0.02344
/*32  */     dc->env = env;                                                         // (27) 0.01758
/*34  */     dc->tb = tb;                                                           // (20) 0.02148
/*36  */     org_flags = dc->synced_flags = dc->tb_flags = tb->flags;               // (3) 0.05078
/*40  */     gen_opc_end = gen_opc_buf + OPC_MAX_SIZE;                              // (4) 0.04687
/*44  */     dc->is_jmp = DISAS_NEXT;                                               // (11) 0.03125
/*46  */     dc->jmp = 0;                                                           // (23) 0.01953
/*48  */     dc->delayed_branch = !!(dc->tb_flags & D_FLAG);                        // (5) 0.04687
/*50  */     dc->pc = pc_start;                                                     // (19) 0.02148
/*52  */     dc->singlestep_enabled = env->singlestep_enabled;                      // (8) 0.03711
/*54  */     dc->cpustate_changed = 0;                                              // (14) 0.02539
/*56  */     dc->abort_at_next_insn = 0;                                            // (10) 0.0332
/*58  */     dc->nr_nops = 0;                                                       // (15) 0.02344
/*62  */     if (pc_start & 3)                                                      // (17) 0.02148
/*64  */         cpu_abort(env, "Microblaze: unaligned PC=%x\n", pc_start);         // (1) 0.0625
/*68  */     if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {                           // (2) 0.05273
/*70  */ #if !SIM_COMPAT                                                            // (28) 0.01563
/*72  */         qemu_log("--------------\n");                                      // 0.0
/*74  */         log_cpu_state(env, 0);                                             // 0.0
/*76  */ #endif                                                                     // 0.0
/*78  */     }                                                                      // 0.0
/*82  */     next_page_start = (pc_start & TARGET_PAGE_MASK) + TARGET_PAGE_SIZE;    // 0.0
/*84  */     lj = -1;                                                               // 0.0
/*86  */     num_insns = 0;                                                         // 0.0
/*88  */     max_insns = tb->cflags & CF_COUNT_MASK;                                // 0.0
/*90  */     if (max_insns == 0)                                                    // 0.0
/*92  */         max_insns = CF_COUNT_MASK;                                         // 0.0
/*96  */     gen_icount_start();                                                    // 0.0
/*98  */     do                                                                     // 0.0
/*100 */     {                                                                      // 0.0
/*102 */ #if SIM_COMPAT                                                             // 0.0
/*104 */         if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {                       // 0.0
/*106 */             tcg_gen_movi_tl(cpu_SR[SR_PC], dc->pc);                        // 0.0
/*108 */             gen_helper_debug();                                            // 0.0
/*110 */         }                                                                  // 0.0
/*112 */ #endif                                                                     // 0.0
/*114 */         check_breakpoint(env, dc);                                         // 0.0
/*118 */         if (search_pc) {                                                   // 0.0
/*120 */             j = gen_opc_ptr - gen_opc_buf;                                 // 0.0
/*122 */             if (lj < j) {                                                  // 0.0
/*124 */                 lj++;                                                      // 0.0
/*126 */                 while (lj < j)                                             // 0.0
/*128 */                     gen_opc_instr_start[lj++] = 0;                         // 0.0
/*130 */             }                                                              // 0.0
/*132 */             gen_opc_pc[lj] = dc->pc;                                       // 0.0
/*134 */             gen_opc_instr_start[lj] = 1;                                   // 0.0
/*136 */                         gen_opc_icount[lj] = num_insns;                    // 0.0
/*138 */         }                                                                  // 0.0
/*142 */         /* Pretty disas.  */                                               // 0.0
/*144 */         LOG_DIS("%8.8x:\t", dc->pc);                                       // 0.0
/*148 */         if (num_insns + 1 == max_insns && (tb->cflags & CF_LAST_IO))       // 0.0
/*150 */             gen_io_start();                                                // 0.0
/*154 */         dc->clear_imm = 1;                                                 // 0.0
/*156 */ 	decode(dc);                                                               // 0.0
/*158 */         if (dc->clear_imm)                                                 // 0.0
/*160 */             dc->tb_flags &= ~IMM_FLAG;                                     // 0.0
/*162 */         dc->pc += 4;                                                       // 0.0
/*164 */         num_insns++;                                                       // 0.0
/*168 */         if (dc->delayed_branch) {                                          // 0.0
/*170 */             dc->delayed_branch--;                                          // 0.0
/*172 */             if (!dc->delayed_branch) {                                     // 0.0
/*174 */                 if (dc->tb_flags & DRTI_FLAG)                              // 0.0
/*176 */                     do_rti(dc);                                            // 0.0
/*178 */                  if (dc->tb_flags & DRTB_FLAG)                             // 0.0
/*180 */                     do_rtb(dc);                                            // 0.0
/*182 */                 if (dc->tb_flags & DRTE_FLAG)                              // 0.0
/*184 */                     do_rte(dc);                                            // 0.0
/*186 */                 /* Clear the delay slot flag.  */                          // 0.0
/*188 */                 dc->tb_flags &= ~D_FLAG;                                   // 0.0
/*190 */                 /* If it is a direct jump, try direct chaining.  */        // 0.0
/*192 */                 if (dc->jmp != JMP_DIRECT) {                               // 0.0
/*194 */                     eval_cond_jmp(dc, env_btarget, tcg_const_tl(dc->pc));  // 0.0
/*196 */                     dc->is_jmp = DISAS_JUMP;                               // 0.0
/*198 */                 }                                                          // 0.0
/*200 */                 break;                                                     // 0.0
/*202 */             }                                                              // 0.0
/*204 */         }                                                                  // 0.0
/*206 */         if (env->singlestep_enabled)                                       // 0.0
/*208 */             break;                                                         // 0.0
/*210 */     } while (!dc->is_jmp && !dc->cpustate_changed                          // 0.0
/*212 */          && gen_opc_ptr < gen_opc_end                                      // 0.0
/*214 */                  && !singlestep                                            // 0.0
/*216 */          && (dc->pc < next_page_start)                                     // 0.0
/*218 */                  && num_insns < max_insns);                                // 0.0
/*222 */     npc = dc->pc;                                                          // 0.0
/*224 */     if (dc->jmp == JMP_DIRECT) {                                           // 0.0
/*226 */         if (dc->tb_flags & D_FLAG) {                                       // 0.0
/*228 */             dc->is_jmp = DISAS_UPDATE;                                     // 0.0
/*230 */             tcg_gen_movi_tl(cpu_SR[SR_PC], npc);                           // 0.0
/*232 */             sync_jmpstate(dc);                                             // 0.0
/*234 */         } else                                                             // 0.0
/*236 */             npc = dc->jmp_pc;                                              // 0.0
/*238 */     }                                                                      // 0.0
/*242 */     if (tb->cflags & CF_LAST_IO)                                           // 0.0
/*244 */         gen_io_end();                                                      // 0.0
/*246 */     /* Force an update if the per-tb cpu state has changed.  */            // 0.0
/*248 */     if (dc->is_jmp == DISAS_NEXT                                           // 0.0
/*250 */         && (dc->cpustate_changed || org_flags != dc->tb_flags)) {          // 0.0
/*252 */         dc->is_jmp = DISAS_UPDATE;                                         // 0.0
/*254 */         tcg_gen_movi_tl(cpu_SR[SR_PC], npc);                               // 0.0
/*256 */     }                                                                      // 0.0
/*258 */     t_sync_flags(dc);                                                      // 0.0
/*262 */     if (unlikely(env->singlestep_enabled)) {                               // 0.0
/*264 */         t_gen_raise_exception(dc, EXCP_DEBUG);                             // 0.0
/*266 */         if (dc->is_jmp == DISAS_NEXT)                                      // 0.0
/*268 */             tcg_gen_movi_tl(cpu_SR[SR_PC], npc);                           // 0.0
/*270 */     } else {                                                               // 0.0
/*272 */         switch(dc->is_jmp) {                                               // 0.0
/*274 */             case DISAS_NEXT:                                               // 0.0
/*276 */                 gen_goto_tb(dc, 1, npc);                                   // 0.0
/*278 */                 break;                                                     // 0.0
/*280 */             default:                                                       // 0.0
/*282 */             case DISAS_JUMP:                                               // 0.0
/*284 */             case DISAS_UPDATE:                                             // 0.0
/*286 */                 /* indicate that the hash table must be used               // 0.0
/*288 */                    to find the next TB */                                  // 0.0
/*290 */                 tcg_gen_exit_tb(0);                                        // 0.0
/*292 */                 break;                                                     // 0.0
/*294 */             case DISAS_TB_JUMP:                                            // 0.0
/*296 */                 /* nothing more to generate */                             // 0.0
/*298 */                 break;                                                     // 0.0
/*300 */         }                                                                  // 0.0
/*302 */     }                                                                      // 0.0
/*304 */     gen_icount_end(tb, num_insns);                                         // 0.0
/*306 */     *gen_opc_ptr = INDEX_op_end;                                           // 0.0
/*308 */     if (search_pc) {                                                       // 0.0
/*310 */         j = gen_opc_ptr - gen_opc_buf;                                     // 0.0
/*312 */         lj++;                                                              // 0.0
/*314 */         while (lj <= j)                                                    // 0.0
/*316 */             gen_opc_instr_start[lj++] = 0;                                 // 0.0
/*318 */     } else {                                                               // 0.0
/*320 */         tb->size = dc->pc - pc_start;                                      // 0.0
/*322 */                 tb->icount = num_insns;                                    // 0.0
/*324 */     }                                                                      // 0.0
/*328 */ #ifdef DEBUG_DISAS                                                         // 0.0
/*330 */ #if !SIM_COMPAT                                                            // 0.0
/*332 */     if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {                           // 0.0
/*334 */         qemu_log("\n");                                                    // 0.0
/*336 */ #if DISAS_GNU                                                              // 0.0
/*338 */         log_target_disas(pc_start, dc->pc - pc_start, 0);                  // 0.0
/*340 */ #endif                                                                     // 0.0
/*342 */         qemu_log("\nisize=%d osize=%td\n",                                 // 0.0
/*344 */             dc->pc - pc_start, gen_opc_ptr - gen_opc_buf);                 // 0.0
/*346 */     }                                                                      // 0.0
/*348 */ #endif                                                                     // 0.0
/*350 */ #endif                                                                     // 0.0
/*352 */     assert(!dc->abort_at_next_insn);                                       // 0.0
/*354 */ }                                                                          // 0.0

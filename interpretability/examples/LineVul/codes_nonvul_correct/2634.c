// commit message qemu@cd42d5b236 (target=0, prob=0.45534742, correct=True): gen-icount: check cflags instead of use_icount global
/*0   */ static inline void gen_intermediate_code_internal(OpenRISCCPU *cpu,             // (7) 0.03906
/*2   */                                                   TranslationBlock *tb,         // (0) 0.1074
/*4   */                                                   int search_pc)                // (1) 0.1055
/*6   */ {                                                                               // (25) 0.001953
/*8   */     CPUState *cs = CPU(cpu);                                                    // (17) 0.02344
/*10  */     struct DisasContext ctx, *dc = &ctx;                                        // (12) 0.03125
/*12  */     uint16_t *gen_opc_end;                                                      // (14) 0.0293
/*14  */     uint32_t pc_start;                                                          // (20) 0.02148
/*16  */     int j, k;                                                                   // (24) 0.01562
/*18  */     uint32_t next_page_start;                                                   // (15) 0.02539
/*20  */     int num_insns;                                                              // (23) 0.01758
/*22  */     int max_insns;                                                              // (22) 0.01758
/*26  */     pc_start = tb->pc;                                                          // (16) 0.02344
/*28  */     dc->tb = tb;                                                                // (19) 0.02148
/*32  */     gen_opc_end = tcg_ctx.gen_opc_buf + OPC_MAX_SIZE;                           // (2) 0.05664
/*34  */     dc->is_jmp = DISAS_NEXT;                                                    // (13) 0.03125
/*36  */     dc->ppc = pc_start;                                                         // (18) 0.02344
/*38  */     dc->pc = pc_start;                                                          // (21) 0.02148
/*40  */     dc->flags = cpu->env.cpucfgr;                                               // (11) 0.03125
/*42  */     dc->mem_idx = cpu_mmu_index(&cpu->env);                                     // (6) 0.04102
/*44  */     dc->synced_flags = dc->tb_flags = tb->flags;                                // (5) 0.04297
/*46  */     dc->delayed_branch = !!(dc->tb_flags & D_FLAG);                             // (4) 0.04687
/*48  */     dc->singlestep_enabled = cs->singlestep_enabled;                            // (9) 0.03711
/*50  */     if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {                                // (3) 0.05273
/*52  */         qemu_log("-----------------------------------------\n");                // (10) 0.03516
/*54  */         log_cpu_state(CPU(cpu), 0);                                             // (8) 0.03711
/*56  */     }                                                                           // 0.0
/*60  */     next_page_start = (pc_start & TARGET_PAGE_MASK) + TARGET_PAGE_SIZE;         // 0.0
/*62  */     k = -1;                                                                     // 0.0
/*64  */     num_insns = 0;                                                              // 0.0
/*66  */     max_insns = tb->cflags & CF_COUNT_MASK;                                     // 0.0
/*70  */     if (max_insns == 0) {                                                       // 0.0
/*72  */         max_insns = CF_COUNT_MASK;                                              // 0.0
/*74  */     }                                                                           // 0.0
/*78  */     gen_tb_start();                                                             // 0.0
/*82  */     do {                                                                        // 0.0
/*84  */         check_breakpoint(cpu, dc);                                              // 0.0
/*86  */         if (search_pc) {                                                        // 0.0
/*88  */             j = tcg_ctx.gen_opc_ptr - tcg_ctx.gen_opc_buf;                      // 0.0
/*90  */             if (k < j) {                                                        // 0.0
/*92  */                 k++;                                                            // 0.0
/*94  */                 while (k < j) {                                                 // 0.0
/*96  */                     tcg_ctx.gen_opc_instr_start[k++] = 0;                       // 0.0
/*98  */                 }                                                               // 0.0
/*100 */             }                                                                   // 0.0
/*102 */             tcg_ctx.gen_opc_pc[k] = dc->pc;                                     // 0.0
/*104 */             tcg_ctx.gen_opc_instr_start[k] = 1;                                 // 0.0
/*106 */             tcg_ctx.gen_opc_icount[k] = num_insns;                              // 0.0
/*108 */         }                                                                       // 0.0
/*112 */         if (unlikely(qemu_loglevel_mask(CPU_LOG_TB_OP | CPU_LOG_TB_OP_OPT))) {  // 0.0
/*114 */             tcg_gen_debug_insn_start(dc->pc);                                   // 0.0
/*116 */         }                                                                       // 0.0
/*120 */         if (num_insns + 1 == max_insns && (tb->cflags & CF_LAST_IO)) {          // 0.0
/*122 */             gen_io_start();                                                     // 0.0
/*124 */         }                                                                       // 0.0
/*126 */         dc->ppc = dc->pc - 4;                                                   // 0.0
/*128 */         dc->npc = dc->pc + 4;                                                   // 0.0
/*130 */         tcg_gen_movi_tl(cpu_ppc, dc->ppc);                                      // 0.0
/*132 */         tcg_gen_movi_tl(cpu_npc, dc->npc);                                      // 0.0
/*134 */         disas_openrisc_insn(dc, cpu);                                           // 0.0
/*136 */         dc->pc = dc->npc;                                                       // 0.0
/*138 */         num_insns++;                                                            // 0.0
/*140 */         /* delay slot */                                                        // 0.0
/*142 */         if (dc->delayed_branch) {                                               // 0.0
/*144 */             dc->delayed_branch--;                                               // 0.0
/*146 */             if (!dc->delayed_branch) {                                          // 0.0
/*148 */                 dc->tb_flags &= ~D_FLAG;                                        // 0.0
/*150 */                 gen_sync_flags(dc);                                             // 0.0
/*152 */                 tcg_gen_mov_tl(cpu_pc, jmp_pc);                                 // 0.0
/*154 */                 tcg_gen_mov_tl(cpu_npc, jmp_pc);                                // 0.0
/*156 */                 tcg_gen_movi_tl(jmp_pc, 0);                                     // 0.0
/*158 */                 tcg_gen_exit_tb(0);                                             // 0.0
/*160 */                 dc->is_jmp = DISAS_JUMP;                                        // 0.0
/*162 */                 break;                                                          // 0.0
/*164 */             }                                                                   // 0.0
/*166 */         }                                                                       // 0.0
/*168 */     } while (!dc->is_jmp                                                        // 0.0
/*170 */              && tcg_ctx.gen_opc_ptr < gen_opc_end                               // 0.0
/*172 */              && !cs->singlestep_enabled                                         // 0.0
/*174 */              && !singlestep                                                     // 0.0
/*176 */              && (dc->pc < next_page_start)                                      // 0.0
/*178 */              && num_insns < max_insns);                                         // 0.0
/*182 */     if (tb->cflags & CF_LAST_IO) {                                              // 0.0
/*184 */         gen_io_end();                                                           // 0.0
/*186 */     }                                                                           // 0.0
/*188 */     if (dc->is_jmp == DISAS_NEXT) {                                             // 0.0
/*190 */         dc->is_jmp = DISAS_UPDATE;                                              // 0.0
/*192 */         tcg_gen_movi_tl(cpu_pc, dc->pc);                                        // 0.0
/*194 */     }                                                                           // 0.0
/*196 */     if (unlikely(cs->singlestep_enabled)) {                                     // 0.0
/*198 */         if (dc->is_jmp == DISAS_NEXT) {                                         // 0.0
/*200 */             tcg_gen_movi_tl(cpu_pc, dc->pc);                                    // 0.0
/*202 */         }                                                                       // 0.0
/*204 */         gen_exception(dc, EXCP_DEBUG);                                          // 0.0
/*206 */     } else {                                                                    // 0.0
/*208 */         switch (dc->is_jmp) {                                                   // 0.0
/*210 */         case DISAS_NEXT:                                                        // 0.0
/*212 */             gen_goto_tb(dc, 0, dc->pc);                                         // 0.0
/*214 */             break;                                                              // 0.0
/*216 */         default:                                                                // 0.0
/*218 */         case DISAS_JUMP:                                                        // 0.0
/*220 */             break;                                                              // 0.0
/*222 */         case DISAS_UPDATE:                                                      // 0.0
/*224 */             /* indicate that the hash table must be used                        // 0.0
/*226 */                to find the next TB */                                           // 0.0
/*228 */             tcg_gen_exit_tb(0);                                                 // 0.0
/*230 */             break;                                                              // 0.0
/*232 */         case DISAS_TB_JUMP:                                                     // 0.0
/*234 */             /* nothing more to generate */                                      // 0.0
/*236 */             break;                                                              // 0.0
/*238 */         }                                                                       // 0.0
/*240 */     }                                                                           // 0.0
/*244 */     gen_tb_end(tb, num_insns);                                                  // 0.0
/*246 */     *tcg_ctx.gen_opc_ptr = INDEX_op_end;                                        // 0.0
/*248 */     if (search_pc) {                                                            // 0.0
/*250 */         j = tcg_ctx.gen_opc_ptr - tcg_ctx.gen_opc_buf;                          // 0.0
/*252 */         k++;                                                                    // 0.0
/*254 */         while (k <= j) {                                                        // 0.0
/*256 */             tcg_ctx.gen_opc_instr_start[k++] = 0;                               // 0.0
/*258 */         }                                                                       // 0.0
/*260 */     } else {                                                                    // 0.0
/*262 */         tb->size = dc->pc - pc_start;                                           // 0.0
/*264 */         tb->icount = num_insns;                                                 // 0.0
/*266 */     }                                                                           // 0.0
/*270 */ #ifdef DEBUG_DISAS                                                              // 0.0
/*272 */     if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {                                // 0.0
/*274 */         qemu_log("\n");                                                         // 0.0
/*276 */         log_target_disas(&cpu->env, pc_start, dc->pc - pc_start, 0);            // 0.0
/*278 */         qemu_log("\nisize=%d osize=%td\n",                                      // 0.0
/*280 */             dc->pc - pc_start, tcg_ctx.gen_opc_ptr -                            // 0.0
/*282 */             tcg_ctx.gen_opc_buf);                                               // 0.0
/*284 */     }                                                                           // 0.0
/*286 */ #endif                                                                          // 0.0
/*288 */ }                                                                               // 0.0

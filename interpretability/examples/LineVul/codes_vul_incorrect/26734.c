// commit message qemu@ed1dda53d0 (target=1, prob=0.18722951, correct=False): target-alpha: bug fix: avoid nop to override next instruction
/*0   */ static always_inline void gen_intermediate_code_internal (CPUState *env,         // (7) 0.03711
/*2   */                                                           TranslationBlock *tb,  // (0) 0.123
/*4   */                                                           int search_pc)         // (1) 0.1211
/*6   */ {                                                                                // (29) 0.001953
/*8   */ #if defined ALPHA_DEBUG_DISAS                                                    // (18) 0.01953
/*10  */     static int insn_count;                                                       // (19) 0.01953
/*12  */ #endif                                                                           // (26) 0.003906
/*14  */     DisasContext ctx, *ctxp = &ctx;                                              // (8) 0.03125
/*16  */     target_ulong pc_start;                                                       // (17) 0.02148
/*18  */     uint32_t insn;                                                               // (21) 0.01953
/*20  */     uint16_t *gen_opc_end;                                                       // (9) 0.0293
/*22  */     CPUBreakpoint *bp;                                                           // (22) 0.01758
/*24  */     int j, lj = -1;                                                              // (12) 0.02344
/*26  */     int ret;                                                                     // (25) 0.01172
/*28  */     int num_insns;                                                               // (24) 0.01758
/*30  */     int max_insns;                                                               // (23) 0.01758
/*34  */     pc_start = tb->pc;                                                           // (13) 0.02344
/*36  */     gen_opc_end = gen_opc_buf + OPC_MAX_SIZE;                                    // (3) 0.04687
/*38  */     ctx.pc = pc_start;                                                           // (15) 0.02344
/*40  */     ctx.amask = env->amask;                                                      // (10) 0.02734
/*42  */ #if defined (CONFIG_USER_ONLY)                                                   // (14) 0.02344
/*44  */     ctx.mem_idx = 0;                                                             // (11) 0.02539
/*46  */ #else                                                                            // (28) 0.003906
/*48  */     ctx.mem_idx = ((env->ps >> 3) & 3);                                          // (5) 0.04102
/*50  */     ctx.pal_mode = env->ipr[IPR_EXC_ADDR] & 1;                                   // (2) 0.05273
/*52  */ #endif                                                                           // (27) 0.003906
/*54  */     num_insns = 0;                                                               // (20) 0.01953
/*56  */     max_insns = tb->cflags & CF_COUNT_MASK;                                      // (4) 0.04297
/*58  */     if (max_insns == 0)                                                          // (16) 0.02344
/*60  */         max_insns = CF_COUNT_MASK;                                               // (6) 0.03906
/*64  */     gen_icount_start();                                                          // 0.0
/*66  */     for (ret = 0; ret == 0;) {                                                   // 0.0
/*68  */         if (unlikely(!TAILQ_EMPTY(&env->breakpoints))) {                         // 0.0
/*70  */             TAILQ_FOREACH(bp, &env->breakpoints, entry) {                        // 0.0
/*72  */                 if (bp->pc == ctx.pc) {                                          // 0.0
/*74  */                     gen_excp(&ctx, EXCP_DEBUG, 0);                               // 0.0
/*76  */                     break;                                                       // 0.0
/*78  */                 }                                                                // 0.0
/*80  */             }                                                                    // 0.0
/*82  */         }                                                                        // 0.0
/*84  */         if (search_pc) {                                                         // 0.0
/*86  */             j = gen_opc_ptr - gen_opc_buf;                                       // 0.0
/*88  */             if (lj < j) {                                                        // 0.0
/*90  */                 lj++;                                                            // 0.0
/*92  */                 while (lj < j)                                                   // 0.0
/*94  */                     gen_opc_instr_start[lj++] = 0;                               // 0.0
/*96  */                 gen_opc_pc[lj] = ctx.pc;                                         // 0.0
/*98  */                 gen_opc_instr_start[lj] = 1;                                     // 0.0
/*100 */                 gen_opc_icount[lj] = num_insns;                                  // 0.0
/*102 */             }                                                                    // 0.0
/*104 */         }                                                                        // 0.0
/*106 */         if (num_insns + 1 == max_insns && (tb->cflags & CF_LAST_IO))             // 0.0
/*108 */             gen_io_start();                                                      // 0.0
/*110 */ #if defined ALPHA_DEBUG_DISAS                                                    // 0.0
/*112 */         insn_count++;                                                            // 0.0
/*114 */         LOG_DISAS("pc " TARGET_FMT_lx " mem_idx %d\n",                           // 0.0
/*116 */                   ctx.pc, ctx.mem_idx);                                          // 0.0
/*118 */ #endif                                                                           // 0.0
/*120 */         insn = ldl_code(ctx.pc);                                                 // 0.0
/*122 */ #if defined ALPHA_DEBUG_DISAS                                                    // 0.0
/*124 */         insn_count++;                                                            // 0.0
/*126 */         LOG_DISAS("opcode %08x %d\n", insn, insn_count);                         // 0.0
/*128 */ #endif                                                                           // 0.0
/*130 */         num_insns++;                                                             // 0.0
/*132 */         ctx.pc += 4;                                                             // 0.0
/*134 */         ret = translate_one(ctxp, insn);                                         // 0.0
/*136 */         if (ret != 0)                                                            // 0.0
/*138 */             break;                                                               // 0.0
/*140 */         /* if we reach a page boundary or are single stepping, stop              // 0.0
/*142 */          * generation                                                            // 0.0
/*144 */          */                                                                      // 0.0
/*146 */         if (((ctx.pc & (TARGET_PAGE_SIZE - 1)) == 0) ||                          // 0.0
/*148 */             num_insns >= max_insns) {                                            // 0.0
/*150 */             break;                                                               // 0.0
/*152 */         }                                                                        // 0.0
/*156 */         if (env->singlestep_enabled) {                                           // 0.0
/*158 */             gen_excp(&ctx, EXCP_DEBUG, 0);                                       // 0.0
/*160 */             break;                                                               // 0.0
/*162 */ 	}                                                                               // 0.0
/*166 */ #if defined (DO_SINGLE_STEP)                                                     // 0.0
/*168 */         break;                                                                   // 0.0
/*170 */ #endif                                                                           // 0.0
/*172 */     }                                                                            // 0.0
/*174 */     if (ret != 1 && ret != 3) {                                                  // 0.0
/*176 */         tcg_gen_movi_i64(cpu_pc, ctx.pc);                                        // 0.0
/*178 */     }                                                                            // 0.0
/*180 */ #if defined (DO_TB_FLUSH)                                                        // 0.0
/*182 */     gen_helper_tb_flush();                                                       // 0.0
/*184 */ #endif                                                                           // 0.0
/*186 */     if (tb->cflags & CF_LAST_IO)                                                 // 0.0
/*188 */         gen_io_end();                                                            // 0.0
/*190 */     /* Generate the return instruction */                                        // 0.0
/*192 */     tcg_gen_exit_tb(0);                                                          // 0.0
/*194 */     gen_icount_end(tb, num_insns);                                               // 0.0
/*196 */     *gen_opc_ptr = INDEX_op_end;                                                 // 0.0
/*198 */     if (search_pc) {                                                             // 0.0
/*200 */         j = gen_opc_ptr - gen_opc_buf;                                           // 0.0
/*202 */         lj++;                                                                    // 0.0
/*204 */         while (lj <= j)                                                          // 0.0
/*206 */             gen_opc_instr_start[lj++] = 0;                                       // 0.0
/*208 */     } else {                                                                     // 0.0
/*210 */         tb->size = ctx.pc - pc_start;                                            // 0.0
/*212 */         tb->icount = num_insns;                                                  // 0.0
/*214 */     }                                                                            // 0.0
/*216 */ #if defined ALPHA_DEBUG_DISAS                                                    // 0.0
/*218 */     log_cpu_state_mask(CPU_LOG_TB_CPU, env, 0);                                  // 0.0
/*220 */     if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM)) {                                 // 0.0
/*222 */         qemu_log("IN: %s\n", lookup_symbol(pc_start));                           // 0.0
/*224 */         log_target_disas(pc_start, ctx.pc - pc_start, 1);                        // 0.0
/*226 */         qemu_log("\n");                                                          // 0.0
/*228 */     }                                                                            // 0.0
/*230 */ #endif                                                                           // 0.0
/*232 */ }                                                                                // 0.0

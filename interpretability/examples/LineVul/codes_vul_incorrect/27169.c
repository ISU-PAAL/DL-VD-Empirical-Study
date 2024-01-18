// commit message qemu@d9bce9d99f (target=1, prob=0.088997, correct=False): Make it safe to use 64 bits GPR and/or 64 bits host registers. For "symetry", add 64 bits versions of all modified functions. As a side effect, add a lot of code provision for PowerPC 64 support. Move overflow and carry checks in common routines for simple cases. Add isel and popcntb instructions from PowerPC 2.03 specification. Remove remaining micro-operations helpers prototypes from op.c. Fix XER_BC field to be 7 bits long. Add power management support for PowerPC 603 & 604. Fix compilation warnings.
/*0   */ int gen_intermediate_code_internal (CPUState *env, TranslationBlock *tb,       // (4) 0.04102
/*2   */                                     int search_pc)                             // (0) 0.07812
/*4   */ {                                                                              // (30) 0.001953
/*6   */     DisasContext ctx, *ctxp = &ctx;                                            // (9) 0.03125
/*8   */     opc_handler_t **table, *handler;                                           // (14) 0.0293
/*10  */     target_ulong pc_start;                                                     // (24) 0.02148
/*12  */     uint16_t *gen_opc_end;                                                     // (15) 0.0293
/*14  */     int j, lj = -1;                                                            // (20) 0.02344
/*18  */     pc_start = tb->pc;                                                         // (21) 0.02344
/*20  */     gen_opc_ptr = gen_opc_buf;                                                 // (8) 0.0332
/*22  */     gen_opc_end = gen_opc_buf + OPC_MAX_SIZE;                                  // (3) 0.04687
/*24  */     gen_opparam_ptr = gen_opparam_buf;                                         // (7) 0.0332
/*26  */     nb_gen_labels = 0;                                                         // (18) 0.02539
/*28  */     ctx.nip = pc_start;                                                        // (19) 0.02539
/*30  */     ctx.tb = tb;                                                               // (23) 0.02344
/*32  */     ctx.exception = EXCP_NONE;                                                 // (16) 0.0293
/*34  */     ctx.spr_cb = env->spr_cb;                                                  // (11) 0.03125
/*36  */ #if defined(CONFIG_USER_ONLY)                                                  // (22) 0.02344
/*38  */     ctx.mem_idx = msr_le;                                                      // (13) 0.03125
/*40  */ #else                                                                          // (28) 0.003906
/*42  */     ctx.supervisor = 1 - msr_pr;                                               // (12) 0.03125
/*44  */     ctx.mem_idx = ((1 - msr_pr) << 1) | msr_le;                                // (2) 0.05469
/*46  */ #endif                                                                         // (29) 0.003906
/*48  */     ctx.fpu_enabled = msr_fp;                                                  // (10) 0.03125
/*50  */     ctx.singlestep_enabled = env->singlestep_enabled;                          // (5) 0.03906
/*52  */ #if defined (DO_SINGLE_STEP) && 0                                              // (17) 0.02734
/*54  */     /* Single step trace mode */                                               // (26) 0.01758
/*56  */     msr_se = 1;                                                                // (25) 0.01953
/*58  */ #endif                                                                         // (27) 0.003906
/*60  */     /* Set env in case of segfault during code fetch */                        // (6) 0.0332
/*62  */     while (ctx.exception == EXCP_NONE && gen_opc_ptr < gen_opc_end) {          // (1) 0.06055
/*64  */         if (unlikely(env->nb_breakpoints > 0)) {                               // 0.0
/*66  */             for (j = 0; j < env->nb_breakpoints; j++) {                        // 0.0
/*68  */                 if (env->breakpoints[j] == ctx.nip) {                          // 0.0
/*70  */                     gen_op_update_nip(ctx.nip);                                // 0.0
/*72  */                     gen_op_debug();                                            // 0.0
/*74  */                     break;                                                     // 0.0
/*76  */                 }                                                              // 0.0
/*78  */             }                                                                  // 0.0
/*80  */         }                                                                      // 0.0
/*82  */         if (unlikely(search_pc)) {                                             // 0.0
/*84  */             j = gen_opc_ptr - gen_opc_buf;                                     // 0.0
/*86  */             if (lj < j) {                                                      // 0.0
/*88  */                 lj++;                                                          // 0.0
/*90  */                 while (lj < j)                                                 // 0.0
/*92  */                     gen_opc_instr_start[lj++] = 0;                             // 0.0
/*94  */                 gen_opc_pc[lj] = ctx.nip;                                      // 0.0
/*96  */                 gen_opc_instr_start[lj] = 1;                                   // 0.0
/*98  */             }                                                                  // 0.0
/*100 */         }                                                                      // 0.0
/*102 */ #if defined PPC_DEBUG_DISAS                                                    // 0.0
/*104 */         if (loglevel & CPU_LOG_TB_IN_ASM) {                                    // 0.0
/*106 */             fprintf(logfile, "----------------\n");                            // 0.0
/*108 */             fprintf(logfile, "nip=%08x super=%d ir=%d\n",                      // 0.0
/*110 */                     ctx.nip, 1 - msr_pr, msr_ir);                              // 0.0
/*112 */         }                                                                      // 0.0
/*114 */ #endif                                                                         // 0.0
/*116 */         ctx.opcode = ldl_code(ctx.nip);                                        // 0.0
/*118 */         if (msr_le) {                                                          // 0.0
/*120 */             ctx.opcode = ((ctx.opcode & 0xFF000000) >> 24) |                   // 0.0
/*122 */                 ((ctx.opcode & 0x00FF0000) >> 8) |                             // 0.0
/*124 */                 ((ctx.opcode & 0x0000FF00) << 8) |                             // 0.0
/*126 */                 ((ctx.opcode & 0x000000FF) << 24);                             // 0.0
/*128 */         }                                                                      // 0.0
/*130 */ #if defined PPC_DEBUG_DISAS                                                    // 0.0
/*132 */         if (loglevel & CPU_LOG_TB_IN_ASM) {                                    // 0.0
/*134 */             fprintf(logfile, "translate opcode %08x (%02x %02x %02x) (%s)\n",  // 0.0
/*136 */                     ctx.opcode, opc1(ctx.opcode), opc2(ctx.opcode),            // 0.0
/*138 */                     opc3(ctx.opcode), msr_le ? "little" : "big");              // 0.0
/*140 */         }                                                                      // 0.0
/*142 */ #endif                                                                         // 0.0
/*144 */         ctx.nip += 4;                                                          // 0.0
/*146 */         table = env->opcodes;                                                  // 0.0
/*148 */         handler = table[opc1(ctx.opcode)];                                     // 0.0
/*150 */         if (is_indirect_opcode(handler)) {                                     // 0.0
/*152 */             table = ind_table(handler);                                        // 0.0
/*154 */             handler = table[opc2(ctx.opcode)];                                 // 0.0
/*156 */             if (is_indirect_opcode(handler)) {                                 // 0.0
/*158 */                 table = ind_table(handler);                                    // 0.0
/*160 */                 handler = table[opc3(ctx.opcode)];                             // 0.0
/*162 */             }                                                                  // 0.0
/*164 */         }                                                                      // 0.0
/*166 */         /* Is opcode *REALLY* valid ? */                                       // 0.0
/*168 */         if (unlikely(handler->handler == &gen_invalid)) {                      // 0.0
/*170 */             if (loglevel > 0) {                                                // 0.0
/*172 */                 fprintf(logfile, "invalid/unsupported opcode: "                // 0.0
/*174 */                         "%02x - %02x - %02x (%08x) 0x%08x %d\n",               // 0.0
/*176 */                         opc1(ctx.opcode), opc2(ctx.opcode),                    // 0.0
/*178 */                         opc3(ctx.opcode), ctx.opcode, ctx.nip - 4, msr_ir);    // 0.0
/*180 */             } else {                                                           // 0.0
/*182 */                 printf("invalid/unsupported opcode: "                          // 0.0
/*184 */                        "%02x - %02x - %02x (%08x) 0x%08x %d\n",                // 0.0
/*186 */                        opc1(ctx.opcode), opc2(ctx.opcode),                     // 0.0
/*188 */                        opc3(ctx.opcode), ctx.opcode, ctx.nip - 4, msr_ir);     // 0.0
/*190 */             }                                                                  // 0.0
/*192 */         } else {                                                               // 0.0
/*194 */             if (unlikely((ctx.opcode & handler->inval) != 0)) {                // 0.0
/*196 */                 if (loglevel > 0) {                                            // 0.0
/*198 */                     fprintf(logfile, "invalid bits: %08x for opcode: "         // 0.0
/*200 */                             "%02x -%02x - %02x (0x%08x) (0x%08x)\n",           // 0.0
/*202 */                             ctx.opcode & handler->inval, opc1(ctx.opcode),     // 0.0
/*204 */                             opc2(ctx.opcode), opc3(ctx.opcode),                // 0.0
/*206 */                             ctx.opcode, ctx.nip - 4);                          // 0.0
/*208 */                 } else {                                                       // 0.0
/*210 */                     printf("invalid bits: %08x for opcode: "                   // 0.0
/*212 */                            "%02x -%02x - %02x (0x%08x) (0x%08x)\n",            // 0.0
/*214 */                            ctx.opcode & handler->inval, opc1(ctx.opcode),      // 0.0
/*216 */                            opc2(ctx.opcode), opc3(ctx.opcode),                 // 0.0
/*218 */                            ctx.opcode, ctx.nip - 4);                           // 0.0
/*220 */                 }                                                              // 0.0
/*222 */                 RET_INVAL(ctxp);                                               // 0.0
/*224 */                 break;                                                         // 0.0
/*226 */             }                                                                  // 0.0
/*228 */         }                                                                      // 0.0
/*230 */         (*(handler->handler))(&ctx);                                           // 0.0
/*232 */ #if defined(DO_PPC_STATISTICS)                                                 // 0.0
/*234 */         handler->count++;                                                      // 0.0
/*236 */ #endif                                                                         // 0.0
/*238 */         /* Check trace mode exceptions */                                      // 0.0
/*240 */         if (unlikely((msr_be && ctx.exception == EXCP_BRANCH) ||               // 0.0
/*242 */                      /* Check in single step trace mode                        // 0.0
/*244 */                       * we need to stop except if:                             // 0.0
/*246 */                       * - rfi, trap or syscall                                 // 0.0
/*248 */                       * - first instruction of an exception handler            // 0.0
/*250 */                       */                                                       // 0.0
/*252 */                      (msr_se && (ctx.nip < 0x100 ||                            // 0.0
/*254 */                                  ctx.nip > 0xF00 ||                            // 0.0
/*256 */                                  (ctx.nip & 0xFC) != 0x04) &&                  // 0.0
/*258 */                       ctx.exception != EXCP_SYSCALL &&                         // 0.0
/*260 */                       ctx.exception != EXCP_SYSCALL_USER &&                    // 0.0
/*262 */                       ctx.exception != EXCP_TRAP))) {                          // 0.0
/*264 */             RET_EXCP(ctxp, EXCP_TRACE, 0);                                     // 0.0
/*266 */         }                                                                      // 0.0
/*268 */         /* if we reach a page boundary or are single stepping, stop            // 0.0
/*270 */          * generation                                                          // 0.0
/*272 */          */                                                                    // 0.0
/*274 */         if (unlikely(((ctx.nip & (TARGET_PAGE_SIZE - 1)) == 0) ||              // 0.0
/*276 */                      (env->singlestep_enabled))) {                             // 0.0
/*278 */             break;                                                             // 0.0
/*280 */         }                                                                      // 0.0
/*282 */ #if defined (DO_SINGLE_STEP)                                                   // 0.0
/*284 */         break;                                                                 // 0.0
/*286 */ #endif                                                                         // 0.0
/*288 */     }                                                                          // 0.0
/*290 */     if (ctx.exception == EXCP_NONE) {                                          // 0.0
/*292 */         gen_goto_tb(&ctx, 0, ctx.nip);                                         // 0.0
/*294 */     } else if (ctx.exception != EXCP_BRANCH) {                                 // 0.0
/*296 */         gen_op_reset_T0();                                                     // 0.0
/*298 */         /* Generate the return instruction */                                  // 0.0
/*300 */         gen_op_exit_tb();                                                      // 0.0
/*302 */     }                                                                          // 0.0
/*304 */     *gen_opc_ptr = INDEX_op_end;                                               // 0.0
/*306 */     if (unlikely(search_pc)) {                                                 // 0.0
/*308 */         j = gen_opc_ptr - gen_opc_buf;                                         // 0.0
/*310 */         lj++;                                                                  // 0.0
/*312 */         while (lj <= j)                                                        // 0.0
/*314 */             gen_opc_instr_start[lj++] = 0;                                     // 0.0
/*316 */         tb->size = 0;                                                          // 0.0
/*318 */     } else {                                                                   // 0.0
/*320 */         tb->size = ctx.nip - pc_start;                                         // 0.0
/*322 */     }                                                                          // 0.0
/*324 */ #ifdef DEBUG_DISAS                                                             // 0.0
/*326 */     if (loglevel & CPU_LOG_TB_CPU) {                                           // 0.0
/*328 */         fprintf(logfile, "---------------- excp: %04x\n", ctx.exception);      // 0.0
/*330 */         cpu_dump_state(env, logfile, fprintf, 0);                              // 0.0
/*332 */     }                                                                          // 0.0
/*334 */     if (loglevel & CPU_LOG_TB_IN_ASM) {                                        // 0.0
/*336 */         int flags;                                                             // 0.0
/*338 */         flags = msr_le;                                                        // 0.0
/*340 */         fprintf(logfile, "IN: %s\n", lookup_symbol(pc_start));                 // 0.0
/*342 */         target_disas(logfile, pc_start, ctx.nip - pc_start, flags);            // 0.0
/*344 */         fprintf(logfile, "\n");                                                // 0.0
/*346 */     }                                                                          // 0.0
/*348 */     if (loglevel & CPU_LOG_TB_OP) {                                            // 0.0
/*350 */         fprintf(logfile, "OP:\n");                                             // 0.0
/*352 */         dump_ops(gen_opc_buf, gen_opparam_buf);                                // 0.0
/*354 */         fprintf(logfile, "\n");                                                // 0.0
/*356 */     }                                                                          // 0.0
/*358 */ #endif                                                                         // 0.0
/*360 */     return 0;                                                                  // 0.0
/*362 */ }                                                                              // 0.0

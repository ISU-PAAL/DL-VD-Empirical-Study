// commit message qemu@23dceda62a (target=0, prob=0.18917859, correct=True): tcg: Respect highwater in tcg_out_tb_finalize
/*0   */ int tcg_gen_code(TCGContext *s, tcg_insn_unit *gen_code_buf)                     // (0) 0.05469
/*2   */ {                                                                                // (36) 0.001953
/*4   */     int i, oi, oi_next, num_insns;                                               // (7) 0.03711
/*8   */ #ifdef CONFIG_PROFILER                                                           // (21) 0.01758
/*10  */     {                                                                            // (28) 0.007812
/*12  */         int n;                                                                   // (20) 0.01953
/*16  */         n = s->gen_last_op_idx + 1;                                              // (2) 0.04297
/*18  */         s->op_count += n;                                                        // (12) 0.0293
/*20  */         if (n > s->op_count_max) {                                               // (5) 0.03906
/*22  */             s->op_count_max = n;                                                 // (3) 0.04102
/*24  */         }                                                                        // (25) 0.01562
/*28  */         n = s->nb_temps;                                                         // (9) 0.03125
/*30  */         s->temp_count += n;                                                      // (13) 0.0293
/*32  */         if (n > s->temp_count_max) {                                             // (6) 0.03906
/*34  */             s->temp_count_max = n;                                               // (4) 0.04102
/*36  */         }                                                                        // (26) 0.01562
/*38  */     }                                                                            // (29) 0.007812
/*40  */ #endif                                                                           // (31) 0.003906
/*44  */ #ifdef DEBUG_DISAS                                                               // (27) 0.01367
/*46  */     if (unlikely(qemu_loglevel_mask(CPU_LOG_TB_OP))) {                           // (1) 0.05273
/*48  */         qemu_log("OP:\n");                                                       // (8) 0.0332
/*50  */         tcg_dump_ops(s);                                                         // (10) 0.03125
/*52  */         qemu_log("\n");                                                          // (11) 0.03125
/*54  */     }                                                                            // (30) 0.007812
/*56  */ #endif                                                                           // (32) 0.003906
/*60  */ #ifdef CONFIG_PROFILER                                                           // (22) 0.01758
/*62  */     s->opt_time -= profile_getclock();                                           // (14) 0.02734
/*64  */ #endif                                                                           // (33) 0.003906
/*68  */ #ifdef USE_TCG_OPTIMIZATIONS                                                     // (17) 0.02539
/*70  */     tcg_optimize(s);                                                             // (19) 0.02148
/*72  */ #endif                                                                           // (34) 0.003906
/*76  */ #ifdef CONFIG_PROFILER                                                           // (23) 0.01758
/*78  */     s->opt_time += profile_getclock();                                           // (15) 0.02734
/*80  */     s->la_time -= profile_getclock();                                            // (16) 0.02734
/*82  */ #endif                                                                           // (35) 0.003906
/*86  */     tcg_liveness_analysis(s);                                                    // (18) 0.02539
/*90  */ #ifdef CONFIG_PROFILER                                                           // (24) 0.01758
/*92  */     s->la_time += profile_getclock();                                            // 0.0
/*94  */ #endif                                                                           // 0.0
/*98  */ #ifdef DEBUG_DISAS                                                               // 0.0
/*100 */     if (unlikely(qemu_loglevel_mask(CPU_LOG_TB_OP_OPT))) {                       // 0.0
/*102 */         qemu_log("OP after optimization and liveness analysis:\n");              // 0.0
/*104 */         tcg_dump_ops(s);                                                         // 0.0
/*106 */         qemu_log("\n");                                                          // 0.0
/*108 */     }                                                                            // 0.0
/*110 */ #endif                                                                           // 0.0
/*114 */     tcg_reg_alloc_start(s);                                                      // 0.0
/*118 */     s->code_buf = gen_code_buf;                                                  // 0.0
/*120 */     s->code_ptr = gen_code_buf;                                                  // 0.0
/*124 */     tcg_out_tb_init(s);                                                          // 0.0
/*128 */     num_insns = -1;                                                              // 0.0
/*130 */     for (oi = s->gen_first_op_idx; oi >= 0; oi = oi_next) {                      // 0.0
/*132 */         TCGOp * const op = &s->gen_op_buf[oi];                                   // 0.0
/*134 */         TCGArg * const args = &s->gen_opparam_buf[op->args];                     // 0.0
/*136 */         TCGOpcode opc = op->opc;                                                 // 0.0
/*138 */         const TCGOpDef *def = &tcg_op_defs[opc];                                 // 0.0
/*140 */         uint16_t dead_args = s->op_dead_args[oi];                                // 0.0
/*142 */         uint8_t sync_args = s->op_sync_args[oi];                                 // 0.0
/*146 */         oi_next = op->next;                                                      // 0.0
/*148 */ #ifdef CONFIG_PROFILER                                                           // 0.0
/*150 */         tcg_table_op_count[opc]++;                                               // 0.0
/*152 */ #endif                                                                           // 0.0
/*156 */         switch (opc) {                                                           // 0.0
/*158 */         case INDEX_op_mov_i32:                                                   // 0.0
/*160 */         case INDEX_op_mov_i64:                                                   // 0.0
/*162 */             tcg_reg_alloc_mov(s, def, args, dead_args, sync_args);               // 0.0
/*164 */             break;                                                               // 0.0
/*166 */         case INDEX_op_movi_i32:                                                  // 0.0
/*168 */         case INDEX_op_movi_i64:                                                  // 0.0
/*170 */             tcg_reg_alloc_movi(s, args, dead_args, sync_args);                   // 0.0
/*172 */             break;                                                               // 0.0
/*174 */         case INDEX_op_insn_start:                                                // 0.0
/*176 */             if (num_insns >= 0) {                                                // 0.0
/*178 */                 s->gen_insn_end_off[num_insns] = tcg_current_code_size(s);       // 0.0
/*180 */             }                                                                    // 0.0
/*182 */             num_insns++;                                                         // 0.0
/*184 */             for (i = 0; i < TARGET_INSN_START_WORDS; ++i) {                      // 0.0
/*186 */                 target_ulong a;                                                  // 0.0
/*188 */ #if TARGET_LONG_BITS > TCG_TARGET_REG_BITS                                       // 0.0
/*190 */                 a = ((target_ulong)args[i * 2 + 1] << 32) | args[i * 2];         // 0.0
/*192 */ #else                                                                            // 0.0
/*194 */                 a = args[i];                                                     // 0.0
/*196 */ #endif                                                                           // 0.0
/*198 */                 s->gen_insn_data[num_insns][i] = a;                              // 0.0
/*200 */             }                                                                    // 0.0
/*202 */             break;                                                               // 0.0
/*204 */         case INDEX_op_discard:                                                   // 0.0
/*206 */             temp_dead(s, args[0]);                                               // 0.0
/*208 */             break;                                                               // 0.0
/*210 */         case INDEX_op_set_label:                                                 // 0.0
/*212 */             tcg_reg_alloc_bb_end(s, s->reserved_regs);                           // 0.0
/*214 */             tcg_out_label(s, arg_label(args[0]), s->code_ptr);                   // 0.0
/*216 */             break;                                                               // 0.0
/*218 */         case INDEX_op_call:                                                      // 0.0
/*220 */             tcg_reg_alloc_call(s, op->callo, op->calli, args,                    // 0.0
/*222 */                                dead_args, sync_args);                            // 0.0
/*224 */             break;                                                               // 0.0
/*226 */         default:                                                                 // 0.0
/*228 */             /* Sanity check that we've not introduced any unhandled opcodes. */  // 0.0
/*230 */             if (def->flags & TCG_OPF_NOT_PRESENT) {                              // 0.0
/*232 */                 tcg_abort();                                                     // 0.0
/*234 */             }                                                                    // 0.0
/*236 */             /* Note: in order to speed up the code, it would be much             // 0.0
/*238 */                faster to have specialized register allocator functions for       // 0.0
/*240 */                some common argument patterns */                                  // 0.0
/*242 */             tcg_reg_alloc_op(s, def, opc, args, dead_args, sync_args);           // 0.0
/*244 */             break;                                                               // 0.0
/*246 */         }                                                                        // 0.0
/*248 */ #ifndef NDEBUG                                                                   // 0.0
/*250 */         check_regs(s);                                                           // 0.0
/*252 */ #endif                                                                           // 0.0
/*254 */         /* Test for (pending) buffer overflow.  The assumption is that any       // 0.0
/*256 */            one operation beginning below the high water mark cannot overrun      // 0.0
/*258 */            the buffer completely.  Thus we can test for overflow after           // 0.0
/*260 */            generating code without having to check during generation.  */        // 0.0
/*262 */         if (unlikely((void *)s->code_ptr > s->code_gen_highwater)) {             // 0.0
/*264 */             return -1;                                                           // 0.0
/*266 */         }                                                                        // 0.0
/*268 */     }                                                                            // 0.0
/*270 */     tcg_debug_assert(num_insns >= 0);                                            // 0.0
/*272 */     s->gen_insn_end_off[num_insns] = tcg_current_code_size(s);                   // 0.0
/*276 */     /* Generate TB finalization at the end of block */                           // 0.0
/*278 */     tcg_out_tb_finalize(s);                                                      // 0.0
/*282 */     /* flush instruction cache */                                                // 0.0
/*284 */     flush_icache_range((uintptr_t)s->code_buf, (uintptr_t)s->code_ptr);          // 0.0
/*288 */     return tcg_current_code_size(s);                                             // 0.0
/*290 */ }                                                                                // 0.0

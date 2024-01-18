// commit message qemu@eabb7b91b3 (target=0, prob=0.50179744, correct=False): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0   */ static void tcg_reg_alloc_call(TCGContext *s, int nb_oargs, int nb_iargs,        // (4) 0.06055
/*2   */                                const TCGArg * const args, uint16_t dead_args,    // (0) 0.08984
/*4   */                                uint8_t sync_args)                                // (1) 0.07422
/*6   */ {                                                                                // (25) 0.001953
/*8   */     int flags, nb_regs, i;                                                       // (13) 0.02734
/*10  */     TCGReg reg;                                                                  // (20) 0.01562
/*12  */     TCGArg arg;                                                                  // (22) 0.01562
/*14  */     TCGTemp *ts;                                                                 // (19) 0.01758
/*16  */     intptr_t stack_offset;                                                       // (16) 0.02148
/*18  */     size_t call_stack_size;                                                      // (15) 0.02344
/*20  */     tcg_insn_unit *func_addr;                                                    // (12) 0.0293
/*22  */     int allocate_args;                                                           // (21) 0.01562
/*24  */     TCGRegSet allocated_regs;                                                    // (14) 0.02344
/*28  */     func_addr = (tcg_insn_unit *)(intptr_t)args[nb_oargs + nb_iargs];            // (2) 0.06836
/*30  */     flags = args[nb_oargs + nb_iargs + 1];                                       // (9) 0.03906
/*34  */     nb_regs = ARRAY_SIZE(tcg_target_call_iarg_regs);                             // (7) 0.05273
/*36  */     if (nb_regs > nb_iargs) {                                                    // (11) 0.0332
/*38  */         nb_regs = nb_iargs;                                                      // (10) 0.03711
/*40  */     }                                                                            // (23) 0.007812
/*44  */     /* assign stack slots first */                                               // (18) 0.01758
/*46  */     call_stack_size = (nb_iargs - nb_regs) * sizeof(tcg_target_long);            // (5) 0.06055
/*48  */     call_stack_size = (call_stack_size + TCG_TARGET_STACK_ALIGN - 1) &           // (3) 0.0625
/*50  */         ~(TCG_TARGET_STACK_ALIGN - 1);                                           // (8) 0.04492
/*52  */     allocate_args = (call_stack_size > TCG_STATIC_CALL_ARGS_SIZE);               // (6) 0.05469
/*54  */     if (allocate_args) {                                                         // (17) 0.02148
/*56  */         /* XXX: if more than TCG_STATIC_CALL_ARGS_SIZE is needed,                // 0.0
/*58  */            preallocate call stack */                                             // 0.0
/*60  */         tcg_abort();                                                             // 0.0
/*62  */     }                                                                            // 0.0
/*66  */     stack_offset = TCG_TARGET_CALL_STACK_OFFSET;                                 // 0.0
/*68  */     for(i = nb_regs; i < nb_iargs; i++) {                                        // 0.0
/*70  */         arg = args[nb_oargs + i];                                                // 0.0
/*72  */ #ifdef TCG_TARGET_STACK_GROWSUP                                                  // 0.0
/*74  */         stack_offset -= sizeof(tcg_target_long);                                 // 0.0
/*76  */ #endif                                                                           // 0.0
/*78  */         if (arg != TCG_CALL_DUMMY_ARG) {                                         // 0.0
/*80  */             ts = &s->temps[arg];                                                 // 0.0
/*82  */             temp_load(s, ts, tcg_target_available_regs[ts->type],                // 0.0
/*84  */                       s->reserved_regs);                                         // 0.0
/*86  */             tcg_out_st(s, ts->type, ts->reg, TCG_REG_CALL_STACK, stack_offset);  // 0.0
/*88  */         }                                                                        // 0.0
/*90  */ #ifndef TCG_TARGET_STACK_GROWSUP                                                 // 0.0
/*92  */         stack_offset += sizeof(tcg_target_long);                                 // 0.0
/*94  */ #endif                                                                           // 0.0
/*96  */     }                                                                            // 0.0
/*98  */                                                                                  // (24) 0.007812
/*100 */     /* assign input registers */                                                 // 0.0
/*102 */     tcg_regset_set(allocated_regs, s->reserved_regs);                            // 0.0
/*104 */     for(i = 0; i < nb_regs; i++) {                                               // 0.0
/*106 */         arg = args[nb_oargs + i];                                                // 0.0
/*108 */         if (arg != TCG_CALL_DUMMY_ARG) {                                         // 0.0
/*110 */             ts = &s->temps[arg];                                                 // 0.0
/*112 */             reg = tcg_target_call_iarg_regs[i];                                  // 0.0
/*114 */             tcg_reg_free(s, reg, allocated_regs);                                // 0.0
/*118 */             if (ts->val_type == TEMP_VAL_REG) {                                  // 0.0
/*120 */                 if (ts->reg != reg) {                                            // 0.0
/*122 */                     tcg_out_mov(s, ts->type, reg, ts->reg);                      // 0.0
/*124 */                 }                                                                // 0.0
/*126 */             } else {                                                             // 0.0
/*128 */                 TCGRegSet arg_set;                                               // 0.0
/*132 */                 tcg_regset_clear(arg_set);                                       // 0.0
/*134 */                 tcg_regset_set_reg(arg_set, reg);                                // 0.0
/*136 */                 temp_load(s, ts, arg_set, allocated_regs);                       // 0.0
/*138 */             }                                                                    // 0.0
/*142 */             tcg_regset_set_reg(allocated_regs, reg);                             // 0.0
/*144 */         }                                                                        // 0.0
/*146 */     }                                                                            // 0.0
/*148 */                                                                                  // 0.0
/*150 */     /* mark dead temporaries and free the associated registers */                // 0.0
/*152 */     for(i = nb_oargs; i < nb_iargs + nb_oargs; i++) {                            // 0.0
/*154 */         if (IS_DEAD_ARG(i)) {                                                    // 0.0
/*156 */             temp_dead(s, &s->temps[args[i]]);                                    // 0.0
/*158 */         }                                                                        // 0.0
/*160 */     }                                                                            // 0.0
/*162 */                                                                                  // 0.0
/*164 */     /* clobber call registers */                                                 // 0.0
/*166 */     for (i = 0; i < TCG_TARGET_NB_REGS; i++) {                                   // 0.0
/*168 */         if (tcg_regset_test_reg(tcg_target_call_clobber_regs, i)) {              // 0.0
/*170 */             tcg_reg_free(s, i, allocated_regs);                                  // 0.0
/*172 */         }                                                                        // 0.0
/*174 */     }                                                                            // 0.0
/*178 */     /* Save globals if they might be written by the helper, sync them if         // 0.0
/*180 */        they might be read. */                                                    // 0.0
/*182 */     if (flags & TCG_CALL_NO_READ_GLOBALS) {                                      // 0.0
/*184 */         /* Nothing to do */                                                      // 0.0
/*186 */     } else if (flags & TCG_CALL_NO_WRITE_GLOBALS) {                              // 0.0
/*188 */         sync_globals(s, allocated_regs);                                         // 0.0
/*190 */     } else {                                                                     // 0.0
/*192 */         save_globals(s, allocated_regs);                                         // 0.0
/*194 */     }                                                                            // 0.0
/*198 */     tcg_out_call(s, func_addr);                                                  // 0.0
/*202 */     /* assign output registers and emit moves if needed */                       // 0.0
/*204 */     for(i = 0; i < nb_oargs; i++) {                                              // 0.0
/*206 */         arg = args[i];                                                           // 0.0
/*208 */         ts = &s->temps[arg];                                                     // 0.0
/*210 */         reg = tcg_target_call_oarg_regs[i];                                      // 0.0
/*212 */         assert(s->reg_to_temp[reg] == NULL);                                     // 0.0
/*216 */         if (ts->fixed_reg) {                                                     // 0.0
/*218 */             if (ts->reg != reg) {                                                // 0.0
/*220 */                 tcg_out_mov(s, ts->type, ts->reg, reg);                          // 0.0
/*222 */             }                                                                    // 0.0
/*224 */         } else {                                                                 // 0.0
/*226 */             if (ts->val_type == TEMP_VAL_REG) {                                  // 0.0
/*228 */                 s->reg_to_temp[ts->reg] = NULL;                                  // 0.0
/*230 */             }                                                                    // 0.0
/*232 */             ts->val_type = TEMP_VAL_REG;                                         // 0.0
/*234 */             ts->reg = reg;                                                       // 0.0
/*236 */             ts->mem_coherent = 0;                                                // 0.0
/*238 */             s->reg_to_temp[reg] = ts;                                            // 0.0
/*240 */             if (NEED_SYNC_ARG(i)) {                                              // 0.0
/*242 */                 tcg_reg_sync(s, reg, allocated_regs);                            // 0.0
/*244 */             }                                                                    // 0.0
/*246 */             if (IS_DEAD_ARG(i)) {                                                // 0.0
/*248 */                 temp_dead(s, ts);                                                // 0.0
/*250 */             }                                                                    // 0.0
/*252 */         }                                                                        // 0.0
/*254 */     }                                                                            // 0.0
/*256 */ }                                                                                // 0.0

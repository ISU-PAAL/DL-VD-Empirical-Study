// commit message qemu@42a268c241 (target=0, prob=0.23842877, correct=True): tcg: Change translator-side labels to a pointer
/*0    */ static int decode_opc(MoxieCPU *cpu, DisasContext *ctx)                         // (7) 0.03906
/*2    */ {                                                                               // (19) 0.001953
/*4    */     CPUMoxieState *env = &cpu->env;                                             // (9) 0.03125
/*8    */     /* Local cache for the instruction opcode.  */                              // (11) 0.02734
/*10   */     int opcode;                                                                 // (17) 0.01367
/*12   */     /* Set the default instruction length.  */                                  // (13) 0.02344
/*14   */     int length = 2;                                                             // (16) 0.01562
/*18   */     if (unlikely(qemu_loglevel_mask(CPU_LOG_TB_OP | CPU_LOG_TB_OP_OPT))) {      // (3) 0.07422
/*20   */         tcg_gen_debug_insn_start(ctx->pc);                                      // (5) 0.04492
/*22   */     }                                                                           // (18) 0.007812
/*26   */     /* Examine the 16-bit opcode.  */                                           // (10) 0.0293
/*28   */     opcode = ctx->opcode;                                                       // (14) 0.02344
/*32   */     /* Decode instruction.  */                                                  // (15) 0.01953
/*34   */     if (opcode & (1 << 15)) {                                                   // (12) 0.02734
/*36   */         if (opcode & (1 << 14)) {                                               // (8) 0.03516
/*38   */             /* This is a Form 3 instruction.  */                                // (6) 0.04102
/*40   */             int inst = (opcode >> 10 & 0xf);                                    // (4) 0.04492
/*44   */ #define BRANCH(cond)                                                         \  // (1) 0.127
/*46   */     do {                                                                     \  // (0) 0.1445
/*48   */         int l1 = gen_new_label();                                            \  // (2) 0.1191
/*50   */         tcg_gen_brcond_i32(cond, cc_a, cc_b, l1);                            \  // 0.0
/*52   */         gen_goto_tb(env, ctx, 1, ctx->pc+2);                                 \  // 0.0
/*54   */         gen_set_label(l1);                                                   \  // 0.0
/*56   */         gen_goto_tb(env, ctx, 0, extract_branch_offset(opcode) + ctx->pc+2); \  // 0.0
/*58   */         ctx->bstate = BS_BRANCH;                                             \  // 0.0
/*60   */     } while (0)                                                                 // 0.0
/*64   */             switch (inst) {                                                     // 0.0
/*66   */             case 0x00: /* beq */                                                // 0.0
/*68   */                 BRANCH(TCG_COND_EQ);                                            // 0.0
/*70   */                 break;                                                          // 0.0
/*72   */             case 0x01: /* bne */                                                // 0.0
/*74   */                 BRANCH(TCG_COND_NE);                                            // 0.0
/*76   */                 break;                                                          // 0.0
/*78   */             case 0x02: /* blt */                                                // 0.0
/*80   */                 BRANCH(TCG_COND_LT);                                            // 0.0
/*82   */                 break;                                                          // 0.0
/*84   */             case 0x03: /* bgt */                                                // 0.0
/*86   */                 BRANCH(TCG_COND_GT);                                            // 0.0
/*88   */                 break;                                                          // 0.0
/*90   */             case 0x04: /* bltu */                                               // 0.0
/*92   */                 BRANCH(TCG_COND_LTU);                                           // 0.0
/*94   */                 break;                                                          // 0.0
/*96   */             case 0x05: /* bgtu */                                               // 0.0
/*98   */                 BRANCH(TCG_COND_GTU);                                           // 0.0
/*100  */                 break;                                                          // 0.0
/*102  */             case 0x06: /* bge */                                                // 0.0
/*104  */                 BRANCH(TCG_COND_GE);                                            // 0.0
/*106  */                 break;                                                          // 0.0
/*108  */             case 0x07: /* ble */                                                // 0.0
/*110  */                 BRANCH(TCG_COND_LE);                                            // 0.0
/*112  */                 break;                                                          // 0.0
/*114  */             case 0x08: /* bgeu */                                               // 0.0
/*116  */                 BRANCH(TCG_COND_GEU);                                           // 0.0
/*118  */                 break;                                                          // 0.0
/*120  */             case 0x09: /* bleu */                                               // 0.0
/*122  */                 BRANCH(TCG_COND_LEU);                                           // 0.0
/*124  */                 break;                                                          // 0.0
/*126  */             default:                                                            // 0.0
/*128  */                 {                                                               // 0.0
/*130  */                     TCGv temp = tcg_temp_new_i32();                             // 0.0
/*132  */                     tcg_gen_movi_i32(cpu_pc, ctx->pc);                          // 0.0
/*134  */                     tcg_gen_movi_i32(temp, MOXIE_EX_BAD);                       // 0.0
/*136  */                     gen_helper_raise_exception(cpu_env, temp);                  // 0.0
/*138  */                     tcg_temp_free_i32(temp);                                    // 0.0
/*140  */                 }                                                               // 0.0
/*142  */                 break;                                                          // 0.0
/*144  */             }                                                                   // 0.0
/*146  */         } else {                                                                // 0.0
/*148  */             /* This is a Form 2 instruction.  */                                // 0.0
/*150  */             int inst = (opcode >> 12 & 0x3);                                    // 0.0
/*152  */             switch (inst) {                                                     // 0.0
/*154  */             case 0x00: /* inc */                                                // 0.0
/*156  */                 {                                                               // 0.0
/*158  */                     int a = (opcode >> 8) & 0xf;                                // 0.0
/*160  */                     unsigned int v = (opcode & 0xff);                           // 0.0
/*162  */                     tcg_gen_addi_i32(REG(a), REG(a), v);                        // 0.0
/*164  */                 }                                                               // 0.0
/*166  */                 break;                                                          // 0.0
/*168  */             case 0x01: /* dec */                                                // 0.0
/*170  */                 {                                                               // 0.0
/*172  */                     int a = (opcode >> 8) & 0xf;                                // 0.0
/*174  */                     unsigned int v = (opcode & 0xff);                           // 0.0
/*176  */                     tcg_gen_subi_i32(REG(a), REG(a), v);                        // 0.0
/*178  */                 }                                                               // 0.0
/*180  */                 break;                                                          // 0.0
/*182  */             case 0x02: /* gsr */                                                // 0.0
/*184  */                 {                                                               // 0.0
/*186  */                     int a = (opcode >> 8) & 0xf;                                // 0.0
/*188  */                     unsigned v = (opcode & 0xff);                               // 0.0
/*190  */                     tcg_gen_ld_i32(REG(a), cpu_env,                             // 0.0
/*192  */                                    offsetof(CPUMoxieState, sregs[v]));          // 0.0
/*194  */                 }                                                               // 0.0
/*196  */                 break;                                                          // 0.0
/*198  */             case 0x03: /* ssr */                                                // 0.0
/*200  */                 {                                                               // 0.0
/*202  */                     int a = (opcode >> 8) & 0xf;                                // 0.0
/*204  */                     unsigned v = (opcode & 0xff);                               // 0.0
/*206  */                     tcg_gen_st_i32(REG(a), cpu_env,                             // 0.0
/*208  */                                    offsetof(CPUMoxieState, sregs[v]));          // 0.0
/*210  */                 }                                                               // 0.0
/*212  */                 break;                                                          // 0.0
/*214  */             default:                                                            // 0.0
/*216  */                 {                                                               // 0.0
/*218  */                     TCGv temp = tcg_temp_new_i32();                             // 0.0
/*220  */                     tcg_gen_movi_i32(cpu_pc, ctx->pc);                          // 0.0
/*222  */                     tcg_gen_movi_i32(temp, MOXIE_EX_BAD);                       // 0.0
/*224  */                     gen_helper_raise_exception(cpu_env, temp);                  // 0.0
/*226  */                     tcg_temp_free_i32(temp);                                    // 0.0
/*228  */                 }                                                               // 0.0
/*230  */                 break;                                                          // 0.0
/*232  */             }                                                                   // 0.0
/*234  */         }                                                                       // 0.0
/*236  */     } else {                                                                    // 0.0
/*238  */         /* This is a Form 1 instruction.  */                                    // 0.0
/*240  */         int inst = opcode >> 8;                                                 // 0.0
/*242  */         switch (inst) {                                                         // 0.0
/*244  */         case 0x00: /* nop */                                                    // 0.0
/*246  */             break;                                                              // 0.0
/*248  */         case 0x01: /* ldi.l (immediate) */                                      // 0.0
/*250  */             {                                                                   // 0.0
/*252  */                 int reg = (opcode >> 4) & 0xf;                                  // 0.0
/*254  */                 int val = cpu_ldl_code(env, ctx->pc+2);                         // 0.0
/*256  */                 tcg_gen_movi_i32(REG(reg), val);                                // 0.0
/*258  */                 length = 6;                                                     // 0.0
/*260  */             }                                                                   // 0.0
/*262  */             break;                                                              // 0.0
/*264  */         case 0x02: /* mov (register-to-register) */                             // 0.0
/*266  */             {                                                                   // 0.0
/*268  */                 int dest  = (opcode >> 4) & 0xf;                                // 0.0
/*270  */                 int src = opcode & 0xf;                                         // 0.0
/*272  */                 tcg_gen_mov_i32(REG(dest), REG(src));                           // 0.0
/*274  */             }                                                                   // 0.0
/*276  */             break;                                                              // 0.0
/*278  */         case 0x03: /* jsra */                                                   // 0.0
/*280  */             {                                                                   // 0.0
/*282  */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*284  */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*288  */                 tcg_gen_movi_i32(t1, ctx->pc + 6);                              // 0.0
/*292  */                 /* Make space for the static chain and return address.  */      // 0.0
/*294  */                 tcg_gen_subi_i32(t2, REG(1), 8);                                // 0.0
/*296  */                 tcg_gen_mov_i32(REG(1), t2);                                    // 0.0
/*298  */                 tcg_gen_qemu_st32(t1, REG(1), ctx->memidx);                     // 0.0
/*302  */                 /* Push the current frame pointer.  */                          // 0.0
/*304  */                 tcg_gen_subi_i32(t2, REG(1), 4);                                // 0.0
/*306  */                 tcg_gen_mov_i32(REG(1), t2);                                    // 0.0
/*308  */                 tcg_gen_qemu_st32(REG(0), REG(1), ctx->memidx);                 // 0.0
/*312  */                 /* Set the pc and $fp.  */                                      // 0.0
/*314  */                 tcg_gen_mov_i32(REG(0), REG(1));                                // 0.0
/*318  */                 gen_goto_tb(env, ctx, 0, cpu_ldl_code(env, ctx->pc+2));         // 0.0
/*322  */                 tcg_temp_free_i32(t1);                                          // 0.0
/*324  */                 tcg_temp_free_i32(t2);                                          // 0.0
/*328  */                 ctx->bstate = BS_BRANCH;                                        // 0.0
/*330  */                 length = 6;                                                     // 0.0
/*332  */             }                                                                   // 0.0
/*334  */             break;                                                              // 0.0
/*336  */         case 0x04: /* ret */                                                    // 0.0
/*338  */             {                                                                   // 0.0
/*340  */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*344  */                 /* The new $sp is the old $fp.  */                              // 0.0
/*346  */                 tcg_gen_mov_i32(REG(1), REG(0));                                // 0.0
/*350  */                 /* Pop the frame pointer.  */                                   // 0.0
/*352  */                 tcg_gen_qemu_ld32u(REG(0), REG(1), ctx->memidx);                // 0.0
/*354  */                 tcg_gen_addi_i32(t1, REG(1), 4);                                // 0.0
/*356  */                 tcg_gen_mov_i32(REG(1), t1);                                    // 0.0
/*362  */                 /* Pop the return address and skip over the static chain        // 0.0
/*364  */                    slot.  */                                                    // 0.0
/*366  */                 tcg_gen_qemu_ld32u(cpu_pc, REG(1), ctx->memidx);                // 0.0
/*368  */                 tcg_gen_addi_i32(t1, REG(1), 8);                                // 0.0
/*370  */                 tcg_gen_mov_i32(REG(1), t1);                                    // 0.0
/*374  */                 tcg_temp_free_i32(t1);                                          // 0.0
/*378  */                 /* Jump... */                                                   // 0.0
/*380  */                 tcg_gen_exit_tb(0);                                             // 0.0
/*384  */                 ctx->bstate = BS_BRANCH;                                        // 0.0
/*386  */             }                                                                   // 0.0
/*388  */             break;                                                              // 0.0
/*390  */         case 0x05: /* add.l */                                                  // 0.0
/*392  */             {                                                                   // 0.0
/*394  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*396  */                 int b = opcode & 0xf;                                           // 0.0
/*400  */                 tcg_gen_add_i32(REG(a), REG(a), REG(b));                        // 0.0
/*402  */             }                                                                   // 0.0
/*404  */             break;                                                              // 0.0
/*406  */         case 0x06: /* push */                                                   // 0.0
/*408  */             {                                                                   // 0.0
/*410  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*412  */                 int b = opcode & 0xf;                                           // 0.0
/*416  */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*418  */                 tcg_gen_subi_i32(t1, REG(a), 4);                                // 0.0
/*420  */                 tcg_gen_mov_i32(REG(a), t1);                                    // 0.0
/*422  */                 tcg_gen_qemu_st32(REG(b), REG(a), ctx->memidx);                 // 0.0
/*424  */                 tcg_temp_free_i32(t1);                                          // 0.0
/*426  */             }                                                                   // 0.0
/*428  */             break;                                                              // 0.0
/*430  */         case 0x07: /* pop */                                                    // 0.0
/*432  */             {                                                                   // 0.0
/*434  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*436  */                 int b = opcode & 0xf;                                           // 0.0
/*438  */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*442  */                 tcg_gen_qemu_ld32u(REG(b), REG(a), ctx->memidx);                // 0.0
/*444  */                 tcg_gen_addi_i32(t1, REG(a), 4);                                // 0.0
/*446  */                 tcg_gen_mov_i32(REG(a), t1);                                    // 0.0
/*448  */                 tcg_temp_free_i32(t1);                                          // 0.0
/*450  */             }                                                                   // 0.0
/*452  */             break;                                                              // 0.0
/*454  */         case 0x08: /* lda.l */                                                  // 0.0
/*456  */             {                                                                   // 0.0
/*458  */                 int reg = (opcode >> 4) & 0xf;                                  // 0.0
/*462  */                 TCGv ptr = tcg_temp_new_i32();                                  // 0.0
/*464  */                 tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));            // 0.0
/*466  */                 tcg_gen_qemu_ld32u(REG(reg), ptr, ctx->memidx);                 // 0.0
/*468  */                 tcg_temp_free_i32(ptr);                                         // 0.0
/*472  */                 length = 6;                                                     // 0.0
/*474  */             }                                                                   // 0.0
/*476  */             break;                                                              // 0.0
/*478  */         case 0x09: /* sta.l */                                                  // 0.0
/*480  */             {                                                                   // 0.0
/*482  */                 int val = (opcode >> 4) & 0xf;                                  // 0.0
/*486  */                 TCGv ptr = tcg_temp_new_i32();                                  // 0.0
/*488  */                 tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));            // 0.0
/*490  */                 tcg_gen_qemu_st32(REG(val), ptr, ctx->memidx);                  // 0.0
/*492  */                 tcg_temp_free_i32(ptr);                                         // 0.0
/*496  */                 length = 6;                                                     // 0.0
/*498  */             }                                                                   // 0.0
/*500  */             break;                                                              // 0.0
/*502  */         case 0x0a: /* ld.l (register indirect) */                               // 0.0
/*504  */             {                                                                   // 0.0
/*506  */                 int src  = opcode & 0xf;                                        // 0.0
/*508  */                 int dest = (opcode >> 4) & 0xf;                                 // 0.0
/*512  */                 tcg_gen_qemu_ld32u(REG(dest), REG(src), ctx->memidx);           // 0.0
/*514  */             }                                                                   // 0.0
/*516  */             break;                                                              // 0.0
/*518  */         case 0x0b: /* st.l */                                                   // 0.0
/*520  */             {                                                                   // 0.0
/*522  */                 int dest = (opcode >> 4) & 0xf;                                 // 0.0
/*524  */                 int val  = opcode & 0xf;                                        // 0.0
/*528  */                 tcg_gen_qemu_st32(REG(val), REG(dest), ctx->memidx);            // 0.0
/*530  */             }                                                                   // 0.0
/*532  */             break;                                                              // 0.0
/*534  */         case 0x0c: /* ldo.l */                                                  // 0.0
/*536  */             {                                                                   // 0.0
/*538  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*540  */                 int b = opcode & 0xf;                                           // 0.0
/*544  */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*546  */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*548  */                 tcg_gen_addi_i32(t1, REG(b), cpu_ldl_code(env, ctx->pc+2));     // 0.0
/*550  */                 tcg_gen_qemu_ld32u(t2, t1, ctx->memidx);                        // 0.0
/*552  */                 tcg_gen_mov_i32(REG(a), t2);                                    // 0.0
/*556  */                 tcg_temp_free_i32(t1);                                          // 0.0
/*558  */                 tcg_temp_free_i32(t2);                                          // 0.0
/*562  */                 length = 6;                                                     // 0.0
/*564  */             }                                                                   // 0.0
/*566  */             break;                                                              // 0.0
/*568  */         case 0x0d: /* sto.l */                                                  // 0.0
/*570  */             {                                                                   // 0.0
/*572  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*574  */                 int b = opcode & 0xf;                                           // 0.0
/*578  */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*580  */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*582  */                 tcg_gen_addi_i32(t1, REG(a), cpu_ldl_code(env, ctx->pc+2));     // 0.0
/*584  */                 tcg_gen_qemu_st32(REG(b), t1, ctx->memidx);                     // 0.0
/*588  */                 tcg_temp_free_i32(t1);                                          // 0.0
/*590  */                 tcg_temp_free_i32(t2);                                          // 0.0
/*594  */                 length = 6;                                                     // 0.0
/*596  */             }                                                                   // 0.0
/*598  */             break;                                                              // 0.0
/*600  */         case 0x0e: /* cmp */                                                    // 0.0
/*602  */             {                                                                   // 0.0
/*604  */                 int a  = (opcode >> 4) & 0xf;                                   // 0.0
/*606  */                 int b  = opcode & 0xf;                                          // 0.0
/*610  */                 tcg_gen_mov_i32(cc_a, REG(a));                                  // 0.0
/*612  */                 tcg_gen_mov_i32(cc_b, REG(b));                                  // 0.0
/*614  */             }                                                                   // 0.0
/*616  */             break;                                                              // 0.0
/*618  */         case 0x19: /* jsr */                                                    // 0.0
/*620  */             {                                                                   // 0.0
/*622  */                 int fnreg = (opcode >> 4) & 0xf;                                // 0.0
/*626  */                 /* Load the stack pointer into T0.  */                          // 0.0
/*628  */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*630  */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*634  */                 tcg_gen_movi_i32(t1, ctx->pc+2);                                // 0.0
/*638  */                 /* Make space for the static chain and return address.  */      // 0.0
/*640  */                 tcg_gen_subi_i32(t2, REG(1), 8);                                // 0.0
/*642  */                 tcg_gen_mov_i32(REG(1), t2);                                    // 0.0
/*644  */                 tcg_gen_qemu_st32(t1, REG(1), ctx->memidx);                     // 0.0
/*648  */                 /* Push the current frame pointer.  */                          // 0.0
/*650  */                 tcg_gen_subi_i32(t2, REG(1), 4);                                // 0.0
/*652  */                 tcg_gen_mov_i32(REG(1), t2);                                    // 0.0
/*654  */                 tcg_gen_qemu_st32(REG(0), REG(1), ctx->memidx);                 // 0.0
/*658  */                 /* Set the pc and $fp.  */                                      // 0.0
/*660  */                 tcg_gen_mov_i32(REG(0), REG(1));                                // 0.0
/*662  */                 tcg_gen_mov_i32(cpu_pc, REG(fnreg));                            // 0.0
/*664  */                 tcg_temp_free_i32(t1);                                          // 0.0
/*666  */                 tcg_temp_free_i32(t2);                                          // 0.0
/*668  */                 tcg_gen_exit_tb(0);                                             // 0.0
/*670  */                 ctx->bstate = BS_BRANCH;                                        // 0.0
/*672  */             }                                                                   // 0.0
/*674  */             break;                                                              // 0.0
/*676  */         case 0x1a: /* jmpa */                                                   // 0.0
/*678  */             {                                                                   // 0.0
/*680  */                 tcg_gen_movi_i32(cpu_pc, cpu_ldl_code(env, ctx->pc+2));         // 0.0
/*682  */                 tcg_gen_exit_tb(0);                                             // 0.0
/*684  */                 ctx->bstate = BS_BRANCH;                                        // 0.0
/*686  */                 length = 6;                                                     // 0.0
/*688  */             }                                                                   // 0.0
/*690  */             break;                                                              // 0.0
/*692  */         case 0x1b: /* ldi.b (immediate) */                                      // 0.0
/*694  */             {                                                                   // 0.0
/*696  */                 int reg = (opcode >> 4) & 0xf;                                  // 0.0
/*698  */                 int val = cpu_ldl_code(env, ctx->pc+2);                         // 0.0
/*700  */                 tcg_gen_movi_i32(REG(reg), val);                                // 0.0
/*702  */                 length = 6;                                                     // 0.0
/*704  */             }                                                                   // 0.0
/*706  */             break;                                                              // 0.0
/*708  */         case 0x1c: /* ld.b (register indirect) */                               // 0.0
/*710  */             {                                                                   // 0.0
/*712  */                 int src  = opcode & 0xf;                                        // 0.0
/*714  */                 int dest = (opcode >> 4) & 0xf;                                 // 0.0
/*718  */                 tcg_gen_qemu_ld8u(REG(dest), REG(src), ctx->memidx);            // 0.0
/*720  */             }                                                                   // 0.0
/*722  */             break;                                                              // 0.0
/*724  */         case 0x1d: /* lda.b */                                                  // 0.0
/*726  */             {                                                                   // 0.0
/*728  */                 int reg = (opcode >> 4) & 0xf;                                  // 0.0
/*732  */                 TCGv ptr = tcg_temp_new_i32();                                  // 0.0
/*734  */                 tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));            // 0.0
/*736  */                 tcg_gen_qemu_ld8u(REG(reg), ptr, ctx->memidx);                  // 0.0
/*738  */                 tcg_temp_free_i32(ptr);                                         // 0.0
/*742  */                 length = 6;                                                     // 0.0
/*744  */             }                                                                   // 0.0
/*746  */             break;                                                              // 0.0
/*748  */         case 0x1e: /* st.b */                                                   // 0.0
/*750  */             {                                                                   // 0.0
/*752  */                 int dest = (opcode >> 4) & 0xf;                                 // 0.0
/*754  */                 int val  = opcode & 0xf;                                        // 0.0
/*758  */                 tcg_gen_qemu_st8(REG(val), REG(dest), ctx->memidx);             // 0.0
/*760  */             }                                                                   // 0.0
/*762  */             break;                                                              // 0.0
/*764  */         case 0x1f: /* sta.b */                                                  // 0.0
/*766  */             {                                                                   // 0.0
/*768  */                 int val = (opcode >> 4) & 0xf;                                  // 0.0
/*772  */                 TCGv ptr = tcg_temp_new_i32();                                  // 0.0
/*774  */                 tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));            // 0.0
/*776  */                 tcg_gen_qemu_st8(REG(val), ptr, ctx->memidx);                   // 0.0
/*778  */                 tcg_temp_free_i32(ptr);                                         // 0.0
/*782  */                 length = 6;                                                     // 0.0
/*784  */             }                                                                   // 0.0
/*786  */             break;                                                              // 0.0
/*788  */         case 0x20: /* ldi.s (immediate) */                                      // 0.0
/*790  */             {                                                                   // 0.0
/*792  */                 int reg = (opcode >> 4) & 0xf;                                  // 0.0
/*794  */                 int val = cpu_ldl_code(env, ctx->pc+2);                         // 0.0
/*796  */                 tcg_gen_movi_i32(REG(reg), val);                                // 0.0
/*798  */                 length = 6;                                                     // 0.0
/*800  */             }                                                                   // 0.0
/*802  */             break;                                                              // 0.0
/*804  */         case 0x21: /* ld.s (register indirect) */                               // 0.0
/*806  */             {                                                                   // 0.0
/*808  */                 int src  = opcode & 0xf;                                        // 0.0
/*810  */                 int dest = (opcode >> 4) & 0xf;                                 // 0.0
/*814  */                 tcg_gen_qemu_ld16u(REG(dest), REG(src), ctx->memidx);           // 0.0
/*816  */             }                                                                   // 0.0
/*818  */             break;                                                              // 0.0
/*820  */         case 0x22: /* lda.s */                                                  // 0.0
/*822  */             {                                                                   // 0.0
/*824  */                 int reg = (opcode >> 4) & 0xf;                                  // 0.0
/*828  */                 TCGv ptr = tcg_temp_new_i32();                                  // 0.0
/*830  */                 tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));            // 0.0
/*832  */                 tcg_gen_qemu_ld16u(REG(reg), ptr, ctx->memidx);                 // 0.0
/*834  */                 tcg_temp_free_i32(ptr);                                         // 0.0
/*838  */                 length = 6;                                                     // 0.0
/*840  */             }                                                                   // 0.0
/*842  */             break;                                                              // 0.0
/*844  */         case 0x23: /* st.s */                                                   // 0.0
/*846  */             {                                                                   // 0.0
/*848  */                 int dest = (opcode >> 4) & 0xf;                                 // 0.0
/*850  */                 int val  = opcode & 0xf;                                        // 0.0
/*854  */                 tcg_gen_qemu_st16(REG(val), REG(dest), ctx->memidx);            // 0.0
/*856  */             }                                                                   // 0.0
/*858  */             break;                                                              // 0.0
/*860  */         case 0x24: /* sta.s */                                                  // 0.0
/*862  */             {                                                                   // 0.0
/*864  */                 int val = (opcode >> 4) & 0xf;                                  // 0.0
/*868  */                 TCGv ptr = tcg_temp_new_i32();                                  // 0.0
/*870  */                 tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));            // 0.0
/*872  */                 tcg_gen_qemu_st16(REG(val), ptr, ctx->memidx);                  // 0.0
/*874  */                 tcg_temp_free_i32(ptr);                                         // 0.0
/*878  */                 length = 6;                                                     // 0.0
/*880  */             }                                                                   // 0.0
/*882  */             break;                                                              // 0.0
/*884  */         case 0x25: /* jmp */                                                    // 0.0
/*886  */             {                                                                   // 0.0
/*888  */                 int reg = (opcode >> 4) & 0xf;                                  // 0.0
/*890  */                 tcg_gen_mov_i32(cpu_pc, REG(reg));                              // 0.0
/*892  */                 tcg_gen_exit_tb(0);                                             // 0.0
/*894  */                 ctx->bstate = BS_BRANCH;                                        // 0.0
/*896  */             }                                                                   // 0.0
/*898  */             break;                                                              // 0.0
/*900  */         case 0x26: /* and */                                                    // 0.0
/*902  */             {                                                                   // 0.0
/*904  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*906  */                 int b = opcode & 0xf;                                           // 0.0
/*910  */                 tcg_gen_and_i32(REG(a), REG(a), REG(b));                        // 0.0
/*912  */             }                                                                   // 0.0
/*914  */             break;                                                              // 0.0
/*916  */         case 0x27: /* lshr */                                                   // 0.0
/*918  */             {                                                                   // 0.0
/*920  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*922  */                 int b = opcode & 0xf;                                           // 0.0
/*926  */                 TCGv sv = tcg_temp_new_i32();                                   // 0.0
/*928  */                 tcg_gen_andi_i32(sv, REG(b), 0x1f);                             // 0.0
/*930  */                 tcg_gen_shr_i32(REG(a), REG(a), sv);                            // 0.0
/*932  */                 tcg_temp_free_i32(sv);                                          // 0.0
/*934  */             }                                                                   // 0.0
/*936  */             break;                                                              // 0.0
/*938  */         case 0x28: /* ashl */                                                   // 0.0
/*940  */             {                                                                   // 0.0
/*942  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*944  */                 int b = opcode & 0xf;                                           // 0.0
/*948  */                 TCGv sv = tcg_temp_new_i32();                                   // 0.0
/*950  */                 tcg_gen_andi_i32(sv, REG(b), 0x1f);                             // 0.0
/*952  */                 tcg_gen_shl_i32(REG(a), REG(a), sv);                            // 0.0
/*954  */                 tcg_temp_free_i32(sv);                                          // 0.0
/*956  */             }                                                                   // 0.0
/*958  */             break;                                                              // 0.0
/*960  */         case 0x29: /* sub.l */                                                  // 0.0
/*962  */             {                                                                   // 0.0
/*964  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*966  */                 int b = opcode & 0xf;                                           // 0.0
/*970  */                 tcg_gen_sub_i32(REG(a), REG(a), REG(b));                        // 0.0
/*972  */             }                                                                   // 0.0
/*974  */             break;                                                              // 0.0
/*976  */         case 0x2a: /* neg */                                                    // 0.0
/*978  */             {                                                                   // 0.0
/*980  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*982  */                 int b = opcode & 0xf;                                           // 0.0
/*986  */                 tcg_gen_neg_i32(REG(a), REG(b));                                // 0.0
/*988  */             }                                                                   // 0.0
/*990  */             break;                                                              // 0.0
/*992  */         case 0x2b: /* or */                                                     // 0.0
/*994  */             {                                                                   // 0.0
/*996  */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*998  */                 int b = opcode & 0xf;                                           // 0.0
/*1002 */                 tcg_gen_or_i32(REG(a), REG(a), REG(b));                         // 0.0
/*1004 */             }                                                                   // 0.0
/*1006 */             break;                                                              // 0.0
/*1008 */         case 0x2c: /* not */                                                    // 0.0
/*1010 */             {                                                                   // 0.0
/*1012 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1014 */                 int b = opcode & 0xf;                                           // 0.0
/*1018 */                 tcg_gen_not_i32(REG(a), REG(b));                                // 0.0
/*1020 */             }                                                                   // 0.0
/*1022 */             break;                                                              // 0.0
/*1024 */         case 0x2d: /* ashr */                                                   // 0.0
/*1026 */             {                                                                   // 0.0
/*1028 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1030 */                 int b = opcode & 0xf;                                           // 0.0
/*1034 */                 TCGv sv = tcg_temp_new_i32();                                   // 0.0
/*1036 */                 tcg_gen_andi_i32(sv, REG(b), 0x1f);                             // 0.0
/*1038 */                 tcg_gen_sar_i32(REG(a), REG(a), sv);                            // 0.0
/*1040 */                 tcg_temp_free_i32(sv);                                          // 0.0
/*1042 */             }                                                                   // 0.0
/*1044 */             break;                                                              // 0.0
/*1046 */         case 0x2e: /* xor */                                                    // 0.0
/*1048 */             {                                                                   // 0.0
/*1050 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1052 */                 int b = opcode & 0xf;                                           // 0.0
/*1056 */                 tcg_gen_xor_i32(REG(a), REG(a), REG(b));                        // 0.0
/*1058 */             }                                                                   // 0.0
/*1060 */             break;                                                              // 0.0
/*1062 */         case 0x2f: /* mul.l */                                                  // 0.0
/*1064 */             {                                                                   // 0.0
/*1066 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1068 */                 int b = opcode & 0xf;                                           // 0.0
/*1072 */                 tcg_gen_mul_i32(REG(a), REG(a), REG(b));                        // 0.0
/*1074 */             }                                                                   // 0.0
/*1076 */             break;                                                              // 0.0
/*1078 */         case 0x30: /* swi */                                                    // 0.0
/*1080 */             {                                                                   // 0.0
/*1082 */                 int val = cpu_ldl_code(env, ctx->pc+2);                         // 0.0
/*1086 */                 TCGv temp = tcg_temp_new_i32();                                 // 0.0
/*1088 */                 tcg_gen_movi_i32(temp, val);                                    // 0.0
/*1090 */                 tcg_gen_st_i32(temp, cpu_env,                                   // 0.0
/*1092 */                                offsetof(CPUMoxieState, sregs[3]));              // 0.0
/*1094 */                 tcg_gen_movi_i32(cpu_pc, ctx->pc);                              // 0.0
/*1096 */                 tcg_gen_movi_i32(temp, MOXIE_EX_SWI);                           // 0.0
/*1098 */                 gen_helper_raise_exception(cpu_env, temp);                      // 0.0
/*1100 */                 tcg_temp_free_i32(temp);                                        // 0.0
/*1104 */                 length = 6;                                                     // 0.0
/*1106 */             }                                                                   // 0.0
/*1108 */             break;                                                              // 0.0
/*1110 */         case 0x31: /* div.l */                                                  // 0.0
/*1112 */             {                                                                   // 0.0
/*1114 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1116 */                 int b = opcode & 0xf;                                           // 0.0
/*1118 */                 tcg_gen_movi_i32(cpu_pc, ctx->pc);                              // 0.0
/*1120 */                 gen_helper_div(REG(a), cpu_env, REG(a), REG(b));                // 0.0
/*1122 */             }                                                                   // 0.0
/*1124 */             break;                                                              // 0.0
/*1126 */         case 0x32: /* udiv.l */                                                 // 0.0
/*1128 */             {                                                                   // 0.0
/*1130 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1132 */                 int b = opcode & 0xf;                                           // 0.0
/*1134 */                 tcg_gen_movi_i32(cpu_pc, ctx->pc);                              // 0.0
/*1136 */                 gen_helper_udiv(REG(a), cpu_env, REG(a), REG(b));               // 0.0
/*1138 */             }                                                                   // 0.0
/*1140 */             break;                                                              // 0.0
/*1142 */         case 0x33: /* mod.l */                                                  // 0.0
/*1144 */             {                                                                   // 0.0
/*1146 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1148 */                 int b = opcode & 0xf;                                           // 0.0
/*1150 */                 tcg_gen_rem_i32(REG(a), REG(a), REG(b));                        // 0.0
/*1152 */             }                                                                   // 0.0
/*1154 */             break;                                                              // 0.0
/*1156 */         case 0x34: /* umod.l */                                                 // 0.0
/*1158 */             {                                                                   // 0.0
/*1160 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1162 */                 int b = opcode & 0xf;                                           // 0.0
/*1164 */                 tcg_gen_remu_i32(REG(a), REG(a), REG(b));                       // 0.0
/*1166 */             }                                                                   // 0.0
/*1168 */             break;                                                              // 0.0
/*1170 */         case 0x35: /* brk */                                                    // 0.0
/*1172 */             {                                                                   // 0.0
/*1174 */                 TCGv temp = tcg_temp_new_i32();                                 // 0.0
/*1176 */                 tcg_gen_movi_i32(cpu_pc, ctx->pc);                              // 0.0
/*1178 */                 tcg_gen_movi_i32(temp, MOXIE_EX_BREAK);                         // 0.0
/*1180 */                 gen_helper_raise_exception(cpu_env, temp);                      // 0.0
/*1182 */                 tcg_temp_free_i32(temp);                                        // 0.0
/*1184 */             }                                                                   // 0.0
/*1186 */             break;                                                              // 0.0
/*1188 */         case 0x36: /* ldo.b */                                                  // 0.0
/*1190 */             {                                                                   // 0.0
/*1192 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1194 */                 int b = opcode & 0xf;                                           // 0.0
/*1198 */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*1200 */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*1202 */                 tcg_gen_addi_i32(t1, REG(b), cpu_ldl_code(env, ctx->pc+2));     // 0.0
/*1204 */                 tcg_gen_qemu_ld8u(t2, t1, ctx->memidx);                         // 0.0
/*1206 */                 tcg_gen_mov_i32(REG(a), t2);                                    // 0.0
/*1210 */                 tcg_temp_free_i32(t1);                                          // 0.0
/*1212 */                 tcg_temp_free_i32(t2);                                          // 0.0
/*1216 */                 length = 6;                                                     // 0.0
/*1218 */             }                                                                   // 0.0
/*1220 */             break;                                                              // 0.0
/*1222 */         case 0x37: /* sto.b */                                                  // 0.0
/*1224 */             {                                                                   // 0.0
/*1226 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1228 */                 int b = opcode & 0xf;                                           // 0.0
/*1232 */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*1234 */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*1236 */                 tcg_gen_addi_i32(t1, REG(a), cpu_ldl_code(env, ctx->pc+2));     // 0.0
/*1238 */                 tcg_gen_qemu_st8(REG(b), t1, ctx->memidx);                      // 0.0
/*1242 */                 tcg_temp_free_i32(t1);                                          // 0.0
/*1244 */                 tcg_temp_free_i32(t2);                                          // 0.0
/*1248 */                 length = 6;                                                     // 0.0
/*1250 */             }                                                                   // 0.0
/*1252 */             break;                                                              // 0.0
/*1254 */         case 0x38: /* ldo.s */                                                  // 0.0
/*1256 */             {                                                                   // 0.0
/*1258 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1260 */                 int b = opcode & 0xf;                                           // 0.0
/*1264 */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*1266 */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*1268 */                 tcg_gen_addi_i32(t1, REG(b), cpu_ldl_code(env, ctx->pc+2));     // 0.0
/*1270 */                 tcg_gen_qemu_ld16u(t2, t1, ctx->memidx);                        // 0.0
/*1272 */                 tcg_gen_mov_i32(REG(a), t2);                                    // 0.0
/*1276 */                 tcg_temp_free_i32(t1);                                          // 0.0
/*1278 */                 tcg_temp_free_i32(t2);                                          // 0.0
/*1282 */                 length = 6;                                                     // 0.0
/*1284 */             }                                                                   // 0.0
/*1286 */             break;                                                              // 0.0
/*1288 */         case 0x39: /* sto.s */                                                  // 0.0
/*1290 */             {                                                                   // 0.0
/*1292 */                 int a = (opcode >> 4) & 0xf;                                    // 0.0
/*1294 */                 int b = opcode & 0xf;                                           // 0.0
/*1298 */                 TCGv t1 = tcg_temp_new_i32();                                   // 0.0
/*1300 */                 TCGv t2 = tcg_temp_new_i32();                                   // 0.0
/*1302 */                 tcg_gen_addi_i32(t1, REG(a), cpu_ldl_code(env, ctx->pc+2));     // 0.0
/*1304 */                 tcg_gen_qemu_st16(REG(b), t1, ctx->memidx);                     // 0.0
/*1306 */                 tcg_temp_free_i32(t1);                                          // 0.0
/*1308 */                 tcg_temp_free_i32(t2);                                          // 0.0
/*1312 */                 length = 6;                                                     // 0.0
/*1314 */             }                                                                   // 0.0
/*1316 */             break;                                                              // 0.0
/*1318 */         default:                                                                // 0.0
/*1320 */             {                                                                   // 0.0
/*1322 */                 TCGv temp = tcg_temp_new_i32();                                 // 0.0
/*1324 */                 tcg_gen_movi_i32(cpu_pc, ctx->pc);                              // 0.0
/*1326 */                 tcg_gen_movi_i32(temp, MOXIE_EX_BAD);                           // 0.0
/*1328 */                 gen_helper_raise_exception(cpu_env, temp);                      // 0.0
/*1330 */                 tcg_temp_free_i32(temp);                                        // 0.0
/*1332 */              }                                                                  // 0.0
/*1334 */             break;                                                              // 0.0
/*1336 */         }                                                                       // 0.0
/*1338 */     }                                                                           // 0.0
/*1342 */     return length;                                                              // 0.0
/*1344 */ }                                                                               // 0.0

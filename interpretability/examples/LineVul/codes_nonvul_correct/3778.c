// commit message qemu@bb3cb951ef (target=0, prob=0.20653303, correct=True): microblaze: Improve srl
/*0   */ static void dec_bit(DisasContext *dc)                                          // (16) 0.02344
/*2   */ {                                                                              // (22) 0.001953
/*4   */     TCGv t0, t1;                                                               // (17) 0.02344
/*6   */     unsigned int op;                                                           // (21) 0.01367
/*8   */     int mem_index = cpu_mmu_index(dc->env);                                    // (11) 0.03711
/*12  */     op = dc->ir & ((1 << 9) - 1);                                              // (13) 0.0332
/*14  */     switch (op) {                                                              // (20) 0.01562
/*16  */         case 0x21:                                                             // (18) 0.02344
/*18  */             /* src.  */                                                        // (15) 0.03125
/*20  */             t0 = tcg_temp_new();                                               // (8) 0.04102
/*24  */             LOG_DIS("src r%d r%d\n", dc->rd, dc->ra);                          // (2) 0.06445
/*26  */             tcg_gen_andi_tl(t0, cpu_R[dc->ra], 1);                             // (3) 0.06445
/*28  */             if (dc->rd) {                                                      // (12) 0.03516
/*30  */                 t1 = tcg_temp_new();                                           // (5) 0.04883
/*32  */                 read_carry(dc, t1);                                            // (7) 0.04688
/*34  */                 tcg_gen_shli_tl(t1, t1, 31);                                   // (4) 0.06445
/*38  */                 tcg_gen_shri_tl(cpu_R[dc->rd], cpu_R[dc->ra], 1);              // (0) 0.08398
/*40  */                 tcg_gen_or_tl(cpu_R[dc->rd], cpu_R[dc->rd], t1);               // (1) 0.08398
/*42  */                 tcg_temp_free(t1);                                             // (6) 0.04883
/*44  */             }                                                                  // (19) 0.02344
/*48  */             /* Update carry.  */                                               // (14) 0.0332
/*50  */             write_carry(dc, t0);                                               // (10) 0.03906
/*52  */             tcg_temp_free(t0);                                                 // (9) 0.04102
/*54  */             break;                                                             // 0.0
/*58  */         case 0x1:                                                              // 0.0
/*60  */         case 0x41:                                                             // 0.0
/*62  */             /* srl.  */                                                        // 0.0
/*64  */             t0 = tcg_temp_new();                                               // 0.0
/*66  */             LOG_DIS("srl r%d r%d\n", dc->rd, dc->ra);                          // 0.0
/*70  */             /* Update carry.  */                                               // 0.0
/*72  */             tcg_gen_andi_tl(t0, cpu_R[dc->ra], 1);                             // 0.0
/*74  */             write_carry(dc, t0);                                               // 0.0
/*76  */             tcg_temp_free(t0);                                                 // 0.0
/*78  */             if (dc->rd) {                                                      // 0.0
/*80  */                 if (op == 0x41)                                                // 0.0
/*82  */                     tcg_gen_shri_tl(cpu_R[dc->rd], cpu_R[dc->ra], 1);          // 0.0
/*84  */                 else                                                           // 0.0
/*86  */                     tcg_gen_sari_tl(cpu_R[dc->rd], cpu_R[dc->ra], 1);          // 0.0
/*88  */             }                                                                  // 0.0
/*90  */             break;                                                             // 0.0
/*92  */         case 0x60:                                                             // 0.0
/*94  */             LOG_DIS("ext8s r%d r%d\n", dc->rd, dc->ra);                        // 0.0
/*96  */             tcg_gen_ext8s_i32(cpu_R[dc->rd], cpu_R[dc->ra]);                   // 0.0
/*98  */             break;                                                             // 0.0
/*100 */         case 0x61:                                                             // 0.0
/*102 */             LOG_DIS("ext16s r%d r%d\n", dc->rd, dc->ra);                       // 0.0
/*104 */             tcg_gen_ext16s_i32(cpu_R[dc->rd], cpu_R[dc->ra]);                  // 0.0
/*106 */             break;                                                             // 0.0
/*108 */         case 0x64:                                                             // 0.0
/*110 */         case 0x66:                                                             // 0.0
/*112 */         case 0x74:                                                             // 0.0
/*114 */         case 0x76:                                                             // 0.0
/*116 */             /* wdc.  */                                                        // 0.0
/*118 */             LOG_DIS("wdc r%d\n", dc->ra);                                      // 0.0
/*120 */             if ((dc->tb_flags & MSR_EE_FLAG)                                   // 0.0
/*122 */                  && mem_index == MMU_USER_IDX) {                               // 0.0
/*124 */                 tcg_gen_movi_tl(cpu_SR[SR_ESR], ESR_EC_PRIVINSN);              // 0.0
/*126 */                 t_gen_raise_exception(dc, EXCP_HW_EXCP);                       // 0.0
/*128 */                 return;                                                        // 0.0
/*130 */             }                                                                  // 0.0
/*132 */             break;                                                             // 0.0
/*134 */         case 0x68:                                                             // 0.0
/*136 */             /* wic.  */                                                        // 0.0
/*138 */             LOG_DIS("wic r%d\n", dc->ra);                                      // 0.0
/*140 */             if ((dc->tb_flags & MSR_EE_FLAG)                                   // 0.0
/*142 */                  && mem_index == MMU_USER_IDX) {                               // 0.0
/*144 */                 tcg_gen_movi_tl(cpu_SR[SR_ESR], ESR_EC_PRIVINSN);              // 0.0
/*146 */                 t_gen_raise_exception(dc, EXCP_HW_EXCP);                       // 0.0
/*148 */                 return;                                                        // 0.0
/*150 */             }                                                                  // 0.0
/*152 */             break;                                                             // 0.0
/*154 */         case 0xe0:                                                             // 0.0
/*156 */             if ((dc->tb_flags & MSR_EE_FLAG)                                   // 0.0
/*158 */                 && (dc->env->pvr.regs[2] & PVR2_ILL_OPCODE_EXC_MASK)           // 0.0
/*160 */                 && !((dc->env->pvr.regs[2] & PVR2_USE_PCMP_INSTR))) {          // 0.0
/*162 */                 tcg_gen_movi_tl(cpu_SR[SR_ESR], ESR_EC_ILLEGAL_OP);            // 0.0
/*164 */                 t_gen_raise_exception(dc, EXCP_HW_EXCP);                       // 0.0
/*166 */             }                                                                  // 0.0
/*168 */             if (dc->env->pvr.regs[2] & PVR2_USE_PCMP_INSTR) {                  // 0.0
/*170 */                 gen_helper_clz(cpu_R[dc->rd], cpu_R[dc->ra]);                  // 0.0
/*172 */             }                                                                  // 0.0
/*174 */             break;                                                             // 0.0
/*176 */         case 0x1e0:                                                            // 0.0
/*178 */             /* swapb */                                                        // 0.0
/*180 */             LOG_DIS("swapb r%d r%d\n", dc->rd, dc->ra);                        // 0.0
/*182 */             tcg_gen_bswap32_i32(cpu_R[dc->rd], cpu_R[dc->ra]);                 // 0.0
/*184 */             break;                                                             // 0.0
/*186 */         case 0x1e2:                                                            // 0.0
/*188 */             /*swaph */                                                         // 0.0
/*190 */             LOG_DIS("swaph r%d r%d\n", dc->rd, dc->ra);                        // 0.0
/*192 */             tcg_gen_rotri_i32(cpu_R[dc->rd], cpu_R[dc->ra], 16);               // 0.0
/*194 */             break;                                                             // 0.0
/*196 */         default:                                                               // 0.0
/*198 */             cpu_abort(dc->env, "unknown bit oc=%x op=%x rd=%d ra=%d rb=%d\n",  // 0.0
/*200 */                      dc->pc, op, dc->rd, dc->ra, dc->rb);                      // 0.0
/*202 */             break;                                                             // 0.0
/*204 */     }                                                                          // 0.0
/*206 */ }                                                                              // 0.0

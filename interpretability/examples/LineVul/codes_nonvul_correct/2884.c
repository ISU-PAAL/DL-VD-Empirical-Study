// commit message qemu@40f860cd6c (target=0, prob=0.01263049, correct=True): target-arm: Split A64 from A32/T32 gen_intermediate_code_internal()
/*0  */ void disas_a64_insn(CPUARMState *env, DisasContext *s)                      // (2) 0.09565
/*2  */ {                                                                           // (14) 0.004348
/*4  */     uint32_t insn;                                                          // (8) 0.04348
/*8  */     insn = arm_ldl_code(env, s->pc, s->bswap_code);                         // (1) 0.1174
/*10 */     s->insn = insn;                                                         // (7) 0.04783
/*12 */     s->pc += 4;                                                             // (9) 0.03913
/*16 */     switch ((insn >> 24) & 0x1f) {                                          // (4) 0.07391
/*18 */     default:                                                                // (11) 0.02174
/*20 */         unallocated_encoding(s);                                            // (6) 0.06957
/*22 */         break;                                                              // (10) 0.03913
/*24 */     }                                                                       // (12) 0.01739
/*28 */     if (unlikely(s->singlestep_enabled) && (s->is_jmp == DISAS_TB_JUMP)) {  // (0) 0.1478
/*30 */         /* go through the main loop for single step */                      // (5) 0.07391
/*32 */         s->is_jmp = DISAS_JUMP;                                             // (3) 0.08696
/*34 */     }                                                                       // (13) 0.01739
/*36 */ }                                                                           // (15) 0.004348

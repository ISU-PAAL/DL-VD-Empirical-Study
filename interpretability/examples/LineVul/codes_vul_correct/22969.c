// commit message qemu@7372c2b926 (target=1, prob=0.7267569, correct=True): target-m68k: Remove custom qemu_assert() function
/*0   */ static TCGv gen_ea(CPUM68KState *env, DisasContext *s, uint16_t insn,      // (1) 0.05664
/*2   */                    int opsize, TCGv val, TCGv *addrp, ea_what what)        // (0) 0.07812
/*4   */ {                                                                          // (27) 0.001953
/*6   */     TCGv reg;                                                              // (24) 0.01562
/*8   */     TCGv result;                                                           // (23) 0.01562
/*10  */     uint32_t offset;                                                       // (22) 0.0176
/*14  */     switch ((insn >> 3) & 7) {                                             // (16) 0.02734
/*16  */     case 0: /* Data register direct.  */                                   // (17) 0.02539
/*18  */         reg = DREG(insn, 0);                                               // (9) 0.0332
/*20  */         if (what == EA_STORE) {                                            // (13) 0.0332
/*22  */             gen_partset_reg(opsize, reg, val);                             // (5) 0.04883
/*24  */             return store_dummy;                                            // (7) 0.0332
/*26  */         } else {                                                           // (20) 0.01953
/*28  */             return gen_extend(reg, opsize, what == EA_LOADS);              // (2) 0.05664
/*30  */         }                                                                  // (26) 0.01562
/*32  */     case 1: /* Address register direct.  */                                // (18) 0.02539
/*34  */         reg = AREG(insn, 0);                                               // (11) 0.0332
/*36  */         if (what == EA_STORE) {                                            // (14) 0.0332
/*38  */             tcg_gen_mov_i32(reg, val);                                     // (4) 0.05078
/*40  */             return store_dummy;                                            // (8) 0.0332
/*42  */         } else {                                                           // (21) 0.01953
/*44  */             return gen_extend(reg, opsize, what == EA_LOADS);              // (3) 0.05664
/*46  */         }                                                                  // (25) 0.01562
/*48  */     case 2: /* Indirect register */                                        // (19) 0.02148
/*50  */         reg = AREG(insn, 0);                                               // (12) 0.0332
/*52  */         return gen_ldst(s, opsize, reg, val, what);                        // (6) 0.04687
/*54  */     case 3: /* Indirect postincrement.  */                                 // (15) 0.0293
/*56  */         reg = AREG(insn, 0);                                               // (10) 0.0332
/*58  */         result = gen_ldst(s, opsize, reg, val, what);                      // 0.0
/*60  */         /* ??? This is not exception safe.  The instruction may still      // 0.0
/*62  */            fault after this point.  */                                     // 0.0
/*64  */         if (what == EA_STORE || !addrp)                                    // 0.0
/*66  */             tcg_gen_addi_i32(reg, reg, opsize_bytes(opsize));              // 0.0
/*68  */         return result;                                                     // 0.0
/*70  */     case 4: /* Indirect predecrememnt.  */                                 // 0.0
/*72  */         {                                                                  // 0.0
/*74  */             TCGv tmp;                                                      // 0.0
/*76  */             if (addrp && what == EA_STORE) {                               // 0.0
/*78  */                 tmp = *addrp;                                              // 0.0
/*80  */             } else {                                                       // 0.0
/*82  */                 tmp = gen_lea(env, s, insn, opsize);                       // 0.0
/*84  */                 if (IS_NULL_QREG(tmp))                                     // 0.0
/*86  */                     return tmp;                                            // 0.0
/*88  */                 if (addrp)                                                 // 0.0
/*90  */                     *addrp = tmp;                                          // 0.0
/*92  */             }                                                              // 0.0
/*94  */             result = gen_ldst(s, opsize, tmp, val, what);                  // 0.0
/*96  */             /* ??? This is not exception safe.  The instruction may still  // 0.0
/*98  */                fault after this point.  */                                 // 0.0
/*100 */             if (what == EA_STORE || !addrp) {                              // 0.0
/*102 */                 reg = AREG(insn, 0);                                       // 0.0
/*104 */                 tcg_gen_mov_i32(reg, tmp);                                 // 0.0
/*106 */             }                                                              // 0.0
/*108 */         }                                                                  // 0.0
/*110 */         return result;                                                     // 0.0
/*112 */     case 5: /* Indirect displacement.  */                                  // 0.0
/*114 */     case 6: /* Indirect index + displacement.  */                          // 0.0
/*116 */         return gen_ea_once(env, s, insn, opsize, val, addrp, what);        // 0.0
/*118 */     case 7: /* Other */                                                    // 0.0
/*120 */         switch (insn & 7) {                                                // 0.0
/*122 */         case 0: /* Absolute short.  */                                     // 0.0
/*124 */         case 1: /* Absolute long.  */                                      // 0.0
/*126 */         case 2: /* pc displacement  */                                     // 0.0
/*128 */         case 3: /* pc index+displacement.  */                              // 0.0
/*130 */             return gen_ea_once(env, s, insn, opsize, val, addrp, what);    // 0.0
/*132 */         case 4: /* Immediate.  */                                          // 0.0
/*134 */             /* Sign extend values for consistency.  */                     // 0.0
/*136 */             switch (opsize) {                                              // 0.0
/*138 */             case OS_BYTE:                                                  // 0.0
/*140 */                 if (what == EA_LOADS) {                                    // 0.0
/*142 */                     offset = cpu_ldsb_code(env, s->pc + 1);                // 0.0
/*144 */                 } else {                                                   // 0.0
/*146 */                     offset = cpu_ldub_code(env, s->pc + 1);                // 0.0
/*148 */                 }                                                          // 0.0
/*150 */                 s->pc += 2;                                                // 0.0
/*152 */                 break;                                                     // 0.0
/*154 */             case OS_WORD:                                                  // 0.0
/*156 */                 if (what == EA_LOADS) {                                    // 0.0
/*158 */                     offset = cpu_ldsw_code(env, s->pc);                    // 0.0
/*160 */                 } else {                                                   // 0.0
/*162 */                     offset = cpu_lduw_code(env, s->pc);                    // 0.0
/*164 */                 }                                                          // 0.0
/*166 */                 s->pc += 2;                                                // 0.0
/*168 */                 break;                                                     // 0.0
/*170 */             case OS_LONG:                                                  // 0.0
/*172 */                 offset = read_im32(env, s);                                // 0.0
/*174 */                 break;                                                     // 0.0
/*176 */             default:                                                       // 0.0
/*178 */                 qemu_assert(0, "Bad immediate operand");                   // 0.0
/*180 */             }                                                              // 0.0
/*182 */             return tcg_const_i32(offset);                                  // 0.0
/*184 */         default:                                                           // 0.0
/*186 */             return NULL_QREG;                                              // 0.0
/*188 */         }                                                                  // 0.0
/*190 */     }                                                                      // 0.0
/*192 */     /* Should never happen.  */                                            // 0.0
/*194 */     return NULL_QREG;                                                      // 0.0
/*196 */ }                                                                          // 0.0

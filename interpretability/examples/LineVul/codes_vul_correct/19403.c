// commit message qemu@7d1b0095bf (target=1, prob=0.99785656, correct=True): target-arm: Remove ad-hoc leak checking code
/*0  */ static inline int gen_iwmmxt_shift(uint32_t insn, uint32_t mask, TCGv dest)  // (1) 0.09119
/*2  */ {                                                                            // (18) 0.003145
/*4  */     int rd = (insn >> 0) & 0xf;                                              // (7) 0.05346
/*6  */     TCGv tmp;                                                                // (13) 0.02516
/*10 */     if (insn & (1 << 8)) {                                                   // (8) 0.04403
/*12 */         if (rd < ARM_IWMMXT_wCGR0 || rd > ARM_IWMMXT_wCGR3) {                // (0) 0.1226
/*14 */             return 1;                                                        // (9) 0.04403
/*16 */         } else {                                                             // (11) 0.03145
/*18 */             tmp = iwmmxt_load_creg(rd);                                      // (3) 0.07862
/*20 */         }                                                                    // (14) 0.02516
/*22 */     } else {                                                                 // (15) 0.01887
/*24 */         tmp = new_tmp();                                                     // (10) 0.04088
/*26 */         iwmmxt_load_reg(cpu_V0, rd);                                         // (4) 0.07547
/*28 */         tcg_gen_trunc_i64_i32(tmp, cpu_V0);                                  // (2) 0.08805
/*30 */     }                                                                        // (17) 0.01258
/*32 */     tcg_gen_andi_i32(tmp, tmp, mask);                                        // (5) 0.05975
/*34 */     tcg_gen_mov_i32(dest, tmp);                                              // (6) 0.0566
/*36 */     dead_tmp(tmp);                                                           // (12) 0.0283
/*38 */     return 0;                                                                // (16) 0.01887
/*40 */ }                                                                            // (19) 0.003145

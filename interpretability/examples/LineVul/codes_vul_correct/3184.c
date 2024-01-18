// commit message qemu@367790cce8 (target=1, prob=0.9521222, correct=True): target-m68k: Inline shifts
/*0  */ uint32_t HELPER(shr_cc)(CPUM68KState *env, uint32_t val, uint32_t shift)  // (0) 0.1676
/*2  */ {                                                                         // (12) 0.005405
/*4  */     uint64_t temp;                                                        // (7) 0.04865
/*6  */     uint32_t result;                                                      // (8) 0.04865
/*10 */     shift &= 63;                                                          // (10) 0.04324
/*12 */     temp = (uint64_t)val << 32 >> shift;                                  // (2) 0.09189
/*14 */     result = temp >> 32;                                                  // (9) 0.04865
/*18 */     env->cc_c = (temp >> 31) & 1;                                         // (3) 0.09189
/*20 */     env->cc_n = result;                                                   // (4) 0.05946
/*22 */     env->cc_z = result;                                                   // (5) 0.05946
/*24 */     env->cc_v = 0;                                                        // (6) 0.05946
/*26 */     env->cc_x = shift ? env->cc_c : env->cc_x;                            // (1) 0.1243
/*30 */     return result;                                                        // (11) 0.03243
/*32 */ }                                                                         // (13) 0.005405

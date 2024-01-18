// commit message qemu@96d7073fb0 (target=0, prob=0.012675539, correct=True): target-i386: Remove confusing X86_64_DEF macro
/*0  */ static inline void gen_op_mov_v_reg(int ot, TCGv t0, int reg)    // (4) 0.1008
/*2  */ {                                                                // (15) 0.003876
/*4  */     switch(ot) {                                                 // (10) 0.03101
/*6  */     case OT_BYTE:                                                // (7) 0.03488
/*8  */         if (reg < 4 X86_64_DEF( || reg >= 8 || x86_64_hregs)) {  // (1) 0.1318
/*10 */             goto std_case;                                       // (5) 0.06202
/*12 */         } else {                                                 // (6) 0.03876
/*14 */             tcg_gen_shri_tl(t0, cpu_regs[reg - 4], 8);           // (0) 0.1357
/*16 */             tcg_gen_ext8u_tl(t0, t0);                            // (2) 0.1085
/*18 */         }                                                        // (11) 0.03101
/*20 */         break;                                                   // (8) 0.03488
/*22 */     default:                                                     // (13) 0.01938
/*24 */     std_case:                                                    // (12) 0.02713
/*26 */         tcg_gen_mov_tl(t0, cpu_regs[reg]);                       // (3) 0.1047
/*28 */         break;                                                   // (9) 0.03488
/*30 */     }                                                            // (14) 0.0155
/*32 */ }                                                                // (16) 0.003876

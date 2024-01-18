// commit message qemu@f248873637 (target=1, prob=0.41430262, correct=False): tcg-arm: Use QEMU_BUILD_BUG_ON to verify constraints on tlb
/*0   */ static void tcg_out_tlb_read(TCGContext *s, TCGReg addrlo, TCGReg addrhi,       // (7) 0.05859
/*2   */                              int s_bits, int tlb_offset)                        // (6) 0.0761
/*4   */ {                                                                               // (16) 0.001959
/*6   */     TCGReg base = TCG_AREG0;                                                    // (11) 0.03015
/*10  */     /* Should generate something like the following:                            // (13) 0.02149
/*12  */      * pre-v7:                                                                  // (14) 0.01951
/*14  */      *   shr    tmp, addr_reg, #TARGET_PAGE_BITS                  (1)           // (4) 0.08975
/*16  */      *   add    r2, env, #off & 0xff00                                          // (9) 0.04293
/*18  */      *   and    r0, tmp, #(CPU_TLB_SIZE - 1)                      (2)           // (1) 0.09951
/*20  */      *   add    r2, r2, r0, lsl #CPU_TLB_ENTRY_BITS               (3)           // (2) 0.09755
/*22  */      *   ldr    r0, [r2, #off & 0xff]!                            (4)           // (0) 0.1093
/*24  */      *   tst    addr_reg, #s_mask                                               // (10) 0.03903
/*26  */      *   cmpeq  r0, tmp, lsl #TARGET_PAGE_BITS                    (5)           // (3) 0.0956
/*28  */      *                                                                          // (15) 0.009756
/*30  */      * v7 (not implemented yet):                                                // (12) 0.02342
/*32  */      *   ubfx   r2, addr_reg, #TARGET_PAGE_BITS, #CPU_TLB_BITS    (1)           // (5) 0.08391
/*34  */      *   movw   tmp, #~TARGET_PAGE_MASK & ~s_mask                               // (8) 0.05463
/*36  */      *   movw   r0, #off                                                        // 0.0
/*38  */      *   add    r2, env, r2, lsl #CPU_TLB_ENTRY_BITS              (2)           // 0.0
/*40  */      *   bic    tmp, addr_reg, tmp                                              // 0.0
/*42  */      *   ldr    r0, [r2, r0]!                                     (3)           // 0.0
/*44  */      *   cmp    r0, tmp                                           (4)           // 0.0
/*46  */      */                                                                         // 0.0
/*48  */ #  if CPU_TLB_BITS > 8                                                          // 0.0
/*50  */ #   error                                                                       // 0.0
/*52  */ #  endif                                                                        // 0.0
/*54  */     tcg_out_dat_reg(s, COND_AL, ARITH_MOV, TCG_REG_TMP,                         // 0.0
/*56  */                     0, addrlo, SHIFT_IMM_LSR(TARGET_PAGE_BITS));                // 0.0
/*60  */     /* We assume that the offset is contained within 16 bits.  */               // 0.0
/*62  */     assert((tlb_offset & ~0xffff) == 0);                                        // 0.0
/*64  */     if (tlb_offset > 0xff) {                                                    // 0.0
/*66  */         tcg_out_dat_imm(s, COND_AL, ARITH_ADD, TCG_REG_R2, base,                // 0.0
/*68  */                         (24 << 7) | (tlb_offset >> 8));                         // 0.0
/*70  */         tlb_offset &= 0xff;                                                     // 0.0
/*72  */         base = TCG_REG_R2;                                                      // 0.0
/*74  */     }                                                                           // 0.0
/*78  */     tcg_out_dat_imm(s, COND_AL, ARITH_AND,                                      // 0.0
/*80  */                     TCG_REG_R0, TCG_REG_TMP, CPU_TLB_SIZE - 1);                 // 0.0
/*82  */     tcg_out_dat_reg(s, COND_AL, ARITH_ADD, TCG_REG_R2, base,                    // 0.0
/*84  */                     TCG_REG_R0, SHIFT_IMM_LSL(CPU_TLB_ENTRY_BITS));             // 0.0
/*88  */     /* Load the tlb comparator.  Use ldrd if needed and available,              // 0.0
/*90  */        but due to how the pointer needs setting up, ldm isn't useful.           // 0.0
/*92  */        Base arm5 doesn't have ldrd, but armv5te does.  */                       // 0.0
/*94  */     if (use_armv6_instructions && TARGET_LONG_BITS == 64) {                     // 0.0
/*96  */         tcg_out_memop_8(s, COND_AL, INSN_LDRD_IMM, TCG_REG_R0,                  // 0.0
/*98  */                         TCG_REG_R2, tlb_offset, 1, 1);                          // 0.0
/*100 */     } else {                                                                    // 0.0
/*102 */         tcg_out_memop_12(s, COND_AL, INSN_LDR_IMM, TCG_REG_R0,                  // 0.0
/*104 */                          TCG_REG_R2, tlb_offset, 1, 1);                         // 0.0
/*106 */         if (TARGET_LONG_BITS == 64) {                                           // 0.0
/*108 */             tcg_out_memop_12(s, COND_AL, INSN_LDR_IMM, TCG_REG_R1,              // 0.0
/*110 */                              TCG_REG_R2, 4, 1, 0);                              // 0.0
/*112 */         }                                                                       // 0.0
/*114 */     }                                                                           // 0.0
/*118 */     /* Check alignment.  */                                                     // 0.0
/*120 */     if (s_bits) {                                                               // 0.0
/*122 */         tcg_out_dat_imm(s, COND_AL, ARITH_TST,                                  // 0.0
/*124 */                         0, addrlo, (1 << s_bits) - 1);                          // 0.0
/*126 */     }                                                                           // 0.0
/*130 */     tcg_out_dat_reg(s, (s_bits ? COND_EQ : COND_AL), ARITH_CMP, 0,              // 0.0
/*132 */                     TCG_REG_R0, TCG_REG_TMP, SHIFT_IMM_LSL(TARGET_PAGE_BITS));  // 0.0
/*136 */     if (TARGET_LONG_BITS == 64) {                                               // 0.0
/*138 */         tcg_out_dat_reg(s, COND_EQ, ARITH_CMP, 0,                               // 0.0
/*140 */                         TCG_REG_R1, addrhi, SHIFT_IMM_LSL(0));                  // 0.0
/*142 */     }                                                                           // 0.0
/*144 */ }                                                                               // 0.0

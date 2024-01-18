// commit message qemu@425532d71d (target=0, prob=0.25131017, correct=True): tcg-sparc: Tidy check_fit_* tests
/*0  */ static TCGReg tcg_out_tlb_load(TCGContext *s, TCGReg addr, int mem_index,        // (7) 0.05859
/*2  */                                TCGMemOp s_bits, int which)                       // (0) 0.08008
/*4  */ {                                                                                // (21) 0.001953
/*6  */     const TCGReg r0 = TCG_REG_O0;                                                // (11) 0.03516
/*8  */     const TCGReg r1 = TCG_REG_O1;                                                // (12) 0.03516
/*10 */     const TCGReg r2 = TCG_REG_O2;                                                // (13) 0.03516
/*12 */     int tlb_ofs;                                                                 // (19) 0.01953
/*16 */     /* Shift the page number down.  */                                           // (18) 0.02344
/*18 */     tcg_out_arithi(s, r1, addr, TARGET_PAGE_BITS, SHIFT_SRL);                    // (3) 0.06641
/*22 */     /* Mask out the page offset, except for the required alignment.  */          // (10) 0.03516
/*24 */     tcg_out_movi(s, TCG_TYPE_TL, TCG_REG_T1,                                     // (8) 0.05469
/*26 */                  TARGET_PAGE_MASK | ((1 << s_bits) - 1));                        // (2) 0.06836
/*30 */     /* Mask the tlb index.  */                                                   // (16) 0.02344
/*32 */     tcg_out_arithi(s, r1, r1, CPU_TLB_SIZE - 1, ARITH_AND);                      // (4) 0.06641
/*34 */                                                                                  // (20) 0.007812
/*36 */     /* Mask page, part 2.  */                                                    // (17) 0.02344
/*38 */     tcg_out_arith(s, r0, addr, TCG_REG_T1, ARITH_AND);                           // (6) 0.06055
/*42 */     /* Shift the tlb index into place.  */                                       // (14) 0.02734
/*44 */     tcg_out_arithi(s, r1, r1, CPU_TLB_ENTRY_BITS, SHIFT_SLL);                    // (1) 0.07227
/*48 */     /* Relative to the current ENV.  */                                          // (15) 0.02539
/*50 */     tcg_out_arith(s, r1, TCG_AREG0, r1, ARITH_ADD);                              // (5) 0.06055
/*54 */     /* Find a base address that can load both tlb comparator and addend.  */     // (9) 0.04297
/*56 */     tlb_ofs = offsetof(CPUArchState, tlb_table[mem_index][0]);                   // 0.0
/*58 */     if (!check_fit_tl(tlb_ofs + sizeof(CPUTLBEntry), 13)) {                      // 0.0
/*60 */         tcg_out_addi(s, r1, tlb_ofs & ~0x3ff);                                   // 0.0
/*62 */         tlb_ofs &= 0x3ff;                                                        // 0.0
/*64 */     }                                                                            // 0.0
/*68 */     /* Load the tlb comparator and the addend.  */                               // 0.0
/*70 */     tcg_out_ld(s, TCG_TYPE_TL, r2, r1, tlb_ofs + which);                         // 0.0
/*72 */     tcg_out_ld(s, TCG_TYPE_PTR, r1, r1, tlb_ofs+offsetof(CPUTLBEntry, addend));  // 0.0
/*76 */     /* subcc arg0, arg2, %g0 */                                                  // 0.0
/*78 */     tcg_out_cmp(s, r0, r2, 0);                                                   // 0.0
/*82 */     /* If the guest address must be zero-extended, do so now.  */                // 0.0
/*84 */     if (SPARC64 && TARGET_LONG_BITS == 32) {                                     // 0.0
/*86 */         tcg_out_arithi(s, r0, addr, 0, SHIFT_SRL);                               // 0.0
/*88 */         return r0;                                                               // 0.0
/*90 */     }                                                                            // 0.0
/*92 */     return addr;                                                                 // 0.0
/*94 */ }                                                                                // 0.0

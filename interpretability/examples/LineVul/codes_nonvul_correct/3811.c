// commit message qemu@eabb7b91b3 (target=0, prob=0.03406973, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static void tcg_out_insn_3314(TCGContext *s, AArch64Insn insn,        // (3) 0.1059
/*2  */                               TCGReg r1, TCGReg r2, TCGReg rn,        // (0) 0.1843
/*4  */                               tcg_target_long ofs, bool pre, bool w)  // (1) 0.1725
/*6  */ {                                                                     // (9) 0.003922
/*8  */     insn |= 1u << 31; /* ext */                                       // (6) 0.05882
/*10 */     insn |= pre << 24;                                                // (7) 0.04314
/*12 */     insn |= w << 23;                                                  // (8) 0.04314
/*16 */     assert(ofs >= -0x200 && ofs < 0x200 && (ofs & 7) == 0);           // (2) 0.1137
/*18 */     insn |= (ofs & (0x7f << 3)) << (15 - 3);                          // (5) 0.09804
/*22 */     tcg_out32(s, insn | r2 << 10 | rn << 5 | r1);                     // (4) 0.1059
/*24 */ }                                                                     // (10) 0.003922

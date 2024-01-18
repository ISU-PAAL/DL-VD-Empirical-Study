// commit message qemu@eabb7b91b3 (target=0, prob=0.01671097, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static void tcg_out_brcond(TCGContext *s, TCGMemOp ext, TCGCond c, TCGArg a,  // (3) 0.06751
/*2  */                            TCGArg b, bool b_const, TCGLabel *l)               // (0) 0.08861
/*4  */ {                                                                             // (24) 0.00211
/*6  */     intptr_t offset;                                                          // (16) 0.01899
/*8  */     bool need_cmp;                                                            // (17) 0.01688
/*12 */     if (b_const && b == 0 && (c == TCG_COND_EQ || c == TCG_COND_NE)) {        // (2) 0.07595
/*14 */         need_cmp = false;                                                     // (12) 0.02743
/*16 */     } else {                                                                  // (18) 0.01266
/*18 */         need_cmp = true;                                                      // (13) 0.02743
/*20 */         tcg_out_cmp(s, ext, a, b, b_const);                                   // (7) 0.05485
/*22 */     }                                                                         // (22) 0.008439
/*26 */     if (!l->has_value) {                                                      // (14) 0.02532
/*28 */         tcg_out_reloc(s, s->code_ptr, R_AARCH64_CONDBR19, l, 0);              // (1) 0.08017
/*30 */         offset = tcg_in32(s) >> 5;                                            // (10) 0.04219
/*32 */     } else {                                                                  // (19) 0.01266
/*34 */         offset = l->u.value_ptr - s->code_ptr;                                // (8) 0.04852
/*36 */         assert(offset == sextract64(offset, 0, 19));                          // (9) 0.04641
/*38 */     }                                                                         // (23) 0.008439
/*42 */     if (need_cmp) {                                                           // (15) 0.0211
/*44 */         tcg_out_insn(s, 3202, B_C, c, offset);                                // (6) 0.05907
/*46 */     } else if (c == TCG_COND_EQ) {                                            // (11) 0.04008
/*48 */         tcg_out_insn(s, 3201, CBZ, ext, a, offset);                           // (4) 0.06118
/*50 */     } else {                                                                  // (20) 0.01266
/*52 */         tcg_out_insn(s, 3201, CBNZ, ext, a, offset);                          // (5) 0.06118
/*54 */     }                                                                         // (21) 0.008439
/*56 */ }                                                                             // (25) 0.00211

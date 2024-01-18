// commit message qemu@eabb7b91b3 (target=0, prob=0.032855786, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static void tcg_out_logicali(TCGContext *s, AArch64Insn insn, TCGType ext,  // (5) 0.06849
/*2  */                              TCGReg rd, TCGReg rn, uint64_t limm)           // (0) 0.1073
/*4  */ {                                                                           // (22) 0.002283
/*6  */     unsigned h, l, r, c;                                                    // (12) 0.0274
/*10 */     assert(is_limm(limm));                                                  // (11) 0.02968
/*14 */     h = clz64(limm);                                                        // (13) 0.0274
/*16 */     l = ctz64(limm);                                                        // (14) 0.0274
/*18 */     if (l == 0) {                                                           // (17) 0.02283
/*20 */         r = 0;                  /* form 0....01....1 */                     // (2) 0.08219
/*22 */         c = ctz64(~limm) - 1;                                               // (6) 0.04566
/*24 */         if (h == 0) {                                                       // (10) 0.03196
/*26 */             r = clz64(~limm);   /* form 1..10..01..1 */                     // (4) 0.07534
/*28 */             c += r;                                                         // (8) 0.03425
/*30 */         }                                                                   // (18) 0.01826
/*32 */     } else {                                                                // (19) 0.0137
/*34 */         r = 64 - l;             /* form 1....10....0 or 0..01..10..0 */     // (1) 0.09361
/*36 */         c = r - h - 1;                                                      // (9) 0.03425
/*38 */     }                                                                       // (20) 0.009132
/*40 */     if (ext == TCG_TYPE_I32) {                                              // (7) 0.03653
/*42 */         r &= 31;                                                            // (15) 0.0274
/*44 */         c &= 31;                                                            // (16) 0.0274
/*46 */     }                                                                       // (21) 0.009132
/*50 */     tcg_out_insn_3404(s, insn, ext, rd, rn, ext, r, c);                     // (3) 0.07534
/*52 */ }                                                                           // (23) 0.002283

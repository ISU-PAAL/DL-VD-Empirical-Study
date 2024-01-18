// commit message qemu@eabb7b91b3 (target=0, prob=0.01759861, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static void tcg_out_dat_rIK(TCGContext *s, int cond, int opc, int opinv,       // (4) 0.07305
/*2  */                             TCGReg dst, TCGReg lhs, TCGArg rhs,                // (0) 0.1108
/*4  */                             bool rhs_is_const)                                 // (3) 0.08816
/*6  */ {                                                                              // (18) 0.002519
/*8  */     /* Emit either the reg,imm or reg,reg form of a data-processing insn.      // (5) 0.06045
/*10 */      * rhs must satisfy the "rIK" constraint.                                  // (11) 0.0403
/*12 */      */                                                                        // (16) 0.01259
/*14 */     if (rhs_is_const) {                                                        // (13) 0.03275
/*16 */         int rot = encode_imm(rhs);                                             // (8) 0.04282
/*18 */         if (rot < 0) {                                                         // (12) 0.03526
/*20 */             rhs = ~rhs;                                                        // (7) 0.04534
/*22 */             rot = encode_imm(rhs);                                             // (6) 0.05038
/*24 */             assert(rot >= 0);                                                  // (9) 0.04282
/*26 */             opc = opinv;                                                       // (10) 0.04282
/*28 */         }                                                                      // (14) 0.02015
/*30 */         tcg_out_dat_imm(s, cond, opc, dst, lhs, rotl(rhs, rot) | (rot << 7));  // (1) 0.1058
/*32 */     } else {                                                                   // (15) 0.01511
/*34 */         tcg_out_dat_reg(s, cond, opc, dst, lhs, rhs, SHIFT_IMM_LSL(0));        // (2) 0.1058
/*36 */     }                                                                          // (17) 0.01008
/*38 */ }                                                                              // (19) 0.002519

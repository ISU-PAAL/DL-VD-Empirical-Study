// commit message qemu@eabb7b91b3 (target=0, prob=0.021903252, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static void tcg_out_setcond2(TCGContext *s, TCGCond cond, TCGReg ret,     // (8) 0.05389
/*2  */                              TCGReg al, TCGReg ah, TCGReg bl, TCGReg bh)  // (0) 0.0978
/*4  */ {                                                                         // (23) 0.001996
/*6  */     TCGReg tmp0 = TCG_TMP0;                                               // (11) 0.03194
/*8  */     TCGReg tmp1 = ret;                                                    // (16) 0.02196
/*12 */     assert(ret != TCG_TMP0);                                              // (13) 0.02794
/*14 */     if (ret == ah || ret == bh) {                                         // (12) 0.02994
/*16 */         assert(ret != TCG_TMP1);                                          // (9) 0.03593
/*18 */         tmp1 = TCG_TMP1;                                                  // (10) 0.03393
/*20 */     }                                                                     // (21) 0.007984
/*24 */     switch (cond) {                                                       // (19) 0.01597
/*26 */     case TCG_COND_EQ:                                                     // (14) 0.02595
/*28 */     case TCG_COND_NE:                                                     // (15) 0.02395
/*30 */         tmp1 = tcg_out_reduce_eq2(s, tmp0, tmp1, al, ah, bl, bh);         // (1) 0.07585
/*32 */         tcg_out_setcond(s, cond, ret, tmp1, TCG_REG_ZERO);                // (6) 0.06387
/*34 */         break;                                                            // (17) 0.01796
/*38 */     default:                                                              // (20) 0.00998
/*40 */         tcg_out_setcond(s, TCG_COND_EQ, tmp0, ah, bh);                    // (2) 0.06786
/*42 */         tcg_out_setcond(s, tcg_unsigned_cond(cond), tmp1, al, bl);        // (4) 0.06587
/*44 */         tcg_out_opc_reg(s, OPC_AND, tmp1, tmp1, tmp0);                    // (5) 0.06587
/*46 */         tcg_out_setcond(s, tcg_high_cond(cond), tmp0, ah, bh);            // (3) 0.06786
/*48 */         tcg_out_opc_reg(s, OPC_OR, ret, tmp1, tmp0);                      // (7) 0.06387
/*50 */         break;                                                            // (18) 0.01796
/*52 */     }                                                                     // (22) 0.007984
/*54 */ }                                                                         // (24) 0.001996

// commit message qemu@f02ca5cbea (target=0, prob=0.04626862, correct=True): Fix bit fitting checks
/*0  */ static inline void tcg_out_movi(TCGContext *s, TCGType type,                     // (8) 0.05641
/*2  */                                 int ret, tcg_target_long arg)                    // (1) 0.1077
/*4  */ {                                                                                // (15) 0.002564
/*6  */ #if defined(__sparc_v9__) && !defined(__sparc_v8plus__)                          // (6) 0.06923
/*8  */     if (arg != (arg & 0xffffffff))                                               // (10) 0.03846
/*10 */         fprintf(stderr, "unimplemented %s with constant %ld\n", __func__, arg);  // (5) 0.08718
/*12 */ #endif                                                                           // (14) 0.005128
/*14 */     if (arg == (arg & 0xfff))                                                    // (11) 0.0359
/*16 */         tcg_out32(s, ARITH_OR | INSN_RD(ret) | INSN_RS1(TCG_REG_G0) |            // (0) 0.1103
/*18 */                   INSN_IMM13(arg));                                              // (7) 0.06667
/*20 */     else {                                                                       // (12) 0.01282
/*22 */         tcg_out32(s, SETHI | INSN_RD(ret) | ((arg & 0xfffffc00) >> 10));         // (3) 0.1
/*24 */         if (arg & 0x3ff)                                                         // (9) 0.04103
/*26 */             tcg_out32(s, ARITH_OR | INSN_RD(ret) | INSN_RS1(ret) |               // (2) 0.1051
/*28 */                       INSN_IMM13(arg & 0x3ff));                                  // (4) 0.08974
/*30 */     }                                                                            // (13) 0.01026
/*32 */ }                                                                                // (16) 0.002564
